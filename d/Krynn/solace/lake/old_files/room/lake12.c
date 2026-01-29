/* created by Splunge, modified by Aridor 10/94*/

#include "../local.h"
#include <ss_types.h>

inherit SOLACE_ROOM_BASE;

object *my_list = ({ });

void
reset_solace_room()
{
    my_list = ({ });
}

void
create_solace_room() 
{
    set_short("Lakeside Road.\nThere is one obvious exit: southeast");
    set_long("It has become totally silent, and you shiver with an " +
	     "unearthly chill. Even a highly lauded adventurer like " +
	     "yourself cannot suppress the feeling of horror you are now " +
	     "experiencing. It is still daylight. However, there is no more " +
	     "light here in the forest than if you were in total blackness " +
	     "with a candle. You can see almost nothing now. You can't even " +
	     "find the way back where you came from! The only direction you " +
	     "might have a chance to go into is southeast.\n" +
	     "There is one obvious exit: southeast.\n");
    
    add_prop(OBJ_S_SEARCH_FUN,"search");
    add_item(({"foliage","trees","forest"}),
	     "You cannot see anything very well at all. It feels leafy, " +
	     "though.\n");
    set_noshow_obvious(1);
    add_exit(ROOM + "scout1","west","@@search_first_but_still_closed",3);
    add_exit(ROOM + "lake10","southeast",0,4);
}

mixed
search(object player, string str)
{    
    int diffi;
    if (str != "here" && str != "forest" &&
	str != "foliage" && str != "ground")
      return 0;
    diffi = random(20) + 20; 
    if (TP->query_skill(SS_TRACKING) < diffi )
      return 0;
    
    if (member_array(player,my_list) == -1)
      my_list += ({ player });
    
    return "You find a few tracks leading west. You cannot, however, " +
      "determine what sort of animal made them.\n";
}

int
search_first_but_still_closed()
{
    if (member_array(TP,my_list) != -1)
      {
	  write("You cannot go this way yet, I'm afraid.\n");
	  return 1; 
	  /* should be return 0; if open*/
      }
    write("There is no obvious exit west.\n");
    return 1;
}
