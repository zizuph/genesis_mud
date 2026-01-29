/* This a secret passage leading from the Grunts guild to the cave entrance */
/* Coded due to lack of light in the rest of the caves by Tulix 1/4/1993    */
/* Recoded on 21/08/95 by Tulix III.                                        */
/* portal added by Fysix, should remain here until Emerald
 * opens again
 */

inherit "/std/room";

#include "default.h"
#include "../guild.h"


void
create_room()
{
    set_short("secret passage");
    set_long(

        "   You are in a small hole between a secret passage and a tunnel " +
        "leading up and out. The tunnel is blocked by a big pile of warm " +
        "ashes from a fire, but you could easily push your way up through " +
      "them.\n\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(THIS_DIR + "secret_passage1c", "down", 0, 1);
    add_exit("/d/Emerald/common/guild/aod/rooms/grunts_entrance", "up",
             "@@up_we_go", 1);


    add_item(({"walls","wall"}),
        "There are torches fixed on both walls of the cave. " +
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n");
    
    add_item(({"roof","ceiling"}),
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
        "The floor on which you are standing seems very firm, and is made " +
        "of volcanic rock.\n");

    add_item(({"torch","torches"}),
        "The torches are fixed firmly to the wall, and cannot be taken.\n");

}

void
init()
{
   ::init();
}

int
enter_portal(string str)
{
   notify_fail("Enter what?\n");
   
   if (!str) return 0;
   if ( (str!="portal") && (str!="dirty portal") &&
         (str!="small portal") ) return 0;
   
   write("You step through the small dirty portal ...\n\n");
   say(QCTNAME(this_player())+" steps through the small dirty "+
      "portal.\n");
   
   this_player()->move_living("X","/d/Emerald/lake/pier2",0,0);
   
   return 1;
}

public int
up_we_go()
{
    write("You push your way up through the ashes.\n");
    say(QCTNAME(this_player())+" pushes "+this_player()->query_possessive() +
        " way up through the ashes.\n");

    return 0;
}
