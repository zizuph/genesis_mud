/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <composite.h>

#define SEE_EAST	({ HALL+"_w2", ROOM+"cross", HALL+"_e" })

object gate;

public string
view(void)
{
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return "";

    return " Down the hall to the east can be seen "+
	COMPOSITE_LIVE(live) + ".";
}

public string
door(void)
{
    if (!present(gate))
	return "";
    else if (gate->query_other_door()->query_broken())
	return " A massive black gate lies in ruins on the ground, "+
	    "broken open by some massive force.";
    else if (gate->query_open())
	return " Rising to the west is a massive black steel "+
	    "gate which stands open to a tunnel beyond.";
    else return " Rising to the west is a massive steel gate, "+
	"its flat, unadorned surface seemingly absorbing all "+
	    "the light cast on it.";
}

public int
go_east(void)
{
    write("You walk down the long hallway to the east.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("west end of a long hallway");
    set_long("The corridor runs straight to the east, the "+
	"walls made of a smooth limestone and the floor is "+
	"covered in an intricate, abstract swirl of stones "+
	"and metals. To the north is a large room from which "+
	"wisps of cold mist blow, and to the south is an "+
	"opening to another room.@@door@@ @@view@@\n");

    add_item(({"floor","ground","stone","stones","swirl",
	"metal","metals"}), "The floor is covered in swirls "+
	"of dark metal and grey stone that seems to merge and "+
	"melt and never repeat itself.\nYou feel slightly "+
	"dizzy staring at the patterns on the floor.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is soft and smooth, a pale white "+
	"limestone that reflects the light.\n");
    add_item(({"hall","corridor","east","hallway"}),
	"The hallway stretches off to the east, perfectly straight "+
	"and wide.@@view@@\n");
    add_item(({"roof","ceiling"}),
	"The ceiling overhead is made of the same dark granite as the "+
	"floor, but is simple and unadorned. It rises slightly in the "+
	"middle, forming a gentle arch that stretches all the way down "+
	"the corridor to the east.\n");
    add_item(({"mist","fog","wisp","wisps"}),
	"Wisps of grey mist drift into the hallway from the room to the "+
	"north, quickly dissipating.\n");
    add_item(({"chamber","room","north"}),
	"It is obscured by the grey fog.\n");

    add_cmd_item(({"fog","mist","wisp"}), "touch",
	"It disperses as you touch it, leaving you hand cold and wet.\n");
    add_cmd_item(({"wall","walls","stone","limstone"}), "touch",
	"It is smooth and soft.\n");
    add_cmd_item(({"floor","ground"}), "touch",
	"It is hard, the patterns rising out from the floor slightly.\n");

    add_exit("hall_w2", "east", "@@go_east@@");
    add_exit("pendentive", "north");
    add_exit("train", "south");

    add_object(OBJ + "gate_e");
}

static void
update_vars(void)	{ gate = present("_union_gate"); }

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->test_bit("Avenir", GUILD_GROUP, PROHIBIT))
    {
	if (FRIEND(ob))
	    ob->clear_bit(GUILD_GROUP, PROHIBIT);

	if (LIST->query_hopeful(ob->query_real_name()))
	    ob->clear_bit(GUILD_GROUP, PROHIBIT);

	if (LIST->query_accepted(ob->query_real_name()))
	{
	    ob->clear_bit(GUILD_GROUP, PROHIBIT);
	} else {
	    ob->catch_msg("A cold hostility seems to seep from the "+
		"from the very walls, making you doubt your welcome.\n");
	}
    }
}
