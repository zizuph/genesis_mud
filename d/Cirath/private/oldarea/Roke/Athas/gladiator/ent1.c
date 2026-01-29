inherit "/std/room";

#include <stdproperties.h>
#include "guild.h"

object brutus;

void reset_room();

void
create_room()
{
   set_short("Small sanctum");
   set_long(BSS("You have entered the inner sanctums of the "+
                "Gladiator guild, and you can see a threshold "+
                "leading west and a doorway leading south, back "+
                "into the entrance hall.\n"));

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 1);

   add_exit(GLAD_DIR+"hall1", "west", "@@west_block@@");
   add_exit(GLAD_DIR+"entrance","south",0);
   reset_room();
}

reset_room()
{
    if (!brutus)
    {
	brutus = clone_object(GLAD_DIR + "brutus");
	brutus->move(this_object());
	tell_room(this_object(),"A dwarf arrives.\n");
    }
}

west_block()
{
   if(!IS_MEMBER(this_player()))
   {
      write("You can't seem to get across the threshold.\n");
      return 1;
   }
   return 0;
}

