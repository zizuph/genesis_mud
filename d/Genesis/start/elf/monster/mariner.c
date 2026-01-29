/*
 * An ancient mariner.
 */

#include "../stddefs.h"
#include "../tefyma.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;

#define IND_NAME "coleridge"		/* Names have to be lowercase. Sigh. */
#define RACE "mariner"

#define LONG \
  "He is an old man, clad in a tattered robe. His head is bald, his beard "+\
  "grey and long, and his stare is intense enough to stop anyone in his "+\
  "tracks, even the most eager wedding-guest.\n"

#define ACT1 \
  ({ \
    "say The albatross...", \
    "say The albatross...", \
    "say I killed the albatross!", \
    "emote sobs silently." \
  })

#define ACT2 \
  ({ \
    "say Day after day, day after day we stuck, nor breath nor motion...", \
    "say ...as idle as a painted ship on a painted ocean.", \
    "say Water, water everywhere, and all the boards did shrink.", \
    "say Water, water everywhere, and not a drop to drink." \
  })

#define ACT3 \
  ({ \
    "say Yea, slimy things did crawl with legs, upon the slimy sea.", \
    "emote shivers." \
  })

#define ACT4 \
  ({ \
    "say I had done a hellish thing, and it would work'em woe...", \
    "say ...for all averred, I had killed the bird... ", \
    "say ...that made the breeze to blow",\
  })

create_monster() {
  if (IS_CLONE) {
    set_name(IND_NAME);
    set_race_name(RACE);
    set_adj("ancient");
    set_long(WRAP(LONG));

    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_WEIGHT,  70 KG);
    add_prop(CONT_I_HEIGHT, 170 CM);
    add_prop(CONT_I_VOLUME,  70 LITRES);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_BLIND_COMBAT, 20);
    set_skill(SS_PARRY, 20);
    

    set_base_stat(SS_STR, 25);
    set_base_stat(SS_DEX, 15);
    set_base_stat(SS_CON, 40);
    set_base_stat(SS_INT, 20);
    set_base_stat(SS_WIS, 20);
    set_base_stat(SS_DIS, 20);

    set_alignment(70);
    set_appearance(65);
    set_aggressive(0);
    set_attack_chance(0);

    set_act_time(0); 
    add_act("glare searchingly");
    add_act(ACT1);
    add_act(ACT2);
    add_act(ACT3);
    add_act(ACT4);

    refresh_mobile();
  }
}
