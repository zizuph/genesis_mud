#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/icewall/castle2/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/d/Ansalon/std/creature";

#define A_BEEK      0
#define A_LEFTCLAW  1
#define A_RIGHTCLAW 2
#define A_LEFTWING  3
#define A_RIGHTWING 4

#define H_HEAD      0
#define H_BODY      1
#define H_LEFTWING  2
#define H_RIGHTWING 3
#define H_TAIL      4
#define H_LEFTCLAW  5
#define H_RIGHTCLAW 6


void
create_creature()
{
  set_adj("young");
  set_race_name("griffon");
  set_short("young griffon");
  set_long("This is a young griffon, a creature half-eagle and half-lion. " +
    "Long ago elves rode those beasts as human ride horses, but the art " +
    "has been mostly lost over the ages.\n");
   
   set_gender(G_MALE);
   set_stats(({ 120, 120, 120, 70, 70, 120}));
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_AWARENESS, 40);
   set_skill(SS_UNARM_COMBAT, 70);
   set_skill(SS_BLIND_COMBAT, 40);
   set_alignment(800);   
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   set_hp(query_max_hp());

    set_act_time(10);
    add_act("emote shrieks loudly.");

    set_cact_time(1);
    add_cact("emote screeches loudly!"); 


   set_attack_unarmed(A_BEEK, 30, 45, W_IMPALE, 20, "sharp beak");
   set_attack_unarmed(A_LEFTCLAW, 25, 20, W_SLASH, 20, "left broken claw");
   set_attack_unarmed(A_RIGHTCLAW, 35, 30, W_SLASH, 20, "right bloody claw");
   set_attack_unarmed(A_LEFTWING, 45, 25, W_SLASH, 20, "left bruised wing");
   set_attack_unarmed(A_RIGHTWING, 45, 25, W_SLASH, 20, "right battered wing");

   add_prop(MAGIC_I_RES_MAGIC, 10);
   add_prop(MAGIC_I_RES_COLD, 50);
   add_prop(MAGIC_I_RES_POISON, 10);
   set_hitloc_unarmed(H_HEAD, ({15,15,15,15}), 15,"head");
   set_hitloc_unarmed(H_BODY, ({25,25,25,25}), 30,"body");
   set_hitloc_unarmed(H_LEFTCLAW, ({25,25,25,25}), 10,"left leg");
   set_hitloc_unarmed(H_RIGHTCLAW, ({25,25,25,25}), 10,"right leg");
   set_hitloc_unarmed(H_TAIL, ({10,10,10,10}), 5, "tail");
   set_hitloc_unarmed(H_LEFTWING, ({15,15,15,15}), 15, "left wing");
   set_hitloc_unarmed(H_RIGHTWING, ({15,15,15,15}), 15, "right wing");

}

void
init_living()
{
    ::init_living();
}