// Book5          (/d/Avenir/common/bazaar/Obj/books/webcloth.c)
// creator(s):    Lilith Dec 1996
// last update:                                                            
// purpose:        Gives info on the webcloth, weavers, and webbers
//
// note:                                                                   
// bug(s):                                                                 
// to-do:                                                                  
inherit "/std/book";                                                        
                                                                                                                                                       
#include <stdproperties.h>                                                  
                                                                            
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/WEBCLOTH/"
                                                                            
create_book()                                                               
{                                                                           
    set_long("This small blue book has a webcloth cover. "+
        "A glittering spiral is affixed to it, and below "+
        "it, printed in flowery letters, is the title.\n");
    set_name("book");                                                        
    add_adj("webcloth");
    add_adj(({"blue", "small"}));
    set_short("blue webcloth book");
    add_name("avenir_webcloth_book");
    add_item(({"letters", "print", "title"}),
        "The flowery lettering reads: "+
        "WEBCLOTH, WEAVERS and WEBBERS: An Account of a Meeting "+
        "With a Weaver.\n");
    set_max_pages(12);
                                                                            
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,200);
    seteuid(getuid());                                                       
}                                                                           
                                                                            
void                                                                        
read_book_at_page(int which)                                                
{                                                                           
    switch(which)                                                            
    {                                                                        
        case 1:                                                                
          cat(BOOKPATH + "p1");                                              
          break;                                                             
        case 2:                              
          cat(BOOKPATH + "p2");             
          break;                            
        case 3:
          cat(BOOKPATH + "p3");
          break;
        case 4:
          cat(BOOKPATH + "p4");
          break;
        case 5:
          cat(BOOKPATH + "p5");
          break;
        case 6:
          cat(BOOKPATH + "p6");
          break;
        case 7:
          cat(BOOKPATH + "p7");
          break;
        case 8:
          cat(BOOKPATH + "p8");
          break;
        case 9:
          cat(BOOKPATH + "p9");
          break;
        case 10:
          cat(BOOKPATH + "p10");
          break;
        case 11:
          cat(BOOKPATH + "p11");
          break;
        case 12:
          cat(BOOKPATH + "p12");
          break;
        default:                             
          cat(BOOKPATH + "blank_page");     
   }                                       
   return;                                 
}                                          

