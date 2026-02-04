#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: Dorm Room
 * Minstrels may choose to start their characters here.
 * Cedric 1/93 with Jorl
 */

void
init()
{
    ::init();
    add_action("do_start_here", "start");
    add_action("do_start_here", "begin");
}

void
create_room()
{
    set_short("The Minstrel's Dormitory");
    set_long(BS("This luxurious hall seems very cozy and comfortable.  "
    + "You don't see any light source, yet a soft diffuse glow pervades "
    + "the room.  The lavishly thick rug immediately drains away the "
    + "weariness of the days travels.  High above you, the midnight-black "
    + "ceiling is painted with numerous stars, creating the illusion of a "
    + "moonless night.  "
    + "Lining the walls are a great number of canopied beds, a few with their "
    + "heavy curtains drawn.  A soothing lullaby is just barely audible over "
    + "the snores of some sleeping minstrel. There is a handsomely engraved "
    + "sign near the southern entrance. The post-office can be found to "
    + "the northwest and the conservatoire is to the south.\n"));
    
    add_item(({"rug", "carpet", "floor", "ground"}), BS("This elegant rug is "
    + "purple with gold accents.  It depicts scenes of a large troupe of bards "
    + "singing, playing, and dancing before a royal feast.  Though the carpet "
    + "must be quite old, nowhere do you perceive signs of wear.\n"));
    add_item(({"ceiling", "stars", "roof"}), BS("The high, vaulted ceiling was "
    + "designed to give the impression of a night sky.  You recognize some of "
    + "the constellations as Terellian.\n"));
    add_item("walls", BS("The plaster walls have been painted with a soothing "
    + "pastel blue.  You notice that they shimmer slightly.  You realize that "
    + "the walls are glowing softly with a magical light.\n"));
    add_item("sign", BS("Please respect the privacy of your colleagues. QUIET "
    + "HOURS OBSERVED AT ALL TIMES! "
    + "If you would like to begin your days here, simply express your wishes and "
    + "it will be done.\n"));
    add_cmd_item("sign", "read", BS("Please respect the privacy of your colleagues. QUIET "
    + "HOURS OBSERVED AT ALL TIMES! "
    + "If you would like to begin your days here, simply express your wishes and "
    + "it will be done.\n"));
    add_item(({"bed","beds"}), BS("You sit on the nearest bed to try it out. It appears to "
    + "to be an extremely comfy feather bed.  You can't wait to spend a night "
    + "here.\n"));
    
    set_noshow_obvious(1);

    add_exit(GUILD+"post", "northwest");
    add_exit(GUILD+"conservatoire", "south");
    add_prop(ROOM_I_INSIDE, 1);
}

int
do_start_here(string str)
{
    if (str!="here")
    {
	notify_fail("Start where? Here, perhaps?\n");
	return 0;
    }
    if (MEMBER(TP()))
    {
	TP()->set_default_start_location(GUILD+"dorm");
	TP()->catch_msg("You shall now begin each day anew in the comfort of our guild.\n");
    }
    else
	TP()->CM("Foolish one, only a Minstrel may begin each day here.\n");
    return 1;
}