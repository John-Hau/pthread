#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sha256/sha256.h"
#include "tinyAES/aes.h"



/////////////////////////////////////////////////////////////////////

// Enable ECB, CTR and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DCTR=1 -DECB=1
#define CBC 1
#define CTR 1
#define ECB 1



static void phex(uint8_t* str);
static int test_encrypt_cbc(void);
static int test_decrypt_cbc(void);
static int test_encrypt_ctr(void);
static int test_decrypt_ctr(void);
static int test_encrypt_ecb(void);
static int test_decrypt_ecb(void);
static void test_encrypt_ecb_verbose(void);




//test_encrypt_cbc() 
//test_decrypt_cbc() 
//test_encrypt_ctr() 
//test_decrypt_ctr() 
//test_decrypt_ecb()
//test_encrypt_ecb();
//test_encrypt_ecb_verbose();



// prints string as hex
static void phex(uint8_t* str)
{

	//defined(AES128)
	uint8_t len = 16;

	unsigned char i;
	for (i = 0; i < len; ++i)
		printf("%.2x", str[i]);
	printf("\n");
}

static void test_encrypt_ecb_verbose(void)
{
	// Example of more verbose verification

	uint8_t i;

	// 128bit key
	uint8_t key[16] =        
	{ 

       	(uint8_t)0x2b, (uint8_t)0x7e, (uint8_t)0x15, (uint8_t)0x16, (uint8_t)0x28, (uint8_t)0xae, (uint8_t)0xd2, (uint8_t)0xa6, 
	(uint8_t)0xab, (uint8_t)0xf7, (uint8_t)0x15, (uint8_t)0x88, (uint8_t)0x09, (uint8_t)0xcf, (uint8_t)0x4f, (uint8_t)0x3c 

	};




	// 512bit text
	uint8_t plain_text[64] = 
	{

   	(uint8_t)0x6b, (uint8_t)0xc1, (uint8_t)0xbe, (uint8_t)0xe2, (uint8_t)0x2e, (uint8_t)0x40, (uint8_t)0x9f, (uint8_t)0x96,
	(uint8_t)0xe9, (uint8_t)0x3d, (uint8_t)0x7e, (uint8_t)0x11, (uint8_t)0x73, (uint8_t)0x93, (uint8_t)0x17, (uint8_t)0x2a,
	(uint8_t)0xae, (uint8_t)0x2d, (uint8_t)0x8a, (uint8_t)0x57, (uint8_t)0x1e, (uint8_t)0x03, (uint8_t)0xac, (uint8_t)0x9c, 
	(uint8_t)0x9e, (uint8_t)0xb7, (uint8_t)0x6f, (uint8_t)0xac, (uint8_t)0x45, (uint8_t)0xaf, (uint8_t)0x8e, (uint8_t)0x51,
	(uint8_t)0x30, (uint8_t)0xc8, (uint8_t)0x1c, (uint8_t)0x46, (uint8_t)0xa3, (uint8_t)0x5c, (uint8_t)0xe4, (uint8_t)0x11, 
	(uint8_t)0xe5, (uint8_t)0xfb, (uint8_t)0xc1, (uint8_t)0x19, (uint8_t)0x1a, (uint8_t)0x0a, (uint8_t)0x52, (uint8_t)0xef,
	(uint8_t)0xf6, (uint8_t)0x9f, (uint8_t)0x24, (uint8_t)0x45, (uint8_t)0xdf, (uint8_t)0x4f, (uint8_t)0x9b, (uint8_t)0x17, 
	(uint8_t)0xad, (uint8_t)0x2b, (uint8_t)0x41, (uint8_t)0x7b, (uint8_t)0xe6, (uint8_t)0x6c, (uint8_t)0x37, (uint8_t)0x10 

	};

	// print text to encrypt, key and IV
	printf("ECB encrypt verbose:\n\n");
	printf("plain text:\n");
	for (i = (uint8_t) 0; i < (uint8_t) 4; ++i)
	{
		phex(plain_text + i * (uint8_t) 16);
	}
	printf("\n");

	printf("key:\n");
	phex(key);
	printf("\n");

	// print the resulting cipher as 4 x 16 byte strings
	printf("ciphertext:\n");

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);

	for (i = 0; i < 4; ++i)
	{
		AES_ECB_encrypt(&ctx, plain_text + (i * 16));
		phex(plain_text + (i * 16));
	}
	printf("\n");
}


