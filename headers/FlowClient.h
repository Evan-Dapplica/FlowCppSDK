#pragma once
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "flowprotobuf.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using namespace flow::access;

//_ProposalKey and _Signature are using in SendTransaction to reduce the number of parameters
struct _ProposalKey
{
    const char *address;
    uint32_t key_id;
    uint64_t sequence_number;
};
struct _Signature
{
    const char *address;
    uint32_t key_id;
    const char *signature;
};

class FlowClient
{
    public:

        FlowClient(std::shared_ptr<Channel> channel) : stub_(AccessAPI::NewStub(channel)) {}

        void Ping() const
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

        // -------------------------------------------- EXECUTING SCRIPTS -------------------------------------------------

        // Execute script at latest block
        const Status ExecuteScriptAtLatestBlock(const char* script, std::vector<const char*> arguments, ExecuteScriptResponse& reply)const
        {
            ExecuteScriptAtLatestBlockRequest request;
            request.set_script(script);
            for (uint64_t i = 0; i < arguments.size(); ++i)
                request.add_arguments(arguments[i]);
            ClientContext context;

            Status status = stub_->ExecuteScriptAtLatestBlock(&context, request, &reply);
            return status;
        }

        // Execute script at latest selected block by id
        const Status ExecuteScriptAtBlockID(const char* block_id, const char* script, std::vector<const char*> arguments, ExecuteScriptResponse& reply)const
        {
            ExecuteScriptAtBlockIDRequest request;
            request.set_block_id(block_id);
            request.set_script(script);
            for (uint64_t i = 0; i < arguments.size(); ++i)
                request.add_arguments(arguments[i]);
            ClientContext context;

            Status status = stub_->ExecuteScriptAtBlockID(&context, request, &reply);
            return status;
        }

        // Execute script at latest selected block by height
        const Status ExecuteScriptAtBlockHeight (const uint64_t &block_height, const char* script, std::vector<const char*> arguments, ExecuteScriptResponse& reply)const
        {
            ExecuteScriptAtBlockHeightRequest request;
            request.set_script(script);
            request.set_block_height(block_height);
            for (uint64_t i = 0; i < arguments.size(); ++i)
                request.add_arguments(arguments[i]);
            ClientContext context;

            Status status = stub_->ExecuteScriptAtBlockHeight(&context, request, &reply);
            return status;
        }

        // ----------------------------------------------------------------------------------------------------------------

        // --------------------------------------------  GET REQUESTS  ----------------------------------------------------

        // Get latest header block
        const Status GetLatestBlockHeader(const  bool &is_sealed, BlockHeaderResponse& reply) const
        {
            GetLatestBlockHeaderRequest request;
            request.set_is_sealed(is_sealed);
            ClientContext context;

            Status status = stub_->GetLatestBlockHeader(&context, request, &reply);
            return status;
        }

        // Get latest header block by id
        const Status GetBlockHeaderByID(const char* id, BlockHeaderResponse& reply) const
        {
            GetBlockHeaderByIDRequest request;
            request.set_id(id);
            ClientContext context;

            Status status = stub_->GetBlockHeaderByID(&context, request, &reply);
            return status;
        }

        // Get latest header block by height
        const Status GetBlockHeaderByHeight(const uint64_t &height, BlockHeaderResponse& reply)const
        {
            GetBlockHeaderByHeightRequest request;
            request.set_height(height);
            ClientContext context;

            Status status = stub_->GetBlockHeaderByHeight(&context, request, &reply);
            return status;
        }

        // Get latest block
        const Status GetLatestBlock(const bool &is_seald, BlockResponse& reply)const
        {
            GetLatestBlockRequest request;
            request.set_is_sealed(is_seald);
            ClientContext context;

            Status status = stub_->GetLatestBlock(&context, request, &reply);
            return status;
        }

        // Get latest block by id
        const Status GetBlockByID(const char* id, BlockResponse& reply)const
        {
            GetBlockByIDRequest request;
            request.set_id(id);
            ClientContext context;

            Status status = stub_->GetBlockByID(&context, request, &reply);
            return status;
        }

        // Get latest block by height
        const Status GetBlockByHeight(const uint64_t &height, BlockResponse& reply)const
        {
            GetBlockByHeightRequest request;
            request.set_height(height);
            ClientContext context;

            Status status = stub_->GetBlockByHeight(&context, request, &reply);
            return status;
        }

        // Get collection by id
        const Status GetCollectionByID(const char* id, CollectionResponse& reply)const
        {
            GetCollectionByIDRequest request;
            request.set_id(id);
            ClientContext context;

            Status status = stub_->GetCollectionByID(&context, request, &reply);
            return status;
        }

