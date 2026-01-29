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
  add_adj("aggressive");
  set_race_name("roc");
  set_short("young aggressive roc");
  set_long("This is a young roc, a giant bird of prey with a " +
    "sharp beak, and powerful claws. When adult, these birds can easily " +
    "carry away a horse. This speciment is not that big yet, having " +
    "a wingspan of barely over two men. It looks quite hungry.\n");
   
   set_aggressive(1);
   
   set_gender(G_MALE);
   set_stats(({ 160, 100, 180, 40, 40, 160}));
   set_skill(SS_DEFENCE, 60);
   set_skill(SS_AWARENESS, 40);
   set_skill(SS_UNARM_COMBAT, 75);
   set_skill(SS_BLIND_COMBAT, 40);
   set_alignment(-300);   
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   set_hp(query_max_hp());

    set_act_time(10);
    add_act("emote screeches hungrily.");
    add_act("emote tears off a lump of something, buried in the ice.");
    add_act("emote gulps something down.");

    set_cact_time(1);
    add_cact("emote beats his powerful wings in an attempt to " +
     "push you off the plateau! You manage to keep your footing.");
    add_cact("emote screeches loudly!"); 


   set_attack_unarmed(A_BEEK, 30, 45, W_IMPALE, 20, "sharp beak");
   set_attack_unarmed(A_LEFTCLAW, 45, 40, W_SLASH, 20, "left claw");
   set_attack_unarmed(A_RIGHTCLAW, 45, 40, W_SLASH, 20, "right claw");
   set_attack_unarmed(A_LEFTWING, 55, 25, W_SLASH, 20, "left wing");
   set_attack_unarmed(A_RIGHTWING, 55, 25, W_SLASH, 20, "right wing");

   add_prop(OBJ_I_RES_MAGIC, 10);
   add_prop(OBJ_I_RES_COLD, 50);
   add_prop(OBJ_I_RES_POISON, 10);
   set_hitloc_unarmed(H_HEAD, ({15,15,15,15}), 15,"head");
   set_hitloc_unarmed(H_BODY, ({25,25,25,25}), 30,"body");
   set_hitloc_unarmed(H_LEFTCLAW, ({25,25,25,25}), 10,"left leg");
   set_hitloc_unarmed(H_RIGHTCLAW, ({25,25,25,25}), 10,"right leg");
   set_hitloc_unarmed(H_TAIL, ({10,10,10,10}), 5, "tail");
   set_hitloc_unarmed(H_LEFTWING, ({15,15,15,15}), 15, "left wing");
   set_hitloc_unarmed(H_RIGHTWING, ({15,15,15,15}), 15, "right wing");

}

public void
do_die(object killer)
{
   object room = E(TO);

   tell_room(room, "The roc screeches haltingly and collapses.\n", ({ TO }));
   ::do_die(killer);   
}


void
init_living()
{
    ::init_living();
}
