// iliya forsati    402106297

#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define max_arr_size 1024

char pro_location[max_arr_size] ;
bool  find  = false ;

// functions
int creat_pro_app() ;
int check_pro_made(bool * is_pro_made) ;
void local_ca( char* na_or_em , char * user ) ;
void global_ca( char* na_or_em , char * user ) ;
int init_creat(char pro_loc[max_arr_size] ) ;
int init() ;
int check_pro_app_exists() ;
int add_one_file_or_dir( char add[] , char first_add_add[max_arr_size] ) ;
int add_to_tracked_txt( char first_add_add[max_arr_size] ) ;
int check_file( char first_add_add[max_arr_size] ) ;
int copy_to_staged_files( char first_add_add[max_arr_size] ) ;
int search_is_staged( int depth ) ;
int wildcard_add( char add[max_arr_size] ) ;
int reset_one_file_or_dir( char add[] , char first_add[max_arr_size] ) ;
int remove_from_tracked_txt( char first_add_add[max_arr_size] ) ;
int remove_frome_staged_files( char first_add_add[max_arr_size] ) ;
int add_to_unstaged_txt( char first_add_add[max_arr_size] ) ;
int wildcard_reset( char address[max_arr_size] ) ;
int add_to_last_add( char first_add_add[max_arr_size] ) ;
int undo_reset() ;
int redo_add() ;
int remove_from_unstaged_files() ;
int commit( char mas[max_arr_size] ) ;
int check_add_file() ;
int copy_fdded_to_commit( char branch[max_arr_size] , char new_commit[max_arr_size]) ;
int set ( char mass[max_arr_size] , char name[max_arr_size] ) ;
int shortcut_commit( char name[max_arr_size] ) ;
int replace( char mass[max_arr_size] , char name[max_arr_size] ) ;
int remmove( char name[max_arr_size] ) ;
int show_n( int n ) ;
int show_log( int n ) ;
int check_log( char name[max_arr_size] , int (*function)(char* , int) ) ;
int branch_check( char name[max_arr_size] , int n ) ;
int author_check( char name[max_arr_size] , int n ) ;
int massage_check( char name[max_arr_size] , int n ) ;
int time_log(long long int time , int mode ) ;
int branch( char name[max_arr_size] ) ;
int check_branch( char name[max_arr_size] ) ;
int id_checkout( char id[max_arr_size] ) ;
int check_head() ;
int branch_checkou( char name[max_arr_size] ) ;
int go_to_head() ;
int tag(char name[max_arr_size] , char mass[max_arr_size] , char id[max_arr_size] ) ;
int del_last_tag( char name[max_arr_size] ) ;
int all_tag() ;
int tag_show( char name[max_arr_size] ) ;
int grep(char file[max_arr_size] , char word[max_arr_size] , int mode) ;
int can_commit() ;
int chop_hooks() ;
int chop_applied() ;
int add_hook( char hook_id[max_arr_size] , int mode ) ;
int all_pre_commits() ;
int one_pre_commits() ;
int size( char file[max_arr_size] ) ;
int checkFileSize(const char *filename) ;
int limit( char file[max_arr_size] ) ;
int checkFileFormatAndSize(const char *filename) ;
int balance( char file[max_arr_size] ) ;
int checkBalance(const char *filename) ;
int eoof( char file[max_arr_size] ) ;
int checkTrailingWhitespace(const char *filename) ;
int todo(char file[max_arr_size] ) ;
int checkTodoInFile(const char *filename) ;



// check
int check_pro_made(bool * is_pro_made)
{
    char cwd[max_arr_size] ;
    getcwd(cwd,max_arr_size) ;
    char temp_add[max_arr_size] ;
    struct dirent * entry ;
    while (1) {
        DIR *dir = opendir(".") ;
        if ( dir == NULL) {
            fprintf(stderr , "Error opening current directory \n ") ;
            return 1;
        }
        while ( ( entry = readdir(dir) ) != NULL ) {
            // printf("%s\n" , entry->d_name ) ;
            if ( strcmp( entry->d_name , ".pro" ) == 0 ) {
                *is_pro_made = true ;
                getcwd(pro_location , max_arr_size) ;
                closedir(dir) ;
                return 0;
            }
        }
        closedir(dir) ;
        if ( getcwd(temp_add,sizeof(temp_add)) == NULL ) return 1;
        if ( strcmp( temp_add , "C:\\" ) != 0 ) {
            chdir("..") ;
        } if ( strcmp( temp_add, "C:\\" ) == 0 ) {
            break;
        }
    }
    chdir(cwd) ;
    return 0;
}
int check_pro_app_exists()  
{
    char first_add[max_arr_size] ;
    if ( getcwd(first_add,sizeof(first_add)) == NULL ) return 1;

    bool is_proapp_exists = false ;
    chdir("C:\\Users\\ASUS\\Desktop\\proo") ;
    DIR * dir = opendir(".") ;
    if ( dir == NULL) {
        fprintf(stderr , "Error opening current directory \n ") ;
        return 1;
    }
    struct dirent * entry ;
    while ((entry = readdir(dir)) != NULL ) {
        if ( strcmp( entry->d_name , ".pro_app" ) == 0 ) {
            is_proapp_exists = true ;
        }
    }
    closedir(dir) ;
    if (is_proapp_exists) {
        chdir(first_add) ;
        return 1;
    }
    if (!is_proapp_exists) {
        system("mkdir .pro_app") ;
        system("attrib +h .pro_app") ;
        chdir(".pro_app") ;
        chdir(first_add) ;
        return 0;
    } 
    return 1;
}

// config user
void local_ca( char* na_or_em , char * user )   // ??????????
{
    bool is_pro_made = false ;
    check_pro_made(&is_pro_made) ;
    if ( !is_pro_made ) {
        fprintf(stderr , "you don't have any new project") ;
        return ; 
    } 
    if ( strcmp(na_or_em , "user.name") == 0 ) {
        chdir(pro_location) ;
        chdir(".pro") ;
        chdir("config") ;
        FILE * file = fopen("user_local_name.txt" , "w" ) ;
        fprintf(file , "%s" , user ) ;
        fclose(file) ;
    } else if ( strcmp(na_or_em , "user.email") == 0 ) {
        chdir(pro_location) ;
        chdir(".pro") ;
        FILE * file = fopen("user_local_email.txt" , "w" ) ;
        fprintf(file , "%s" , user ) ;
        fclose(file) ;
    }
}
void global_ca( char* na_or_em , char * user ) 
{
    if ( strcmp(na_or_em , "user.name") == 0 ) {
        FILE *glo_name = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\global_name.txt" , "w" ) ;   // ???
        fprintf(glo_name , "%s" , user ) ;
        fclose(glo_name) ;
        char line[max_arr_size] ;
        FILE * file = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\first_location.txt" , "r" ) ;
        while (fgets(line,max_arr_size,file)) {
            if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0' ;
            char add[max_arr_size] ;
            snprintf(add , max_arr_size , "%s\\.pro\\config\\user_local_name.txt" , line) ;
            FILE * f = fopen(add , "w" ) ;
            fprintf(f , "%s" , user ) ;
            fclose(file) ;
        }
        fclose(file) ;
    } else if ( strcmp(na_or_em , "user.email" ) == 0 ) {
        FILE  *glo_email = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\global_email.txt" , "w" ) ;  // ????
        fprintf(glo_email , "%s" , user ) ;
        fclose(glo_email) ;
        char line[max_arr_size] ;
        FILE * file = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\first_location.txt" , "r" ) ;
        while (fgets(line,max_arr_size,file)) {
            if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0' ;
            char add[max_arr_size] ;
            snprintf(add , max_arr_size , "%s\\.pro\\config\\userr_local_email.txt" , line ) ;
            FILE * f = fopen(add , "w" ) ;
            fprintf(f , "%s" , user ) ;
            fclose(file) ;
        }
        fclose(file) ;
    }
}

