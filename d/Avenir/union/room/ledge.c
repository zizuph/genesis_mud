/* A place where you can get the lava.
 *  Cirion May 12 1996
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>


public void
union_room(void)
{
    set_short("wide ledge");
    set_long("Deep into the abyss, just inches away from death by "+
	"incineration. Running along just inches below the lip of this "+
	"wide ledge is a langorous river of white-hot molten rock. "+
	"The heat rising from the tide is dizzying, making your eyes "+
	"water and your skin tight and hot. High above, a wall of rock "+
	"rises up hundreds of meters to a distant overhang.\n");

    add_item(({"lake","molten rock","lava","down","river","rock"}),
	"The river of lava flows very slowly by, its surface broken "+
	"by occasional bubbles.\n");
    add_item(({"wall","walls","chasm", "chasm wall", "abyss"}),
	"Looking up from the bottom of the abyss, you can see "+
	"the walls of the chasm rising sheer and smooth, with only "+
	"a few hand-holds marring the surface.\n");
    add_item(({"hand-hold", "handhold", "handholds", "hand-holds"}),
	"If you are careful, you should be able to use the handholds "+
	"to climb back up the chasm wall.\n");
    add_item("overhang", "There lies safety, if you have the courage "+
	"and strength to climb up to it.\n");

    add_cmd_item(({"lava", "rock", "molten rock"}), "get",
	"Get it with what? Maybe you should try using something you "+
	"can fill with lava, rather than burning your hands off.\n");

    add_exit("midway", "up", 0, 10, 1);
}

public int
do_climb(string str)
{
    NF("Climb how? Where?\n");
    if (!strlen(str))
	return 0;

    if ((str != "up") && !parse_command(str, ({ }),
	    "[up] [to] [the] 'wall' / 'ledge' / 'overhang'"))
	return 0;

    write("You climb up the side of the abyss.\n");
    say(QCTNAME(TP) +" pulls "+ HIM(TP) +"self upward, climbing "+
	"toward safety.\n");

    TP->add_fatigue(10);
    TP->move_living("M", ROOM +"midway", 1, 0);
    return 1;
}

public int
fill(string str)
{
    object ob;

    NF("Fill what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, TP, "[the] %o 'with' [the] / [some] [hot] "+
	    "/ [molten] 'rock' / 'lava'", ob))
	return NF("Fill what with what?\n");

    if (!ob->query_prop(CONT_I_IN))
    {
	write("You cannot fill "+ LANG_THESHORT(ob) +" with anything.\n");
	return 1;
    }

    if (!ob->query_prop(CONT_I_RIGID))
    {
	write(CAP(LANG_THESHORT(ob)) +" is too soft to fill with "+
	    "the hot rock.\n");
	return 1;
    }

    if (ob->query_prop(CONT_I_CLOSED))
    {
	write(CAP(LANG_THESHORT(ob)) +" is closed.\n");
	return 1;
    }

    if (ob->query_prop(CONT_M_NO_INS))
    {
	write("You cannot seem to do that.\n");
	return 1;
    }

    if (sizeof(deep_inventory(ob)))
    {
	write("You would need to empty it first.\n");
	return 1;
    }

    write("You lean over the ledge and fill "+ LANG_THESHORT(ob) +
	" with as much of the molten rock as it will hold.\n");
    say(QCTNAME(TP) +" leans over the ledge and fills "+ LANG_ASHORT(ob) +
	" with as much of the molten rock as it will hold.\n");

    clone_object(OBJ+"lava")->move(ob, 1);
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(fill,     "fill");
    add_action(do_climb, "climb");
}
