#!/bin/bash


#openssl req -new -sha256 -key fixture.key -out fixture.csr -subj "/C=US/O=Honeywell International Inc./OU=HBT/CN=<Fixture Name>/"
openssl req -new -sha256 -key fixture.key -out SNAPON.csr -subj "/C=US/O=Honeywell International Inc./OU=HBT/CN=SNAPON/"
echo "done"
