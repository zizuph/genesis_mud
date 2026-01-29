/*
 *  /d/Gondor/guilds/rangers/ithilien/train.c
 *
 * Traininghall of the Rangers of Ithilien
 *
 * The train hall of Ithilien Company
 * Modified by Olorin, 30-Oct-1993
 *
 * 26 August 1998, Gnadnar: make real curtain (door) so can
 *  block access to training recess if officers are using it 
 *  for privacy, add some items, tidy up.
 *
 * 13 October 1998, Gnadnar: determine curtain status every time
 *  long is called, rather than storing it and only updating
 *  when it changes. less efficient, but the stored strings
 *  were sometimes getting out of sync. :-(
 *
 * 20 July 2001, Alto: revise inheritance and make minor changes
 * to fit new rangers theme.
 *
 * 12 October 2003, Gwyneth: Revised to allow distribution of
 * weapon skills.
 *
 * 24 March 2004, Tigerlily removed curtain and Mablung--Faramir/
 * Mablung added instead to window for enlist processes.
 */
inherit "/d/Gondor/guilds/rangers/train_base.c";
/*
inherit "/d/Shire/lib/training.c";
*/


#include "../rangers.h"

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

/* A few definitions */

/* prototypes */
public string   exa_plaque();
public string   exa_sign();



public varargs int
sk_query_max(int snum, int silent)
{
    object who = this_player();
    
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


public void 
create_trainhall() 
{ 

    FIX_EUID;

    set_short("Rangers of Ithilien Training Chamber");
    set_long("This small recess, tucked at the back of the rock chamber, has "
        + "rough walls and a low sloping ceiling. A torch fixed into an " 
        + "iron torch stand casts a flickering warm light around the "
        + "room. A green banner embroidered with a silver rising moon "
        + "hangs on the inner wall. A wooden plaque is tacked to the wall "
        + "to the left.\n");

    add_exit((RANGERS_ITH_DIR + "rackchamber"), "west", &check_ranger(1));
    add_exit((RANGERS_ITH_DIR + "closet"), "north", &check_ranger(1));

    add_item(({"recess", "room"}), &long());
    add_item(({"wooden plaque", "plaque"}), &exa_plaque());

    add_item(({"banner"}), "The rich fabric of the banner is deep green, "
        + "with a soft nap. In its center is embroidered a silvery rising "
        + "moon, the emblem of Ithilien.\n");
    add_item(({"rich fabric", "fabric"}), "The deep green fabric of the "
        + "banner is soft, with a nap like velvet.\n");
    add_item(({"silvery rising moon", "silvery moon", "rising moon", 
        "moon", "emblem"}), "The Ithilien moon, embroidered in silver, "
        + "seems almost to have a pale light of its own.\n");
    add_item(({"north wall", "south wall",}), "The wall is simply stone, "
        + "rough and unadorned.\n");
    add_item(({"inner wall", "east wall"}), "Little of the inner wall can "
        + "be seen behind the banner.\n");
    add_item(({"torch", "torch stand", "stand"}), "A torch is contained "
        + "within the iron torch stand and casts a warm light in the " 
        + "room.\n");

    add_cmd_item(({"wooden plaque", "plaque"}), "read", &exa_plaque());
    //add_cmd_item(({"sign", "large sign"}), "read", &exa_sign());
    add_cmd_item( ({ "nap", "banner", "rich fabric", "fabric" }),
        ({ "touch", "feel", }), "The banner is very soft to the touch.\n");
    add_cmd_item( ({ "silvery rising moon", "silvery moon", "rising moon",
        "moon", "emblem", }), ({ "touch", "feel", }), "The silvery moon "
        + "is cool and smooth beneath your fingers.\n");
    //add_item(({"sign", "large sign"}), &exa_sign());

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    set_company_num(ITHILIEN_LEVEL);
}


public string
exa_plaque()
{
    return ("Here you may <meditate> to set your stat-preferences, and "
        + "<learn> or <improve> your skills. You may also <list guilds> "
        + "to discover information about the guilds of which you are a "
        + "member.\n");
}


public string
exa_sign()
{
   return "\t __________________________________________\n" +
          "\t/                                          \\\n" +
          "\t|         Weapon Specialization            |\n" +
          "\t|            ~~~~~~~~~~~~~~~~~             |\n" +
          "\t|         You may choose a weapon          |\n" +
          "\t|      skill in which to specialize,       |\n" +
          "\t|   but do not make this choice lightly!   |\n" +
          "\t|     For once your choice is made, the    |\n" +
          "\t|        Master Ranger will charge         |\n" +
          "\t|      additional fees for altering        |\n" +
          "\t|        your course of training           |\n" +
          "\t|      later. To select a specialty        |\n" +
          "\t|             you may either:              |\n" +
          "\t|                                          |\n" +
          "\t|          < train polearm >               |\n" + 
          "\t|                                          |\n" +
          "\t|               ~~or~~                     |\n" +
          "\t|                                          |\n" +
          "\t|            < train sword >               |\n" +
          "\t|                                          |\n" +
          "\t|      Take heed to choose wisely!         |\n" +
          "\t|                                          |\n" +
          "\t|                                          |\n" +
         "\t\\__________________________________________/\n";
}




