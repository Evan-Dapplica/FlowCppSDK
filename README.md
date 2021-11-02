# Welcome to the C++ SDK!

We're glad to have you here.
There are a few important items that we should cover real quick before you dive in.

## Signing Algorithms

- Only `ECDSA_P256` is supported at this time

## Hashing

- Only `SHA3_256` is supported at this time

## Security

- Remember that you will be dealing with private keys, which can be more powerful and dangerous than passwords. Please treat them as such.
- Consider reading [this whitepaper by Google](https://cloud.google.com/solutions/modern-password-security-for-system-designers.pdf).


### Currently the following Flow Access API methods have been implemented:

### Connection
- [x] Ping
- [x] GetNetworkParameters

### Accounts
- [x] GetAccountAtLatestBlock
- [x] GetAccountAtBlockHeight
- [x] GetAccount

### Blocks
- [x] GetLatestBlockHeader
- [x] GetBlockHeaderByID
- [x] GetBlockHeaderByHeight
- [x] GetLatestBlock
- [x] GetBlockByHeight
- [x] GetBlockByID

### Collections
- [x] GetCollectionByID

### Transactions
- [x] GetTransaction
- [x] GetTransactionResult

### Events
- [x] GetEventsForHeightRange
- [x] GetEventsForBlockIDs

### Scripts
- [x] ExecuteScriptAtLatestBlock
- [x] ExecuteScriptAtBlockHeight
- [x] ExecuteScriptAtBlockID


### Before using SDK, you have to install GRPC

Just follow the buildig [guide](https://grpc.io/docs/languages/cpp/quickstart/)


### How to build FlowCppSDK

- `$ cd FlowCppSDK` 
- `$ mkdir -p cmake/build`
- `$ cd cmake/build`
- `$ cmake ../..`
- `$ make`

#### Now you can start using SDK. Try ty run client & tests:
- `$ ./client`
- `$ ./tests`

#### Example of using
```c++std::string target_address("access.mainnet.nodes.onflow.org:9000");
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
```