// init
int init_creat( char pro_loc[max_arr_size] )
{
    system("mkdir .pro") ;
    system("attrib +h .pro") ;
    chdir(".pro") ;
    system("mkdir staged_files") ;
    chdir("staged_files") ;
    system("mkdir files") ;
    chdir("..") ;
    system("mkdir tag") ;
    system("mkdir pre_commits") ;
    chdir("pre_commits") ;
    system("echo 0 >todo_check.txt") ;
    system("echo 0 >eof_blank_space.txt") ;
    system("echo 0 >balance_braces.txt") ;
    system("echo 0 >character_limit.txt") ;
    system("echo 0 >file_size_check.txt") ;
    system("echo 0 >is_bad.txt") ;
    chdir("..") ;
    system("mkdir commits") ;
    chdir("commits") ;
    FILE * file11 = fopen( "last_commit.txt" , "w" ) ;
    fprintf(file11 , "0" ) ;
    fclose(file11) ;
    FILE * file21 = fopen("branch.txt" , "w" ) ;
    fprintf(file21 , "master" ) ;
    fclose(file21) ; 
    FILE * fi = fopen("is_head.txt" , "w" ) ;
    fprintf(fi , "1" ) ;
    fclose(fi) ;
    FILE * f = fopen("branches.txt" , "w" ) ;
    fprintf(f , "master\n") ;
    fclose(f) ;
    system("mkdir master") ;
    system("mkdir all_commits") ;
    chdir("master") ;
    FILE * y = fopen("head_id.txt" , "w" ) ;
    fprintf(y , "0") ;
    fclose(y) ;
    system("mkdir 0") ;
    chdir("0") ;
    system("mkdir files") ;
    char cmd[max_arr_size] ,cmd2[max_arr_size];
    strcpy(cmd , "xcopy ") ;
    strcat(cmd , pro_loc) ;
    system("mkdir D:\\temp") ;
    strcat(cmd , " D:\\temp /E") ;
    system(cmd) ; 
    strcpy(cmd2 ,"xcopy D:\\temp ") ;
    strcat(cmd2,pro_loc) ;
    strcat(cmd2 ,"\\.pro\\commits\\master\\0\\files /E") ;
    system(cmd2) ;
    system("rd /s /q D:\\temp") ;
    strcat(cmd2 ," 0 /E") ;
    chdir("..") ;
    chdir("..") ;
    chdir("..") ;
    chdir("..") ;
    chdir(".pro") ;
    char user_name[100] , user_email[100] ;
    FILE *file1 = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\global_name.txt" , "r" ) ;
    fgets(user_name , 100 , file1) ;
    fclose(file1) ;
    FILE *file2 = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\global_email.txt" , "r" ) ;
    fgets(user_email , 100 , file2) ;
    fclose(file2) ;
    FILE * fil3 = fopen("C:\\Users\\ASUS\\Desktop\\proo\\.pro_app\\first_location.txt" , "a" ) ;
    fprintf(fil3 , "%s\n" , pro_loc ) ;
    fclose(fil3) ;
    system("mkdir config") ;
    chdir("config") ;
    FILE * file3 = fopen("user_local_name.txt" , "w" ) ;
    fprintf(file3 , "%s" , user_name) ;
    fclose(file3) ;
    FILE *file4 = fopen("user_local_email.txt" , "w" ) ;
    fprintf(file4 , "%s" , user_email ) ;
    fclose(file4) ;
    return 0;
}
int init() {

    bool is_exists_pro = false ;
    check_pro_made(&is_exists_pro) ; 
 
    if ( is_exists_pro ) {
        fprintf(stderr , " pro repository has already initialized \n "  ) ;
        return 1;
    } else if ( !is_exists_pro ) {
        char cwd[max_arr_size] ;
        getcwd(cwd,max_arr_size) ;
        init_creat(cwd) ;
    }
    return 0 ;
}

// add
int remove_from_unstaged_files()
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file1 = fopen("unstaged_files.txt" , "w" ) ;
    fclose(file1) ;
    return 0;
}
int redo_add()
{
    FILE * file1 = fopen("unstaged_files.txt" , "r" ) ;
    char add[max_arr_size] ;
    while ( fgets(add , sizeof(add) , file1) ) {
        int len = strlen(add) ;
        if ( add[len-1] == '\n' ) add[len-1] = '\0' ;
        add_one_file_or_dir(add , NULL) ;
    }
    remove_from_unstaged_files() ;
    return 0;
}
int add_to_last_add( char first_add_add[max_arr_size] ) 
{
    chdir(pro_location) ;
    chdir(".pro\\staged_files") ;
    FILE * file1 = fopen("last_add.txt" , "w" ) ;
    fprintf(file1 , "%s" , first_add_add ) ;
    fclose(file1) ; 
    return 0;
}
int wildcard_add( char address[max_arr_size] )
{
    char cmd[max_arr_size] = "dir /B " ;
    strcat( cmd , address ) ;
    strcat( cmd , " > file_name.txt") ;
    system(cmd) ;
    FILE * file = fopen( "file_name.txt" , "r" ) ;
    char add[max_arr_size] ;
    char cwd[max_arr_size] ;
    getcwd(cwd , sizeof(cwd) ) ;
    while ( fgets(add , sizeof(add) , file ) ) {
        if ( strstr(add , "File Not Found") != NULL ) {
            fprintf(stdout , "There is no file with  this name \n") ;
            break;
        }
        int len = strlen(add) - 1;
        if (add[len] == '\n' ) {
            add[len] = '0' ;
        } 
        add_one_file_or_dir( add , cwd ) ;
    }
    system("del file_name.txt") ;
    fclose(file) ;
    return 0;
}
int search_is_staged( int depth )
{
    char files[55][55] ;
    DIR * dir = opendir(".") ;
    struct dirent * entry ;
    int i ;
    for ( i = 0 ; ( entry = readdir(dir) ) != NULL ; i++ ) {
        if ( strcmp(entry->d_name , ".pro") && strcmp(entry->d_name , "." ) && strcmp(entry->d_name , ".." ) ) {
            strcpy( files[i] , entry->d_name ) ;
        } else {
            i-- ;
        }
    } 
    closedir(dir) ;
    char cwd_copy[max_arr_size] ;
    getcwd(cwd_copy , sizeof(cwd_copy) ) ;
    for ( int j = 0 ; j < i ; j++ ) {
        chdir(cwd_copy) ;
        char cwd[max_arr_size] ;
        getcwd(cwd , sizeof(cwd)) ;
        strcat(cwd , "\\") ;
        strcat(cwd , files[j]) ;

        bool is_folder = false ;
        struct stat file_info ;
        stat(cwd , &file_info ) ;

        if( S_ISDIR( file_info.st_mode ) ) {
            is_folder = true ;
        }
        if ( is_folder && depth > 1  ) {
            fprintf( stdout , "%s <it is a folder> \n" , cwd ) ;
            chdir(files[j]) ;
            search_is_staged( depth - 1 ) ;
            chdir("..") ;
        } else if ( is_folder && depth == 1 ) {
            fprintf( stdout , "%s <it is a folder> \n" , cwd ) ;
        } else if ( !is_folder ) {
            if ( check_file(cwd) == 0 ) {
                fprintf(stdout , "%s is staged\n" , cwd ) ;
            } else {
                fprintf(stdout , "%s isn't staged\n" , cwd ) ;
            }
        }
    }
    return 0; 
}
int copy_to_staged_files( char first_add_add[max_arr_size] )
{
    char copy[max_arr_size] ;
    strcpy(copy , pro_location) ;
    strcat(copy , "\\.pro\\staged_files\\files") ;
    char command[max_arr_size] ;
    strcpy(command , "copy" ) ;
    strcat(command , " " ) ;
    strcat( command , first_add_add ) ;
    strcat( command , " " ) ;
    strcat( command , copy ) ;
    system ( command ) ;
    return 0;
}
int check_file( char first_add_add[max_arr_size] )
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file1 = fopen("trackted_files.txt" , "r" ) ;
    char file_name[max_arr_size] ;
    while ( fgets(file_name , sizeof(file_name) , file1 ) ) {
        int len ;
        len = strlen(file_name) ;
        if ( file_name[len-1] == '\n' ) file_name[len-1] = '\0' ;
        if ( !strcmp(file_name , first_add_add ) ) {
            return 0 ;
        }
    }
    return 1;
}
int add_to_tracked_txt( char first_add_add[max_arr_size] )
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file2 = fopen("trackted_files.txt" , "a" ) ;
    fprintf(file2 , "%s\n" , first_add_add ) ;
    fclose(file2) ;
    FILE * file3 = fopen("added_befor.txt" , "a" ) ;
    fprintf(file3 , "%s\n" , first_add_add ) ;
    fclose(file3) ;
    return 0;
}
int add_one_file_or_dir( char add[] , char first_add[max_arr_size] )
{
    char first_add_add[max_arr_size] ;
    if(first_add != NULL) {
        strcpy( first_add_add , first_add ) ;
        strcat(first_add_add , "\\") ;
        strcat(first_add_add , add ) ; 
    } else {
        strcpy(first_add_add , add) ;
    }
    
    // with CHAT GBT help
    struct stat file_info ;
    stat( first_add_add , &file_info ) ;   
        if ( S_ISDIR( file_info.st_mode ) ) {
            chdir(first_add_add) ;
            DIR * dir = opendir(".") ;
            struct dirent * entry ;
            while ( (entry = readdir(dir) ) != NULL ) {
                if ( strcmp( entry->d_name , ".pro" )  && strcmp( entry->d_name , "." ) && strcmp( entry->d_name , ".." ) ) {
                    add_one_file_or_dir( entry->d_name , first_add_add ) ;
                }
            }
            add_to_last_add(first_add_add) ; 
            chdir("..") ;
        } else if ( S_ISREG(file_info.st_mode ) ) {
            if ( check_file( first_add_add ) ){
                add_to_last_add(first_add_add) ; 
                // قبلا ادد نشده
                add_to_tracked_txt( first_add_add ) ;
                // add name to the list 
                copy_to_staged_files( first_add_add ) ;
                return 0;
            } else {
                fprintf(stderr , "the file << %s >> has been added befor \n" , first_add_add ) ;
                return 1;
            }
        } else {
            fprintf(stderr , " the file << %s >> doesn't exist \n" , first_add_add ) ;
            return 1; 
        }
    return 0;
}

