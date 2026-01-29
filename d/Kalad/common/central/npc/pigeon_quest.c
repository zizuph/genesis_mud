inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
/* by korat */
#define A_BITE 0
#define A_LWING 1
#define A_RWING 2
#define H_HEAD 0
#define H_BODY 1
create_monster()
{
   ::create_monster();
   set_name("pigeon");
   set_race_name("pigeon");
   switch(random(3)){
      case 0:
      set_adj("white");
      break;
      case 1:
      set_adj("grey");
      break;
      case 2:
      set_adj("black");
      break;
      case 3:
      set_adj("brown");
      break;
   }
   set_long("A small pigeon. Its probably hungry...but then again "+
      "pigeons always are!\n");
   set_stats(({5,5,5,5,5,5}));
   set_skill(SS_DEFENCE,20);
   set_skill(SS_UNARM_COMBAT,20);
   set_act_time(6);
   add_act("eat all");
   add_act("emote flaps its wings.");
   add_act("emote cooes.");
   set_gender(G_NEUTER);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,350);
   add_prop(CONT_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(CONT_I_VOLUME,350);
   add_prop(OBJ_I_NO_INS,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_attack_unarmed(A_BITE, 5, 5, W_BLUDGEON, 20, "beak");
   set_attack_unarmed(A_RWING, 5, 5, W_BLUDGEON, 40, "right wing");
   set_attack_unarmed(A_LWING, 5, 5, W_BLUDGEON, 30, "left wing");
   set_hitloc_unarmed(H_HEAD, ({5,5,8}),20, "head");
   set_hitloc_unarmed(H_BODY, ({5,5,5}), 80, "body");
   set_alarm(1.0,0.0,"get_cylinder");
}

get_cylinder()
{
   clone_object("/d/Kalad/common/central/obj/cylinder_quest")->move(TO);
}
