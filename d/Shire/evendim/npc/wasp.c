/*
 * Small wasp for a newbee to kill.
 * OOOOPS now I've stolen code again.
 * This used to be the bee in the start/hobbit/farm.
 * Can be cloned in: ~Shire/common/evendim/ev[1-2,4-5]
 */
 inherit "/std/creature";
inherit "/std/combat/unarmed";
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
 /* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_STING    0
#define HIT_BODY     0

void
create_creature()
{
   set_name("wasp");
   set_short("yellow striped wasp");
   add_adj(({"yellow","striped"}));
   set_race_name("wasp");
   set_gender(G_NEUTER);
   set_long("The wasp flies around looking for its hive.\n");
    set_stats(({ 2, 4, 2, 15, 15, 25 }));
    set_skill(SS_DEFENCE, 5);
     set_attack_unarmed(ATT_STING,  8, 8,W_IMPALE, 100, "sting");
    set_hitloc_unarmed(HIT_BODY, ({ 8, 8, 8, 8 }), 100, "body");
    add_prop(CONT_I_WEIGHT, 5);   /* 0.005 Kg  */
   add_prop(CONT_I_VOLUME, 10);   /* 0.010 Ltr */
}

