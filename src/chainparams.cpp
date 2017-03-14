// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 Fasbit Inc.
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>
#include <stdint.h>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x01020304, 
};

static const unsigned int timeMainGenesisBlock = 1387677831;
uint256 hashMainGenesisBlock("0x00000761d34428953a5de9b39e85404a15dec719f196d4385cb0fd79ab55d24e");
static CBigNum bnMainProofOfWorkLimit(~uint256(0) >> 20);

static const int64_t nGenesisBlockRewardCoin = .0001 * COIN;
static const int64_t nBlockRewardStartCoin = 100 * COIN;
static const int64_t nBlockRewardMinimumCoin = 100 * COIN;

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x05;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("0493e6dc310a0e444cfb20f3234a238f77699806d47909a42481010c5ce68ff04d3babc959cd037bd3aa6ded929f2b9b4aa2f626786cd7f8495e5bb61e9cfebbc4");
        nDefaultPort = 18491;
        nRPCPort = 18490;
        bnProofOfWorkLimit = bnMainProofOfWorkLimit;
        nSubsidyHalvingInterval = 60480;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
		const char* pszTimestamp = "'tis all about tha Benjamins.";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = nGenesisBlockRewardCoin;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 112;
        genesis.nTime    = timeMainGenesisBlock;
        genesis.nBits    = bnMainProofOfWorkLimit.GetCompact();
		genesis.nNonce   = 114695;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == hashMainGenesisBlock);
        assert(genesis.hashMerkleRoot == uint256("0x0d7647d5755faf897a2416ab51b65ad2f3608cd504610efe61abc464414db7b5"));

        vSeeds.push_back(CDNSSeedData("96.67.25.134", "96.67.25.134"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,6);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,186);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x01; //0x05;
        pchMessageStart[1] = 0x1A; //0xfe;
        pchMessageStart[2] = 0x39; //0xa5;
        pchMessageStart[3] = 0xF7; //0x03;
        vAlertPubKey = ParseHex("04218bc3f08237baa077cb1b0e5a81695fcf3f5b4e220b4ad274d05a31d762dd4e191efa7b736a24a32d6fd9ac1b5ebb2787c70e9dfad0016a8b32f7bd2520dbd5");
        nDefaultPort = 28491;
        nRPCPort = 18490;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1373481000;
        genesis.nNonce = 905523645;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x00000e5e37c42d6b67d0934399adfb0fa48b59138abb1a8842c88f4ca3d4ec96"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,119);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,199);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,247);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x9cc7038a62931521a044f22acd7d9cf3e6f1f35d4e877ffe106b39e946f8000e"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
