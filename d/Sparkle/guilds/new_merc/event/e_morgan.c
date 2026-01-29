/*
 * Morgan, guild trainer of the Mercenaries Guild
 * 	by Morrigan, 11/2001
 *
 * Adapted from code by Auberon and Gwyneth
 * Updated for Sparkle by Lunatari 2006
 * Updated again and used in the New Merc camp by Gorboth, 2009.
 */
#include "../merc_defs.h"

inherit "/d/Gondor/std/monster";

#include <ss_types.h>
#include <stdproperties.h>

void
create_gondor_monster()
{
    set_name("morgan");
    add_name("trainer");
    set_gender(1);
    set_title("the Wanderer, Recruiting Overseer of the Free Mercenary"
      + " Guild");
    set_race_name("human");
    set_long("Auburn hair, loosely gathered, falls in winding streams "+
	"down the back of "+
	"this small woman. She observes her surroundings with intense "+
	"icy blue eyes, that seem to take in every minute detail. She "+
	"is dressed in soft leathers, and wears a dark green cloak. "+
	"A short sword hangs at her side, and a thin dagger is sheathed "+
    "in her boot.\n");
    set_adj(({"auburn-haired", "blue-eyed"}));

    set_stats(({ 120, 135, 130, 135, 150, 130 }));
    set_skill(SS_WEP_SWORD, 93);
    set_skill(SS_AWARENESS,   70);
    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_APPR_MON,    50);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "Are you out of your mind? Attacking her "+
	"in the middle of her own camp? You would be slaughtered for sure!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Are you out of your mind? Attacking her "+
	"in the middle of her own camp? You would be slaughtered for sure!\n");
}

