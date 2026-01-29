inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <macros.h>

 
create_room()
{
set_short("On the bottom of the pond");
set_long("You are swimming near the very bottom of the pond. \n" +
  "The water is rather dirty and opaque here and you can barely\n" +
  "see your hands. The bottom seems very soft and covered with\n"+
  "thick layer of ooze and litter.\n");
add_item("ooze","The dark green ooze looks slimey and disgusting.\n");
add_prop(OBJ_I_SEARCH_TIME,10);
add_prop(OBJ_S_SEARCH_FUN,"get_chain");
add_prop(ROOM_I_INSIDE,1);
add_exit(MICH_DIR +"pond","surface",0);


}

void
init()
{
    ::init();
   write("You manage to gobble up some of the air bubbles that float up from the bottom.\n");
}
get_chain(object player, string str)
{ object bracelet;
  if (str != "ooze") return "";
  if (!player->query_prop("_me_found_chain_"))
  { if (player->query_skill(110) > 10+random(10))
       {  bracelet = clone_object(MICH_DIR +"arm/chain");
          bracelet->move(player);
          player->add_prop("_me_found_chain_",1);
          say(QCTNAME(player)+" has found something!\n");
          return("You find a silver chain in the ooze!\n");
       }
  }
  return("You looked all over the sand and found nothing.\n");
}

