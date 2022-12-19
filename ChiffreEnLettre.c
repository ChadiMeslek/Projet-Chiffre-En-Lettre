#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define _OPEN_SYS_ITOA_EXT
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

char * SaisirChaineClavier()
{
     unsigned int c, nbc = 0 ;
     char * ch = NULL ;

     while((c = getchar()) != '\n')
     {
        ch = realloc(ch, (nbc+1)*sizeof(char));
        ch[nbc++] = c ;
     }
     ch = realloc(ch, (nbc+1)*sizeof(char));
     ch[nbc] = '\0' ;

     return ch ;
}

// Fonction Ã  adapter
char * SaisirLigneFichier(FILE * pf)
{
    unsigned int c, nbc = 0 ;
    char * ch = NULL ;

    while(((c = fgetc(pf)) != '\n') && (c != EOF))
    {
        ch = realloc(ch, (nbc+1)*sizeof(char));
        ch[nbc++] = c ;
    }
    if((nbc > 0) || (c == '\n'))
    {
        ch = realloc(ch, (nbc+1)*sizeof(char));
        ch[nbc] = '\0' ;
        return ch ;
    }

    return NULL ;
}


char ** CreerVecteurNombres(char *nf , unsigned int * taille)
{
    FILE * pf = fopen(nf, "r") ;
    char * str = NULL ;
    unsigned int i = 0 ;
    char ** VN = NULL ;

    if(pf == NULL)
    {
        printf("\n probleme lors de l ouverture du fichier %s\n", nf) ;
        fclose(pf) ;
        *taille = 0 ;
        return NULL ;
    }

    while((str = SaisirLigneFichier(pf)) != NULL)
    {
        VN = realloc(VN, (i+1)*sizeof(char*)) ;
        VN[i++] = str ;
    }

    fclose(pf) ;
    *taille = i ;
    return VN ;
}

void ChiffreEnLettre(char * num)
{
    //explication de mon algo
    double centaine, dizaine, unite, reste, y,i,chiffre;
    char output[50];
    unsigned int icentaine,idizaine,iunite,inty,nbc,DizPlusUni;
    
    char ** TC = CreerVecteurNombres("CL_FR0.txt" , &nbc) ;
    setlocale(LC_CTYPE,"") ;
    
	chiffre=atof(num); //la convertion du numero ; par exemple notre chiffre est 12345
    
    char lettre[256];    
    strcpy(lettre, "");   //lettre=""
    reste = chiffre; 
    for(i=1000000000000; i>=1; i=i/1000)
    {
        y = reste/i; // 12345/1000000000000 = 0  ; 12345/1000000000 = 0 ; 12345/1000000 =0 ; 12345/1000 =12,345
        inty=y;//=12
        if(inty!=0)//=12
        {
            centaine = inty/100;//=0
            icentaine=centaine;//=0
            dizaine  = (inty - icentaine*100)/10;//=1,2
            idizaine = dizaine;//=1
            unite = inty-(icentaine*100)-(idizaine*10);//=2
            iunite= unite;//=2
            DizPlusUni=(idizaine*10)+iunite;//=12
            //centaine
            switch(icentaine)//=0
                {
        	     case 0:
                  break;
                 case 1:
                  strcat(lettre,"cent");
                  strcat(lettre," ");
                  break;
                 default:
	                  if((idizaine == 0)&&(iunite == 0)) 
						{
							strcat(lettre,TC[icentaine]);
							strcat(lettre," ");
							strcat(lettre,"cents");	
							strcat(lettre," ");
						}
	                  else 
						{
							strcat(lettre,TC[icentaine]);
							strcat(lettre," ");
							strcat(lettre,"cent");
							strcat(lettre," ");	
						}
                	break;                    
                }
            switch(DizPlusUni)//=12
                {
	            	case 0:
	            		break;
	            	default:
	            		{
	              			if(i==1000 && DizPlusUni == 1)//!=1
	              				{
	              					strcat(lettre,"");
	  							}
						    else
							    {
			            			strcat(lettre,TC[DizPlusUni]);//lettre="douze"
			            			strcat(lettre," ");//lettre="douze "
	          					}
	            		}
			    }
                 
             	snprintf(output, 50, "%f", i);//conversion le double en string on a i=1000.000000
                if(strcmp(output,"1000000000000.000000")==0)
                {
                    if(y>1) 
                    {strcat(lettre,"billions ");
                    }
                    else {strcat(lettre,"billion ");}
                }
                else if(strcmp(output,"1000000000.000000")==0)
                {
                    if(y>1) {strcat(lettre,"milliards ");}
                    else {strcat(lettre,"milliard ");}
                }
                else if(strcmp(output,"1000000.000000")==0)
                {
                    if(y>1) {strcat(lettre,"millions ");}
                    else {strcat(lettre,"million ");}
                }
                else if(strcmp(output,"1000.000000")==0)
                {
					strcat(lettre,"mille ");
				}//lettre="douze mille "             
        } 
        reste -= inty*i;//reste=12345-12000=345 et recommencons le même algo
    } // end for
    if(strlen(lettre)==0) // si aprés la boucle lettre="" donc le numero est zéro
	{
		strcpy(lettre,TC[0]);   
		strcat(lettre," ");
	}
    printf("%s",lettre);//lettre="douze mille trois cent quarante-cinq "
}

