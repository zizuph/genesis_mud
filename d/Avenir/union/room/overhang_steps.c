/*
 * Overlook in the Union guildhall
 *  Cirion 060597
 *  Finished quest to get to lava for the flame.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>

#define LOOKED		"_Union_looked_over_ledge"
#define ARCH_LETTERS	\
    "Through gloom and shadows we pass,\n    beyond the torrid abyss,"+\
    "\nto slay our enemies in their homes.\n"


public int
up_steps(void)
{
    write("You ascend the narrow slate steps onto a narrow ledge.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("square landing");
    set_long("The floor of this square landing is made from very "+
	"thin slate, jutting out over the terrible, fiery "+
	"depths with no apparent means of support. A narrow set of "+
	"slate steps ascends up to the chasm ledge "+
	"to the east.\nSouth is wide archway opening into "+
	"the chasm wall, into a dark passage.\n");

    add_item(({"lake","molten rock","lava","chasm","chasm wall"}),
	"@@exa_chasm@@");
    add_item(({"wall","walls","rock"}),
	"The walls from the corridor to the south widen here, making "+
	"the ledge quite wide.\n");
    add_item(({"stair","stairs","step","steps"}),
	"The steps are quite narrow and are made from dark, smooth "+
	"plates of slate. They ascend up to the chasm ledge.\n");
    add_item(({"landing","slate","ground","floor"}),
	"The floor is of a single piece of smooth, black slate. It is "+
	"perfectly square, the base of which juts out from beneath the "+
	"archway to the south.\nIt appears to have no additional means "+
	"of support from above.\n");
    add_item(({"arch","archway","south"}),
	"The archway leading into the chasm wall is made from smooth, "+
	"unadorned white alabaster. The arch makes a graceful curve at "+
	"the top, where thin letters are carved into the soft material.\n");
    add_item(({"hand-hold", "handhold"}),
	"You might be able to reach it if you could somehow swing "+
	"yourself over the edge.\n");
    add_item(({"inscription", "letters"}),
	"The letters read: " + ARCH_LETTERS);

    add_cmd_item(({"arch","archway","letters","inscription"}),"read",
	ARCH_LETTERS);

    add_exit("overhang_nw", "east", up_steps);
    add_exit(TUNNEL + "tunnel_landing", "south");
}

public string
exa_chasm(void)
{
    TP->add_prop(LOOKED, 1);
    return ::exa_chasm();
}

public int
do_lean(string str)
{

    NF(CAP(query_verb())+" over what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({ }), "[out] 'over' [the] 'ledge' /"+
	   " 'side' / 'overhang' / 'edge'"))
	return 0;

    TP->add_prop(LOOKED, 1);
    write("You take a deep breath and lean over the ledge, careful "+
	"not to look down into the abyss.\nYour eyes catch on what "+
	"looks like a hand-hold an arms-length below the ledge.\n");
    say(QCTNAME(TP) +" leans over the side of the ledge, looking down "+
	"into the abyss.\n");

    return 1;
}

public int
do_climb(string str)
{
    if (!strlen(str))
	return 0;

    if (!TP->query_prop(LOOKED))
    {
	write("Your intellect asserts that it is not wise to do the "+
	    "without a more thorough examination of the chasm wall.\n");
	return 1;
    }

    if (!IS_TORNU(TP))
    {
	write("Your curiosity does not sufficiently out-weigh your courage "+
	    "in this matter.\n");
	return 1;
    }

    if (!parse_command(str, ({ }), "'over' / 'down' [for] [the] [to] "+
	    "'ledge' / 'edge' / 'overhang' / 'handhold' / "+
	    "'hand-hold' / 'slate'"))
    {
	NF(CAP(query_verb()) +" how? Try climbing over the edge "+
	    "or reaching down for the handhold.\n");
	return 0;
    }

    LOG_EVENT(NM(TP) +" reached the lava");
    write("Emboldened by your link with Jazur, you swing yourself over "+
	"the side of the overhang!\nYou keep hold of the ledge with one "+
	"hand and grab onto the hand-hold.\n");
    say(QCTNAME(TP) +" performs a singular act of grace and dexterity, "+
	"swinging over the ledge to "+ HIS(TP) +" apparent death.\n");

    TP->move_living("M", ROOM + "midway", 1, 0);
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(jump_ledge, "jump");
    add_action(jump_ledge, "leap");
    add_action(do_lean,    "lean");
    add_action(do_climb,   "climb");
    add_action(do_climb,   "swing");
    add_action(do_climb,   "reach");
    add_action(do_climb,   "scale");
}

public void
leave_inv(object ob, object where)
{
    ::leave_inv(ob, where);
    ob->remove_prop(LOOKED);
    remove_warned(ob);
}