// reset
int undo_reset() 
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file1 = fopen( "last_add.txt" , "r" ) ;
    char add[max_arr_size] ;
    fgets( add , sizeof(add) , file1 ) ;
    fclose(file1) ;
    reset_one_file_or_dir( add , NULL ) ;
    FILE * file2 = fopen( "last_add.txt" , "W" ) ;
    fclose(file2) ;
    return 0;
}
int wildcard_reset( char address[max_arr_size] ) 
{
    char cmd[max_arr_size] = "dir /B " ;
    strcat( cmd , address ) ;
    strcat( cmd , " > file_name.txt") ;
    system(cmd) ;
    FILE * file = fopen( "file_name.txt" , "r" ) ;
    char add[max_arr_size] ;
    while ( fgets(add , sizeof(add) , file ) ) {
        if ( strstr(add , "File Not Found") != NULL ) {
            fprintf(stdout , "There is no file with this name \n") ;
            break;
        }
        int len = strlen(add) - 1;
        if (add[len] == '\n' ) {
            add[len] = '0' ;
        } 
        char cwd[max_arr_size] ;
        getcwd(cwd , sizeof(cwd) ) ;
        add_one_file_or_dir( add , cwd ) ;
    }
    system("del file_name.txt") ;
    fclose(file) ;
    return 0;
}
int add_to_unstaged_txt( char first_add_add[max_arr_size] ) 
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file1 = fopen("unstaged_files.txt" , "a" ) ;
    fprintf(file1 , "%s\n" , first_add_add ) ;
    fclose(file1) ;
    return 0;
}
int remove_frome_staged_files( char first_add[max_arr_size] ) 
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    chdir("files") ;
    char first_add_add[max_arr_size] ;
    strcpy(first_add_add , first_add) ;
    char file_name[max_arr_size] ;
    char *tok = strtok(first_add_add , "\\") ;
    while( ( tok = strtok(NULL , "\\" ) ) != NULL ) {
        strcpy( file_name , tok ) ;
    }
    char cmd[max_arr_size] ;
    strcpy(cmd,"del ") ;
    strcat(cmd , file_name);
    system(cmd) ;

    return 0;
}
int remove_from_tracked_txt( char first_add_add[max_arr_size] )  
{
    char lines[100][max_arr_size] ;
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    FILE * file2 = fopen("trackted_files.txt" , "r" ) ;
    char add[max_arr_size] ;
    int i = 0 ;
    while( fgets(add , sizeof(add) , file2 ) != NULL ) {
        int len ;
        len = strlen(add) - 1 ;
        if ( add[len] == '\n' ) add[len] = '\0' ;
        if ( strcmp( add , first_add_add ) == 0 ) {
            continue ;
        } else {
            strcpy( lines[i] , add ) ;
            i++ ;
        }
    }
    fclose(file2) ;
    FILE * file3 = fopen("trackted_files.txt" , "w" ) ; 
    for ( int j = 0 ; j < i ; j++ ) {
        fprintf(file3 , "%s\n" , lines[j] ) ;
    }
    fclose(file3) ;
    return 0;
}
int reset_one_file_or_dir( char add[] , char first_add[max_arr_size] )
{
    char first_add_add[max_arr_size] ;
    if (first_add != NULL) {
        strcpy( first_add_add , first_add ) ;
        strcat(first_add_add , "\\") ;
        strcat(first_add_add , add ) ;
    } else {
        strcpy(first_add_add , add) ;
    }
    
    struct stat file_info ;
    stat( first_add_add , &file_info ) ;
    if ( S_ISDIR( file_info.st_mode ) ) {
        // printf()
        chdir(first_add_add) ;
        DIR * dir = opendir(".") ;
        struct dirent * entry ;
        while ( (entry = readdir(dir) ) != NULL ) {
            if ( strcmp( entry->d_name , ".pro" ) && strcmp( entry->d_name , "." ) && strcmp( entry->d_name , ".." ) ) {
                reset_one_file_or_dir( entry->d_name , first_add_add ) ;
            }
        } 
        chdir("..") ;
    } else if ( S_ISREG(file_info.st_mode ) ) {
        if ( !check_file( first_add_add ) ) {
            remove_from_tracked_txt( first_add_add ) ;
            remove_frome_staged_files( first_add_add ) ;
            add_to_unstaged_txt( first_add_add ) ;
        } else {
            fprintf(stderr , "the file << %s >> has not been added befor \n" , first_add_add ) ;
            return 1;
        }
    } else {
        fprintf(stderr , " the file << %s >> doesn't exist \n" , first_add_add ) ;
        return 1; 
    }
    return 0;
}

