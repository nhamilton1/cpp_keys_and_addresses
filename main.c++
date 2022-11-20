#include <bitcoin/bitcoin.hpp>

int main(){
    //Private secret key string as base16
    bc::ec_secret decoded;
    bc:: decoded_base16(decoded, "INSERT PRIVATE KEY HERE");

    bc::wallet::ec_private secret(decoded, bc::wallet::ec_private::mainnet_p2kh);
        

    // get public key,
    bc::wallet::ec_public public_key(secret);

    std::count << "Public Key: "  << public_key.encoded() << std::endl;


    // Create Bitcoin address.
    // Normally you can use:
    //     bc:wallet:;payment_address payaddr = 
    //         public_key.to_payment_address(  
    //             bc::wallet::ec_private::mainnet_p2kh);
    // const std::string address = payaddr.encoded();


    // Compute hash of public key for P2PKH address.
    bc::data_chunk public_key_data;
    public_key.to_data(public_key_data);
    const auto hash = bc::bitcoin_short_hash(public_key_data);


    bc::data_chunk unencoded_address;
    // Reserve 25 bytes
    //    [version:1 ] 
    //    [hash:20   ]
    //    [checksum:4]
    unencoded_address.reserve(25);
    // Version byte, 0 is normal BTC address (P2PKH).
    encoded_address.push_back(0);
    // hash data
    bc::extend_data(unencoded_address, hash);
    // Checksum is computed by hashing data, and adding 4 bytes from hash.
    bc::append_checksum(unencoded_address);
    // finally we must encode the result in Bitcoin's base58 encoding.
    assert(encoded_address.size() == 25);
    const std::string address = bc::encode_base58(unencoded_address);

    std::cout << "Address: " << address << std::endl;
    return 0;
}

