inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#include <ss_types.h>
void
create_monster() {
   int i;
   set_name("rat");
   add_name("rat");
   set_race_name("rat");
   set_long("You cannot determine whether this is a nasty, " +
      "black rat or extremely filthy brown rat.  Nonetheless " +
      "this foot and a half long creature appears fetid and " +
      "disease ridden with its long, nasty, rotted, pale " +
      "teeth tinged by blood or some other equally foul " +
      "taint.  Surely this rat carries some disease you think.\n");
   set_gender(G_NEUTER);
   set_adj("brackish");
   set_adj("grimey");
   set_stats(({ 15, 30, 30, 10, 20, 70 }));
   set_alignment(-20);
   set_aggressive(1);
   set_hp(125);
   add_prop(CONT_I_WEIGHT, 9000);
   add_prop(CONT_I_HEIGHT, 125);
   add_prop(CONT_I_VOLUME, 7700);
   set_attack_unarmed(A_BITE, 20, 15, W_IMPALE, 75, "rotted teeth");
   set_attack_unarmed(A_LCLAW, 15, 11, W_SLASH, 13, "left paw");
   set_attack_unarmed(A_RCLAW, 15, 11, W_SLASH, 12, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15, 10 }), 15, "head");
   set_hitloc_unarmed(H_BODY, ({  5,  9, 10, 10 }), 85, "body");
   set_act_time(5);
   add_act("emote shudders violently and splashes through the " +
      "water circling around closer to you.");
}