        // Get transaction by id
        const Status GetTransaction(const char* id, TransactionResponse& reply)const
        {
            GetTransactionRequest request;
            request.set_id(id);
            ClientContext context;

            Status status = stub_->GetTransaction(&context, request, &reply);
            return status;
        }

        // Get transaction result in selected block id by transaction id
        const Status GetTransactionResult(const char* block_id,const char* transaction_id, GetTransactionResultResponse& reply)const
        {
            GetTransactionResultRequest request;
            request.set_block_id(block_id);
            request.set_transaction_id(transaction_id);
            ClientContext context;

            Status status = stub_->GetTransactionResult(&context, request, &reply);
            return status;
        }

        // Get account by address
        const Status GetAccount(const char* address, GetAccountResponse& reply)const
        {
            GetAccountRequest request;
            request.set_address(address);
            ClientContext context;

            Status status = stub_->GetAccount(&context, request, &reply);
            return status;
        }

        // Get account at latest block by address
        const Status GetAccountAtLatestBlock(const char* address, AccountResponse& reply)const
        {
            GetAccountAtLatestBlockRequest request;
            request.set_address(address);
            ClientContext context;

            Status status = stub_->GetAccountAtLatestBlock(&context, request, &reply);
            return status;
        }

        // Get account at block height by address
        const Status GetAccountAtBlockHeight(const char* address, const uint64_t &block_height, AccountResponse& reply)const
        {
            GetAccountAtBlockHeightRequest request;
            request.set_address(address);
            request.set_block_height(block_height);
            ClientContext context;

            Status status = stub_->GetAccountAtBlockHeight(&context, request, &reply);
            return status;
        }

        // Get events for height range by type
        const Status GetEventsForHeightRange(const std::string &type, const uint64_t &start_height, const uint64_t &end_height, EventsResponse& reply)const
        {
            GetEventsForHeightRangeRequest request;
            request.set_type(type);
            request.set_start_height(start_height);
            request.set_end_height(end_height);
            ClientContext context;

            Status status = stub_->GetEventsForHeightRange(&context, request, &reply);
            return status;
        }

        // Get events for selected block ids by type
        const Status GetEventsForBlockIDs(const std::string &type, const std::vector<const char*> &block_ids, GetEventsForBlockIDsResponse& reply)const
        {
            std::vector<uint64_t> by;
            GetEventsForBlockIDsRequest request;
            request.set_type(type);
            for (uint64_t i = 0; i < block_ids.size(); ++i)
                request.add_block_ids(block_ids[i]);
            ClientContext context;

            Status status = stub_->GetEventsForBlockIDs(&context, request, &reply);
            return status;
        }

        // Get network parameters
        const Status GetNetworkParameters()const
        {
            GetNetworkParametersRequest request;
            GetNetworkParametersResponse reply;
            ClientContext context;

            Status status = stub_->GetNetworkParameters(&context, request, &reply);
            return status;
        }
       
        // -----------------------------------------------------------------------------------------------------------------
    
        //  ------------------------------------------- SENDING TRANSACTION -----------------------------------------------

        const Status SendTransaction(  const char* script,
                                                        const std::vector<const char*> arguments,
                                                        const char* reference_block_id,
                                                        const uint64_t &gas_limit,
                                                        const _ProposalKey &proposalkey,
                                                        const char* payer,
                                                        const std::vector<const char*> authorizers,
                                                        const std::vector<const _ProposalKey&> &payload_signatures,
                                                        const std::vector<const _ProposalKey&> &envelope_signatures,
                                                        SendTransactionResponse& reply
                                                     )  const
        {
            SendTransactionRequest request;
            Transaction txrequest;
            
            // setting transaction elements
            txrequest.set_script(script);
            for (uint64_t i = 0; i < arguments.size(); ++i)
                txrequest.add_arguments(arguments[i]);
            txrequest.set_reference_block_id(reference_block_id);
            txrequest.set_gas_limit(gas_limit);
            txrequest.set_payer(payer);
            for (uint64_t i = 0; i < arguments.size(); ++i)
                txrequest.add_authorizers(authorizers[i]);
            

            // setting message ProposalKey
            Transaction::ProposalKey pkeyrequest;
            pkeyrequest.set_address(proposalkey.address);
            pkeyrequest.set_key_id(proposalkey.key_id);
            pkeyrequest.set_sequence_number(proposalkey.sequence_number);
            txrequest.set_allocated_proposal_key(&pkeyrequest);

            // setting hashed signatures  IMPORTANT!!!!
            // payload_signatures
            // envelope_signatures

            request.set_allocated_transaction(&txrequest);
            ClientContext context;

            Status status = stub_->SendTransaction(&context, request, &reply);
            return status;
        }

        // ----------------------------------------------------------------------------------------------------------------


    private : 

        std::unique_ptr<AccessAPI::Stub> stub_;
 };
