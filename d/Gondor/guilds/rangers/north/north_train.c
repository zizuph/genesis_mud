/*
 *  /d/Gondor/guilds/rangers/north/north_train.c
 *  
 *  Training hall of the Rangers of the North.
 *
 *  Coded by Alto and Gwyneth, 14 July 2001
 *  
 *   Previous incarnation:
 *
 *   Rangers of the North training hall - coded by Elessar
 *   Gwyneth, Aug 13, 2002 - Made alterations for the recode
 *
 */
inherit "/d/Gondor/guilds/rangers/train_base.c";
/*
inherit "/d/Shire/lib/training";
*/

#include "../rangers.h"

/*
inherit (RANGERS_NOR_DIR + "north_funcs.c");
*/

#include <files.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string      long_desc();
public string      exa_plaque();
public string      exa_sign();

string
long_desc()
{
    string txt;

/*
    if (gTstand->query_torch_is_lit())
        txt = "The room is lit by an iron torch stand ";
    else
        txt = "An iron torch stand is ";
*/

    txt = "An iron torch stand is ";

    return "This large hall appears to be designed for the express purpose "
        + "of combat training and practice. The stone floor is free of "
        + "furniture, and is painted with an intricate pattern of concentric "
        + "and overlapping circles. A master ranger passes through the room "
        + "now and then, pausing to examine your form and technique. The "
        + "hall is large and has a vaulted ceiling. Tapestries hang on each "
        + "of the four walls. There is a wooden plaque on one of the walls. "
        + txt + "mounted on the north wall.\n";
}

void
reset_room()
{
/*
     set_alarm(1.0, 0.0, &north_add_torch());
*/
}

void
create_trainhall()
{
    set_short("the Training Hall of the Rangers of the North");
    set_long(&long_desc());

    add_exit(RANGERS_NOR_DIR + "n_corridor", "east");
    add_exit(RANGERS_NOR_DIR + "w_corridor", "south");

    /*
    north_add_items();
*/

    add_item(({"room", "hall", "large hall"}), &long_desc());
    add_item(({"tapestry", "tapestries"}), "Each tapestry depicts a "
        + "different forest, and the forests are also set in different "
        + "seasons. On the west tapestry is a willow-meadow in spring, on "
        + "the south an elm-wood in summer, on the east a beech-forest in "
        + "autumn and on the north wall is depicted a pine-forest in "
        + "winter.\n");
    add_item(({"north wall", "wall to the north"}), "The north wall is made "
        + "of stone like the other walls, but is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"circles", "circle", "concentric circles", "floor",
        "stone floor", "overlapping circles"}), "The circles are painted "
        + "in a perplexing array of patterns. Some circles lie within "
        + "larger circles, while others stand alone, and yet others overlap. "
        + "When a Master ranger works with the new recruits, he or she uses "
        + "these circles to test the agility of each new ranger. As rangers "
        + "rise in skill, they are able to leap and roll through more "
        + "circles before the Master leaves them flat on their backs and "
        + "bruised from blows with a blunted practice sword.\n");

    add_item(({"ranger", "master ranger"}), "The master ranger is old and "
        + "grizzled from years of battle-won experience. He does not look "
        + "entirely happy with your progress.\n");

    add_item(({"wooden plaque", "plaque"}), &exa_plaque());
    add_cmd_item(({"wooden plaque", "plaque"}), "read", &exa_plaque());
    //add_cmd_item(({"sign", "large sign"}), "read", &exa_sign());
    //add_item(({"sign", "large sign"}), &exa_sign());

    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");

    set_company_num(NORTH_LEVEL);
    add_prop(ROOM_M_NO_SCRY, 1);

    add_prop(ROOM_I_INSIDE, 1);
/*
    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, &daylight()));
*/

    reset_room();
}

public string
exa_plaque()
{
    return "Here you may <meditate> to set your stat-preferences, and "
        + "<learn> or <improve> your skills. You may also <list guilds> "
        + "to discover information about the guilds of which you are a "
        + "member.\n";
}

public string
exa_sign()
{
   return "\t __________________________________________\n" +
          "\t/                                          \\\n" +
          "\t|         Weapon Specialization            |\n" +
          "\t|            ~~~~~~~~~~~~~~~~~             |\n" +
          "\t|         Ye may choose a weapon           |\n" +
          "\t|      skill in which to specialize,       |\n" +
          "\t|   but do not make this choice lightly!   |\n" +
          "\t|     For once thy choice is made, the     |\n" +
          "\t|        Master Ranger will charge         |\n" +
          "\t|      additional fees for altering        |\n" +
          "\t|        thy course of training            |\n" +
          "\t|      later. To select a specialty        |\n" +
          "\t|             ye may either:               |\n" +
          "\t|                                          |\n" +
          "\t|            < train bow >                 |\n" + 
          "\t|               ~~or~~                     |\n" +
          "\t|            < train sword >               |\n" +
          "\t|                                          |\n" +
          "\t|      Take heed to choose wisely!         |\n" +
          "\t|                                          |\n" +
          "\t|                                          |\n" +
         "\t\\__________________________________________/\n";
}

public varargs int
sk_query_max(int snum, int silent)
{
    object who = this_player();
    int wep_choice = query_primary(who);

    if (who->query_ranger_has_virtues())
    {
        return ::sk_query_max(snum, silent);
    }

    /* Give them max skill for their primary weapon. */
    if (snum == query_primary(who))
        return ::sk_query_max(snum, silent);

    /* Give them AG skill for their secondary weapon. */
    if (snum == query_secondary(who))
        return SS_SKILL_DESC[snum][4];

    /* Neither primary nor secondary weapon skills */
    return ::sk_query_max(snum, silent);
}
