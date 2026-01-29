
// Silkseller   silkseller.c
// creator(s):  Grace
// last update: Denis, May'97: Regular updates: triggers and such.
// purpose:
// note:
// bug(s):
// to-do:
/* Modified by Marisol to be used as Fan the weaver in the new Re 
 * Albi. (2/24/98) */
/* Modified by Marisol to be used as a tailor for the town of Ovejuno
 * in Emerald. (07/13/98)*/


# pragma strict_types

#include <defs.h>
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>
#include <const.h>

inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro";

void
create_emerald_monster()
{
    set_name("gorgi");
    add_name("man");
    set_title("the Tailor");
    set_race_name("human");
    set_gender(G_MALE);
    add_adj(({"old", "humble"}));
    set_long("An old and humble human. He seems to be a "+
        "little near-sighted. He is wearing a simple robe.\n");
    add_prop(OBJ_M_NO_ATTACK, "Shame on you! This old man could  "+
        "be your grandfather.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "For some reason you don't feel "+
        "like hurting this old man\n");
    set_mm_in("arrives.");
}

