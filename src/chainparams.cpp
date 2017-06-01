// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

unsigned int pnSeed[] =
{
};

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xac;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0x71;
        vAlertPubKey = ParseHex("0446cee2ce910e55f522e23fbcca47d63e13f6c9db1b9b20e8da27e41018d439390010f685b18a4a00fa0d56bc953032a487e5c061049fe0afd881f8deb95dac97");
        nDefaultPort = 6753;
        nRPCPort = 6743;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);


        const char* pszTimestamp = "2017 PirateBlocks!!!!!";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
		CTransaction txNew(1, 1496250225, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1496250225;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 111942;

		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000ab234f5eb1e0fd10ede39a80018bb1a66feb587fd80f790be348306481d9"));
       

		vSeeds.push_back(CDNSSeedData("pblocks.servep2p.com", "pblocks.servep2p.com"));



        base58Prefixes[PUBKEY_ADDRESS] = list_of(55);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(32);
        base58Prefixes[SECRET_KEY] =     list_of(145);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x73)(0xAE)(0xE7);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x73)(0xD2)(0x5E);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 26;
		
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcc;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0xff;
        pchMessageStart[3] = 0xee;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("046c5ac99d7e5ee661d8ec7b5de1dae0893a4378b010544a51fd807523572332c03a1af436a72f984e7ab575048f3035f70e1c90382acf746d9e21098d8d29f787");
        nDefaultPort = 27991;
        nRPCPort = 27992;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 111942;
		
		
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000ab234f5eb1e0fd10ede39a80018bb1a66feb587fd80f790be348306481d9"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(110);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x17)(0xFF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x43)(0x99);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
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
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0x55;
        pchMessageStart[3] = 0xdd;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1412222222;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 37992;
        strDataDir = "regtestnet";

        assert(hashGenesisBlock == uint256("0x5fcf85de516b168e20833f15bbd461aabc655698d49a9f3516b3e27f55845d3d"));

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
