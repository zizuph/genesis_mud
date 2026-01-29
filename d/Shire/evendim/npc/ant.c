/*
 * Small ant for a newbee to kill.
 * OOOOPS now I've stolen code again.
 * Can be cloned by ~Shire/common/evendim/ev[11-13]
 */
 inherit "/std/creature";
inherit "/std/combat/unarmed";
#include <ss_types.h>
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
 /* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BITE    0
#define HIT_BODY     0
void
 create_creature()
{
   set_pname("ants");
   set_pshort("little red ants");
   set_short("little red ant");
   add_adj(({"little","red"}));
   set_race_name("ant");
   set_gender(G_NEUTER);
    set_long("The ant crawls around in the grass.\n");
    set_stats(({2,2,2,4,5,6}));
   set_skill(SS_DEFENCE, 5);
   set_attack_unarmed(ATT_BITE,  8, 8,W_IMPALE, 100, "bite");
   set_hitloc_unarmed(HIT_BODY, ({ 8, 8, 8, 8 }), 100, "body");
    add_prop(CONT_I_WEIGHT, 5);   /* 0.005 Kg  */
   add_prop(CONT_I_VOLUME, 10);   /* 0.010 Ltr */
  }
