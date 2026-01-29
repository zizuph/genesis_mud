/*
 * * Lucius May 2009: /d/Terel/dark/ moved to Avenir except for
 * 	Terel side of the pool, moved to /d/Terel/mountains/
 * 	and exits updated.
 *
 *  Lilith, Jan 2022: Commented out the Terel vamp guild code.
 *                    Made it so the shadows exit works for anyone and changed
 *                    it so it leads to a spot closer to where this valley is
 *                    located.
 */
//#include "/d/Terel/guilds/vamp/guild.h"
//inherit "/d/Terel/guilds/vamp/room/vamp_room";
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#define TP  this_player()

object *gargoyl_arr;

reset_room()
{
   while(sizeof(gargoyl_arr) < 4)
   gargoyles();
}

gargoyles()
{
   object ob;
   ob = clone_object("/d/Terel/mountains/obj/gargoyle");
   ob->move_living("xx", this_object());
   
   if (!gargoyl_arr)
      gargoyl_arr = ({ ob });
   else
      gargoyl_arr += ({ ob });
}

string
do_shadows()
{
        TP->catch_msg("You step into the shadows.\n");
        say(QCTNAME(TP)+" steps into the shadows and disappears!\n");
        TP->move_living("M", "/d/Terel/mountains/pool", 0, 0);
    return "";
	
}

void
create_room()
{
   set_short("Dark Cavern");
   set_long(
      "A shadowed cavern, filled with columns of ice, sharp stalagmites\n"
      +"and stalactites. The rock seems to have a coal base, which mixes\n"
      +"with melted ice and creates puddles of fetid black water. A dark\n"
	  +"and dire wind blows by, screaming.\n"
   );
   add_item(({"shadow", "shadows"}), "The shadows fade to blackness.\n");
   add_cmd_item(({"shadow", "shadows"}), ({"enter", "walk into"}),
       "@@do_shadows"); 
   add_item(({"wind", "dark wind", "dire wind"}),
      "A wind screams from the shadows and through the cavern, pushing "
     +"you toward the entrance.\n");
   add_cmd_item(({"wind"}), ({"enter", "walk into"}), "@@do_shadows");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit("/d/Terel/mountains/pool","down",0);
   add_exit("/d/Terel/mountains/dcliff", "out", 0);
   reset_room();
}

