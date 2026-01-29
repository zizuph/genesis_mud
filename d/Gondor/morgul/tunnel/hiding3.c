/*
 * Hiding3.c
 *
 * A deadend tunnel in Shelobs lair, Torech Ungol.
 *
 * Olorin, 30 oct 1993, copied and modifed from 
 * /Mercade, 18 july 1993
 */
#pragma strict_types

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define DOWN_ROOM       (MORGUL_DIR + "tunnel/hiding4")
#define DUMMY           (MORGUL_DIR + "tunnel/dummy")

int     down_slope();
void    throw_down(object *arr);
void    throw_rope_down(object rope);

object  tied_rope;
int     thrown_down = 0;

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/deadend6", "southeast", 0, 4);
    add_exit(DOWN_ROOM, "northeast", down_slope, 4);

    make_the_room(" The tunnel makes a turn here. To the northeast " +
        "it leads steeply downwards on a smooth slope. On the wall close to the " +
        "corner there is a torchstand mounted on the wall.");

    add_item(({"tunnel","slope"}), BSN(
        "The tunnel runs from the southeast to the northeast. Right at the turn " +
        "the ground starts to go down, first slowly, but after a few feet the " +
        "slope becomes much steeper. You also notice that the ground is exceedingly " +
        "smooth there."));
    remove_item("ground");
    add_item(({"ground","floor"}), BSN(
        "Right where you are standing the ground looks like everywhere else in the " +
        "cave, but a few feet further to the northeast, it suddenly becomes very " +
        "smooth, without the slightest unevenness that might give you a hold on the " +
        "steep slope."));
    remove_item("wall");
    add_item(({"wall","walls"}), BSN(
        "The walls feel remarkably smooth to the touch. On the corner a torchstand " +
        "is mounted on the eastern wall."));
    add_item(({"torch stand","stand","torchstand","rod","rods"}), BSN(
        "It is large iron torchstand mounted to the wall with two thick iron rods. " +
        "But the rings that once were used to hold a torch are broken, so that the " +
        "torch stand is useless now."));
    add_prop(ROOM_I_NO_CLEANUP,1);
}

int
tie_object(object rope, string str)
{
    NF("You cannot tie anything to the "+str+".\n");
    if(!str || (str != "torch stand" && str != "stand" && str != "torchstand"
        && str != "rod" && str != "rods"))
        return 0;
    NF("There is already "+LANG_ADDART(tied_rope->query_name())+" tied to the "+str+".\n");
    if (objectp(tied_rope))
        return 0;
    
    tied_rope = rope;
    return 1;
}

void
pull_rope_up()
{
    tell_room(DOWN_ROOM,"Suddenly, someone pulls up the "+tied_rope->query_name()+".\n");
    write("Ok.\n");
    SAY(" pulls up the "+tied_rope->query_name()+".\n");
    thrown_down = 0;
    DOWN_ROOM->remove_my_desc(TO);
    DOWN_ROOM->remove_item(tied_rope->query_name());
}

int
untie_object(object rope)
{
    if(rope != tied_rope)
        return 0;
    if(thrown_down)
    {
        pull_rope_up();
    }
    tied_rope = 0;
    return 1;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(objectp(tied_rope) && ob == tied_rope && thrown_down)
        untie_object(tied_rope);
}

int
down_slope()
{
    write(BSN("As you walk on the steep slope, you suddenly lose all hold " +
        "and slide downwards."));
    LSAY("As "," walks on the steep slope, "+PRONOUN(TP)+" suddenly loses " +
        "all hold and slides downwards.");
    return 0;
}

void
init()
{
    ::init();
    add_action("do_throw","throw");
    add_action("do_pull","pull");
}

int
do_pull(string str)
{
    string  vb = query_verb(),
            dummy,
            what;
    object *ob;

    NF(CAP(vb) + " what?\n");
    if(!str)
        return 0;

    if(!objectp(tied_rope) || !thrown_down)
        return 0;
    
    if(tied_rope->id(str))
        what = str;
    else if(sscanf(str,"at %s",dummy) == 1)
        what = dummy;
    else if(sscanf(str,"%s up",dummy) == 1)
        what = dummy;
    else
        return 0;

    if(!sizeof(ob = FIND_STR_IN_OBJECT(what, ENV(TP))))
        return 0;

    if(ob[0] != tied_rope)
        return 0;

    pull_rope_up();
    return 1;
}

int
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
    if(sscanf(str,"%s dow%s", what, dir) != 2 && sscanf(str,"%s northeas%s", what, dir) != 2)
        return 0;

    NF(CAP(vb) + " what?\n");
    if(!sizeof(ob = FIND_STR_IN_OBJECT(what, TP)))
        if(!sizeof(ob = FIND_STR_IN_OBJECT(what, ENV(TP))))
            return 0;

    if(msg = ob[0]->query_prop(OBJ_M_NO_DROP))
    {
        if( (function_exists("create_object", ob[0]) != "/std/rope") ||
            (!objectp(ob[0]->query_tied_to())) || (ob[0] != tied_rope) )
        {
            if(stringp(msg))
                NF(msg);
            else
                NF("You cannot throw away the "+ob[0]->query_name()+"!\n");
            return 0;
        }
    }

    diff = ob[0]->query_prop(OBJ_I_WEIGHT) / 60;

    if(diff/10 > TP->query_fatigue())
    {
        NF("You are too tired.\n");
        return 0;
    }

    write("You throw the "+ob[0]->query_name()+" down the slope to the northeast.\n");
    SAY(" throws the "+ob[0]->query_name()+" down the slope to the northeast.");

    TP->add_fatigue( - diff/20 );

    if(!msg)
    {
        ob[0]->move(DUMMY);
        set_alarm(4.0, 0.0, &throw_down(({TP, ob[0]})));
    }
    else
    {
        if(ob[0]->query_length() < 500)
        {
            NF("The "+ob[0]->short()+" is too short.\n");
            return 0;
        }
    /* is rope tied in here */
        set_alarm(2.0, 0.0, &throw_rope_down(ob[0]));
    }
    return 1;
}

void
throw_down(object *arr)
{
    object  player   = arr[0],
            thrown   = arr[1];

    tell_room(DOWN_ROOM, CAP(LANG_ADDART(thrown->short())) + " falls down in front of your feet.\n");
    thrown->move(DOWN_ROOM);
}

void
throw_rope_down(object rope)
{
    thrown_down = 1;
    tell_room(DOWN_ROOM,BSN(
        "Suddenly, the end of "+LANG_ADDART(rope->query_name())+" comes sliding down the slope."));
    DOWN_ROOM->change_my_desc(CAP(LANG_ADDART(rope->query_name()))+" is hanging down from above.\n");
    DOWN_ROOM->add_item(rope->query_names(),BSN(
        "The "+rope->query_name()+" is hanging down from above. With its help, " +
        "you might be able to climb out of this trap."));
}

int query_thrown_down() { return thrown_down; }

object query_tied_rope() { return tied_rope; }

