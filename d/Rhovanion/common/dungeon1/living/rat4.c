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
   set_long("This large two foot creature is solid black in " +
      "color including its rotting black fangs and claws.  It " +
      "looks like no other rat you have seen before...  it's " +
      "somehow unnatural and evil.\n");
   set_gender(G_NEUTER);
   set_adj("black");
   set_adj("black-eyed");
   set_adj("solid");
   set_stats(({ 30, 30, 30, 30, 30, 150 }));
   set_hp(50);
   set_alignment(-100);
   set_aggressive(1);
   add_prop(CONT_I_WEIGHT, 12000);
   add_prop(CONT_I_HEIGHT, 200);
   add_prop(CONT_I_VOLUME, 10000);
   set_attack_unarmed(A_BITE, 20, 15, W_IMPALE, 75, "black fangs");
   set_attack_unarmed(A_LCLAW, 15, 11, W_SLASH, 13, "left black claw");
   set_attack_unarmed(A_RCLAW, 15, 11, W_SLASH, 12, "right black claw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15, 10 }), 15, "head");
   set_hitloc_unarmed(H_BODY, ({  5,  9, 10, 10 }), 85, "body");
   set_act_time(10);
   add_act("emote throws its head back and charges into you hard!");
}
