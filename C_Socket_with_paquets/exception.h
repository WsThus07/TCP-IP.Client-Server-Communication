//Gestion des erreurs

#ifndef EXCEPTION_H
#define EXCEPTION_H


void error(const char *msg)
{
   perror(msg);
   exit(0);
}

#endif // EXCEPTION_H

