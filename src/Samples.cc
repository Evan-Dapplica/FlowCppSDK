#include "../headers/FlowClient.h"
void const RunClient() 
{
    std::string target_address("access.mainnet.nodes.onflow.org:9000");
    FlowClient client(grpc::CreateChannel(target_address,grpc::InsecureChannelCredentials()));

    BlockHeaderResponse bh;
    BlockResponse bb;

    if(!(client.GetBlockByHeight(19198966, bb).ok()))
    {
        std::cout << "Error reading block by height";
        return;
    }
    if(!(client.GetBlockHeaderByHeight(19198966, bh).ok()))
    {
        std::cout << "Error reading header block by height";
        return;
    }

    BlockHeaderResponse bh_by_id;
    if(!(client.GetBlockHeaderByID(bh.block().id().c_str(),bh_by_id).ok()))
    {
        std::cout << "Error reading header block by id";
        return;
    }

    BlockResponse bb_by_id;
    if(!(client.GetBlockByID(bb.block().id().c_str(),bb_by_id).ok()))
    {
        std::cout << "Error reading block by id";
        return;
    }

    CollectionResponse coll;
    if(!(client.GetCollectionByID(bb.block().collection_guarantees()[1].collection_id().c_str(),coll).ok()))
    {
        std::cout << "Error reading collection by id";
        return;
    }

    TransactionResponse tx;
    if(!client.GetTransaction(coll.collection().transaction_ids()[0].c_str(),tx).ok())
    {
        std::cout << "Error reading transaction response";
        return;
    }

    // now you can work with these variables as you wish

    
}

int main(int argc, char* argv[]) 
{
    RunClient();
    return 0;
}
