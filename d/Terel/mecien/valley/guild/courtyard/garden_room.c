inherit "/std/room";
inherit "/d/Gondor/common/lib/herbsearch.c";
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

string *herb_list;

create_room(){

set_short("Garden");
set_long("This is a beautiful garden.\n");

add_item("earth", "It is rich and smells very strong.\n");
add_item("ground", "The earth here is rich, covered with many plants.\n");
 add_item("plants", "They are many varieties.\n");

   add_prop(OBJ_I_SEARCH_TIME, 5);
  add_prop(OBJ_S_SEARCH_FUN, "herb_search");

     get_herbs();

}

more_herbs(){
  set_alarm(1.0, -1.0, "get_herbs");
}

get_herbs(){

   seteuid(getuid());
   restore_object(HERBS);
   
    add_herb_file(herb_list[random(sizeof(herb_list))]);
   if(random(100) > 68){
    add_herb_file(herb_list[random(sizeof(herb_list))]);
   }
  if(random(470) > 2){
    add_herb_file(herb_list[random(sizeof(herb_list))]);
  }
   if(random(10) > 4){
    add_herb_file(herb_list[random(sizeof(herb_list))]);
  }
}

