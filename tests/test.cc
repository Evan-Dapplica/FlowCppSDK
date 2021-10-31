#include "../headers/FlowClient.h"

#define BOOST_TEST_MODULE client_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(client_test) 
{
    std::string target_address("access.mainnet.nodes.onflow.org:9000");
    FlowClient client(grpc::CreateChannel(target_address,grpc::InsecureChannelCredentials()));
    BlockResponse block_testing;
    BlockHeaderResponse blockheader_testing;
    GetTransactionResultResponse txresult_testing;
    GetAccountResponse getaccount_testing;
    AccountResponse account_testing;
    BlockResponse bb;
    GetEventsForBlockIDsResponse geteventsforids_testing;
    EventsResponse events_testing;
    ExecuteScriptResponse executescript_testing;

    BOOST_CHECK_MESSAGE((client.GetLatestBlock(true, bb)).ok(),
                        "Error: GetLatestBlock");

    BlockHeaderResponse bh;
    BOOST_CHECK_MESSAGE((client.GetLatestBlockHeader(true, bh)).ok(),
                        "Error: GetLatestBlockHeader");

    BOOST_CHECK_MESSAGE((client.GetBlockHeaderByID(bh.block().id().c_str(), blockheader_testing)).ok(),
                        "Error: GetBlockHeaderByID");

    BOOST_CHECK_MESSAGE(client.GetBlockHeaderByHeight(bh.block().height(), blockheader_testing).ok(),
                        "Error GetBlockHeaderByHeight");

    BOOST_CHECK_MESSAGE(client.GetBlockByHeight(bb.block().height(), block_testing).ok(),
        "Error GetBlockByHeight");

    BOOST_CHECK_MESSAGE(client.GetBlockByID(bb.block().id().c_str(),block_testing).ok(),
        "Error GetBlockByID");

    CollectionResponse coll;
    BOOST_CHECK_MESSAGE(client.GetCollectionByID(bb.block().collection_guarantees()[1].collection_id().c_str(),coll).ok(),
        "Error GetCollectionByID");

    TransactionResponse tx;
    BOOST_CHECK_MESSAGE(client.GetTransaction(coll.collection().transaction_ids()[0].c_str(),tx).ok(), 
        "Error GetTransaction");

    BOOST_CHECK_MESSAGE(client.GetTransactionResult(bb.block().id().c_str(), coll.collection().transaction_ids()[0].c_str(), txresult_testing).ok(), 
        "Error GetTransactionResult");

    BOOST_CHECK_MESSAGE(client.GetAccount(tx.transaction().payer().c_str(), getaccount_testing).ok(),
        "Error GetAccount");

    BOOST_CHECK_MESSAGE(client.GetAccountAtLatestBlock(tx.transaction().payer().c_str(), account_testing).ok(), 
        "Error GetAccountAtLatestBlock");

    BOOST_CHECK_MESSAGE(client.GetAccountAtBlockHeight(tx.transaction().payer().c_str(), bb.block().height(), account_testing).ok(), 
        "Error GetAccountAtBlockHeight");

    BOOST_CHECK_MESSAGE(client.GetEventsForBlockIDs("A.0b2a3299cc857e29.TopShot.Deposit", {bb.block().id().c_str()},geteventsforids_testing).ok(), 
        "Error GetEventsForBlockIDs");

    BOOST_CHECK_MESSAGE(client.GetEventsForHeightRange("A.0b2a3299cc857e29.TopShot.Deposit", 19198966, 19198968,events_testing).ok(), 
        "Error GetEventsForHeightRange");

    BOOST_CHECK_MESSAGE(client.ExecuteScriptAtLatestBlock("pub fun main(): Int {return 1 + 2}", {},executescript_testing).ok(),
        "Error ExecuteScriptAtLatestBlock");
}
