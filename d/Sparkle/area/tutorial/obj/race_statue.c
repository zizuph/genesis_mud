/*
 *  /d/Sparkle/area/tutorial/obj/race_statue.c
 *
 *  These statues provide players with information about the
 *  various races of Genesis during the pre-creation tutorial
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 1, 2016 to fix article for elf
 *  Updated the race information to match the new race system, 
 *  Cherek, March 2023
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>

/* global variables */
public string      Race;

/* prototypes */
public void        create_object();
public string      short_desc();
public string      describe();
public string      name();
public void        set_statue(string s) { Race = s; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("statue");
    add_name("_tutorial_statue");
    set_adj("great");
    set_short(short_desc);
    set_long(describe);

    add_prop(OBJ_M_NO_GET, "The statue is too heavy to move.\n");
} /* create_object */


/*
 * Function name:        short_desc
 * Description  :        provide the appropriate short
 *                       description for the race type
 * Returns      :        string - the short description
 */
public string
short_desc()
{
    return "statue of " + LANG_ADDART(Race);
} /* short_desc */

/*
 * Function name:        name
 * Description  :        racial name for statue
 * Returns      :        string - second name
 */
public string
name()
{
    return Race + " statue";
} /* name */

/*
 * Function name:        describe
 * Description  :        provide a description for each race
 *                       type the statue might be
 * Returns      :        string - the description
 */
