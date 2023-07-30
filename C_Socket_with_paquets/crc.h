

char* CRC(char dataword[], char generator[]) {

    int dsize0 = strlen(dataword);
    int gsize = strlen(generator);

    for (int i = 0; i < gsize-1; i++) {
        dataword[dsize0 + i] = '0';
    }
    
    int dsize = strlen(dataword);
   // printf("Dataword de size %d : %s\n",dsize,dataword);
    for (int i = 0; i < dsize - gsize + 1; i++) {
        if (dataword[i] == '1') {
            for (int j = 0; j < gsize; j++) {
                dataword[i+j] = dataword[i+j] == generator[j] ? '0' : '1';
            }
        }
    }

    return &dataword[dsize - gsize + 1];
}

char* CRC_Verify_Data(char dataword[], char remainder[],char generator[]) {
    int dsize0 = strlen(dataword);
    int gsize = strlen(generator);
    printf("dataword dsize0: %d\n",dsize0);

    for (int i = 0; i < gsize-1; i++){
        dataword[dsize0 + i] =  remainder[i];
    }

    int dsize = strlen(dataword);
    //printf("dataword CRC_VERIFY: %s\n",dataword);
    return dataword;
}

char* CRC_Verify_3bits(char dataword[],char generator[]) {
    int dsize = strlen(dataword);
    int gsize = strlen(generator);

    //printf("data+crc in crc.h: %s\n",dataword);
    
     for (int i = 0; i < dsize - gsize + 1; i++) {
        if (dataword[i] == '1') {
            for (int j = 0; j < gsize; j++) {
                dataword[i+j] = dataword[i+j] == generator[j] ? '0' : '1';
            }
        }
    }
    //printf("3bits : %s \n",&dataword[dsize - gsize + 1]);
    return &dataword[dsize - gsize + 1];
}

int Error404(char verified[],int gsize){
        if(strlen(verified) == gsize-1){
            for(int i=0; i<gsize;i++){
            if(verified[i]=='1') { 
		   
		    return 1;
		    }
            }
        }
         return 0;
}