static int test_encrypt_ecb(void)
{
//defined(AES128)
  uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
  uint8_t out[] = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };

  uint8_t in[]  = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
  struct AES_ctx ctx;

  AES_init_ctx(&ctx, key);
  AES_ECB_encrypt(&ctx, in);

  printf("ECB encrypt: ");

  if(0 == memcmp((char*) out, (char*) in, 16)) 
  {
	  printf("SUCCESS!\n");
	  return(0);
  }
  else 
  {
	  printf("FAILURE!\n");
	  return(1);
  }
}

static int test_decrypt_cbc(void)
{

	//defined(AES128)
  uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

  uint8_t in[]  = {
	        0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
		0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
		0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
		0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7 
                  };

  uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

  uint8_t out[] = 
  { 
	  0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
   	  0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
	  0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
	  0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 
  };

  //  uint8_t buffer[64];
  struct AES_ctx ctx;

  AES_init_ctx_iv(&ctx, key, iv);
  AES_CBC_decrypt_buffer(&ctx, in, 64);

  printf("CBC decrypt: ");

  if (0 == memcmp((char*) out, (char*) in, 64)) {
	  printf("SUCCESS!\n");
	  return(0);
  } else {
	  printf("FAILURE!\n");
	  return(1);
  }
}

static int test_encrypt_cbc(void)
{
	//defined(AES128)
   uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

   uint8_t out[] = {

	   0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
	   0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
	   0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
	   0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7 

                   };


   uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

   uint8_t in[]  = { 

	   0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
	   0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
	   0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
	   0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 
                   };

   struct AES_ctx ctx;

   AES_init_ctx_iv(&ctx, key, iv);
   AES_CBC_encrypt_buffer(&ctx, in, 64);

   printf("CBC encrypt: ");

   if(0 == memcmp((char*) out, (char*) in, 64)) 
   {
	   printf("SUCCESS!\n");
	   return(0);
   }
   else 
   {
	   printf("FAILURE!\n");
	   return(1);
   }
}

static int test_xcrypt_ctr(const char* xcrypt);
static int test_encrypt_ctr(void)
{
	return test_xcrypt_ctr("encrypt");
}

static int test_decrypt_ctr(void)
{
	return test_xcrypt_ctr("decrypt");
}

static int test_xcrypt_ctr(const char* xcrypt)
{
	//defined(AES128)
  uint8_t key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

  uint8_t in[64]  = { 

	  0x87, 0x4d, 0x61, 0x91, 0xb6, 0x20, 0xe3, 0x26, 0x1b, 0xef, 0x68, 0x64, 0x99, 0x0d, 0xb6, 0xce,
	  0x98, 0x06, 0xf6, 0x6b, 0x79, 0x70, 0xfd, 0xff, 0x86, 0x17, 0x18, 0x7b, 0xb9, 0xff, 0xfd, 0xff,
	  0x5a, 0xe4, 0xdf, 0x3e, 0xdb, 0xd5, 0xd3, 0x5e, 0x5b, 0x4f, 0x09, 0x02, 0x0d, 0xb0, 0x3e, 0xab,
	  0x1e, 0x03, 0x1d, 0xda, 0x2f, 0xbe, 0x03, 0xd1, 0x79, 0x21, 0x70, 0xa0, 0xf3, 0x00, 0x9c, 0xee 
                   };



  uint8_t iv[16]  = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

  uint8_t out[64] = { 

	  0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
	  0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
	  0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
	  0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 

                    };

  struct AES_ctx ctx;

  AES_init_ctx_iv(&ctx, key, iv);
  AES_CTR_xcrypt_buffer(&ctx, in, 64);

  printf("CTR %s: ", xcrypt);

  if(0 == memcmp((char *) out, (char *) in, 64)) 
  {
	  printf("SUCCESS!\n");
	  return(0);
  }
  else 
  {
	  printf("FAILURE!\n");
	  return(1);
  }
}


