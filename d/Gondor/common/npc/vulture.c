/*
 *  Vulture which eats corpses
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BEAK     0
#define ATT_CLAWS    1

#define HIT_HEAD     0
#define HIT_BODY     1
#define HIT_TAIL     2
#define HIT_LWING    3
#define HIT_RWING    4
#define HIT_LBPAW    5
#define HIT_RBPAW    6

/* Some random values */
#define RADJ    ({ "large", "black" })
#define RSTAT   10+random(8)

create_creature()
{
   int ran;
   ran = random(4);

   if (!IS_CLONE)
      return;
   set_name("vulture");
   set_race_name("vulture");
   set_adj(RADJ[random(2)]);
   set_gender(G_NEUTER);
   set_long(break_string("The vulture is searching for meat. It looks "+
            "rather dangerous. Fortunately it usually eats carrion.\n",70));

   add_prop(CONT_I_WEIGHT, 9000);   /* 9.0 Kg  */
   add_prop(CONT_I_VOLUME, 7500);   /* 7.5 Ltr */
   add_prop(LIVE_I_NEVERKNOWN, 1);


   set_stats(({  RSTAT,  RSTAT, RSTAT,  2,  2,  RSTAT }));
   set_hp(10000); /* Heal fully */
  set_alignment(0);

   set_m_out("flies");
   set_m_in("@@arrive_msg");

  set_skill(SS_DEFENCE, 15);

   set_attack_unarmed(ATT_BEAK ,  20, 20,W_IMPALE, 70, "beak");
   set_attack_unarmed(ATT_CLAWS,  20, 20, W_SLASH, 30, "claws");

   set_hitloc_unarmed(HIT_HEAD,  ({ 4, 4, 4, 4 }), 10, "head");
   set_hitloc_unarmed(HIT_BODY,  ({ 10, 10, 10, 10 }), 20, "body");
   set_hitloc_unarmed(HIT_LWING, ({ 10, 10, 10, 10 }), 25, "left wing");
   set_hitloc_unarmed(HIT_RWING, ({ 10, 10, 10, 10 }), 25, "right wing");
   set_hitloc_unarmed(HIT_LBPAW, ({ 10, 10, 10, 10 }),  5, "left claw");
   set_hitloc_unarmed(HIT_RBPAW, ({ 10, 10, 10, 10 }),  5, "right claw");
   set_hitloc_unarmed(HIT_TAIL,  ({ 10, 10, 10, 10 }), 10, "tail");


   /* And now make it move every now and then... */
  set_act_time(3);
   add_act("@@eat_carrion");

}

string arrive_msg()
{
   if (present("corpse"))
      return "arrives flying and descends on the corpse.";
   return "arrives flying and descends on the ground.";
}

eat_carrion()
{

  if (present("corpse",environment(this_object())))
    tell_room(environment(this_object()),QCTNAME(this_object())+
    " pecks a piece of half-rotten flesh from the corpse.\n");
  return "";
}

/* solemnians */
query_knight_prestige() {return 50;}

