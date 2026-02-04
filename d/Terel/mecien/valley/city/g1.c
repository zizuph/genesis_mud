/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
* forest_room.c
*
* A generic silver forest room.  All the silver forest rooms should inherit
* this file.
*/

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

object mon;


#define MONSTER_DIR SILVER_DIR + "monster/"

#define PATH "/d/Terel/mecien/valley/city/"

#include "/d/Terel/include/herbsearch.h"
/*
* Function name: query_herb_list
* Description:   list of available herbs.  Those inappropriate for the
*                cold climate of the silver forest are removed from the
*                master list.
* Returns:       the list of herbs in an array of strings.

*/
public string*
query_herb_list()
{
   return ::query_herb_list() -
   ({"basil", "clove", "culkas", "curugwath", "dill", "fennel",
         "garlic", "ginger", "laurel", "majoram", "morgurth", "red_pepper",
         "rosemary", "saffron", "sage", "savory", "tarragon", "thyme",
         "tyelka"});
}

reset_room(){
if(mon) return 0;
   mon = clone_object(PATH + "monk");
   mon->move(TO);
}


/*
* Function name: create_room
* Description:   Default constructor
*/
public void
create_room()
{
   string *herb_list;
   
   
   set_short("Monastery Garden");
   set_long(
      "Amazing in its elegance, this small garden rests peacefully in " +
      "the center of a stone courtyard. All around, great gothic walls rise " +
      "to enclose this place in solitude. The variety of plants is " +
      "spectacular, many being rare and wonderful, obviously cultivated " +
      "by masters of horticulture.\n"
   );
   OUTSIDE;
   
   add_item("garden", "It is a wondrful garden of elegance.\n");
   add_item("walls", "They enclose the garden with their mighty stones.\n");
  add_item("plants", "There are so many differing types. Flowers, trimmed bushes, orchids, " +
"shrubs, little trees and vines.\n");
   add_item("courtyard", "This area seems to be a courtyard " +
"that is made into a beautiful garden.\n");
   add_prop(OBJ_I_SEARCH_TIME, 2);
   add_prop(OBJ_S_SEARCH_FUN, "herb_search");
   
   herb_list = query_herb_list();
   set_search_places(({"garden", "ground"}));
   add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);
   add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);    
   add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);
   add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);

   add_exit(PATH + "monastery", "gate", "@@gate");
   reset_room();
}

gate(){
  TP->catch_msg("You open the gate and abandon the tranquility of the garden.\n");
  return 0;
}

