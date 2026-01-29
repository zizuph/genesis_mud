// Book6         (/d/Avenir/common/bazaar/Obj/books/book5.c)
// creator(s):   Lilith, March 1997
// revisions:                                                            
// purpose:      A first-person story about a Knight on the Holm
// note:                                                                   
// bug(s):                                                                 
// to-do:                                                                  

inherit "/std/book";                                                        
#include "/d/Avenir/common/bazaar/bazaar.h"
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B6/"

void                                                                            
create_book()                                                               
{                                                                           
    set_name("book");                                                        
    add_name(({"volume", "booklet"}));
    add_adj("slender");
    set_short("slender volume");
    set_long("A slender volume consisting of a few sheets of parch"+
        "ment sewn along the left side to form a booklet. In big, "+
        "block letters are printed the words: A Knight on the Holm.\n");

    set_max_pages(5);
                                                                            
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
        case 5:    cat(BOOKPATH + "p5");    break;
        default:   cat(BOOKPATH + "blank_page");     
    }                                       
    return;                                 
}                                          

