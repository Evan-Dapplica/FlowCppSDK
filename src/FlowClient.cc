#include "../headers/FlowClient.h"

FlowClient::Ping()const
{
    PingRequest preq;
    PingResponse prep;
    ClientContext context;
    Status status = stub_->Ping(&context, preq, &prep);

    if(status.ok())
        std::cout << "Successfully" << std::endl;
    else
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
}