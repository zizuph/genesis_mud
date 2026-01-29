inherit "/std/room";

#include "/d/Emerald/defs.h"

#include <options.h>

void
create_room()
{
	set_short("Honeymoon suite");
	set_long("   You have entered the Honeymoon suite.  Upon entering "+
		 "you can smell fresh flowers.  There is a tray of food on the table. "+
		 "There is a heart shaped bed in the center of the room. And "+
		 "a well lit fire going in the fireplace.  The room is a bit "+
		 "misty.  The mist is comming from the bathtub. There is a porch "+
		 "just outside the large window.\n\n");

	add_item("flowers", "There is a bouquet of wild roses sitting in a vase "+
		 "on the table.\n");
	add_item("vase", "The vase has a bouquet of wild roses in it.\n");
	add_item(({"tray", "food"}), "The tray of food contains an assortment "+
		 "of fruits, meats, and sweets.\n");
	add_item("bed", "@@bed_desc2@@");
	add_item(({"pillow", "pillows"}), "The pillows are red, soft with white "+
		 "lace around the edges. They are heart shaped.\n");
	add_item("fireplace", "The fireplace is glowing a firery orange, it seems "+
		 "to have just been lit and will not need tending for several hours.\n");
	add_item("mist", "The mist is comming up out of the water from the bath tub.\n");
	add_item(({"bath", "tub", "bathtub"}), "The bathtub has mist comming up out of "+
		 "it.  There is enough room in the tub for two persons.\n");
	add_item("porch", "The porch is made of ceder.  And blocks anyones view into "+
		 "the suite.\n");
	add_item("window", "When you look out the window you can see a swing on the "+
		 "porch.  The swing is built for two.\n");

	add_prop(ROOM_I_INSIDE, 1);

	add_exit(VILLAGE_DIR + "hotel/entrance", "north");
	add_exit(VILLAGE_DIR + "hotel/porch", "west");
}

/*
 * Function name: query_prevent_snoop
 * Description  : This function will prevent mortals from being snooped in
 *                this room by most wizards.
 * Returns      : int 1 - always.
 */
int
query_prevent_snoop()
{
	return 1;
}

void
init()
{
    ::init();

    add_action("do_emote", "emote");

    /* Invisible and hidden people should not be here. */
    if (this_player()->query_prop(OBJ_I_INVIS) ||
	this_player()->query_prop(OBJ_I_HIDE))
    {
	write("You walk out of the room again being invisible to some.\n");
	this_player()->move(VILLAGE_DIR + "hotel/entrance", 1);

	if (environment(this_player()) == this_object())
	{
	    write("Being persistant?\n");
	    this_player()->remove_object();
	}
    }	
}
int
do_emote(string arg)
{
    notify_fail("Emote what?\n");
    if (!arg)
	return 0;

    say(QCTNAME(this_player()) + " " + arg + "\n");
    if (this_player()->query_option(OPT_ECHO))
	write("You emote: " + this_player()->query_name() + " " + arg + "\n");
    else
	write("Ok.\n");
    return 1;
}
