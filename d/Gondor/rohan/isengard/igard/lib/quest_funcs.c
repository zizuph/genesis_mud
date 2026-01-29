/*
 *  IGARD_LIB + "quest_funcs.c"
 *
 *  Various functions common to Isengard quest rooms.
 *
 *  Last modified by Alto, 5 December 2001
 *
 */

#pragma strict_types

#include "../igard_defs.h"

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "/sys/formulas.h"

/* Prototypes */

public int           igard_stage_check();
public int           send_igard_caverns();
public int           send_igard_orcwarg();
public int           send_igard_furnace();
public int           send_igard_wall();
public int           cavern_instructions();
public int           orcwarg_instructions();
public int           furnace_instructions();
public int           wall_instructions();


public int
igard_stage_check()
{
    if (FIW && FFI && FOI)
    {
        send_igard_caverns();
        return 1;
    }

    if (FIW && FFI)
    {
        send_igard_orcwarg();
        return 1;
    }

    if (FIW && FOI)
    {
        send_igard_furnace();
        return 1;
    }

    if (FFI && FOI)
    {
        send_igard_wall();
        return 1;
    }

    if (FIW)
    {
        switch (random(2))
        {
            case 0:
                send_igard_orcwarg();
                break;
            case 1:
                send_igard_furnace();
                break;
            default:
                break;
        }
        return 1;
    }

    if (FFI)
    {
        switch (random(2))
        {
            case 0:
                send_igard_orcwarg();
                break;
            case 1:
                send_igard_wall();
                break;
            default:
                break;
        }
        return 1;
    }

    if (FOI)
    {
        switch (random(2))
        {
            case 0:
                send_igard_wall();
                break;
            case 1:
                send_igard_furnace();
                break;
            default:
                break;
        }
        return 1;
    }

        write("This is one of those wrongness in space and time messages, "
            + "which means you should probably file a bugreport in this "
            + "room.\n");

    return 1;
}


public int
send_igard_caverns()
{
    TP->add_prop(SENT_IGARD_CAVERNS, 1);
    cavern_instructions();
    return 1;
}


public int
send_igard_orcwarg()
{
    switch (random(2))
    {
        case 0:
            TP->add_prop(SENT_ORCWARG_IGARD1, 1);
            break;
        case 1:
            TP->add_prop(SENT_ORCWARG_IGARD2, 1);
            break;
        default:
            break;
    }
    orcwarg_instructions();
    return 1;
}


public int
send_igard_furnace()
{
    switch (random(3))
    {
        case 0:
            TP->add_prop(SENT_FURNACE_IGARD1, 1);
            break;
        case 1:
            TP->add_prop(SENT_FURNACE_IGARD2, 1);
            break;
        case 2:
            TP->add_prop(SENT_FURNACE_IGARD3, 1);
            break;
        default:
            break;
    }
    furnace_instructions();
    return 1;
}


public int
send_igard_wall()
{
    switch (random(7))
    {
        case 0:
            TP->add_prop(SENT_IGARD_WALL1, 1);
            break;
        case 1:
            TP->add_prop(SENT_IGARD_WALL2, 1);
            break;
        case 2:
            TP->add_prop(SENT_IGARD_WALL3, 1);
            break;
        case 3:
            TP->add_prop(SENT_IGARD_WALL4, 1);
            break;
        case 4:
            TP->add_prop(SENT_IGARD_WALL5, 1);
            break;
        case 5:
            TP->add_prop(SENT_IGARD_WALL6, 1);
            break;
        case 6:
            TP->add_prop(SENT_IGARD_WALL7, 1);
            break;
        default:
            break;
    }
    wall_instructions();
    return 1;
}


public int
cavern_instructions()
{
    object cavern_clue;

    if (SIC)
    {
        cavern_clue = clone_object(IGARD_QUEST_OBJ + "cavern_clue.c");
        cavern_clue->move(TP);
        TP->catch_tell("You find a " + cavern_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    return 1;
}


public int
orcwarg_instructions()
{
    object orc_clue, warg_clue;

    if (SOI1)
    {
        orc_clue = clone_object(IGARD_QUEST_OBJ + "orc_clue.c");
        orc_clue->move(TP);
        TP->catch_tell("You find a " + orc_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SOI2)
    {
        warg_clue = clone_object(IGARD_QUEST_OBJ + "warg_clue.c");
        warg_clue->move(TP);
        TP->catch_tell("You find a " + warg_clue->query_short()
            + " on the floor and pick it up.\n"); 
        return 1;
    }        

    return 1;
}


public int
furnace_instructions()
{
    object furn1_clue, furn2_clue, furn3_clue;

    if (SFI1)
    {
        furn1_clue = clone_object(IGARD_QUEST_OBJ + "furn1_clue.c");
        furn1_clue->move(TP);
        TP->catch_tell("You find a " + furn1_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SFI2)
    {
        furn2_clue = clone_object(IGARD_QUEST_OBJ + "furn2_clue.c");
        furn2_clue->move(TP);
        TP->catch_tell("You find a " + furn2_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SFI3)
    {
        furn3_clue = clone_object(IGARD_QUEST_OBJ + "furn3_clue.c");
        furn3_clue->move(TP);
        TP->catch_tell("You find a " + furn3_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    return 1;
}


public int
wall_instructions()
{
    object wall1_clue, wall2_clue, wall3_clue, wall4_clue;
    object wall5_clue, wall6_clue, wall7_clue;

    if (SIW1)
    {
        wall1_clue = clone_object(IGARD_QUEST_OBJ + "wall1_clue.c");
        wall1_clue->move(TP);
        TP->catch_tell("You find a " + wall1_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SIW2)
    {
        wall2_clue = clone_object(IGARD_QUEST_OBJ + "wall2_clue.c");
        wall2_clue->move(TP);
        TP->catch_tell("You find a " + wall2_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SIW3)
    {
        wall3_clue = clone_object(IGARD_QUEST_OBJ + "wall3_clue.c");
        wall3_clue->move(TP);
        TP->catch_tell("You find a " + wall3_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SIW4)
    {
        wall4_clue = clone_object(IGARD_QUEST_OBJ + "wall4_clue.c");
        wall4_clue->move(TP);
        TP->catch_tell("You find a " + wall4_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }
    if (SIW5)
    {
        wall5_clue = clone_object(IGARD_QUEST_OBJ + "wall5_clue.c");
        wall5_clue->move(TP);
        TP->catch_tell("You find a " + wall5_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SIW6)
    {
        wall6_clue = clone_object(IGARD_QUEST_OBJ + "wall6_clue.c");
        wall6_clue->move(TP);
        TP->catch_tell("You find a " + wall6_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    if (SIW7)
    {
        wall7_clue = clone_object(IGARD_QUEST_OBJ + "wall7_clue.c");
        wall7_clue->move(TP);
        TP->catch_tell("You find a " + wall7_clue->query_short() 
            + " on the floor and pick it up.\n"); 
        return 1;
    }

    return 1;
}










