/* created by Aridor 12/20/93 */
/*
 * Modification history:
 *     Oct-2014: Modified to provide link area to Warden Swamp, where will
 *               be found the Cult of Chemosh guildhalls. (Gorboth)
 */

#include "../local.h"

inherit OUTSIDE_BASE;

/* Prototypes */
public int         check_exit();


void
create_splains_room()
{
    set_short("At the foot of the mountains");
    set_long("Impressive mountains rise up right to your west and northwest. " +
	     "The plains stretch out to your east as far as you can see. " +
	     "There is a river blocking your path southwest. The river " +
	     "is coming out of the narrow " +
	     "valley to your west and flowing onto the plains southeast. You are " +
	     "still on the plains, and the grass is just as dry as everywhere " +
	     "else, since the level of the river is just too low. Beyond the " +
	     "river to the south the plains continue, but you can't get across " +
	     "the river.\n");

    add_item(({"mountain","mountains","cliff"}),
	     "The mountains you see rise up direct in front of you to your west. " + 
	     "The mountain range runs in " +
	     "a southwest - northeastern direction. The cliff looks impossible to " +
	     "climb.\n");
    add_item( ({ "valley", "gorge", "west" }),
        "To the west of here, the river winds its way through a narrow"
      + " valley which cleaves the mountains, providing passage toward"
      + " Warden Swamp in the far western distance.\n");
    add_item( ({ "swamp", "warden swamp" }),
        "It is far to the west, beyond the mountain ranges which are"
      + " cloven by the river valley in that direction.\n");
    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the water level is much lower than the " +
	     "plains. The river comes from a narrow valley to your west and flows " +
	     "south of you and flows to the east onto the plains.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_cmd_item(({"mountain","cliff","mountains"}),"climb",
		 "You can't do that, it is just too steep.\n");
    add_cmd_item("river",({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");

    set_noshow_obvious(1);
    add_exit(ROOM + "mount4","northeast",0,3);
    add_exit(ROOM + "plain23","east",0,3);
    add_exit(ROOM + "river18","southeast",0,3);
    add_exit("/d/Krynn/guilds/necro/rooms/area_entrance", "west",
             check_exit, 0, 1);
}



/*
 * Function name:        check_exit
 * Description  :        see if we allow players to go here
 * Returns      :        int 0 - allow, 1 - prevent
 */
public int
check_exit()
{
    if (this_player()->query_wiz_level())
    {
        write("As a wizard, you go where you please, but this area is"
          + " not yet open to mortals.\n");
        return 0;
    }

    write("Debris choke the river valley, making passage impossible"
      + " until it has been cleared.\n");
    return 1;
} /* check_exit */
