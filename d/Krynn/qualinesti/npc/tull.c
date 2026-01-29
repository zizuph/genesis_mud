/* File : deorl.c
 *
 * A wounded elf. Part of the quest.
 *
 * Blizzard, 02/2003
 *
 */

#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include "../local.h"

inherit M_FILE
inherit "/d/Krynn/std/equip";

object weapon;

void
create_krynn_monster()
{
    set_name("tull");
    set_race_name("elf");
    set_adj("tall");
    add_adj("long-haired");
    set_short("tall long-haired male elf");
    set_long("This elf is probably the one of the lost elven scouts.\n");

    set_gender(0);
    set_alignment(400);
    set_knight_prestige(-100);
//    set_no_team_member(1);  I dont want him to join Qualthas team in 
                           // the final sequence.
    
    set_stats(({ 90, 120, 100, 120, 120, 90 }));

    set_skill(SS_WEP_SWORD, 40);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_HIDE, 60);
    
    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 175);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_hp(200);

    seteuid(getuid(TO));
    equip(({ WEP + "elongsword", ARM + "elven_boots", ARM + "lchain" }));
}

int 
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
       return 1;
}

