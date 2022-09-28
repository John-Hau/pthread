openssl x509 -in SMB_FW_SIGNING_ECDSA.crt -pubkey  -noout | openssl pkey -pubin -outform der | openssl dgst -sha256 -binary > phash.bin
