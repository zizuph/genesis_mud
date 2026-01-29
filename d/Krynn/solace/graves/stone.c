
/* A moveable stone door by eiram */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

#define START_ROOM "/d/Krynn/solace/graves/grave8"

int moves;

create_object()
{
    moves = 0;

    set_name("my_stone");
    set_no_show_composite(1);

    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME, 60000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, 1);

    seteuid(getuid(TO));
}


init()
{
    ADA("push");
    ADD("push", "move");
    ADA("climb");
}

push(str)
{
    string *ss, to;
    mixed *arr;
    int i,see;
    object from;

    NF("Push what?\n");

    if (!str)
        return 0;
    ss = explode(str, " ");
    if (ss[0] != "stone")
        return 0;
    
    NF("Push stone where?\n");

    if (sizeof(ss) == 1)
        return 0;

    if (!(from = E(TO)))
        return 0;

    arr = from->query_exit();
    for (i = 1; i < sizeof(arr); i += 3)
    {
        if (arr[i] == ss[1])
        {
            to = arr[i - 1];
	    see = (E(TP) == E(TO));
            if (!move(to))
            {
                if (see)
		  tell_room(from, QCTNAME(TP) + " pushes the stone " + ss[1] + ".\n", TP);
		else
		  tell_room(from, "Someone pushes the stone " + ss[1] + ".\n",TP);
                tell_room(to, "A stone arrives.\n");
                write("You pushed the stone " + ss[1] + ".\n");
                moves++;
                if (moves > 2)
		  set_alarm(8.0,0.0,"gravekeeper_arrives");
                return 1;
            }
        }
    }

    NF("No direction " + ss[1] + " found.\n");
    return 0;
}


gravekeeper_arrives()
{
    moves = 0;
    tell_room(E(TO), BS(
        "The gravekeeper arrives screaming: There is the stone, Don't you ever move it again! " +
        "The next second both the gravekeeper and the stone is gone.", 70));

    move(START_ROOM);
    tell_room(find_object(START_ROOM),
        "The gravekeeper arrives with his stone on his head puts it\n" +
        "down over the crypt with a bump, then he disappears.\n");
}


climb(str)
{
    NF("Climb what?\n");
    if (str != "stone")
        return 0;

    write("You climb up on and down the huge stone, it was fun.\n");
    say(QCTNAME(TP) + " climbs up and down the huge stone.\n");

    return 1;
}

leave_env(old, dest)
{
    ::leave_env(old, dest);
    if (old)
    {
	old->remove_my_desc(TO);
	old->remove_item("stone");
    }
}

enter_env(dest, old)
{
    ::enter_env(dest, old);
    if (dest)
    {
	dest->add_my_desc("There is a huge stone here.\n");
	dest->add_item(({"stone", "huge stone"}),
            "Its a huge stone and it is formed by a skilled hand. It has the\n"+
            "shape of a large door and it looks impossible to move.\n"+
            "Maybe you shouldn't try to move it.\n");
    }
}


