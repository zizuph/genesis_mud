/*
 *  /d/Sparkle/area/orc_temple/wep/quest_weapon.c
 *
 *  The quest item for the enchanter's quests in the Orc Temple.
 *
 *  Created August 2010, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Sparkle/sys/quests.h"
#include "../defs.h"


/* Global Variables */
public mixed       Imbued = 0; /* Has the dagger been imbued? */

/* Prototypes */
public void        create_weapon();
public string      describe(string which = "");
public string      short_desc();

public void        set_imbued(mixed m) { Imbued = m; }
public mixed       query_imbued() { return Imbued; }

public void
create_weapon()
{
    set_name("dagger");
    add_name( ({ "knife", QUEST_WEAPON }) );
    add_adj( ({ "nullstone", "null", "stone", "unusual" }) );

    set_short("@@short_desc@@");
    set_long("@@describe@@");
    set_default_weapon(20, 15, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(5, W_SWORD) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5,5) + random(45));
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. Perhaps you"
      + " could <show> it to someone, instead?\n");
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. Perhaps you"
      + " could <show> it to someone, instead?\n");

    add_item( ({ "glow" }), &describe("glow"));
    add_item( ({ "dull glow" }), &describe("dull glow"));
} /* create_weapon */


/*
 * Function name:        describe
 * Description  :        Provide a specialized message for the weapon
 *                       if it has been imbued.
 * Arguments    :        string which - what are we describing?
 * Returns      :        string - the desciption 
 */
public string
describe(string which = "")
{
    string  desc = "The stone of this dagger is very unusual, and seems"
      + " to produce an odd magnetic sensation. ";

    if (strlen(which))
    {
        if (Imbued)
        {
            return "The nullstone dagger appears to have been imbued"
              + " with strange power, but the power seems unstable, and"
              + " is apparently fading.\n";
        }

        return "You find no " + which + ".\n";
    }

    if (!this_player()->test_bit("Sparkle",
            ORCTEMPLE_WEAPON_GROUP,
            ORCTEMPLE_WEAPON_BIT))
    {
        desc += "This is what the enchanter asked you to find! You should"
              + " return and <show> it to him!";
    }

    if (this_player()->test_bit("Sparkle",
            ORCTEMPLE_FLUTE_GROUP,
            ORCTEMPLE_FLUTE_BIT) &&
        !this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        if (Imbued)
        {
            desc += "This object is surrounded by a"
              + " dull glow that seems to be growing weaker by the"
              + " minute.";
        }
        else
        {
            desc += "You need to follow the methods detailed in the High"
              + " Priest's journal to find a way to imbue this weapon using"
              + " ghost tears that you find. Use a bone flute in the cells"
              + " on the second level of the orc dungeons to summon ghosts"
              + " that you can kill to get the tears.";
        }
    }

    /* If players have already completed the quest, they have no
     * business owning these anymore.
     */
    if (this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        desc += "As you are gazing at it, the dagger evaporates into"
          + " blackish smoke, and drifts away!";
        set_alarm(0.0, 0.0, &remove_object());
    }

    return desc + "\n";
} /* describe */


/*
 * Function name:        short_desc
 * Description  :        provide a state-dependant short description
 * Returns      :        string - the description
 */
public string
short_desc()
{
    if (Imbued)
    {
        return "unusual nullstone dagger";
    }

    return "nullstone dagger";
} /* short_desc */