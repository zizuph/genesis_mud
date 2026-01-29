/*
 * /d/Gondor/morgul/cellar/pass_2e1.c
 *
 * Olorin, 12-aug-1994
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"


void   reset_room();
void   player_took_loot(string name);

static mapping	took_loot = ([]);
static int	hid_loot;

void
create_morgul_cellar_room()
{
    set_level(2);
    set_room_type("dead end");
    set_extra_long("The short tunnel ends here, you can only go back "
      + "south.");

    add_walls();
    add_floor();
    add_ceiling();
    add_archway("south");

    add_exit(CELLAR_DIR + "dung_2e1", "south", "@@check_exit", 1);

    reset_room();
}

void
reset_room()
{
    object  chest;

    if (objectp(chest = present("chest", TO)))
    {
        chest->reset_container();
        return;
    }

    clone_object(MORGUL_DIR + "obj/treasure_chest")->move(TO);

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
	log_file("chests",
	    ctime(time()) + " HID morgul loot from " + name + ".\n");
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
	chest->reset_container();
	hid_loot = 0;
    }
    else if (ob->id("chest") &&
	     interactive(dest) &&
	     sizeof(all_inventory(ob)))
    {
	name = dest->query_name();
	log_file("chests",
	    ctime(time())+" "+name+" took chest from the morgul cellar.\n");
	player_took_loot(name);
    }
}

public void
player_took_loot(string name)
{
    took_loot[CAP(name)] = 1;
}
