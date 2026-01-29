/*
 * Old graveyard
 */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
inherit GRAVE_STD;

#define  NO_CLIMB  200 /* can't climb fence */
#define  DAMAGE    30  /* tangleshoot usually traps, this one injures */

object ob;

create_solace_room()
{
    object door;

    set_short("Just inside the Old Graveyard");
    set_long(BS("This is just inside the old graveyard. The old weathered f" +
		"ence is just to the east and north of the graves, forming " +
		"its northeast corner. There is a gate in the fence just we" +
		"st of the corner. There are old, weathered, cracked and br" +
		"oken gravestones here. " +
		"There are lots of brambles to the" +
		" west.", 70));

    add_item(({"fence", "old fence", "old wrought iron fence",
		 "wrought iron fence"}), "The north or east fence?");
    add_item("north fence", "It's old and weathered, with a gate in it.\n");
    add_item("east fence", "It runs south, looks like this fence encircles " +
	"the whole graveyard.\n");
    add_item("brambles","The thick brambles prevent movement " +
        "in this direction, as they look plenty sharp.\n");

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
                "You can't kill the tangleshoot. You hack it up a bit, " +
                "but there is just too much of it to kill.", 70));

    add_exit(TDIR + "o_grave6", "south", "@@south_msg");

    door = clone_object(OBJ + "gate_n");
    door->move(this_object());

    reset_room();
}

reset_solace_room()
{
    if (!ob)
	(ob = clone_object(MONSTER + "skeletal_rabbit"))->move_living("xx", TO);
}

tangleshoot()
{
    if (this_player()->query_skill(SS_CLIMB) < (NO_CLIMB))
    {
	say(QCTNAME(this_player()) + "was grabbed by the tangleshoot and\n" +
		"injured.\n");
	this_player()->reduce_hit_point(DAMAGE);
	return("You are grabbed by the tangleshoot. It injures you.\n");
    }
    else
	return("Greetings Guru climber. This is below your skill.\n");
}

south_msg()
{
     write(BS("You get scratched by the brambles, but it is only a minor fle" +
	      "sh wound.", 70));
}

graveyard()
{
    write("You are in the elder part of the Solace Graveyard.\n");
    say(QCTNAME(TP) + " looks all around.\n");
    return 1;
}
