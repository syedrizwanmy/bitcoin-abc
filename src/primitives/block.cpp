// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <support/allocators/secure.h>
#include <primitives/block.h>
#include <hash.h>
#include <tinyformat.h>

BlockHash CBlockHeader::GetHash() const {
    return BlockHash(SerializeHash(*this));
}

std::string CBlock::ToString() const {
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, "
                   "hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, "
                   "vtx=%u)\n",
                   GetHash().ToString(), nVersion, hashPrevBlock.ToString(),
                   hashMerkleRoot.ToString(), nTime, nBits, nNonce, vtx.size());
    for (const auto &tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}

void CBlock::SetTransaction(CTransactionRef ptx, int idx,
                            SecureString passphrase) {
    if (!passphrase.empty()) {
        CTransaction tx = *ptx;
        tx.SecureTransaction(passphrase);
    }
    vtx[idx] = ptx;
}

void CBlock::AddTransaction(CTransactionRef ptx,
                            SecureString passphrase) {
    if (!passphrase.empty()) {
        CTransaction tx = *ptx;
        tx.SecureTransaction(passphrase);
    }
    vtx.push_back(ptx);
}
