// Ziggurat Fetish-shop (ZIG_RL3 + "fetish.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Ziggurat shop where players can buy various items.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;
inherit "/d/Avenir/inherit/shop";

#define STORE_ROOM   (ZIG_RL3 + "store_fetish")

public void
reset_room(void)
{
    fix_keeper();
}

public void
zig_room(void)
{
    set_short("fetish shop");
    set_long("@@my_long");

    set_maxlist(45);
    set_store_room(STORE_ROOM);
    set_keeper_file(ZIG_MON + "maddy");
    set_favoured_race(({"elf", "gnome"}));
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_money_greed_buy(50);

    add_exit("room3", "west", 0);
    add_exit(STORE_ROOM, "store", wiz_check, 0, 1);

    add_item(({"circle", "silver circle", "floor", "ground"}),
	"The floor is made of black stone, similar to the rest of the "+
	"Ziggurat, but much less polished than the corridor. Oddly, there "+
	"is an enormous circle carved into the stone and filled with silver "+
	"and nearly touching the walls of the shop.\n");

    add_item(({"walls", "north wall", "south wall", "stone wall", "panels",
	"oak panels", "shelves", "oak shelves", "ledge", "stone ledge"}),
	"The walls of this shop are made of black stone; however, the back "+
	"wall of the shop is covered in light oak panels, which match the "+
	"light oak rack running along the north wall. Along the south wall, "+
	"many stone torsos stand on a ledge carved out of the wall's black "+
	"stone.\n");

    add_item(({"counter", " enormous counter", "slab", "marble slab",
	"enormous marble slab", "black marble slab", "patterns", "marble",
	"work table", "scraps", "cloth", "enormous black marble slab"}),
	"In front of the black wall, an enormous slab of black marble "+
	"serves as a counter and a work table. The marble must have been "+
	"placed here as the room was built as there is no way it could "+
	"have been hauled in after. It is perfectly cut with smooth, polished "+
	"sides and right angles. Crimson veins run throughout the stone "+
	"making it vaguely look as though it were cracked and bleeding. On "+
	"top of the counter, several reed baskets are set out to display "+
	"small merchandise not suited to the rack or pegs. Beyond the "+
	"baskets, scraps of cloth and carefully cut patterns lie, waiting "+
	"to be assembled into a corset.\n");

    add_item(({"ceiling", "lanterns", "lamps", "lamp", "light", "glass lanterns"}),
	"The high ceiling of this shop is made of highly polished, black "+
	"stone. Several lanterns made of brass and colored glass hang "+
	"from it, lighting the shop with red and blue light.\n");

    /* special listing add_items */
    add_item(({"pegs", "back wall", "east wall"}), "@@view_pegs");
    add_item(({"rack", "racks", "garments", "oak rack", "wooden rack",
	"oak racks", "wooden racks"}), "@@view_rack");
    add_item(({"torsos", "stone torsos", "carved torsos", "carved stone torsos",
	"south wall"}), "@@view_torsos");
    add_item(({"cage", "cages", "large cage", "northeast cage",}),
	"@@view_cage");
    add_item(({"small merchandise", "baskets", "reed baskets",}),
	"@@view_baskets");
    add_item(({"merchandise","wares",}), "@@view_wares");

    fix_keeper();
    config_shop();
}

public string
my_long(void)
{
    object ob;
    string str = "This shop is cluttered with a strange mix of specialty "+
	"items set on display throughout the shop. The back wall is "+
	"paneled in white oak and covered with pegs, which display a mix "+
	"of wares. In front of the display, an enormous black marble "+
	"slab serves as a work table and display for baskets holding "+
	"small merchandise. Brass lamps with colored glass panes cast red "+
	"and blue light on assorted garments hanging on a long rack along "+
	"the north wall and a line of carved stone torsos along south wall "+
	"which hold the shapes of custom-made corsets on display.";

    if (objectp(ob = present("EN::Cage", get_store_object())))
    {
	str += " A large, empty cage is tucked in the corner, but "+
	    "seems much too big for a normal pet.";
    }

    return str + "\n";
}

/* Functions for listing what is for sale by examining displays. */

public string
view_pegs(void)
{
    write("The back wall is paneled with light oak wood and covered with "+
	"small pegs which hold a variety of wares which you make note of "+
	"as you examine them.\n\n");
    say(QCTNAME(TP) + " examines the back wall of the shop, making note of "+
	"the wares held on display by wooden pegs.\n");
    do_list("weapons");
    return "";
}

public string
view_rack(void)
{
    write("A wooden rack made of oak displays garments for sale, including:\n\n");
    say(QCTNAME(TP) + " examines the garments displayed on the oak rack.\n");
    do_list("stat::item");
    return "";
}

public string
view_torsos(void)
{
    write("Carved stone torsos stand upon a stone ledge carved out of "+
	"the glossy black stone of the south wall. The torsos are of "+
	"varying sizes and though not detailed, appear very feminine. They "+
	"serve to hold the shape of custom-made corsets until they are "+
	"purchased.\n\n");
    say(QCTNAME(TP) + " scans the south wall, examining the row of stone "+
	"torsos.\n");
    do_list("corsets");
    return "";
}

public string
view_baskets(void)
{
    write("You examine the reed baskets on the counter which nicely display "+
	"the smaller merchandise for sale.\n\n");
    say(QCTNAME(TP) + " peers into the small baskets on the oak counter.\n");
    do_list("basket::item");
    return "";
}

public string
view_cage(void)
{
    object ob;

    if (objectp(ob = present("EN::Cage", get_store_object())))
    {
	write(ob->long() + "You notice a small tag on one of the bars "+
	    "that denotes it is for sale.\n\n");
	say(QCTNAME(TP) +" examines the large cage tucked in the "+
	    "northeast corner.\n");
	do_list("cage");
    }
    else
    {
	write("You find no such cage.\n");
    }

    return "";
}

public string
view_wares(void)
{
    write("Specialty wares and peculiarities are displayed wall to wall in "+
	"this shop. You look around slowly to take them all in.\n\n");
    say(QCTNAME(TP) + " looks around slowly, examining the wares for sale.\n");
    do_list("all");
    return "";
}

/*
 * Function name: do_sell
 * Description:   Try to let the player sell the_item
 * Returns:       1 on sucess, 0 fail; should always fail.
 * Arguments:     str - string holding name of item, hopefully
 */
public int
do_sell(string str)
{
    if (keeper_speak("I only sell things, not buy them."))
	return 1;

    notify_fail("This shop only sells items, it doesn't buy them.\n");
    return 0;
}

/*
* Function name: do_buy
* Description:   Try to let the player buy the_item if not an infidel.
* Returns:       1 on sucess, 0 fail.
* Arguments:     str - string holding name of item, hopefully
*/
public int
do_buy(string str)
{
    if (!check_keeper())
	return 0;

    if (IS_INFIDEL(this_player()))
    {
	if (keeper_speak("I don't do business with criminals."))
	    return 1;

	notify_fail("This shop does not conduct business with criminals.\n");
	return 0;
    }

    return ::do_buy(str);
}

public void
init(void)
{
    ::init();
    init_shop();
}

/* Shop List customizations. */

public string
category(object ob)
{
    if (ob->id("rod") || ob->id("switch") || ob->id("flogger"))
	return "Rod";

    if (ob->id("paddle"))
	return "Paddle";

    if (ob->id("whip"))
	return "Whip";

    if (ob->id("corset"))
	return "Corset";

    if (ob->id("harness"))
	return "Harness";

    if (ob->id("feather"))
	return "Feather";

    if (ob->id("skirt"))
	return "Skirts";
}
