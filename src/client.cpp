#include <iostream>
#include <string>
#include <limits>

#include <grpc++/grpc++.h>
#include "emailverifier.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using emailverifier::EmailVerifier;
using emailverifier::EmailRequest;
using emailverifier::EmailReply;

class EmailVerifierClient {
public:
    EmailVerifierClient(std::shared_ptr<Channel> channel)
        : stub_(EmailVerifier::NewStub(channel)) {}

    EmailReply CheckEmail(const std::string& email) {
        EmailRequest request;
        request.set_email(email);

        EmailReply reply;
        ClientContext context;

        Status status = stub_->CheckEmail(&context, request, &reply);

        if (!status.ok()) {
            std::cerr << "RPC failed: " << status.error_message()
                      << " (code: " << status.error_code() << ")" << std::endl;
        }

        return reply;
    }

private:
    std::unique_ptr<EmailVerifier::Stub> stub_;
};

int main() {
    EmailVerifierClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    while (true) {
        std::string input_email;
        std::cout << "\nEnter email to verify: ";
        std::getline(std::cin, input_email);

        EmailReply result = client.CheckEmail(input_email);

        std::cout << "Result:\n"
                  << " - Valid: " << (result.is_valid() ? "Yes" : "No") << "\n"
                  << " - Domain: " << result.domain() << "\n"
                  << " - Common Provider: " << (result.is_common_domain() ? "Yes" : "No") << std::endl;

        std::cout << "\nPress Enter to test another email or Ctrl+C to exit...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
