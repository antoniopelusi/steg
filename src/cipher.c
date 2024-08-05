long encrypt(unsigned char *message, unsigned char *encrypted_message, unsigned char *key, long size_byte)
{
	long msg_len = 0;

    for (long i = 0; i < size_byte; i++)
    {
        encrypted_message[i] = message[i] ^ key[i];
        
        msg_len++;
        
        if (message[i] == '\0')
        {
        	break;
        }
    }
    
    return msg_len;
}

void decrypt(unsigned char *extracted_message, unsigned char *decrypted_message, unsigned char *key, long size_byte)
{
    for (long i = 0; i < size_byte; i++)
    {
        decrypted_message[i] = extracted_message[i] ^ key[i];
    }
}
