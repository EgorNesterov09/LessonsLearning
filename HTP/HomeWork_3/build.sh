rm -r src/*
rm -r build/*
mkdir src
mkdir build
asn1c rrc.asn1 -D src -no-gen-OER -no-gen-example
gcc -Isrc -o build/coder rrc_coder.c src/*.c -DPDU=RRCSetupRequest -DASN_DISABLE_OER_SUPPORT
gcc -Isrc -o build/decoder rrc_decoder.c src/*.c -DPDU=RRCSetupRequest -DASN_DISABLE_OER_SUPPORT
./build/coder ./build/rrc_ber_out
./build/decoder ./build/rrc_ber_out