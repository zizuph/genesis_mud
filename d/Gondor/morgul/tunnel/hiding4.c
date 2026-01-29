/*
 * Hiding4.c
 *
 * A deadend tunnel in Shelobs lair, Torech Ungol.
 *
 * Olorin, 1-nov-1993, copied and modifed from 
 * /Mercade, 18 july 1993
 */
#pragma strict_types

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"

#define MIN_AWARE1      20                /* find skeleton      */
#define MIN_AWARE2      35                /* find grid          */
#define UP_ROOM         (MORGUL_DIR + "tunnel/hiding3")
#define DUMMY           (MORGUL_DIR + "tunnel/dummy")

object  skeleton,
        centipede,
        hole;
int     isth = 0;       /* search status of the heap of bones */
int     reset_alarm;

public  int     do_climb(string str);
public  int     do_throw(string str);
public  int     up_slope();
        void    get_centipede(object victim);
varargs void    fail_climb(int i = 0);
        void    reset_room();
        void    throw_fail(object *arr);
        void    throw_up(object *arr);

public void 
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/hiding3", "up", up_slope, 4);

    make_the_room("@@extra_desc@@");

    remove_item("ground");
    add_item(({"ground","floor","pile","heap","bones","skeletons"}), VBFC_ME("exa_heap"));
    add_item(({"tunnel","slope","exit"}), VBFC_ME("exa_slope"));

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(ROOM_I_NO_CLEANUP,1);

    reset_room();
}

string 
extra_desc()
{
    string  desc     = "\nThe ground is covered with skeletons of many unlucky " +
                       "creatures that died here. Probably they could not leave " +
                       "again over the steep slope leading upwards " +
                       "once they had arrived here. ";

    switch (isth)
    {
    case 0:
    case 1:
    case 2:
	break;
    case 3:
	desc += "In the middle of the room, someone has cleared the floor " +
	    "of skeletons, uncovering a metal grid. ";
	break;
    default:
    }

    return BS(desc);
}

void 
init()
{
    ::init();
    add_action(do_throw, "throw");
    add_action(do_climb, "climb");
}

void 
add_stuff()
{
    if (!skeleton)
    {
        skeleton = clone_object(MORGUL_DIR + "obj/skeleton");
        skeleton->move(TO);
    }
}

/*
 * reset room only if no livings are present
 */
void 
reset_room()
{
    if (sizeof(FILTER_LIVE(all_inventory(TO))))
    {
        if (!get_alarm(reset_alarm))
            reset_alarm = set_alarm(300.0, 0.0, reset_room);
        return;
    }
    isth = 0;
    add_stuff();
    if (skeleton)
        skeleton->reset_object();
    if (objectp(hole))
        hole->remove_object();
    centipede = 0;
}

string 
do_search(object searcher, string str)
{
    if (!strlen(str))
        return 0;

    if (str == "heap" || str == "pile" || str == "skeletons" ||
        str == "ground" || str == "floor" || str == "bones")

        switch(isth)
        {
	case 0:
	    if (searcher->query_skill(SS_AWARENESS) > MIN_AWARE1)
	    {
		skeleton->unset_no_show();
		skeleton->unset_no_show_composite();
		skeleton->query_tied_rope()->unset_no_show();
		SAY(" finds the "+skeleton->short()+" lying on top of the heap of bones.");
		isth = 1;
		return "You find the "+skeleton->short()+" lying on top of the heap of bones.\n";
	    }
	    break;
	case 1:
	    set_alarm(0.0, 0.0, &get_centipede(TP));
	    isth = 2;
	    SAY(" rouses a dangerous looking centipede.");
	    return "Your search seems to have angered a dangerous looking centipede.\n";
	    break;
	case 2:
	    if (searcher->query_skill(SS_AWARENESS) > MIN_AWARE2)
	    {
		isth = 3;
		if(!objectp(hole))
		{
		    hole = clone_object(MORGUL_DIR + "obj/key_hole");
		    hole->move(TO);
		}
		SAY(" clears the space in the centre of the cave, uncovering a metal grid there.");
		return BSN("Finally, when you have cleared the space in the centre of " +
			   "the cave down to the rock floor, you find a metal grid there.");
		break;
	    }
	default:
	    break;
        }
    return 0;
}

void 
get_centipede(object victim)
{
    centipede = clone_object(MORGUL_DIR + "npc/centipede");
    centipede->move(TO);
    tell_room(TO,QCNAME(centipede) + " comes running out of its hiding place under the heap of bones.\n");
    centipede->command("kill " + victim->query_real_name());
}

string 
exa_heap()
{
    string  desc     = "The floor of the cave is covered with the remains of " +
                       "several hundred skeletons, some are still almost complete, " +
                       "while of others only a few single bones remain. ";
    switch(isth)
    {
    case 0:
    case 1:
    case 2:
	break;
    case 3:
	desc += "In the middle of the heap someone has dug a hole. There the " +
	    "rock floor of the cave becomes visible. In the midst of the cleared " +
	    "space you can see a metal grid. ";
	break;
    default:
	break;
    }
    return BSN(desc);
}

