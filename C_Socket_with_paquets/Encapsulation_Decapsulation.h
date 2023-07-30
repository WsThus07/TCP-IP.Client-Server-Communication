#ifndef FILE_H
#define FILE_H

#include "exception.h"



//Function of decapsulation 
void decapsulation(int newsockfd,char paquet[]){
    int i,j,n;
    char delimiter[17],MACsourceAdress[17],MACdestAdress[17],data[17],crc[4];
    char IPsource[9],IPdest[9];
    char header[17*4];
     header[0] = '\0';
    char generator[]="1011";
    
    printf("---------------------------------\n");
    for (int i = 0; i < 8; i++) {
           IPsource[i] = paquet[i];
    }
    IPsource[16] = '\0'; // Add null terminator at the end of the string
    printf("IPsource : %s\n", IPsource);
    
    printf("---------------------------------\n");
    for (int i = 0; i < 8; i++) {
           IPdest[i] = paquet[8+i];
    }
    IPdest[16] = '\0'; // Add null terminator at the end of the string
    printf("IPdest : %s\n", IPdest);
    
    printf("---------------------------------\n");
    
    for (int i = 0; i < 16; i++) {
           delimiter[i] = paquet[16+i];
    }
    delimiter[16] = '\0'; // Add null terminator at the end of the string
    printf("Delimiter : %s\n", delimiter);
    printf("---------------------------------\n");
    
    for (int j = 0; j < 16; j++) {
    MACsourceAdress[j] = paquet[32+j];
    }
    MACsourceAdress[16] = '\0';
    printf("MACsourceAdress = %s\n", MACsourceAdress);
    printf("---------------------------------\n");

    for (int j = 0; j < 16; j++) {
    MACdestAdress[j] = paquet[48+j];
    }
    MACdestAdress[16] = '\0';
    printf("MACdestAdress = %s\n", MACdestAdress);
    printf("---------------------------------\n"); 
    
    strcat(header,delimiter);
    strcat(header,MACsourceAdress);
    strcat(header,MACdestAdress);
    header[16*3] = '\0';
    printf("header = %s\n", header);
    printf("---------------------------------\n");

    for (int j = 0; j < 16; j++) {
    data[j] = paquet[64+j];
    }
    data[16] = '\0';
    printf("data = %s\n", data);
    printf("---------------------------------\n");

    for (int j = 0; j < 3; j++) {
    crc[j] = paquet[80+j];
    }
    crc[3] = '\0';
    printf("crc = %s\n", crc);
    printf("---------------------------------\n");
    
    char DataPlusCrc[19];
    DataPlusCrc[0] = '\0';
    strcat(DataPlusCrc,data);
    strcat(DataPlusCrc,crc);
    
   
    char* verifybits = CRC_Verify_3bits(DataPlusCrc,generator);
    printf("CRC_Verifybits : %s\n", verifybits);
   
    int gsize = strlen(generator);
    int er=Error404(verifybits,gsize);
    char* receive;
    if(er==1){
      receive="Error received..\n";
    }else{
      receive="Message received correctly..\n"; 
    }
    printf("%s\n",receive);
    printf("---------------------------------\n");
    n=write(newsockfd,receive,strlen(receive));
    if(n<0){
      error("Error on Reading");
    } 
   
}

//Function of encapsulation
void encapsulation(int sockfd,char Data[],char trame[],char packet[],char IPsource[],char IPdest[],char generator[]){
    int n;
    char buffer[97];
    buffer[0] = '\0';
    char Delimiteur[17] = "0000000000000000";
    char Adresse_Source[17]="1010101010101010";
    char Adresse_Destinateur[17]="1111111111111111";
    trame[0] = '\0';
    packet[0] = '\0';
    strcat(trame, Delimiteur);
    strcat(trame, Adresse_Source);
    strcat(trame, Adresse_Destinateur);
    strcat(trame, Data); 
    char* remainder = CRC(Data,generator);
    printf("Remainder: %s\n", remainder);
    strcat(trame, remainder);
    strcat(packet,IPsource);
    strcat(packet,IPdest);
    strcat(packet,trame);
    
    strcat(buffer,packet);
   
    printf("---------------------------------\n");
    printf("Packet (@Ip_Source + @Ip_destination +donnéees( trames : Delimiteur + @mac_Source + @mac_Destination + Data +crc) ) : %s\n", buffer);
    n=write(sockfd,buffer,97);
    if(n<0) 
       error("ERROR reading from socket"); 
}


#endif // FILE_H
