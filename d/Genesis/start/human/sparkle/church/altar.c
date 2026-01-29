/*
 * /d/Genesis/treacher/obj/altar.c
 * Created by: Treacher
 * Started: 1999-09-13
 */

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    set_name("altar");
    set_adj("marble");
    set_long("The altar is completely made of marble and its smooth "+
      "surface @@reflect_what@@ "+
      "It stands heavily on the marble floor, almost as if the "+ 
      "floor and altar was made out of the same piece of marble.\n");

    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_S_SEARCH_FUN, "search_altar");
    add_prop(OBJ_I_SEARCH_TIME, 5);
}

string 
search_altar(object player, string search_what)
{
    object altar_room = find_object("/d/Genesis/start/human/sparkle/church/altar_room.c");

    if(search_what != "altar")
	return "";

    if (altar_room->query_candle_status())
	return("The reflection from the candles is to bright, "+
	  "it's too hard to find anything.\n");
    else
	return("You found an inscription on the altar!\n");
}


string
reflect_what()
{
    int stat;
    object altar_room = find_object("/d/Genesis/start/human/sparkle/church/altar_room.c");

    if (stat = altar_room->query_candle_status())
	return "brightly reflects the light from the candles.";
    else
	return "softly refelects the surroundings.";
}













