# Welcome to the Flow C++ SDK!

We're glad to have you here.
There are a few important items that we should cover real quick before you dive in.

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
```cpp
BlockResponse bb = client.GetBlockByHeight(19198966);
client.GetBlockHeaderByID(bh.block().id().c_str());
client.GetBlockByID(bb.block().id().c_str());
CollectionResponse coll = client.GetCollectionByID(bb.block().collection_guarantees()[1].collection_id().c_str());
TransactionResponse tx = client.GetTransaction(coll.collection().transaction_ids()[0].c_str());
```

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Code of Conduct

Everyone interacting in the FlowClient project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/[USERNAME]/flow_client/blob/master/CODE_OF_CONDUCT.md).
