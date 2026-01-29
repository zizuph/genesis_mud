

/*
* Small ant for a newbee to kill.
* OOOOPS now I've stolen code again.
* Can be cloned by ~Shire/common/evendim/ev[11-13]
*              -briaeros
*/

inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/monster/defs.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BITE    0

#define HIT_BODY     0

create_creature()
{
   set_name("rat");
   set_pname("rats");
   set_living_name("rat");
   set_race_name("rat");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   default_config_mobile(20);
   set_all_hitloc_unarmed(30);
   set_gender(G_NEUTER);
   set_stats(({20,60,10,10,10,5}));
   
   set_long("The crab digs in the sand.\n");
   set_exp(10);
   
   set_skill(SS_DEFENCE, 5);
   
   set_attack_unarmed(ATT_BITE,  8, 8,W_IMPALE, 100, "teeth");
   
   add_prop(CONT_I_WEIGHT, 5);   /* 0.005 Kg  */
   add_prop(CONT_I_VOLUME, 10);   /* 0.010 Ltr */
}
