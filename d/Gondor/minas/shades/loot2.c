/*
 *      /d/Gondor/minas/shades/loot2.c
 *
 *      Coded by Sithas
 *
 *      Modification log:
 *       3-mar-97, Olorin:      Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Shade;

public int	refuse_get();
public void	player_took_loot(string name);

static mapping	took_loot = ([]);
static int	hid_loot;

public void
create_gondor() 
{
    set_short("a room in the Shades' hideout");
    set_long(BSN("This room is very simple, it seems nothing more then a " +
        "place for the Shades to hide loot that they've obtained " +
        "from some unfortunate citizen of Minas Tirith. The room " +
        "is quite small perhaps five feet in length and again in width. " +
        "An oil-lamp lights the room from above and the wall you " +
        "entered from seems to be the only way out."));

    add_item("oil-lamp","A oil-lamp hangs on a chain above lighting the room.");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);

    add_exit(SHADES_DIR + "hall2", "west", 0, 1);

    reset_room();
}

public void
reset_room()
{
    Shade = clone_npc(Shade, SHADES_DIR + "shade");

    if (!objectp(present("chest", TO)))
        clone_object(SHADES_DIR + "obj/chest")->move(TO);
    else
        present("chest", TO)->setup_treasure();
}

void
init()
{
    ::init();
    add_action(refuse_get, "get");
    add_action(refuse_get, "take");
    add_action(refuse_get, "pick");
    add_action(refuse_get, "steal");
}

int
refuse_get()
{
    if (TP != Shade &&
	objectp(Shade) &&
	present(Shade, TO) &&
	CAN_SEE(Shade, TP))
    {
        write("The dark-robed man stops you from getting anything.\n");
        return 1;
    }
    return 0;
}

void
enter_inv(object ob, object from)
{
    string name;
    object chest, *gems;

    ::enter_inv(ob, from);
    if (interactive(ob) &&
	objectp(chest = present("chest", TO)) &&
	sizeof(gems = all_inventory(chest)) &&
	took_loot[(name = ob->query_name())])
    {
	gems->remove_object();
	hid_loot = 1;
	/* one pile of loot per person per reboot */
	log_file("chests", ctime(time())+" HID shades loot from "+name+".\n");
    }
}

void
leave_inv(object ob, object dest)
{
    object chest;
    string name;

    ::leave_inv(ob, dest);
    if (hid_loot &&
	interactive(ob) &&
	objectp(chest = present("chest", TO)) &&
	!sizeof(FILTER_PLAYERS(all_inventory(TO))))
    {
	/* ok, we hid the loot when someone entered, and all
	 * players have now left --- restore it
	 */
	 chest->setup_treasure();
	 hid_loot = 0;
    }
    else if (ob->id("chest") &&
	     interactive(dest) &&
	     sizeof(all_inventory(ob)))
    {
	name = dest->query_name();
	log_file("chests",
	    ctime(time())+" "+name+" took chest from the shades.\n");
	player_took_loot(name);
    }
}

public void
player_took_loot(string name)
{
    took_loot[CAP(name)] = 1;
}
