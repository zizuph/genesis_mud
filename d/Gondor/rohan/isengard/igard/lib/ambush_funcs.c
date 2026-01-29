/*
 *  IGARD_LIB + "ambush_funcs.c"
 *
 *  Various functions common to ambush routines in rooms.
 *
 *  Last modified by Alto, 01 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

/* PROTOTYPES */

public int         spring_trap();
public int	        catch_all(string str);

static object    Squad, Squad2, Squad3;
static object   *Qsquad = allocate(3);


public void
spring_trap()
{
    int toughness;
    object trappee;
    string alertphrase, alertphrase2, alertphrase3;

    trappee = TP;
    toughness = TP->query_average_stat();

    switch(random(5))
    {
        case 0:
            alertphrase  = "Hey look! Its a filthy spy!";
            alertphrase2 = "Get it! Get it! Don't let it get away!";
            alertphrase3 = "Lets kill it, no need for a trial.";
            break;
        case 1:
            alertphrase  = "A spy!";
            alertphrase2 = "Catch it quick!";
            alertphrase3 = "I'll make it feel welcome, oh yes!";
            break;
        case 2:
            alertphrase  = "Hmm. It seems we have a spy in our midst.";
            alertphrase2 = "Must be the one the Boss sent us to look for?";
            alertphrase3 = "It would be easiest to just kill it now.";
            break;
        case 3:
            alertphrase  = "Look what I found!";
            alertphrase2 = "That's a spy if I ever saw one!";
            alertphrase3 = "Get it! Get it! Don't let it escape!";
            break;
        case 4:
            alertphrase  = "Arrrrgh! This maggot is a spy!";
            alertphrase2 = "Kill it! Kill it!";
            alertphrase3 = "We have it now!";
            break;
        case 5:
            alertphrase  = "That was almost too easy!";
            alertphrase2 = "What a pathetic spy!";
            alertphrase3 = "Let us not bother the Boss with it. Kill it now!";
            break;
        default:
            break;
    }

    
    if (!objectp(Squad))
    {

    switch (toughness)
    {
    case 0..20:
        Squad = clone_object(IGARD_NPC + "igard_orc.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();
        break;
    case 21..40:
        Squad = clone_object(IGARD_NPC + "igard_orc.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc2.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();
        break;
    case 41..60:
        Squad = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();
        break;
    case 61..80:
        Squad = clone_object(IGARD_NPC + "igard_orc2.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad3 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad3->set_restrain_path(IGARD_PLAIN);
        Squad3->arm_me();
        Squad3->move_living("down", TO);
        Squad3->command("shout " + alertphrase3);
        Squad3->ambush_retreat();
        break;
    case 81..100:
        Squad = clone_object(IGARD_NPC + "igard_orc3.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad3 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad3->set_restrain_path(IGARD_PLAIN);
        Squad3->arm_me();
        Squad3->move_living("down", TO);
        Squad3->command("shout " + alertphrase3);
        Squad3->ambush_retreat();
        break;
    case 101..120:
        Squad = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad3 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad3->set_restrain_path(IGARD_PLAIN);
        Squad3->arm_me();
        Squad3->move_living("down", TO);
        Squad3->command("shout " + alertphrase3);
        Squad3->ambush_retreat();
        break;
    case 121..140:
        Squad = clone_object(IGARD_NPC + "igard_orc4.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad3 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad3->set_restrain_path(IGARD_PLAIN);
        Squad3->arm_me();
        Squad3->move_living("down", TO);
        Squad3->command("shout " + alertphrase3);
        Squad3->ambush_retreat();
        break;
    default:
        Squad = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad->set_restrain_path(IGARD_PLAIN);
        Squad->arm_me();
        Squad->move_living("down", TO);
        Squad->command("shout " + alertphrase);
        Squad->ambush_retreat();

        Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad2->set_restrain_path(IGARD_PLAIN);
        Squad2->arm_me();
        Squad2->move_living("down", TO);
        Squad2->command("shout " + alertphrase2);
        Squad2->ambush_retreat();

        Squad3 = clone_object(IGARD_NPC + "igard_uruk.c");
        Squad3->set_restrain_path(IGARD_PLAIN);
        Squad3->arm_me();
        Squad3->move_living("down", TO);
        Squad3->command("shout " + alertphrase3);
        Squad3->ambush_retreat();
        break;
    }
    return;
    }
}


public void
spring_quest_trap()
{
    Squad = clone_object(IGARD_NPC + "igard_uruk.c");
    Squad->arm_me();
    Squad->move_living("down", TO);
    Squad->ambush_retreat();

    Squad2 = clone_object(IGARD_NPC + "igard_uruk.c");
    Squad2->arm_me();
    Squad2->move_living("down", TO);
    Squad2->ambush_retreat();

    Squad3 = clone_object(IGARD_NPC + "igard_uruk.c");
    Squad3->arm_me();
    Squad3->move_living("down", TO);
    Squad3->ambush_retreat();

    set_alarm(10.0, 0.0, &clone_npcs(Qsquad, IGARD_NPC + "igard_uruk.c", -1.0));
    return;
}

public int 
catch_all(string str)
{
    string  vb = query_verb();
    object trappee;
    trappee = TP;

    TO->remove_item("net");

    if (!AMBUSHED) 
        return 0;

    if (!TP->query_enemy() || !TP->query_attack())
    {
    TP->remove_prop(IGARD_AMBUSHED);
    TO->remove_item("net");

    write("You finally work your way out of the meshing by ripping "
        + "it to shreds!\n");
    tell_room(environment(trappee), QCTNAME(trappee) + " finally works "
        + HIS_HER(trappee) + " way out of the meshing by ripping it to "
        + "shreds!\n", ({trappee}));

    return 0;
    }
    
    add_item(({"net", "netting", "mesh", "meshing"}), "The netting "
        + "is not all that tough, but it is so gnarled and stretched "
        + "that it is almost impossible to break out of.\n");

    switch (vb)
    {
    case "north":
    case "northeast":
    case "northwest":
    case "southwest":
    case "southeast":
    case "west":
    case "up":
    case "down":
    case "south":
    case "east":
        WRITE("You are tangled in meshing and cannot seem to break away!");
        return 1;
        break;
    default:
        return 0;
    }
}

public int
initiate_trap()
{
    add_action(catch_all, "", 1);
}