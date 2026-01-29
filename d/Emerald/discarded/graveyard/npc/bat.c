 
/* graveyard/npc/bat.c is cloned by various files in graveyard/ */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>"
 
/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_TEETH     0
#define ATT_CLAWS    1
 
#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_LWING    2
#define HIT_RWING    3
#define HIT_LBCLAW    4
#define HIT_RBCLAW    5
 
void
create_creature()
{
   if (!IS_CLONE)
      return;
    set_name("bat");
    set_race_name("bat");
    add_adj("evil");
    add_adj("black");
    set_long("It looks like it would like a taste of your blood.\n");
 
   add_prop(CONT_I_WEIGHT, 250);
   add_prop(CONT_I_VOLUME, 180);
   add_prop(LIVE_I_NEVERKNOWN, 1);  /* You'll never know it */
 
   set_stats(({  8,  8, 7,  1,  1,  8 }));
   set_hp(10000); /* Heal fully */
 
   set_skill(SS_DEFENCE, 5);
 
   set_attack_unarmed(ATT_TEETH ,  8, 8,W_IMPALE, 70, "teeth");
   set_attack_unarmed(ATT_CLAWS,  8, 8, W_SLASH, 30, "claws");
 
   set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 20, "body");
   set_hitloc_unarmed(HIT_LWING, ({ 8, 8, 8, 8 }), 25, "left wing");
   set_hitloc_unarmed(HIT_RWING, ({ 8, 8, 8, 8 }), 25, "right wing");
   set_hitloc_unarmed(HIT_LBCLAW, ({ 8, 8, 8, 8 }), 05, "left claw");
   set_hitloc_unarmed(HIT_RBCLAW, ({ 8, 8, 8, 8 }), 05, "right claw");
 
    set_aggressive(1);
 
    set_alignment(-25);
}
