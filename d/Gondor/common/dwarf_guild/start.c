/*
 * /d/Gondor/common/dwarf_guild/start.c
 *
 * This room is the starting room of the dwarven race guild.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

void
create_room()
{
    set_short("the private cave of the " + DWARVEN_RACE_GUILD_NAME);

    set_long("This cave is not as large as some other caves in this " +
	"complex structure. It is used by the members of the " +
	DWARVEN_RACE_GUILD_NAME + " to rest after a long day of hard " +
	"labour or adventuring. On the floor you see various bunks and " +
	"blankets, allowing for you to start here. There are some stairs " +
	"leading up. To the west you find the post-office.\n");

#include "cavedesc.h" /* some add_items for the rocky cave ect. */

    remove_item("floor");
    add_item( ({ "floor", "ground" }),
	   "The floor is made of plain rock, just like the rest of these " +
	   "caves are hewn out of rock. On it you see some bunks and some " +
	   "blankets.\n");
    add_item( ({ "blanket", "blankets" }),
	   "On the floor you see several blankets. These blankets are " +
	   "rather thick and made of wool. They are probably very warm and " +
	   "they can be used by dwarves who sleep here.\n");
    add_item( ({ "bunk", "bunks", "mattress", "mattresses" }),
	   "Several mattresses are lying on the floor. They are made of " +
	   "straw and they are probably rather comfortable. Dwarves can use " +
	   "these bunks if they decide to rest and return to this exciting " +
	   "world later.\n");

    add_item( ({ "stair", "stairs" }),
	   "Some stairs are hewn out the solid rock. They lead up to the " +
	   "main hall of this guild complex.\n");

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "up");
    add_exit(DWARF_DIR + "post",  "west");

    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_NO_ATTACK,       1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}

void
init()
{
    ::init();

    /* A wizard will use the start command in the apprentice soul. */
    if (!(TP->query_wiz_level()))
    {
	add_action("do_start", "start");
    }
}

int
do_start(string str)
{
    object tp = TP;

    if (LOW(str) != "here")
    {
	NFN0("Start where? Here?");
    }

    if (!IS_MEMBER(tp))
    {
	NFN0("Only a member of the " + DWARVEN_RACE_GUILD_NAME +
	    " is allowed to start here.");
    }

    if (!(tp->set_default_start_location(MASTER)))
    {
	   write("For some reason you cannot start here. Please make a " +
	    "bugreport about this. This should not have happened.\n");
	   return 1;
    }

    write("From now on you will start in this cave if you enter the game.\n");
    return 1;
}