void ChiffreEnLettre2(char * num)
{
    //même algo mais on a fait deux chose:
    double centaine, dizaine, unite, reste, y,i,chiffre;
    char output[50];
    unsigned int icentaine,idizaine,iunite,inty,nbc,DizPlusUni,length,NbrZero=0,l;
    
    char ** TC = CreerVecteurNombres("CL_FR0.txt" , &nbc) ;
    setlocale(LC_CTYPE,"") ;
    
    //le cas de 1,00001 les zéros et on a supprimer le numéro zéro car par exemple 50,00 on dit ciquante 
    while(num[NbrZero]=='0')
      {
      	NbrZero++;
  	  }
    for(l=1;l<=NbrZero;l++)
      {
      	printf("zéro ");
  	  }
	  chiffre=atof(num);
    
    char lettre[256];    
    strcpy(lettre, "");   
    reste = chiffre;
    for(i=1000000000000; i>=1; i=i/1000)
    {
        y = reste/i;
        inty=y;
        if(inty!=0)
        {
            centaine = inty/100;
            icentaine=centaine;
            dizaine  = (inty - icentaine*100)/10;
            idizaine = dizaine;
            unite = inty-(icentaine*100)-(idizaine*10);
            iunite= unite;
            DizPlusUni=(idizaine*10)+iunite;
            //centaine
            switch(icentaine)
            {
            	case 0:
                    break;
                case 1:
                    strcat(lettre,"cent");
                    strcat(lettre," ");
                    break;
                default:
                    if((idizaine == 0)&&(iunite == 0)) 
					{
						strcat(lettre,TC[icentaine]);
						strcat(lettre," ");
						strcat(lettre,"cents");	
						strcat(lettre," ");
					}
                    else 
					{
						strcat(lettre,TC[icentaine]);
						strcat(lettre," ");
						strcat(lettre,"cent");
						strcat(lettre," ");	
					}
                    break;                    
            }
            switch(DizPlusUni)
            {
            	case 0:
            		break;
            	default:
            		{
            			if(i==1000 && DizPlusUni == 1)
            				{
            					strcat(lettre,"");
							}
						else
							{
		            			strcat(lettre,TC[DizPlusUni]);
		            			strcat(lettre," ");
            				}
					}
			}
			
			
             	snprintf(output, 50, "%f", i);
             	
             	
                if(strcmp(output,"1000000000000.000000")==0)
                {
                    if(y>1) 
                    {strcat(lettre,"billions ");
                    }
                    else {strcat(lettre,"billion ");}
                }
                else if(strcmp(output,"1000000000.000000")==0)
                {
                    if(y>1) {strcat(lettre,"milliards ");}
                    else {strcat(lettre,"milliard ");}
                }
                else if(strcmp(output,"1000000.000000")==0)
                {
                    if(y>1) {strcat(lettre,"millions ");}
                    else {strcat(lettre,"million ");}
                }
                else if(strcmp(output,"1000.000000")==0)
                    {strcat(lettre,"mille ");}             
        } 
        reste -= inty*i;
    } // end for    
    printf("%s",lettre);
}

void Menu(char * num)
  {
  	int d=ExistVirg(num);
  	if(d==1)//si d=1 la virgule n'existe pas
    	{
    		ChiffreEnLettre(num);
    	}
  	else if(d==0)//si d=0 la virgule existe
    	{
    		char leftHalf[256], rightHalf[256];//on fait le split
    		double a;
    		int len,virg,k,i;
    		len=strlen(num);
    		for(virg = 0;virg<len; virg++) 
        		{
        			if( num[virg] == ',')
          			{
          				break;
          			}
        		}
    		for(i = 0; i < virg; i++) 
        		{
        	        leftHalf[i]= num[i];
        	  }
    	    	leftHalf[i] = '\0';
    	  for(i = virg+1, k = 0; i <= len; i++, k++) 
        		{
        	 		rightHalf[k]= num[i];
        		}
    		a=atof(rightHalf);
    		ChiffreEnLettre(leftHalf);
    		if(a!=0)
      		{
      		printf("virgule ");
      		ChiffreEnLettre2(rightHalf);
      		}
    		else
      		{
      			printf("");
      		}
    	}
  	else if (d==(-1))//si d=(-1) il y'a autre caractere ou double virgule 
  	{
  		printf("\nvote nombre est invalide!\n");
  	}
  }

int ExistVirg(char * num)
  {
  	int len,i,d,virg=0;
  	len=strlen(num);
  	for(i=0;i<len;i++)
    	{
    		if(num[i]=='0' || num[i]=='1' || num[i]=='2' || num[i]=='3' || num[i]=='4' || num[i]=='5' || num[i]=='6' || num[i]=='7' || num[i]=='8' || num[i]=='9')
      		{
      			d=1;
      		}
    		else if (num[0]!=',' && num[i]==',')
      		{
      				if(virg==1)
      					{
      						return -1;
      					}
      		        virg=1;
      		}
    		else if(!isdigit(num[i]))
      		{
      			d=(-1);
      			return d;
      		}
    	}
  	if(virg==1)
    	{
    		return 0;
    	}
  	else return d;
  }




int main()
{
	char nombre[256];
	printf("\n\t             **********************************               ");
    printf("\n\t***************   Projet Chiffre En Lettre   ***************");
    printf("\n\t             **********************************              ");
    printf("\n\n\n\n");
    printf("\n-La valeur maximal est:999999999999999,999999999999999\nvotre valeur doit etre inferieure à cette valeur.\n");
    printf("\n-Pour un nombre reelle utiliser la virgule "","" \n\n\n");
	printf("\nEntrer votre nombre : ");
	scanf("%[^\n]s",nombre);
	Menu(nombre);
}