// commit
int is_empty(char *filename ) { 
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;  
    }
    int isEmpty = 1;  
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '\t') {
            isEmpty = 0;
            break;
        }
    }
    fclose(file);
    return isEmpty;
}
int check_add_file()
{
    chdir(pro_location) ;
    chdir(".pro") ;
    chdir("staged_files") ;
    if ( is_empty("trackted_files.txt") ) {
        chdir("..") ;
        chdir("..") ;
        return 1;
    } 
    chdir("..") ;
    chdir("..") ;
    return 0;
}
int copy_fdded_to_commit( char branch[max_arr_size] , char new_commit[max_arr_size] )
{
    chdir(pro_location) ;
    chdir(".pro\\staged_files") ;
    FILE * f1 = fopen("trackted_files.txt" , "r" ) ; 
    char add[max_arr_size] ;
    char name[max_arr_size] ;
    int count = 0 ;
    while( fgets(add , sizeof(add) , f1 ) ) {
        int len = strlen(pro_location) ;
        int i ;
        if ( add[strlen(add)-1] == '\n' ) add[strlen(add)-1] = '\0' ; 
        for ( i = len+1 ; add[i] != '\0' ; i++ ) {
            name[i-len-1] = add[i] ;
        }
        name[i-len-1] = '\0' ;
        char cmd[max_arr_size] ;
        cmd[0] = '\0' ;
        snprintf(cmd , sizeof(cmd) ,"copy /Y %s %s\\.pro\\commits\\%s\\%s\\files\\%s" , add , pro_location , branch , new_commit , name ) ;
        system(cmd) ;
        count++ ;
    }
    system("del /Q /S files") ;
    FILE * clear_trackted = fopen("trackted_files.txt" , "w") ;
    fclose(clear_trackted) ;
    FILE * clear_trackted1 = fopen("added_befor.txt" , "w") ;
    fclose(clear_trackted1) ;
    FILE * clear_trackted2 = fopen("last_add.txt" , "w") ;
    fclose(clear_trackted2) ;
    return count ;
}
int commit( char mas[max_arr_size] )
{
    if ( can_commit() ) {
        fprintf(stderr , "pre_commit : you cann't commit \n") ;
        return 1;
    }
    if ( check_head() ) {
        fprintf(stderr , "you aren't in head commit\n") ;
        return 1;
    }
    printf("1") ;
    if ( check_add_file() ) {
        fprintf(stdout , "you don't have any added file" ) ;
        return 1;
    }
    printf("1") ;
    if ( strlen(mas) > 72 ) {
        fprintf(stderr , "your massage is too long \n");
        return 1;
    }
    char cwd[max_arr_size] ;
    getcwd(cwd , max_arr_size) ;
    chdir(".pro\\commits") ;
    FILE * f1 = fopen("last_commit.txt" , "r" ) ;
    int last_commit_id ;
    fscanf(f1 , "%d" , &last_commit_id) ;
    last_commit_id++ ;
    fclose(f1) ;
    FILE * f2 = fopen("last_commit.txt" , "w" ) ;
    fprintf(f2 , "%d" , last_commit_id ) ;
    fclose(f2) ; 
    FILE * f3 = fopen("branch.txt" , "r" ) ;
    char branch[max_arr_size] ;
    fscanf(f3 , "%s" , branch ) ;
    fclose(f3) ;
    char new_commit_name[5] ,last_commit_name[5] ;
    sprintf(new_commit_name , "%d" , last_commit_id) ;
    int last_branch_id ;
    chdir(branch) ;
    FILE * q = fopen("head_id.txt" , "r" ) ;
    fscanf(q , "%d" , &last_branch_id ) ;
    fclose(q) ;
    FILE * q1 = fopen("head_id.txt" , "w" ) ;
    fprintf(q1 , "%d" , last_commit_id ) ;
    fclose(q1) ;
    sprintf(last_commit_name , "%d" , last_branch_id ) ;
    char cmd[max_arr_size] ;
    strcpy(cmd,"mkdir ") ;
    strcat(cmd,new_commit_name) ;
    system(cmd) ;
    chdir(new_commit_name) ;
    system("mkdir files") ;
    char cmd2[max_arr_size] ;
    strcpy(cmd2,"xcopy ") ;
    strcat(cmd2,cwd) ;
    strcat(cmd2,"\\.pro\\commits\\") ;
    strcat(cmd2,branch) ;
    strcat(cmd2,"\\") ;
    strcat(cmd2,last_commit_name) ;
    strcat(cmd2,"\\files ") ;
    strcat(cmd2,cwd) ;
    strcat(cmd2,"\\.pro\\commits\\") ;
    strcat(cmd2,branch) ;
    strcat(cmd2,"\\") ;
    strcat(cmd2,new_commit_name) ;
    strcat(cmd2,"\\files /E") ;
    system(cmd2) ;
    int count = copy_fdded_to_commit( branch , new_commit_name ) ;
    chdir("..") ;
    chdir("commits") ;
    chdir(branch) ;
    chdir(new_commit_name) ;
    FILE * file1 = fopen("massage.txt" , "w" ) ;
    fprintf(file1 , "%s" , mas ) ;
    fclose(file1) ;
    FILE * file2 = fopen("id.txt" , "w" ) ;
    fprintf(file2 , "%d" , last_commit_id ) ;
    fclose(file2) ;
    FILE * file5 = fopen("who.txt" , "w" ) ;
    char username[max_arr_size] ;
    username[0] = '\0' ;
    snprintf(username , sizeof(username) , "%s\\.pro\\config\\user_local_name.txt" , cwd ) ;
    FILE * name = fopen( username , "r") ;
    fscanf( name , "%s" , username ) ;
    fclose(name) ;
    fprintf(file5 , "%s" , username ) ;
    fclose(file5) ;
    FILE * file6 = fopen("branch.txt" , "w" ) ;
    fprintf(file6 , "%s" , branch ) ;
    fclose(file6) ;
    FILE * file3 = fopen("count.txt" , "w" ) ;
    fprintf(file3 , "%d" , count ) ;
    fclose(file3) ;
    FILE * file4 = fopen("time.txt" , "w") ;
    time_t t ;
    time(&t) ;
    struct tm * local_time = localtime(&t) ;
    fprintf(file4 , "%lld\n%s" , t , asctime(local_time) ) ;
    fclose(file4) ;
    chdir("..") ;
    chdir("..") ;
    char cmd3[max_arr_size] ;
    cmd3[0] = '\0' ;
    snprintf(cmd3 , sizeof(cmd3) , "xcopy %s all_commits /E /I /Q /Y" , branch) ;
    system(cmd3) ;
    return 0;
}
int set ( char mass[max_arr_size] , char name[max_arr_size] )
{
    if( strlen(mass) > 72 ) {
        fprintf(stderr , "your massage is too long \n");
        return 1;
    }
    chdir(".pro\\commits") ;
    char copy[max_arr_size] ;
    strcpy(copy,name) ;
    strcat(copy,".txt") ;
    FILE * file = fopen(copy , "w") ;
    fprintf(file, "%s" , mass ) ;
    fclose(file) ;
    return 0;
}
int shortcut_commit( char name[max_arr_size] )
{
    chdir(".pro\\commits");
    strcat(name,".txt") ;
    FILE * file = fopen(name , "r" ) ;
    if(file == NULL) {
        fprintf(stderr , "shortcut doesn't exist\n") ;
        fclose(file) ;
        return 1;
    }
    char mass[max_arr_size] ;
    fgets(mass ,sizeof(mass) , file) ;
    fclose(file) ;
    commit(mass) ;
    return 0;
}
int replace( char mass[max_arr_size] , char name[max_arr_size] ) 
{
    chdir(".pro\\commits") ;
    strcat(name, ".txt") ;
    FILE * file = fopen(name , "r") ;
    if ( file == NULL ) {
        fprintf(stderr , "shrtcut doesn't exist\n") ;
        fclose(file) ;
        return 1;
    }
    fclose(file) ;
    FILE * file1 = fopen(name , "w") ;
    fprintf(file1 , "%s" , mass) ;
    return 0;
}
int remmove( char name[max_arr_size] ) 
{
    chdir(".pro\\commits") ;
    strcat(name , ".txt") ;
    FILE * file = fopen(name , "r") ;
    if ( file == NULL ) {
        fprintf(stderr , "shortcut doesn't exist\n") ;
        fclose(file) ;
        return 1;
    }
    fclose(file) ;
    char cmd[max_arr_size] = "del " ;
    strcat(cmd , name) ;
    system(cmd) ;
    return 0;
}

