/*
 * /d/Sparkle/guilds/mercs/room/rack_room, by Morrigan 11/2001
 *
 * Adapted from code by Auberon and Gwyneth on 19 February 2001
 * Updated for Sparkle by Lunatari 2006
 */
inherit "/std/room";

#include "../merc.h"
#include "room.h"

object gRack1, gRack2, gRack3;

void
reset_room()
{
    if (!present(gRack1))
    {
        gRack1 = clone_object(MOBJ + "eq_rack");
        gRack1->move(this_object(), 1);
    }

    if (!present(gRack2))
    {
        gRack2 = clone_object(MOBJ + "neq_rack");
        gRack2->move(this_object(), 1);
    }

    if (!present(gRack3))
    {
        gRack3 = clone_object(MOBJ + "junk_box");
        gRack3->move(this_object(), 1);
    }

}

public string
read_poster()
{
    return "NOTICE:\n\n"+
	"I reserve the right to punish abusers of these\n"+
	"racks, as well as those who whine about them\n"+
	"so often as to become annoying to me.\n\n"+
	"Maligant\n";
}

public string
read_door()
{
    return "The small plaque has several flowing characters\n"+
	"which look like elven. Below them is written in\n"+
	"common: Dalizen the Dark.\n";
}

int enter_hall()
{
    write(GREAT_HALL_ENTER);
}

public void
create_room()
{
    set_short("The equipment room");
    set_long(BUILDING_DESC+
	"The hallway to the Great Hall heads west from here, "+
	"and to the south is the bunkroom. Along the east wall "+
	"sit two large racks for equipment. Between them hangs "+
	"a poster. You notice a locked door to the north, with "+
	"a small plaque upon it.\n");


    add_item("door", "The door is in the north wall, upon it is "+
	"a small plaque. You notice no doorknob or other obvious "+
	"way of opening it.\n");
    add_cmd_item("door", "open", "You see no way of "+
	"opening this door.\n");
    add_cmd_item(({"door", "lock"}), "pick", "There is no visible "+
	"lock upon the door to pick.\n");
    add_item(({"poster", "sign"}), &read_poster());
    add_cmd_item(({"poster", "sign"}), "read", 
        &read_poster());
    add_item(({"plaque"}), &read_door());
    add_cmd_item(({"plaque"}), "read", &read_door());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1); 
    add_exit(MROOM + "start.c", "south", 0, 1, 0);
    add_exit(MROOM + "great_hall.c", "west", "@@enter_hall", 1, 0);
    reset_room();
}

public int sort_racks(string str)
{
    object weapon_rack = present("_merc_guild_weapon_rack_", this_object());
    object armour_rack = present("_merc_guild_armour_rack_", this_object());
    object junk_box = present("_merc_guild_junk_box_", this_object());
    object *winv, *ainv, *junk;
    string *moved = ({ });
    int i;

    notify_fail("What?\n");
    if (!ARMAGEDDON->shutdown_active() && !this_player()->query_wiz_level())
        return 0;

    notify_fail("Sort what? The racks?\n");
    if (!str)
        return 0;

    if (str != "racks" && str != "the racks" && str != "rack" &&
	str != "the rack")
	return 0;

    if (objectp(weapon_rack))
	winv = all_inventory(weapon_rack);

    if (objectp(armour_rack))
	ainv = all_inventory(armour_rack);

    if (objectp(junk_box))
	junk = all_inventory(junk_box);

    write("You start to hastily sort the racks.\n");

    if (sizeof(winv))
    {
        for (i=0;i<sizeof(winv);i++)
	{
	    if (!winv[i]->check_recoverable())
	    {
		moved += ({ winv[i]->short() });
		winv[i]->move(this_object(), 1);
            }
        }
    }

    if (sizeof(moved))
    {
        write("You remove a "+COMPOSITE_WORDS(moved)+" from the "+
	"weapon rack and drop "+(sizeof(moved) == 1 ? "it" : "them")+
	" on the ground here.\n");
        say(QCTNAME(this_player())+" removes a "+COMPOSITE_WORDS(moved)+
	" from the weapon rack and drops "+(sizeof(moved) == 1 ? "it" :
	"them")+" on the ground here.\n");
    }
    else
	write("The weapon rack looks to be well sorted.\n");

    moved = ({ });

    if (sizeof(ainv))
    {
        for (i=0;i<sizeof(ainv);i++)
        {
	    if (!ainv[i]->check_recoverable())
            {
		moved += ({ ainv[i]->short() });
    	        ainv[i]->move(this_object(), 1);
            }
        }
    }

    if (sizeof(moved))
    {
        write("You remove a "+COMPOSITE_WORDS(moved)+" from the "+
	"armour rack and drop "+(sizeof(moved) == 1 ? "it" : "them")+
	" on the ground here.\n");
        say(QCTNAME(this_player())+" removes a "+COMPOSITE_WORDS(moved)+
	" from the armour rack and drops "+(sizeof(moved) == 1 ? "it" :
	"them")+" on the ground here.\n");
    }
    else
	write("The armour rack looks to be well sorted.\n");

    /*
     * sizeof(ainv) was used before, no clue why, must have been
     * some soft of misshap.
     * Lunatari 2006 Feb
     */
    moved = ({ });
    if (sizeof(junk))
    {
        for (i=0;i<sizeof(junk);i++)
        {
	    if (!junk[i]->check_recoverable())
            {
		moved += ({ junk[i]->short() });
    	        junk[i]->move(this_object(), 1);
            }
        }
    }

    if (sizeof(moved))
    {
        write("You remove a "+COMPOSITE_WORDS(moved)+" from the "+
	"wooden crate and drop "+(sizeof(moved) == 1 ? "it" : "them")+
	" on the ground here.\n");
        say(QCTNAME(this_player())+" removes a "+COMPOSITE_WORDS(moved)+
	" from the wooden crate and drops "+(sizeof(moved) == 1 ? "it" :
	"them")+" on the ground here.\n");
    }
    else
	write("The wooden crate looks to be well sorted.\n");

    return 1;
}

void tell_of_sort(object ob)
{
    ob->catch_tell("As Armageddon is active, you can 'sort' the racks "+
	"in order to separate the good equipment from the junk.\n");
}

void init()
{
    ::init();

    add_action("sort_racks", "sort");

    if (IS_MERC(this_player()) && ARMAGEDDON->shutdown_active())
	set_alarm(1.0, 0.0, &tell_of_sort(this_player()));
}
