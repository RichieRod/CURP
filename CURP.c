/*La Clave Única de Registro de Población, mejor conocida como CURP sirve para registrar en forma individual a todas las personas que residen en México, 
nacionales y extranjeras, así como a las mexicanas y mexicanos que radican en otros países. Está conformado por números y letras de 18 dígitos utilizado por 
distintas instituciones, públicas o privadas, para identificar a los residentes
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<regex.h> //https://www.onlinegdb.com/online_c_compiler
int validar_curp();//prototipo

int my_match(char* pattern,char* buf){
    int status,i;
    int flag=REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    regex_t reg;
    
    
    
    // compilando el modo regular
    regcomp(&reg,pattern,flag);
    
    // comparación de expresiones regulares y caché
    status=regexec(&reg,buf,nmatch,pmatch,0);
    
    // Imprima la cadena coincidente
    for(i=pmatch[0].rm_so;i<pmatch[0].rm_eo;++i){
        putchar(buf[i]);
    }
    printf("\n");
    regfree(&reg);
    return status;
}
int main(){
    char buf[1024]="RORR040925HPLDVCA4";
    
    printf("\t\t***Programa que valida el CURP***\n");
    system("pause");
    
    
    validar_curp(buf);
    
    return 0;
}

int validar_curp(char buf[1024]){
    char pattern[1024]="^(([A-Z]{1}[AEIOUX]{1}[A-Z]{2}[0-9]{2}(0[1-9]|1[0-2])(0[1-9]|1[0-9]|2[0-9]|3[0-1])[HM]{1}(AS|BC|BS|CC|CS|CH|CL|CM|DF|DG|GT|GR|HG|JC|MC|MN|MS|NT|NL|OC|PL|QT|QR|SP|SL|SR|TC|TS|TL|VZ|YN|ZS|NE)[B-DF-HJ-NP-TV-Z]{3}[0-9A-Z]{1}[0-9]{1}))$";
    
    int status=my_match(pattern,buf);
    if(0 == status){
        printf("¡Partiendo el éxito! \n");
    }
    //Cuando NO es válida la cadena
    else if(status != 0 || status==REG_NOMATCH){
        
        
        
        //Extensión de la CURP
        if(buf[18] != 0 || buf[17] == 0){
            printf("Hay errores en la CURP: \n");
            printf("- La CURP no es de la extensión indicada, favor de escribir todos los digitos de su CURP \n");
            return 0;
        } 
        
        printf("Hay errores en la CURP: \n");
        
        //Que no exista un número en la parte del nombre
        if(buf[0] >= 48 && buf[0] <= 57) printf("- Hay un número en el área del nombre completo, verificar nuevamente posicion 1-4 \n");
        
        //Añadiendo validación de todo el nombre
        for(int i = 0; i <= 3; i++) {
            if(buf[i] >= 48 && buf[i] <= 57) {
                printf("- El numero que esta escribiendo en la posicion del nombre completo es: (%c) \n", buf[i]);
            }
        }
        if(buf[6] == 49) {
            if(buf[7] >= 51 && buf[7] <= 57){ 
                printf("- No se puede tener un mes mayor a 12, verificar posición 7 y 8 (%c) \n", buf[7]);
            }
        }
        
        
        if(buf[6] >= 50 && buf[7] <= 57){ 
            printf("- No se puede tener un mes mayor a 12, verificar posicion 7 y 8 \n");
        }
        
        //Fecha de nacimiento
        for(int i = 4; i <= 9; i++){
                if(!(buf[i] >= 48 && buf[i] <= 57)){
                printf("- Solo puede haber números en el área de la fecha de nacimiento (%c), verificar nuevamente posición 5-10 \n", buf[i]);
                break;
            }
        }
        
        //Sexo
        if(buf[10] != 'H' && buf[10] != 'M') printf("- Es incorrecto el caracter del sexo (%c), verificarlo nuevamente (H o M) en la posicion 11 \n", buf[10]); 
        
        //Solo letras en entidad federativa 
        for(int i = 11; i <= 12; i++) {
            if(!(buf[i] >= 64 && buf[i] <= 90)) printf("- Caracter incorrecto en la entidad federativa (%c), verificar nuevamente posicion 12 o 13 \n",buf[i]);
           
        }

        // letras y consonantes de apellidos y nombre
        for(int i = 13; i <= 15; i++) {
            if(!(buf[i] >= 64 && buf[i] <= 90)) printf("- Caracter incorrecto en primeras consonantes del apellido y nombre (%c), verificar nuevamente posición 14-16 \n", buf[i]);
           
        }
        //Solo números en la ultima posición
        if(!(buf[17] >= 48 && buf[17] <= 57)) printf("- Caracter incorrecto en los digitos otorgados por RENAPO (%c), verificar nuevamente posicion 18", buf[17]);
        
    }
}

