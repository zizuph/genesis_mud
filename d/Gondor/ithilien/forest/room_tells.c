/*
 * Haradrim camp room tells
 * -- Finwe, July 2005
 *
 *   Modification log:
 *
 *   -- 28-Mar-2007, Toby:
 *      Fixed typo flys -> flies
 *      Also added a few tells in the Morgul spirit.
 */
#pragma strict_types

#include "/d/Gondor/defs.h"

inherit "/d/Gondor/std/tell.c";

public void add_harad_camp_tells()
{
    set_tell_time(240);
    add_tell("Somewhere in the camp you hear 'Get up and fight, you pile " +
        "of horse dung!'\n");
    add_tell("You hear from nearby, 'To arms! We're under attack!'\n");
    add_tell("Sounds of battle echo from nearby.\n");
    add_tell("A feeling of dread and hopelessness falls on you as a " +
        "fell beast flies overhead.\n");
    add_tell("A group of Haradrim march past you, eyeing you suspiciously.\n");
    add_tell("The smell of garbage floats past by.\n");
    add_tell("The smell of garbage wafts past by.\n");
    add_tell("A warm breeze blows past.\n");
    add_tell("Dark clouds float past by from the east.\n");
    add_tell("Nearby you hear, 'You slugs, pay attention!'\n");
    add_tell("Nearby you hear, 'You miserable wretches, get to work!'\n");
    add_tell("You catch snatches of mumblings and incoherent muttering " +
        "sounds from nearby.\n");

}


public void add_orc_camp_tells()
{
    set_tell_time(120+random(90));
    add_tell("Dark clouds drift in from the east.\n");
    add_tell("Somewhere you hear, 'You worthless maggots, get to work!'\n");
    add_tell("A fetid smell drifts past.\n");
    add_tell("Nearby you hear, 'Wake up maggots, there are enemies in the camp!'\n");
    add_tell("An orc watches you suspiciously.\n");
    add_tell("Orcs push past you and march on.\n");
    add_tell("The sounds of an argument breaks out in the distance. Suddenly it ends.\n");
    add_tell("Grunts and snorts echo nearby.\n");
    add_tell("A flock of birds wheel overhead then fly off to the east.\n");
    add_tell("Dread and hopelessness falls on you as a fell beast flies overhead.\n");
    add_tell("Dread rush through your veins as a fell beast circle and screeches far overhead.\n");
    add_tell("An orc head flies past you as an argument between two orcs stops abruptly.\n");
}