// log 
int show_log( int n ) 
{
    char name[5] ;
    sprintf(name , "%d" , n ) ;
    char file[max_arr_size] ;
    snprintf(file , max_arr_size , "%s\\branch.txt" , name ) ;
    FILE * f1 = fopen(file , "r" ) ;
    char branch[max_arr_size] ;
    branch[0] = '\0' ;
    fscanf(f1 , "%s" , branch ) ;
    fclose(f1) ;
    snprintf(file ,max_arr_size , "%s\\count.txt" , name ) ;
    FILE * f2 = fopen(file , "r" ) ;
    int count ;
    fscanf(f2 , "%d" , &count ) ;
    fclose(f2) ;
    snprintf(file ,max_arr_size , "%s\\massage.txt" , name ) ;
    FILE * f3 = fopen(file , "r" ) ;
    char massage[max_arr_size] ;
    fscanf(f3 , "%[^\n]s" , massage ) ; 
    fclose(f3) ;
    snprintf(file ,max_arr_size , "%s\\time.txt" , name ) ;
    FILE * f4 = fopen(file , "r" ) ;
    char time[max_arr_size] ;
    long long int t ;
    fscanf(f4 , "%lld\n%[^\n]s" , &t , time ) ;
    fclose(f4) ;
    snprintf(file ,max_arr_size , "%s\\who.txt" , name ) ;
    FILE * f5 = fopen(file , "r" ) ;
    char who[max_arr_size] ;
    fscanf(f5 , "%s" , who ) ;
    fclose(f5) ;
    fprintf(stdout , "commit id : %d with massage : %s at: %s with user: %s in branch : %s and %d files committed\n" , n , massage , time , who , branch , count ) ;
    return 0 ;
}
int show_n( int n )
{
    FILE * file = fopen(".pro\\commits\\last_commit.txt" , "r" ) ;
    int last_commit  ;
    fscanf(file , "%d" , &last_commit ) ;
    fclose(file) ;
    chdir(".pro\\commits\\all_commits") ;
    if ( n == -1 ) n = last_commit ;
    for ( int i = last_commit ; i > last_commit-n ; i-- ) {
        show_log(i) ;
    }
    return 0;
}
int branch_check( char name[max_arr_size] , int n ) 
{
    chdir(".pro\\commits\\all_commits") ;
    char id[5] ;
    sprintf(id , "%d" , n) ;
    char branch_file[max_arr_size] ;
    snprintf(branch_file , max_arr_size ,"%s\\branch.txt" , id ) ;
    FILE * file = fopen(branch_file , "r") ;
    char branch[max_arr_size] ;
    fscanf(file , "%s" , branch ) ;
    if ( strcmp(branch,name) == 0 ) {
        return 1;
    } 
    return 0;
}
int author_check( char name[max_arr_size] , int n) 
{
    chdir(".pro\\commits\\all_commits") ;
    char id[5] ;
    sprintf(id , "%d" , n) ;
    char f[max_arr_size] ;
    snprintf(f , max_arr_size ,"%s\\who.txt" , id ) ;
    FILE * file = fopen(f , "r") ;
    char author[max_arr_size] ;
    fscanf(file , "%s" , author ) ;
    if ( strcmp(author,name) == 0 ) {
        return 1;
    } 
    return 0;
}
int massage_check( char name[max_arr_size] , int n )
{
    chdir(".pro\\commits\\all_commits") ;
    char id[5] ;
    sprintf(id , "%d" , n) ;
    char f[max_arr_size] ;
    snprintf(f , max_arr_size ,"%s\\massage.txt" , id ) ;
    FILE * file = fopen(f , "r") ;
    char massage[max_arr_size] ;
    fscanf(file , "%[^\n]s" , massage ) ;
    if ( strstr(massage,name) != NULL ) {
        return 1;
    } 
    return 0;
}
int check_log( char name[max_arr_size] , int (*function)(char* , int) )
{
    FILE * file = fopen(".pro\\commits\\last_commit.txt" , "r" ) ;
    int last_commit ;
    fscanf(file , "%d" , &last_commit ) ;
    fclose(file) ;
    for ( int i = last_commit ; i > 0 ; i-- ) {
        if ( function(name , i) ) {
            show_log(i) ;
        }
    }
    return 0;
}
int time_log(long long int time , int mode )
{
    FILE * file = fopen(".pro\\commits\\last_commit.txt" , "r" ) ;
    int last_commit , index = 0 ;
    long long int t ;
    fscanf(file , "%d" , &last_commit ) ;
    fclose(file) ;
    chdir(".pro\\commits\\all_commits") ;
    for ( int i = last_commit ; i > 0 ; i-- ) {
        char f[max_arr_size] ;
        snprintf(f , max_arr_size ,"%d\\time.txt" , i ) ;
        FILE * file = fopen(f , "r") ;
        fscanf(file , "%lld" , &t ) ;
        if ( time > t ) {
                index = i ;
                fclose(file) ;
                break;
        }
    }
    if ( mode == 1 ) {
        for ( int i = last_commit ; i > index ; i-- ) {
            show_log(i) ;
        }
        return 0;
    } else {
        for ( int i = index ; i > 0 ; i-- ) {
            show_log(i) ;
        }
        return 0;
    }
    fprintf(stderr , "0 file found" ) ;
    return 1;
}

// branch 
int check_branch( char name[max_arr_size] ) 
{
    char line[max_arr_size] ;
    FILE * file = fopen(".pro\\commits\\branches.txt" , "r") ;
    while(fgets(line , max_arr_size , file )) {
        if(line[strlen(line)-1] == '\n' ) line[strlen(line)-1] = '\0' ;
        if( strcmp(line,name) == 0 ) {
            return 1;
        }
    }
    return 0 ;
}
int branch( char name[max_arr_size] ) 
{
    if (check_branch(name) ) {
        fprintf(stderr , "branch is already exists\n") ;
        return 1;
    }
    check_pro_made(&find) ;
    chdir(".pro\\commits") ;
    mkdir(name) ;
    chdir(name) ;
    FILE * y = fopen("head_id.txt" , "w") ;
    char cmd[max_arr_size] ;
    int last_commit ;
    chdir("..") ;
    FILE * file = fopen("last_commit.txt" , "r" ) ;
    chdir(name) ;
    fscanf(file , "%d" , &last_commit ) ;
    fclose(file) ;
    fprintf(y , "%d" , last_commit ) ;
    fclose(y) ;
    char id[5] ;
    sprintf(id , "%d" , last_commit) ;
    mkdir(id) ;
    chdir("..") ;
    snprintf(cmd , max_arr_size , "xcopy all_commits\\%d %s\\%s /E" , last_commit  , name , id ) ;
    system(cmd) ;
    FILE * f = fopen("branches.txt" , "a" ) ;
    fprintf(f , "%s\n" , name ) ;
    fclose(f) ;
    FILE * fi = fopen("branch.txt" , "w" ) ;    // ????
    fprintf(fi , "%s" , name ) ;
    fclose(fi) ;
    return 0;
}
int show_branch()
{
    FILE * file = fopen(".pro\\commits\\branches.txt" , "r" ) ;
    char line[max_arr_size] ;
    while (fgets(line , max_arr_size , file) ){
        fprintf(stdout , "%s" , line ) ;
    }
    return 0;
}

