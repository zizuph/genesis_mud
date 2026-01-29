 // Book4          (/d/Avenir/common/bazaar/Obj/books/book4.c)
 // creator(s):    Grace June 1995
 // last update:                                                            
 // purpose:       To provide mortals with background information
 //                on the Cult of the Hours
 // note:                                                                   
 // bug(s):                                                                 
 // to-do:                                                                  
inherit "/std/book";                                                        
                                                                                                                                                       
#include <stdproperties.h>                                                  
                                                                            
#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B4/"
                                                                            
create_book()                                                               
{                                                                           
   set_long("A heavy book with golden lettering.\n");
   set_name("book");     
   set_short("heavy book");                                                   
   add_adj("heavy");
   add_name("avenir_cult_of_the_hours_book");
   add_item(({"lettering", "inscription"}),"The golden letters read: " +
            "Sybarite Gods of the Hours.\n");
   set_max_pages(15);
                                                                            
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
      case 4 :                             
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
      case 13:
         cat(BOOKPATH + "p13");
         break;                            
      case 14 :
         cat(BOOKPATH + "p14");
         break;                            
      case 15:
         cat(BOOKPATH + "p15");
         break;                                               
      default:                             
         cat(BOOKPATH + "blank_page");     
   }                                       
   return;                                 
}                                          

