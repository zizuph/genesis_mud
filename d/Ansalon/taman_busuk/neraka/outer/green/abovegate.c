/* Carridin */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

inherit OUTER_IN;

object g;

#define R_OUTSIDE           NOUTER + "green/g7"
#define GATE                ((R_OUTSIDE)->query_gate())
#define STR_TO_TURN_WHEEL   35

void
reset_neraka_room()
{
    if (!objectp(g))
    {
        g = clone_npc(NNPC + "ogre","green");
        g->set_stat_extra(SS_STR, 25);
    }
}

void
create_neraka_room()
{
    set_short("above the gate");
    set_long("You are standing in the gatehouse, above the gate. In the " +
        "middle of the room is some sort of mechanism, with chains " +
        "leading down through some holes in the floor. A large wheel is " +
        "set on side of the mechanism. On the outer wall, a number of " +
        "slits allow a view of the outside. A circular staircase set in " +
        "a corner of the room leads down towards the bottom level of the " +
        "gatehouse.\n");
    set_quarter(GREEN);
        
    add_item_inside();
    remove_item("floor");
    add_item("floor","The floor is of wooden planks, and a number of holes " +
        "has chains going through them, connecting the mechanism to " +
        "something below the floor.\n");
    add_item(({"holes","hole"}),
        "The holes in the floor are there to allow the chains to connect " +
        "to something below the floor.\n");
    add_item(({"chain","chains"}),
        "The chains are made of thick metal links, and connect the " +
        "mechanism to something below the floor.\n");
    add_item(({"staircase","circular staircase"}),
        "The staircase, made of smooth stones, leads down.\n");

    add_item("mechanism","The mechanism seems to contain some pulleys and " +
        "cogwheels. A large wooden wheel is set on the side of the " +
        "mechanism.\n");
    add_item(({"wheel","large wheel","wooden wheel"}),
        "The wheel has worn handles to facilitate the grip if one were to " +
        "try turning it.\n");
    add_cmd_item(({"wheel","large wheel","wooden wheel"}),
        "turn", "@@do_turn_wheel");

    add_item(({"slit","slits"}),
        "The narrow slits allow you a limited view of the outside. " +
        "@@look_through_slit@@");

    add_exit(NOUTER+"green/gatehouse","down","@@go_down");

    reset_room();
}

int
go_down()
{
    write("You descend the staircase.\n");
    return 0;
}

void
set_portcullis_open(int os)
{
    if (os)
    {
        tell_room(TO, "The floor shudders as the portcullis slams into " +
            "a raised position.\n");
        (GATE)->remote_open();
    }
    else
    {
        tell_room(TO, "You hear a large crashing sound as the portcullis " +
            "slams down into the ground, sealing off the gate.\n");
        (GATE)->remote_close();
    }
}
    
string
do_turn_wheel()
{
    if (objectp(g) && (g != TP) && (E(g) == TO))
    {
        tell_room(TO,QCTNAME(g) + " stops " + QTNAME(TP) + " from " +
            "turning the large wheel.\n", TP);
        return "The " + g->short() + " stops you from turning the " +
            "large wheel.\n";
    }
    if (TP->query_stat(SS_STR) < STR_TO_TURN_WHEEL)
    {
        tell_room(TO,QCTNAME(TP) + " grows red in the face as " + HE(TP) +
            " tries in vain to turn the large wheel.\n", TP);
        return "You try in vain to turn the large wheel, but you are " +
            "just not strong enough.\n";
    }
    tell_room(TO,QCTNAME(TP) + " takes a steady grip of the large wheel " +
        "and starts to turn it, slowly at first, then faster and faster.\n",
        TP);
    if ((GATE)->query_open())
        set_alarm(1.0,0.0,&set_portcullis_open(0));
    else
        set_alarm(2.0,0.0,&set_portcullis_open(1));
    return "You take a steady grip of the large wheel and start to " +
        "turn it, slowly at first, then faster and faster.\n";
}

string
look_through_slit()
{
    object r,*l = ({ });

    if (r = find_object(R_OUTSIDE))
    {
        l = FILTER_SHOWN( FILTER_LIVE( all_inventory(r) ) );
    }

    if (sizeof(l))
        return "Looking down through the slit, you see " +
            COMPOSITE_LIVE(l) + " standing outside the gate.\n";
    else
        return "Looking down through the slit, you see the gate " +
            "unguarded.\n";
}

/* called by admin */
void
raise_portcullis()
{
    if (objectp(g) && !(GATE)->query_open() && ((R_OUTSIDE)->query_defenders_left()))
    {
        g->command("turn large wheel");
    }
}

void
lower_portcullis()
{
    if (objectp(g) && (GATE)->query_open())
    {
        g->command("turn large wheel");
    }
}

int
query_attack_going_on()
{
    return (R_OUTSIDE)->query_attack_going_on();
}

void
extra_defences()
{
    object pitch,target;

    if (!objectp(g))
        return;

    if (g->query_attack())
        return;

    setuid();
    seteuid(getuid());

    target = find_object(R_OUTSIDE);
    if (!objectp(target))
        return;
    
    pitch = clone_object(NOBJ + "pitch");
    if (!objectp(pitch))
        return;

    pitch->move(target);
    pitch->start_burning(2 + random(3));

    tell_room(TO, QCTNAME(g) + " lights a cask of pitch and throws it out " +
        "through a hatch.\n");
}
