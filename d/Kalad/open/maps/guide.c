/* Ashbless 10/93 */
/* modified by Antharanos */
   
inherit "/std/book";
#include "/d/Kalad/defs.h"

void
create_book()
{
   set_name("guidebook");
   add_name("guide");
   add_name("book");
   set_short("visitor's guidebook to Kalad");
   set_long("It is labeled 'A Comprehensive Guide to Kalad'.\n");
   
   set_max_pages(13);
}

varargs void
read_book_at_page(int which, string verb)
{
   switch(which)
   {
      case 1:
      write(
         "                     TABLE OF CONTENTS                     \n"+
         "___________________________________________________________\n"+
         "\n"+
         "   P.2     A GENERALIZED MAP OF THE CITY OF KABAL\n"+
         "\n"+
         "   P.3     A MAP OF KABAL AND THE SURROUNDING AREA\n"+
         "\n"+
         "   P.4-7   OVERVIEW OF THE CITY OF KABAL\n" +
         "\n"+
         "   P.8-9   CITY POLITICS IN KABAL\n"+
         "\n"+
         "   P.10    THE SEWERS OF KABAL\n"+
         "\n"+
         "   P.11    A MAP OF THE CENTRAL DISTRICT OF KABAL\n"+
         "\n"+ 
         "   P.12    MAP OF KABAL AREA (undetailed)\n" +
         "\n"+
         "   P.13    MORE DETIALED MAP OF THE KABAL AREA\n" +
         "");
      break;
      
      case 2:
      cat("/d/Kalad/open/maps/Kabal");
      break;
      
      case 3:
      cat("/d/Kalad/open/maps/Kabal_area");
      break;
      
      case 4:
      cat("/d/Kalad/open/KABAL.OVERVIEW",1,22);
      break;
      
      case 5:
      cat("/d/Kalad/open/KABAL.OVERVIEW",23,22);
      break;
      
      case 6:
      cat("/d/Kalad/open/KABAL.OVERVIEW",45,22);
      break;
      
      case 7:
      cat("/d/Kalad/open/KABAL.OVERVIEW",67,25);
      break;
      
      case 8:
      cat("/d/Kalad/open/CITY_POLITICS",1,24);
      break;
      
      case 9:
      cat("/d/Kalad/open/CITY_POLITICS",25,45);
      break;
      
      case 10:
      cat("/d/Kalad/open/SEWERS.README");
      break;
      
      case 11:
      cat("/d/Kalad/open/maps/central");
      break;
      case 12:
      cat("/d/Kalad/open/maps/Kabal_area2");
      break;
      
      case 13:
      cat("/d/Kalad/open/maps/WKalad");
      break;
      
   }
}