string 
exa_slope()
{
    string  desc;

    desc = "The slope to the southwest is very steep and exceedingly smooth. " +
        "You doubt that you could find any hold there if you tried to climb the " +
        "slope. ";

    if (UP_ROOM->query_thrown_down())
        desc += CAP(LANG_ADDART(UP_ROOM->query_tied_rope()->query_name())) + 
            " is hanging down from above. ";
    return BSN(desc);
}

public int 
up_slope()
{
    object  rope;
    int     result,
            fat,
            e_w;

    if (!UP_ROOM->query_thrown_down())
    {
        write("You try to climb up on the steep slope.\n");
        SAY(" tries to climb up on the steep slope.");
        set_alarm(2.0, 0.0, fail_climb);
        return 1;
    }
    rope = UP_ROOM->query_tied_rope();
    write("You grasp the "+rope->query_name()+" and try to climb up.\n");
    SAY(" grasps the "+rope->query_name()+" and tries to climb up.");
    result = TP->resolve_task(TASK_ROUTINE,({TS_STR,TS_DEX,SS_CLIMB}));
    e_w = TP->query_encumberance_weight();
    fat = (1000 - result) * (100 + e_w);
    fat /= 2000;
    if(fat > TP->query_fatigue())
    {
        set_alarm(4.0, 0.0, &fail_climb(2));
        TP->set_fatigue(0);
        return 1;
    }
    if(result < e_w)
    {
        TP->add_fatigue(-fat/2);
        set_alarm(4.0, 0.0, &fail_climb(1));
        return 1;
    }
    TP->add_fatigue(-fat);
    return 0;
}

varargs void 
fail_climb(int i = 0)
{
    if(i == 1)
        write("You are not strong enough, and have to let go of the rope.\n");
    if(i == 2)
        write("You are too exhausted to continue climbing up the slope.\n");
    write("You lose your hold on the steep slope and slide back down.\n");
    SAY(" loses the hold on the steep slope and slides back down.");
    if( i > 0 && TP->query_encumberance_weight() > 20)
        write("Perhaps you carry too much weight?\n");
}

public int 
do_throw(string str)
{
    string  vb       = query_verb(),
            what,
            dir;
    object *ob;
    int     diff,
            result;
    mixed   msg;

    NF(CAP(vb) + " what?\n");
    if(!str)
        return 0;

    NF(CAP(vb) + " what into which direction?\n");
    if(sscanf(str,"%s u%s", what, dir) != 2)
        return 0;
    if(dir[0..0] != "p")
        return 0;

    NF(CAP(vb) + " what?\n");
    if(!sizeof(ob = FIND_STR_IN_OBJECT(what, TP)))
        if(!sizeof(ob = FIND_STR_IN_OBJECT(what, ENV(TP))))
            return 0;

    if(msg = ob[0]->query_prop(OBJ_M_NO_DROP))
    {
        if(stringp(msg))
            NF(msg);
        else
            NF("You cannot throw away the "+ob[0]->query_name()+"!\n");
        return 0;
    }

    diff = ob[0]->query_prop(OBJ_I_WEIGHT) / 12;

    if(diff/10 > TP->query_fatigue())
    {
        NF("You are too tired.\n");
        return 0;
    }

    write("You throw the "+ob[0]->query_name()+" up the slope.\n");
    SAY(" throws the "+ob[0]->query_name()+" up the slope.");

    TP->add_fatigue( - diff/20 );

    ob[0]->move(DUMMY);

    if(result = TP->resolve_task(diff,({TS_STR, TS_DEX})) < 0)
        set_alarm(2.0, 0.0, &throw_fail(({TP, ob[0]})));
    else
        set_alarm(4.0, 0.0, &throw_up(({TP, ob[0]})));
    return 1;
}

void 
throw_fail(object *arr)
{
    object  player   = arr[0],
            thrown   = arr[1];

    tell_room(TO,"The "+thrown->query_name()+" comes sliding back down the slope.\n");
    thrown->move(TO);
}

void 
throw_up(object *arr)
{
    object  player   = arr[0],
            thrown   = arr[1];

    tell_room(UP_ROOM, CAP(LANG_ADDART(thrown->short())) + " falls down in front of your feet.\n");
    thrown->move(UP_ROOM);
}

int 
do_climb(string str)
{
    if (!str || (str != "up" && str != "slope"))
    {
        NF("Climb where?\n");
        return 0;
    }

    if (up_slope())
        return 1;
    TP->move_living("up", UP_ROOM);
    reset_alarm = set_alarm(300.0, 0.0, reset_room);
    return 1;
}
