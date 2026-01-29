/* 
 * /d/Kalad/common/guilds/sh_walkers/rooms/tunnel2.c
 * Purpose    : A tunnel leading into the Shadow Walkers' guild hall.
 * Located    : 
 * Created By : Rico 23.May.97
 * Modified By: 
 */ 

#include "../defs.h"

inherit "/std/room.c";
inherit SHADOW + "std/room_std.c";

#define  POSSESSIVE(x)   x->query_possessive()

void
create_room()
{
   ::create_room();

   set_short("\nDark tunnel");
   set_long ("\n@@from_direction@@"+
      "This tunnel has a rather low ceiling and you need to "+
      "lean over slightly so you don't bump your head.  Flickering "+
      "shadows caused by the torches make you feel a touch uneasy.  "+
      "The tunnel leads upward into the gloomy darkness toward the "+
      "southwest, while also turning sharply to the northwest."+
      "\n\n");

   add_item(({ "dark", "darkness", "black", "blackness" }), 
      "\nAll you see is a big black void.  There isn't enough light "+
      "being cast by the torches to see very far at all.  The way "+
      "northwest seems to be relatively clear of obstacles, though.  "+
      "You should be able to traverse it without much difficulty.\n\n");
   add_item("tunnel", "\nIt is rather cramped, but still large enough "+
      "move around in.  It leads off into the darkness toward the "+
      "northwest and the southwest.\n\n");
   add_item("light", "\nThere is a light further down the tunnel.  It "+
      "begins to make you squint your eyes as you grow closer to it.  "+
      "There must be a well lit, rather large cavern of some kind at "+
      "its source.\n\n");

   /*  Take off 3 fatigue points for going sw (long, treacherous). */
   add_exit((SHADOW + "rooms/tunnel1"), "southwest", 0, 3);

   add_exit((SHADOW + "rooms/tunnel4"), "northwest", 0 , 3);

   room_add_object(SHADOW + "obj/obj_torch");
}

/*
 *  Function Name :  from_direction
 *  Description   :  To give a direction specific string in the room's
 *                   long descrip.
 *  Returns       :  Direction dependant strings.
 */
string
from_direction()
{
   object last = this_player()->query_prop(LIVE_O_LAST_ROOM);

   if(!last)
      return "";

   if(last == find_object(SHADOW + "rooms/tunnel2"))
   {
      return "It is relatively easy for you to make your way down the "+
         "gradual slope of the tunnel.  As you cover more distance, "+
         "you notice a light growing slightly brighter further down "+
         "the tunnel with every step you take.\n\n";
   }
   else if(last == find_object(SHADOW + "rooms/tunnel4"))
   {
      return "As you turn and make your way up the slow incline of the "+
         "tunnel, "+
         "the light of the cavern behind you slowly fades away.  You "+
         "are walking along with only the dim glow of the torches to "+
         "light your way.\n\n";
   }
   else 
   {
      return "";
   }
}

