#include "gtest/gtest.h"

static const char *const DB_FILE = "/tmp/testChatDB/";

// The fixture for testing class Foo.
class ChatDAOTest : public ::testing::Test {

protected:

    // You can do set-up work for each test here.
    ChatDAOTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~ChatDAOTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    DBConnector * connector;
};