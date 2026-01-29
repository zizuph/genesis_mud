 // Book5          (/d/Avenir/common/bazaar/Obj/books/book5.c)
 // creator(s):    Grace June 1995
 // last update:                                                            
// purpose:        Gives info on the 'codpiece' social status
//
 // note:                                                                   
 // bug(s):                                                                 
 // to-do:                                                                  
inherit "/std/book";                                                        
                                                                                                                                                       
#include <stdproperties.h>                                                  
                                                                            
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B5/"
                                                                            
create_book()                                                               
{                                                                           
   set_long("A small thin book with the figure of "+
      "a codpiece tooled into the leather cover. "+
      "Below the codpiece, printed in bold letters, is the title.\n");
   set_name("book");                                                        
   add_adj("small");
   add_adj("thin");
   set_short("small thin book");
   add_name("avenir_codpiece_book");
   add_item(({"letters", "print", "title"}),
      "The boldly printed lettering reads: "+
     "Codpieces: Notes on the Socio-sexual Heirarchy "+
     "of Sybarus.\n");
   set_max_pages(5);
                                                                            
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
      default:                             
         cat(BOOKPATH + "blank_page");     
   }                                       
   return;                                 
}                                          