static int test_decrypt_ecb(void)
{
	//defined(AES128)
  uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
  uint8_t in[]  = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };


  uint8_t out[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };

  struct AES_ctx ctx;

  AES_init_ctx(&ctx, key);
  AES_ECB_decrypt(&ctx, in);

  printf("ECB decrypt: ");

  if(0 == memcmp((char*) out, (char*) in, 16)) 
  {
	  printf("SUCCESS!\n");
	  return(0);
  }
  else
  {
	  printf("FAILURE!\n");
	  return(1);
  }
}




////////////////////////////////////////////////////////////////////













// "hello"
unsigned char hello_hashed[] = {
	0x2c, 0xf2, 0x4d, 0xba, 0x5f, 0xb0, 0xa3, 0x0e, 0x26, 0xe8, 0x3b, 0x2a,
	0xc5, 0xb9, 0xe2, 0x9e, 0x1b, 0x16, 0x1e, 0x5c, 0x1f, 0xa7, 0x42, 0x5e,
	0x73, 0x04, 0x33, 0x62, 0x93, 0x8b, 0x98, 0x24
};


// ""
unsigned char empty_hashed[] = {
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4, 0xc8,
	0x99, 0x6f, 0xb9, 0x24, 0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
	0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
};




char message[] =
"Be that word our sign of parting, bird or fiend! I shrieked upstarting"
"Get thee back into the tempest and the Nights Plutonian shore!"
"Leave no black plume as a token of that lie thy soul hath spoken!"
"Leave my loneliness unbroken! quit the bust above my door!"
"Take thy beak from out my heart, and take thy form from off my door!"
"Quoth the raven, Nevermore.  ";


/* Expected SHA-256 for the message. */
uint8_t sha256[] = {0x63, 0x76, 0xea, 0xcc, 0xc9, 0xa2, 0xc0, 0x43, 0xf4, 0xfb, 0x01,
	0x34, 0x69, 0xb3, 0x0c, 0xf5, 0x28, 0x63, 0x5c, 0xfa, 0xa5, 0x65,
	0x60, 0xef, 0x59, 0x7b, 0xd9, 0x1c, 0xac, 0xaa, 0x31, 0xf7};

uint8_t pubkey[] = 
{

	0x96,0x14,0xee,0x53,0x90,0xdb,0x1c,0xfb,
	0xbd,0xcd,0x09,0x10,0xa2,0x19,0x27,0xa9,
	0xa7,0x88,0x8a,0xd4,0xbe,0xd5,0x26,0x39,
	0xe9,0xe4,0xa3,0xe8,0x7f,0x8e,0xe0,0xe9,
	0x6c,0x64,0x53,0xdf,0xef,0xa4,0xfb,0xb7,
	0xf2,0xde,0xbc,0xfd,0x50,0xe0,0xc9,0xf4,
	0x1c,0xce,0xb3,0x1c,0x4b,0xc2,0x73,0xc3,
	0x44,0x16,0x91,0x7b,0xfb,0x8c,0xca,0x33

};



unsigned char buf[1024*8] = {0};
int sha256_test(void)
{
	sha256_t hash;
	sha256_init(&hash);
	sha256_update(&hash, (unsigned char*)pubkey, 64);
	sha256_final(&hash, buf);

	for(int i=0;i<32;i++)
	{
		printf("%02x ",buf[i]);
		if(i)
		{
			if((i+1)%16 == 0)
				printf("\n");
		}

	}

	printf("\n");

}


int main(void) 
{

	//test_encrypt_ecb();
        test_decrypt_ecb();


	return 0;