// checkout
int check_head()
{
    FILE * file = fopen(".pro\\commits\\is_head.txt" , "r" ) ;
    int a ;
    fscanf(file , "%d" ,&a ) ;
    return a-1 ;
}
int id_checkout( char id[max_arr_size] )
{
    char cmd[max_arr_size] ;
    chdir(pro_location) ;
    snprintf(cmd , max_arr_size , "xcopy .pro\\commits\\all_commits\\%s\\files %s /E /Y" , id , pro_location ) ;
    system(cmd) ;
    FILE * file = fopen(".pro\\commits\\is_head.txt" , "w" ) ;
    fprintf(file , "0" ) ;
    fclose(file) ;
    return 0;
}
int branch_checkou( char name[max_arr_size] )
{
    char id[max_arr_size] ;
    chdir(pro_location) ;
    chdir(".pro\\commits") ;
    chdir(name) ;
    FILE * file = fopen("head_id.txt" , "r") ;
    fscanf(file , "%s" , id ) ;
    fclose(file) ;
    id_checkout( id ) ;
    chdir("..") ;
    FILE * file1 = fopen("is_head.txt" , "w" ) ;
    fprintf(file1 , "1" ) ;
    fclose(file1) ;
    return 0;
}
int go_to_head()
{
    char branch[max_arr_size] ;
    chdir(pro_location) ;
    FILE * file = fopen(".pro\\commits\\branch.txt" , "r" ) ;
    fscanf(file , "%s" , branch ) ;
    fclose(file) ;
    branch_checkou( branch ) ;
    return 0;
}

// tag 
int tag(char name[max_arr_size] , char mass[max_arr_size] , char id[max_arr_size] ) 
{
    chdir(pro_location) ;
    char tag_id[max_arr_size] ;
    char branch[max_arr_size] ;
    if ( id == NULL ) {
        chdir(".pro\\commits") ;
        FILE * file = fopen("branch.txt" , "r" ) ;
        fscanf(file , "%s" , branch) ;
        fclose(file) ;
        chdir(branch) ;
        FILE * file1 = fopen("head_id.txt" , "r" ) ;
        fscanf(file1 , "%s" , tag_id ) ;
        fclose(file1) ;
    } else {
        strcpy(tag_id , id) ;
    } 
    chdir("..\\..") ;
    chdir("tag") ;
    if( mkdir(name) == -1 ) {
        fprintf(stderr , "tag is already exists\n") ;
        return 1;
    } 
    chdir(name) ;
    FILE * f1 = fopen("v.txt" , "w") ;
    fprintf(f1 , "%s" , name) ;
    fclose(f1) ;
    FILE * f2 = fopen("id.txt" , "w") ;
    fprintf(f2 , "%s" , tag_id) ;
    fclose(f2) ;
    FILE * f3 = fopen("who.txt" , "w") ;
    char file_add[max_arr_size] ;
    snprintf(file_add , max_arr_size , "%s\\.pro\\config\\user_local_name.txt" , pro_location ) ;
    FILE * y = fopen(file_add , "r" ) ;
    char who[max_arr_size] ;
    fscanf(y , "%s" , who ) ;
    fclose(y) ;
    fprintf(f3 , "%s" , who ) ;
    fclose(f3) ;
    int trash ;
    char time[max_arr_size] ;
    FILE * f4 = fopen("time.txt" , "w") ;
    snprintf(file_add , max_arr_size , "%s\\.pro\\commits\\all_commits\\%s\\time.txt" , pro_location , tag_id ) ;
    FILE * y1 = fopen(file_add , "r" ) ;
    fscanf(y1 , "%d\n%[^\n]s" , &trash , time ) ;
    fclose(y1) ;
    fprintf(f4 , "%s" , time ) ;
    fclose(f4) ;
    FILE * f5 = fopen("massage.txt" , "w" ) ;
    if ( mass == NULL ) {
        fprintf(f5 , "< tag don't have any massages >" ) ;
    } else {
        fprintf(f5 , "%s" , mass ) ;
    }
    fclose(f5) ;
    chdir("..") ;
    FILE * last = fopen("last_tag_name.txt" , "w" ) ;
    fprintf(last , "%s" , name ) ;
    fclose(last) ;

    return 0;
}
int del_last_tag( char name[max_arr_size] )
{
    chdir(pro_location) ;
    chdir(".pro\\tag") ;
    char cmd[max_arr_size] ;
    snprintf(cmd , max_arr_size , "rd %s /Q /S" , name ) ;
    system(cmd) ;
    return 0 ;
}
int all_tag()
{
    chdir(pro_location) ;
    chdir(".pro\\tag") ;
    DIR * dir = opendir(".") ;
    struct dirent * entry ;
    while ( (entry = readdir(dir)) != NULL ) {
        if ( strcmp( entry->d_name , "last_tag_name.txt" )  && strcmp( entry->d_name , "." ) && strcmp( entry->d_name , ".." ) ) {
            fprintf(stdout , "%s\n" , entry->d_name ) ;
        }
    }
    return 0;
}
int tag_show( char name[max_arr_size] )
{
    char str[max_arr_size] ;
    chdir(pro_location) ;
    chdir(".pro\\tag") ;
    chdir(name) ;
    FILE * f1 = fopen("v.txt" , "r") ;
    fscanf(f1 , "%s" , str ) ;
    fprintf(stdout , "%s\n" , str) ;
    fclose(f1) ;
    FILE * f2 = fopen("id.txt" , "r") ;
    fscanf(f2 , "%s" , str ) ;
    fprintf(stdout , "%s\n" , str) ;
    fclose(f2) ;
    FILE * f3 = fopen("who.txt" , "r") ;
    fscanf(f3 , "%s" , str ) ;
    fprintf(stdout , "%s\n" , str) ;
    fclose(f3) ;
    FILE * f4 = fopen("time.txt" , "r") ;
    fscanf(f4 , "%[^\n]s" , str ) ;
    fprintf(stdout , "%s\n" , str) ;
    fclose(f4) ;
    FILE * f5 = fopen("massage.txt" , "r") ;
    fscanf(f5 , "%[^\n]s" , str ) ;
    fprintf(stdout , "%s\n" , str) ;
    fclose(f5) ;
    return 0 ;
}

// grep
int grep(char file[max_arr_size] , char word[max_arr_size] , int mode) 
{
    int n = 0 ;
    FILE * filee = fopen(file , "r" ) ;
    char line[max_arr_size] ;
    while ( fgets(line , max_arr_size , filee) ) {
        n++ ;
        if ( strstr(line,word)) {
            fprintf(stdout , "%s" , line) ;
            if(mode) printf("%d\n" , n) ;
        }
    }
    fclose(filee) ;
    return 0;
}

