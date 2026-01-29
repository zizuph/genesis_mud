// creator(s):   Lilith, April 1997
// revisions:                                                            
// purpose:      A tragic tale about the Daughter of Azauph
// note:                                                                   
// bug(s):                                                                 
// to-do:                                                         

inherit "/std/book";                                                        
#include "/d/Avenir/common/bazaar/bazaar.h"
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B7/"

void                                                                            
create_book()                                                               
{                                                                           
    set_name("book");                                                        
    add_name(({"volume", "booklet"}));
    add_adj(({"saffron-yellow", "saffron", "yellow"}));
    set_short("saffron-yellow booklet");
    set_long("A booklet consisting of a few sheets of parch"+
        "ment sewn along the left side to form a booklet. The "+
        "pigskin cover has been dyed saffron-yellow. Upon it, "+
        "in big, block letters, are imprinted the words: "+
        "Tjana's Story.\n");

    set_max_pages(4);
                                                                            
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_M_NO_SELL, 1);

    seteuid(getuid());                                                       
}                                                                           
                                                                            
void                                                                        
read_book_at_page(int which)                                                
{                                                                           
    switch(which)                                                            
    {                                                                        
        case 1:    cat(BOOKPATH + "p1");    break;                                                             
        case 2:    cat(BOOKPATH + "p2");    break;                            
        case 3:    cat(BOOKPATH + "p3");    break;
        case 4:    cat(BOOKPATH + "p4");    break;
        default:   cat(BOOKPATH + "p1");     
    }                                       
    return;                                 
}                                          

