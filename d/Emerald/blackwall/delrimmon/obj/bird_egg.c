/*
 *  /d/Emerald/blackwall/delrimmon/obj/bird_egg.c
 *
 *  A speckled blue egg, perhaps to be found in a birds nest in
 *  the Blackwall Mountains area.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  TBD: Add support for boiling the egg in a container of water
 */
#pragma strict_types
inherit "/std/food";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define    STUFFED        TP->query_stuffed()

/*
 *  Global Variables
 */
int    Is_Egg = 1;      /* False if only eggshells remain */
int    Hard_Boiled = 0; /* True if egg has been cooked */

void
create_food()
{
    set_name("egg");
    add_adj( ({"small", "blue", "speckled"}) );

    set_short("small blue egg");
    set_long(BSN("Light gleams dully off the polished surface of this"
               + " speckled blue egg."));

    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 120);
}

/*
 *  Function name: eat_egg
 *  Description  : Allow goblins to eat the egg raw, but other races
 *                 are more graceful, and simply break the egg.
 *  Arguments    : str - what the player tried to eat
 *  Returns      : 1 - success, 0 - failed
 */
int
eat_egg(string str)
{
    if (!strlen(str))
        NFN0("Eat what?");

    if (str != "egg" && str != "blue egg" &&
        str != "speckled egg" &&
        str != "speckled blue egg")
    {
        NFN0("What do you wish to eat?");
    }

    if (!Is_Egg)
    {
        NFN0("The eggshells are not edible.");
    }

    if (TP->query_race() == "goblin")
    {
        write(BSN("Cramming the entire egg in your mouth, you"
                + " crunch it to pieces and swallow the slimy"
                + " mass in one gulp."));
        say(QCTNAME(TP) + " crams a small blue egg in " +
            TP->query_possessive() + " mouth and crunches the mass of"
          + " yoke and shell into a slavering mess.\n");


        TP->set_stuffed(STUFFED + 4); /* Feed the player! */
        TO->remove_object();
        return 1;
    }

    if (Hard_Boiled)
    {
        WRITE("Peeling the shell off of the egg, you bite"
                + " carefully into the tender innards. Realizing"
                + " how tasty it is, you eat the remainder with"
                + " relish!");
        SAY(" peels the shell off of the blue speckled egg and"
          + " eats the hard-boiled interior.");

        TP->set_stuffed(STUFFED + 4); /* Feed the player! */
        TO->remove_object();

        return 1;
    }

    WRITE("You crack the egg to eat it, but since it is"
            + " raw, the innards spill out and are lost on"
            + " the ground.");

    add_name("shell");
    add_adj( ({"egg", "broken"}) );
    set_short("broken egg shell");
    set_long(BSN("These are the remains of a small egg shell. The"
               + " blue finish of the surface with tiny brown"
               + " specks is still somewhat visible along the"
               + " surface."));
    Is_Egg = 0;

    return 1;
}

void
init()
{
    ::init();

    add_action(eat_egg, "eat");
}
