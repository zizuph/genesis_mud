/*
 *  A random ranger with random equipment
 *  for North company
 *
 *  Recoded using /d/Gondor/common/npc/random_ranger,
 *  December 1st 1994, Olorin
 *  Tweeked stats and skills to be more realistic and added prestige.
 *  Gwyneth 18 August 2000
 *  Alto 8 March 2002 -- Moved and modified for new ranger code.
 */
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "random_npc_ranger.c";

                  /* str dex con int wis dis */
#define RSTAT ({ \
                   ({ 54, 53, 55, 50, 57, 80 }), \
                   ({ 69, 66, 62, 64, 62, 85 }), \
                   ({ 54, 53, 47, 50, 48, 80 }), \
                   ({ 46, 42, 33, 31, 33, 55 }), \
                   ({ 36, 44, 49, 38, 38, 70 }), \
                   ({ 54, 54, 48, 50, 56, 80 }), \
                   ({ 56, 50, 57, 65, 64, 85 }), \
                   ({ 57, 59, 50, 50, 54, 40 }) })

#define SK ({ 53, 47, 41, 37, 49, 53, 45, 38 })


public void
add_guild_token()
{
    clone_object(RANGERS_NOR_EMBLEM)->move(TO, 1);
    set_alarm(2.0, 0.0, &command("wear brooch"));
}

public void
set_up_stats(int ran)
{
   int rpow, power;
   power = random(100) + 20;
   rpow = random(130) + 130;

   set_base_stat(SS_STR, MIN((RSTAT[ran][0] + power), 200));
   set_base_stat(SS_DEX, MIN((RSTAT[ran][1] + power), 200));
   set_base_stat(SS_CON, MIN((RSTAT[ran][2] + power), 200));
   set_base_stat(SS_INT, MIN((RSTAT[ran][3] + power), 200));
   set_base_stat(SS_WIS, MIN((RSTAT[ran][4] + power), 200));
   set_base_stat(SS_DIS, MIN((RSTAT[ran][5] + power), 200));
   set_alignment(250 + random(250));

   set_skill(SS_WEP_SWORD, MIN(SK[ran] + (rpow / 5), 100));
   set_skill(SS_WEP_AXE, MIN(SK[ran] + (rpow / 5), 100));
   set_skill(SS_WEP_KNIFE, MIN(SK[ran] + (rpow / 5), 100));
   set_skill(SS_WEP_POLEARM, MIN(SK[ran] + (rpow / 5), 100));
   set_skill(SS_DEFENCE, MIN(SK[ran] + (rpow / 5), 100));
   set_skill(SS_PARRY, MIN(SK[ran] + (rpow / 5), 100));
}

/* For the solamnic Knights */
public int
query_knight_prestige()
{
    return(-7);
}