public string
describe()
{
    switch (Race)
    {
        case "hobbit":
            return "This is a beautiful statue of a quite generic-looking"
              + " hobbit. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As a hobbit you may select two of the following six      |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Stealthy                                                 |\n"
     + "   |  You will get a ten skill level bonus (up to superior     |\n"
     + "   |  guru) in sneak and hide.                                 |\n"
     + "   |                                                           |\n"
     + "   |  Fleet-footed                                             |\n"
     + "   |  If you are not in combat, you will be able to recover    |\n"
     + "   |  your energy quicker after you get tired.                 |\n"
     + "   |                                                           |\n"
     + "   |  Insatiable                                               |\n"
     + "   |  You will be able to eat more food than other people,     |\n"
     + "   |  meaning you will not tire as easily.                     |\n"
     + "   |                                                           |\n"
     + "   |  Tenacious                                                |\n"
     + "   |  You will recover lost experience (from death, leaving    |\n"
     + "   |  guilds, etc.) faster than other people.                  |\n"
     + "   |                                                           |\n"
     + "   |  Opportunistic                                            |\n"
     + "   |  You will have a slightly higher chance of scoring a      |\n"
     + "   |  critical hit (additional damage) on your enemy.          |\n"
     + "   |                                                           |\n"
     + "   |  Explorer                                                 |\n"
     + "   |  You will get a ten skill level bonus in herbalism,       |\n"
     + "   |  awareness, location sense, and tracking.                 |\n"
     + "   |                                                           |\n"
     + "   +-----------------------------------------------------------+\n";
            break;
        case "human":
            return "This is a beautiful statue of a quite generic-looking"
              + " human. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As a human you may select two of the following six       |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Good memory                                              |\n"
     + "   |  You will be able to remember twenty-five percent more    |\n"
     + "   |  names compared to other people.                          |\n"
     + "   |                                                           |\n"
     + "   |  Eye for detail                                           |\n"
     + "   |  You will get a twenty skill level bonus (up to superior  |\n"
     + "   |  guru) in trading, appraise object, and appraise value.   |\n"
     + "   |                                                           |\n"
     + "   |  Light-fingered                                           |\n"
     + "   |  You will get a twenty skill level bonus (up to superior  |\n"
     + "   |  guru) in pick pocket.                                    |\n"
     + "   |                                                           |\n"
     + "   |  Tenacious                                                |\n"
     + "   |  You will recover lost experience (from death, leaving    |\n"
     + "   |  guilds, etc.) faster than other people.                  |\n"
     + "   |                                                           |\n"
     + "   |  Scavenger                                                |\n"
     + "   |  You will occasionally find more coins on fallen enemies  |\n"
     + "   |  compared to other people.                                |\n"
     + "   |                                                           |\n"
     + "   |  Apothecary                                               |\n"
     + "   |  The cooldown time between using herbs will be slightly   |\n"
     + "   |  reduced for you.                                         |\n"
     + "   |                                                           |\n"
     + "   +-----------------------------------------------------------+\n";
            break;
        case "goblin":
            return "This is a beautiful statue of a quite generic-looking"
              + " goblin. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As a goblin you may select two of the following six      |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Stalwart                                                 |\n"
     + "   |  You will be able to carry heavier loads than other       |\n"
     + "   |  people before becoming encumbered by it.                 |\n"
     + "   |                                                           |\n"
     + "   |  Scavenger                                                |\n"
     + "   |  You will occasionally find more coins on fallen enemies  |\n"
     + "   |  compared to other people.                                |\n"
     + "   |                                                           |\n"
     + "   |  Opportunistic                                            |\n"
     + "   |  You will have a slightly higher chance of scoring a      |\n"
     + "   |  critical hit (additional damage) on your enemy.          |\n"
     + "   |                                                           |\n"
     + "   |  Light-fingered                                           |\n"
     + "   |  You will get a twenty skill level bonus (up to superior  |\n"
     + "   |  guru) in pick pocket.                                    |\n"
     + "   |                                                           |\n"
     + "   |  Stealthy                                                 |\n"
     + "   |  You will get a ten skill level bonus (up to superior     |\n"
     + "   |  guru) in sneak and hide.                                 |\n"
     + "   |                                                           |\n"
     + "   |  Resilient                                                |\n"
     + "   |  Your resistance to magic, and especially poison, will    |\n"
     + "   |  be stronger than other people.                           |\n"
     + "   |                                                           |\n"
     + "   +-----------------------------------------------------------+\n";
            break;
        case "gnome":
            return "This is a beautiful statue of a quite generic-looking"
              + " gnome. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As a gnome you may select two of the following six       |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Resilient                                                |\n"
     + "   |  Your resistance to magic, and especially poison, will    |\n"
     + "   |  be stronger than other people.                           |\n"
     + "   |                                                           |\n"
     + "   |  Scotopic vision                                          |\n"
     + "   |  You will be able to see inside many areas covered in     |\n"
     + "   |  non-magical darkness.                                    |\n"
     + "   |                                                           |\n"
     + "   |  Eye for detail                                           |\n"
     + "   |  You will get a twenty skill level bonus (up to superior  |\n"
     + "   |  guru) in trading, appraise object, and appraise value.   |\n"
     + "   |                                                           |\n"
     + "   |  Stealthy                                                 |\n"
     + "   |  You will get a ten skill level bonus (up to superior     |\n"
     + "   |  guru) in sneak and hide.                                 |\n"
     + "   |                                                           |\n"
     + "   |  Good memory                                              |\n"
     + "   |  You will be able to remember twenty-five percent more    |\n"
     + "   |  names compared to other people.                          |\n"
     + "   |                                                           |\n"
     + "   |  Well-connected                                           |\n"
     + "   |  You will get a twenty-five percent discount when         |\n"
     + "   |  exchanging coins at all Gnomes of Genesis (GoG) banks.   |\n"
     + "   |                                                           |\n"
     + "   +-----------------------------------------------------------+\n";
            break;
        case "elf":
            return "This is a beautiful statue of a quite generic-looking"
              + " elf. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As an elf you may select two of the following six        |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Fleet-footed                                             |\n"
     + "   |  If you are not in combat, you will be able to recover    |\n"
     + "   |  your energy quicker after you get tired.                 |\n"
     + "   |                                                           |\n"
     + "   |  Scotopic vision                                          |\n"
     + "   |  You will be able to see inside many areas covered in     |\n"
     + "   |  non-magical darkness.                                    |\n"
     + "   |                                                           |\n"
     + "   |  Apothecary                                               |\n"
     + "   |  The cooldown time between using herbs will be slightly   |\n"
     + "   |  reduced for you.                                         |\n"
     + "   |                                                           |\n"
     + "   |  Explorer                                                 |\n"
     + "   |  You will get a ten skill level bonus (up to superior     |\n"
     + "   |  guru) in herbalism, awareness, location sense, and       |\n"
     + "   |  tracking.                                                |\n"
     + "   |                                                           |\n"
     + "   |  Stealthy                                                 |\n"
     + "   |  You will get a ten skill level bonus (up to superior     |\n"
     + "   |  guru) in sneak and hide.                                 |\n"
     + "   |                                                           |\n"
     + "   |  Light-footed                                             |\n"
     + "   |  There will be a ten percent chance that you will not     |\n"
     + "   |  leave any tracks behind when moving.                     |\n"
     + "   |                                                           |\n" 
     + "   +-----------------------------------------------------------+\n";
            break;
        case "dwarf":
            return "This is a beautiful statue of a quite generic-looking"
              + " dwarf. It's actually hard to even determine the gender."
              + " Your attention is immediately drawn to a large sign at"
              + " the base of the statue that reads:\n\n"
     + "   +-----------------------------------------------------------+\n"
     + "   |                                                           |\n"
     + "   |  As a dwarf you may select two of the following six       |\n"
     + "   |  racial abilities:                                        |\n"
     + "   |                                                           |\n"
     + "   |  Stalwart                                                 |\n"
     + "   |  You will be able to carry heavier loads than other       |\n"
     + "   |  people before becoming encumbered by it.                 |\n"
     + "   |                                                           |\n"
     + "   |  Good memory                                              |\n"
     + "   |  You will be able to remember twenty-five percent more    |\n"
     + "   |  names compared to other people.                          |\n"
     + "   |                                                           |\n"
     + "   |  Resilient                                                |\n"
     + "   |  Your resistance to magic, and especially poison, will    |\n"
     + "   |  be stronger than other people.                           |\n"
     + "   |                                                           |\n"
     + "   |  Strong liver                                             |\n"
     + "   |  You will heal slightly faster due to your ability to     |\n"
     + "   |  consume more alcohol than other people.                  |\n"
     + "   |                                                           |\n"
     + "   |  Insatiable                                               |\n"
     + "   |  You will be able to eat more food than other people,     |\n"
     + "   |  meaning you will not tire as easily.                     |\n"
     + "   |                                                           |\n"
     + "   |  Eye for detail                                           |\n"
     + "   |  You will get a twenty skill level bonus (up to superior  |\n"
     + "   |  guru) in trading, appraise object, and appraise value.   |\n"
     + "   |                                                           |\n"
     + "   +-----------------------------------------------------------+\n";
            break;
        default:
            return "The statue is bugged.\n";
    }

    return "";
} /* describe */
