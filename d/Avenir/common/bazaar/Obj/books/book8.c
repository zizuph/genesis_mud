// creator(s):   Lilith, Agu 1999
// revisions:                                                            
// purpose:      An explanation of the Holm
// note:                                                                   
// bug(s):                                                                 
// to-do:                                                         

inherit "/std/book";                                                        
#include "/d/Avenir/common/bazaar/bazaar.h"
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B8/"

void                                                                            
create_book()                                                               
{                                                                           
    set_name("scroll");                                                       
    add_name(({"paper"}));
    add_adj(({"blood-red", "red", "blood"}));
    set_short("blood-red scroll");
    set_long("A scroll printed on paper lacquered red on one "+
        "side. It is rolled up and tied with a ribbon. Upon "+
        "the ribbon, in simple script, are imprinted the words: "+
        "Holm of the Icondite.\n");

    set_max_pages(2);
                                                                            
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_M_NO_SELL, 1);

    seteuid(getuid());                                                       
}                                                                           

/* Access for 3 wei, which equals 36 days */
void
do_holm()
{
    int i, wei;

    wei = ("/d/Avenir/inherit/avenir_time.c")->get_avenir_week() + 3;
    if (wei > 12)
        this_player()->set_skill(139001, 3);
    else
        this_player()->set_skill(139001, wei);
}


                                                                            
void                                                                        
read_book_at_page(int which)                                                
{                                                                           
    switch(which)                                                            
    {                                                                        
        case 1:    cat(BOOKPATH + "p1");    break;                                          
        case 2:    
        {
            cat(BOOKPATH + "p2");    
            do_holm();
        }  
        break;                            
        default:   cat(BOOKPATH + "p1");     
    }                                       
    return;                                 
}                                          

