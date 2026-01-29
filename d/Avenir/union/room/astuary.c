/*
 * Union Astuary
 *  Cirion 050596
 *
 * Revisions:
 *   Lilith, Dec 2000: Added water clock
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <stdproperties.h>

public void
union_room()
{
    set_short("astuary");
    set_long("Massive pillars of glossy black stone hold of the south "
      +"end of this chamber, perfectly rectangular and smooth. To the north, "
      +"the chamber slowly descends and turns rough, until it becomes completely "
      +"unhewn. A large pool of clear water has collected at the north end, "
      +"fed by the dripping of a thousand droplets of water falling from the "
      +"ceiling, hanging like glistening jewels before they fall in "
      +"a light rain on the water's surface.\nThe whole place seems to "
      +"shine with dazzling refracted light.\n");

    add_item(({"pillar","pillars","column","columns"}),
	"There are two columns at the south end of the chamber, "+
	"massive and strong. They are made from a glossy black stone, "+
	"perfectly formed.\n");
    add_item(({"water","pool"}),
	"The pool forming at the north end of the chamber is brimming "+
	"with crystal clear water, fed by droplets of water falling "+
	"from above. It leads up the north wall of the chamber, which "+
	"is a rocky and unhewn cavern wall.\n");
    add_item(({"wall","walls"}),
	"The walls of the southern end of the chamber are perfectly "+
	"formed of deep grey stone, angular and straight. They quickly "+
	"become less smooth as they lead northwards, until they are "+
	"completely rough and unhewn at the northern end of the cavern.\n");
    add_item(({"floor","ground"}),
	"The floor is smooth and is decorated with a long winding "+
	"pattern, much like a mosaic of ivy. The floor drops to the "+
	"north, where it becomes filled with water from the pool.\n");
    add_item(({"ceiling","roof"}),
	"The ceiling high above follows the same design as the floor and "+
	"walls, being smooth and flat at the south end of the chamber, "+
	"and decaying into roughness to the north.\nOver the pool, "+
	"thousands of droplets of water glimmer and shine like stars, "+
	"before falling gracefully into the water below.\n");
    add_item(({"drop","drops","droplets"}),
	"They shine like stars, gleaming with a dazzling light.\n");
    add_item("north wall",
	"It is unhewn, the rough face of a natural cavern. Along it, "+
	"dozens of rivulets of clear water trickle down into the pool "+
	"below.\n");
    add_item(({"east wall"}),
	"It is smooth and angular at the south end, turning rough and "+
	"unhewn as it leads north.\n");
    add_item(({"west wall"}),
	"It is smooth and angular at the south end, turning rough and "+
	"unhewn as it leads north.\n There seems to be some writing "+
	"etched on a smooth part of the wall.\n");
    add_item(({"inscription","writing"}), "@@writing@@");
    add_item("south wall",
	"A massive wall of grey stone, with a large opening in the "+
	"centre framed by two massive pillars, leading out into a "+
	"hallway.\n");

    add_cmd_item(({"water","pool"}),"taste",
	"It tastes clean and fresh, making you want to drink from it.\n");
    add_cmd_item(({"drop","droplet","drops","droplets"}),({"touch","feel"}),
	"You cannot reach them of course.\n");
    add_cmd_item(({"water","pool"}),({"touch","feel"}),
	"It is very cold!\n");
    add_cmd_item(({"water","pool","in water","in pool"}),
	({"enter","wade","swim","dive"}),
	"It is far too cold to swim in.\n");

    add_prop(ROOM_I_LIGHT, 5);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_exit("hall_low", "south");

    add_object(COM + "obj/clepsydra");
}

public string
writing(void)
{
    if (!present(SWAY_ID_ALL, TP))
	return "It is so faint as to make it indecipherable.\n";

    return "The writing seems to gleam with intensity, as if "+
	"there were some unearthly light illuminating it.\n"+
	"  Beneath the swirl of stone and colour,\n"+
	"  Cry out to the Shadows, and they shall hear you.\n";
}

public int
read(string str)
{
    if (!strlen(str) || !CAN_SEE_IN_ROOM(TP))
	return 0;

    if (!parse_command(str, ({}),
	"[the] [west] 'writing' / 'inscription' / 'wall' [on] [the] [west] [wall]"))
    {
	return notify_fail(CAP(query_verb()) + " what?\n");
    }

    write(writing());
    return 1;
}

public int
do_drink(string str)
{
    int dr;

    if (!strlen(str) ||
	!parse_command(str, ({}), "[from] [the] 'water' / 'pool'"))
    {
	return NF("Drink what?\n");
    }

    dr = TP->query_prop(LIVE_I_MAX_DRINK) / 16;
    if (!dr) dr = 200;

    if (!TP->drink_soft(dr))
    {
	write("The water is too much for you.\n");
	return 1;
    }

    write("You kneel at the edge of the water and drink deeply "+
	"from it.\nThe water is cool and refreshing.\n");
    say(QCTNAME(TP)+" kneels at the edge of the water and drinks "+
	"deeply from it.\n");

    return 1;
}

public int
do_wash(string str)
{
    object ob;

    if (!strlen(str) ||
	!parse_command(str, ({}),
	    "[me] / [myself] 'in' [the] 'pool' / 'water'"))
    {
	return NF("Wash where?\n");
    }

    write("You kneel by the pool and "+ query_verb() +" yourself.\n");
    say(QCTNAME(TP)+" kneels by the edge of the water and washes "+
	HIM(TP) +"self.\n");

    /* The player gains purity by bathing, but only once / half hour */
    TP->emote_adjust_union_virtue(US_PURITY, 25);
    TP->add_prop(CLEANSED, time());

    while(ob = present("dirty", TP))
    {
	ob->remove_object();
	TP->catch_tell("You feel much less dirty now.\n");
    }

    TP->command("$shiver");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(read,     "read");
    add_action(do_drink, "drink");
    add_action(do_wash,  "wash");
    add_action(do_wash,  "bathe");
}