// pre_commit
int checkTodoInFile(const char *filename)
 {
    const char *extension = strrchr(filename, '.');
    if (extension == NULL) {
        return 0; 
    }
    char lowercaseExtension[10];
    int i;
    for (i = 0; i < 10 && extension[i] != '\0'; i++) {
        lowercaseExtension[i] = tolower(extension[i]);
    }
    lowercaseExtension[i] = '\0';
    if (strcmp(lowercaseExtension, ".c") == 0 || strcmp(lowercaseExtension, ".cpp") == 0 || strcmp(lowercaseExtension, ".txt") == 0) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return -1; 
        }
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strstr(buffer, "todo") != NULL || strstr(buffer, "TODO") != NULL) {
                fclose(file);
                return 1; 
            }
        }
        fclose(file);
        return -1;
    }
    return 0; 
}
int todo(char file[max_arr_size] ) 
{
    int result = checkTodoInFile(file) ;

    if( result == 1 ) {
        printf("%20s\n" , "FAILED" ) ;
    } else if ( result == -1 ) {
        printf("%20s\n" , "PASSED" ) ;
    } else {
        printf("%20s\n" , "SKIPPED" ) ;
    }
    return 0;
}
int checkTrailingWhitespace(const char *filename) { 
    const char *extension = strrchr(filename, '.');
    if (extension == NULL) {
        return 0; 
    }
    char lowercaseExtension[10];
    int i;
    for (i = 0; i < 10 && extension[i] != '\0'; i++) {
        lowercaseExtension[i] = tolower(extension[i]);
    }
    lowercaseExtension[i] = '\0';
    if (strcmp(lowercaseExtension, ".c") == 0 || strcmp(lowercaseExtension, ".cpp") == 0 || strcmp(lowercaseExtension, ".txt") == 0) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return -1; 
        }
        fseek(file, -1, SEEK_END); 
        int lastChar = fgetc(file);
        fclose(file);
        if (lastChar == ' ' || lastChar == '\t' || lastChar == '\n') {
            return 1; 
        } else {
            return -1; 
        }
    }
    return 0; 
}
int eoof( char file[max_arr_size] )
{
    int result = checkTrailingWhitespace(file) ;

    if( result == 1 ) {
        printf("%20s\n" , "FAILED" ) ;
    } else if ( result == -1 ) {
        printf("%20s\n" , "PASSED" ) ;
    } else {
        printf("%20s\n" , "SKIPPED" ) ;
    }
    return 0;
}
int checkBalance(const char *filename) {
    const char *extension = strrchr(filename, '.');
    if (extension == NULL) {
        return 0; 
    }
    char lowercaseExtension[10];
    int i;
    for (i = 0; i < 10 && extension[i] != '\0'; i++) {
        lowercaseExtension[i] = tolower(extension[i]);
    }
    lowercaseExtension[i] = '\0';
    if (strcmp(lowercaseExtension, ".c") == 0 || strcmp(lowercaseExtension, ".cpp") == 0 || strcmp(lowercaseExtension, ".txt") == 0) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return -1; 
        }
        int parenthesesCount = 0;
        int curlyBracesCount = 0;
        int squareBracketsCount = 0;
        int c;
        while ((c = fgetc(file)) != EOF) {
            switch (c) {
                case '(':
                    parenthesesCount++;
                    break;
                case ')':
                    parenthesesCount--;
                    break;
                case '{':
                    curlyBracesCount++;
                    break;
                case '}':
                    curlyBracesCount--;
                    break;
                case '[':
                    squareBracketsCount++;
                    break;
                case ']':
                    squareBracketsCount--;
                    break;
            }
        }
    fclose(file);
    if (parenthesesCount == 0 && curlyBracesCount == 0 && squareBracketsCount == 0) {
        return -1; 
    } else {
        return 1; 
    }
    } else return 0;
}
int balance( char file[max_arr_size] )
{
    int result = checkBalance(file) ;

    if( result == 1 ) {
        printf("%20s\n" , "FAILED" ) ;
    } else if ( result == -1 ) {
        printf("%20s\n" , "PASSED" ) ;
    } else {
        printf("%20s\n" , "SKIPPED" ) ;
    }
    return 0;
}
int checkFileFormatAndSize(const char *filename) {
    const char *extension = strrchr(filename, '.');
    if (extension == NULL) {
        return 0; 
    }
    char lowercaseExtension[10];
    int i;
    for (i = 0; i < 10 && extension[i] != '\0'; i++) {
        lowercaseExtension[i] = tolower(extension[i]);
    }
    lowercaseExtension[i] = '\0';
    if (strcmp(lowercaseExtension, ".txt") == 0 || strcmp(lowercaseExtension, ".c") == 0 || strcmp(lowercaseExtension, ".cpp") == 0) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file");
            return -1; 
        }
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fclose(file);
        if (fileSize > 20000) {
            return 1;
        } else {
            return -1;
        }
    } else {
        return 0; 
    }
}
int limit( char file[max_arr_size] ) 
{
    int result = checkFileFormatAndSize(file) ;

    if( result == 1 ) {
        printf("%20s\n" , "FAILED" ) ;
    } else if ( result == -1 ) {
        printf("%20s\n" , "PASSED" ) ;
    } else {
        printf("%20s\n" , "SKIPPED" ) ;
    }
    return 0;
}
int checkFileSize(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1 ; 
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);

    if (fileSize > 5 * 1024 * 1024) { 
        return 1; 
    } else {
        return -1; 
    }
}
int size( char file[max_arr_size] ) 
{
    int result = checkFileSize(file) ;

    if( result == 1 ) {
        printf("%20s\n" , "FAILED" ) ;
    } else if ( result == -1 ) {
        printf("%20s\n" , "PASSED" ) ;
    }
    return 0;
}
int can_commit()
{
    chdir(pro_location) ;
    FILE * file = fopen(".pro\\pre_commits\\is_bad.txt" , "r" ) ;
    int a ;
    fscanf(file , "%d" , &a ) ;
    fclose(file) ;
    return a ;
}
int chop_hooks()
{
    chdir(pro_location) ;
    chdir(".pro\\pre_commits") ;
    DIR * dir = opendir(".") ;
    struct dirent * entry ;
    while ( (entry = readdir(dir)) != NULL ) {
        if ( strcmp(entry->d_name , ".") && strcmp(entry->d_name , "..") ) {
            char * tok = strtok(entry->d_name , "." ) ;
            printf("%s\n" , tok ) ;
        }
    }
    return 0;
}
int chop_applied()
{
    chdir(pro_location) ;
    chdir(".pro\\pre_commits") ;
    DIR * dir = opendir(".") ;
    struct dirent * entry ;
    while ( (entry = readdir(dir)) != NULL ) {
        if ( strcmp(entry->d_name , ".") && strcmp(entry->d_name , "..") ) {
            FILE * file = fopen(entry->d_name , "r" ) ;
            int a ;
            fscanf(file , "%d" , & a ) ;
            if (a) {
                char * tok = strtok(entry->d_name , "." ) ;
                printf("%s\n" , tok ) ;
            }
            fclose(file) ;
        }
    }
    return 0;
}
int add_hook( char hook_id[max_arr_size] , int mode ) 
{
    chdir(pro_location) ;
    chdir(".pro\\pre_commits") ;
    strcat(hook_id , ".txt") ;
    FILE * file = fopen(hook_id , "w") ;
    if ( mode ) fprintf(file , "1" ) ;
    else fprintf(file , "0" ) ;
    fclose(file) ;
    return 0;
}
int one_pre_commits(char file[max_arr_size] )
{
    int a ;
    FILE * f1 = fopen("..\\..\\pre_commits\\todo_check.txt" , "r" ) ;
    fscanf(f1 , "%d" , &a) ;
    fclose(f1) ;
    fprintf(stdout , "%s\n" , file ) ;
    if(a) {
        printf("todo_check") ;
        todo(file) ;
        } 
    FILE * f2 = fopen("..\\..\\pre_commits\\eof_blank_space.txt" , "r" ) ;
    fscanf(f2 , "%d" , &a) ;
    fclose(f2) ;
    if(a) {
        printf("eof_blank_space") ;
        eoof(file) ;
    }
    FILE * f3 = fopen("..\\..\\pre_commits\\balance_braces.txt" , "r" ) ;
    fscanf(f3 , "%d" , &a) ;
    fclose(f3) ;
    if(a) {
        printf("balance_braces") ;
        balance(file) ;
    }
    FILE * f4 = fopen("..\\..\\pre_commits\\character_limit.txt" , "r" ) ;
    fscanf(f4 , "%d" , &a) ;
    fclose(f4) ;
    if(a) {
        printf("character_limit") ;
        limit(file) ;
    }
    FILE * f5 = fopen("..\\..\\pre_commits\\file_size_check.txt" , "r" ) ;
    fscanf(f5 , "%d" , &a) ;
    fclose(f5) ;
    if(a) {
        printf("file_size_check") ;
        size(file) ;
    }
    return 0;
}
int all_pre_commits()
{
    chdir(pro_location) ;
    chdir(".pro\\staged_files\\files") ;
    DIR * dir = opendir(".") ;
    struct dirent * entry ;
    while ( (entry = readdir(dir)) != NULL ) {
        if ( strcmp(entry->d_name , ".") && strcmp(entry->d_name , "..") ) {
            one_pre_commits(entry->d_name) ;
        }
    }
    return 0;
}

