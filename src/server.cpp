#include <iostream>
#include <string>
#include <set>

#include <grpc++/grpc++.h>
#include "emailverifier.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using emailverifier::EmailVerifier;
using emailverifier::EmailRequest;
using emailverifier::EmailReply;

class EmailVerifierServiceImpl final : public EmailVerifier::Service {
public:
    Status CheckEmail(ServerContext* context, const EmailRequest* request, EmailReply* reply) override {
        std::string email = request->email();

        // Cek apakah mengandung '@'
        auto at_pos = email.find('@');
        bool is_valid = (at_pos != std::string::npos) && (at_pos > 0) && (at_pos < email.size() - 1);
        reply->set_is_valid(is_valid);

        std::string domain = "";
        if (is_valid) {
            domain = email.substr(at_pos + 1);
        }
        reply->set_domain(domain);

        // Cek apakah domain umum
        static const std::set<std::string> common_domains = {
            "gmail.com", "yahoo.com", "outlook.com", "hotmail.com", "icloud.com"
        };
        reply->set_is_common_domain(common_domains.count(domain) > 0);

        std::cout << "[Request] Email: " << email
                  << " | Valid: " << is_valid
                  << " | Domain: " << domain << std::endl;

        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    EmailVerifierServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Email Verifier Server running at " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