int main(int argc , char *argv[])
{
    if ( argc < 2 ) {
        fprintf(stdout , "please enter a valid command" ) ;
        return 1;
    }

    check_pro_app_exists() ;

    if ( strcmp(argv[1] , "init") == 0 ) {      //  init 
        init() ;
    } else if ( strcmp(argv[1] , "config" ) == 0 ) {   // config
        if ( strcmp( argv[2] , "-global") == 0 ) {
            if ( argv[3][0] == 'u' ) {
                global_ca( argv[3] , argv[4] ) ;
            } else if ( argv[3][0] == 'a' ) {   // for alias

            }
        } else if ( strcmp(argv[2] , "-global") != 0 ) {
            if ( argv[3][0] == 'u' ) {
                local_ca( argv[2] , argv[3] ) ;
            } else if ( argv[3][0] == 'a' ) {
                
            }
        } 
    } else if ( strcmp(argv[1] , "add" ) == 0 ) {  // add
        char first_add_add[max_arr_size] ;
        getcwd(first_add_add , sizeof(first_add_add) ) ;
        bool is_pro_exist = false ;
        check_pro_made(&is_pro_exist) ;
        if ( !is_pro_exist ) {
            fprintf(stderr , "you don't have any new project" ) ; 
            return 1;
        } else if ( strcmp(argv[2] , "-f" ) == 0 ) {
            for ( int i = 3 ; i < argc ; i++ ) {
                add_one_file_or_dir( argv[i] , first_add_add ) ;
            }
        } else if ( strcmp(argv[2] , "-n" ) == 0 ) {
            int depth = argv[3][0] - '0' ;
            chdir( first_add_add ) ;
            search_is_staged( depth ) ;
        // } else if ( strstr( argv[2] , "*" ) ) {
        //     chdir( first_add_add ) ;
        //     wildcard_add( argv[2] ) ;
        } else if ( strcmp(argv[2] , "-redo") == 0 ) {
            redo_add() ;
        } else {  // so it's a normal add
            add_one_file_or_dir( argv[2] , first_add_add ) ;
        }
    } else if ( strcmp(argv[1] , "reset" ) == 0 ) {
        char first_add_add[max_arr_size] ;
        getcwd(first_add_add , sizeof(first_add_add) ) ;
        bool is_pro_exist = false ;
        check_pro_made(&is_pro_exist) ;
        if ( !is_pro_exist ) {
            fprintf(stderr , "you don't have any new project" ) ; 
            return 1;
        } else if ( strcmp(argv[2] , "-f" ) == 0 ) {
            for ( int i = 3 ; i < argc ; i++ ) {
                reset_one_file_or_dir( argv[i] , first_add_add ) ;
            }
        } else if ( strcmp(argv[2] , "-undo" ) == 0 ) {
            undo_reset() ;
        // } else if ( strstr(argv[2] , "*" ) ) {  // به صورت خودکار در ویندوز کار میکنه ولی من مینویسمش
        //     chdir(first_add_add) ;
        //     wildcard_reset( argv[2] ) ;
        } else { // it is a normal reset
            reset_one_file_or_dir( argv[2] , first_add_add ) ;
        }
    } else if ( strcmp(argv[1] , "commit" ) == 0 ) {
        check_pro_made(&find) ;
        if ( strcmp(argv[2] , "-m" ) == 0 ) {
            if (argc != 4) {
                fprintf(stderr , "commit with no massage or wrong massage\n") ;
                return 1;
            }
            commit( argv[3] ) ;
        } else if ( strcmp(argv[2] , "-s" ) == 0 ) {
            if (argc != 4) {
                fprintf(stderr , "commit with no massage or wrong massage\n") ;
                return 1;
            }
            shortcut_commit( argv[3] ) ;
        }
    } else if ( strcmp(argv[1] , "set") == 0 ) {
        set( argv[3] , argv[4] ) ;
    } else if ( strcmp(argv[1] , "replace") == 0 ) {
        replace( argv[3] , argv[4] ) ;
    } else if ( strcmp(argv[1] , "remove") == 0 ) {
        remmove( argv[3] ) ;
    } else if ( strcmp(argv[1] , "log" ) == 0 ) {
        if ( argc == 2 ) { // it is a normal log
            show_n(-1) ;
        } else if ( strcmp(argv[2] , "-n") == 0 ) {
            int n ;
            sscanf(argv[3] , "%d" , &n ) ;
            show_n(n) ;
        } else if ( strcmp(argv[2] , "-branch") == 0 ) {
            check_log( argv[3] , branch_check ) ;
        } else if ( strcmp(argv[2] , "-author") == 0 ) {
            check_log( argv[3] , author_check ) ;
        } else if ( strcmp(argv[2] , "-search") == 0 && argc == 4 ) {
            check_log( argv[3] , massage_check ) ;
        } else if ( strcmp(argv[2] , "-search") == 0 && argc > 4 ) {
            for ( int i = 3 ; i < argc ; i++ ) {
                check_log( argv[i] , massage_check ) ;
            }
        } else if ( strcmp(argv[2] , "-since") == 0 ) {
            long long int t ;
            sscanf(argv[3] , "%lld" , &t ) ;
            time_log(t ,  1) ;
        } else if ( strcmp(argv[2] , "-befor") == 0 ) {
            long long int t ;
            sscanf(argv[3] , "%lld" , &t ) ;
            time_log(t , -1) ;
        }
    } else if ( strcmp(argv[1] , "branch" ) == 0 ) {
        if (argc == 3) branch( argv[2] ) ;
        else show_branch() ;
    } else if ( strcmp(argv[1] , "checkout" ) == 0 ) {
        check_pro_made(&find) ;
        if ( argv[2][0] <= '9' && argv[2][0] >= '0' ) id_checkout( argv[2] ) ;
        else if ( strcmp( argv[2] , "HEAD") == 0 ) go_to_head() ;
        else branch_checkou( argv[2] ) ;
    } else if ( strcmp(argv[1] , "tag" ) == 0 ) { 
        check_pro_made(&find) ;
        if ( argc == 2 ) {
            all_tag() ;
        } else if ( strcmp(argv[2] , "-a") == 0 ) {
            char* id = NULL ;
            char * mass = NULL ;
            int mode = 0 ;
            for ( int i = 4 ; i < argc ; i++ ) {
                if (strcmp(argv[i] , "-m") == 0 ) {
                    mass = malloc(max_arr_size) ;
                    strcpy(mass , argv[i+1]) ;
                }
                if (strcmp(argv[i] , "-c") == 0 ) {
                    id = malloc(max_arr_size) ;
                    strcpy(id , argv[i+1]) ;
                }
                if (strcmp(argv[i] , "-f") == 0 ) mode = 1 ;
            }
            if (mode) del_last_tag( argv[3] ) ;
            tag(argv[3] , mass , id) ;
        } else {
            tag_show( argv[2] ) ;
        }
    } else if ( strcmp(argv[1] , "grep") == 0) {
        check_pro_made(&find) ;
        int mode = 0 ;
        if ( argc == 7 && strcmp(argv[6] , "-n" ) == 0 ) mode = 1 ;
        grep( argv[3] , argv[5] , mode ) ;
    } else if ( strcmp(argv[1] , "pre_commit") == 0 ) {
        check_pro_made(&find) ;
        if ( argc == 4 && strcmp(argv[2],"hooks") == 0 && strcmp(argv[3],"list" ) == 0 ) {
            chop_hooks() ;
        } else if ( argc == 4 && strcmp(argv[2],"applied") == 0 && strcmp(argv[3],"hooks" ) == 0 ) {
            chop_applied() ;
        } else if ( argc == 5 && strcmp(argv[3],"hook" ) == 0 ) {
            int mode = 0 ;
            if ( strcmp(argv[2],"add") == 0 ) mode = 1 ;
            add_hook( argv[4] , mode ) ;
        } else if (argc == 2) {
            all_pre_commits() ;
        } else {
            chdir(pro_location) ;
            chdir(".pro\\staged_files\\files") ;
            for ( int i = 3 ; i < argc ; i++ ) {
                one_pre_commits( argv[i] ) ;
            }
        }
    } else {  // error
        fprintf(stderr , "please enter a valid command\n") ;
    }
    return 0;
}