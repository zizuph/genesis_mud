inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#define A_BITE  0
#define H_HEAD 0
#define H_BODY 1
#include <ss_types.h>
void
create_monster() {
   set_name("water snake");
   set_living_name("mute_snake");
   set_race_name("water snake");
   add_name("snake");
   set_adj("black");
   set_adj("giant");
   set_long("This is a giant water snake slimey black in color " +
      "and longer than two humans by the look of it.  Its eyes are " +
      "dull green and a pair of pale fangs extend from its mouth. " +
      "Looking at the flat tail the snake uses to aid in swimming " +
      "you think this snake would be pretty quick.\n");
   set_gender(G_NEUTER);
   default_config_mobile(40);
   set_alignment(0);
   set_aggressive(1);
   set_hp(350);
   set_skill(SS_SWIM, 100);
   add_prop(CONT_I_WEIGHT, 50000);
   add_prop(CONT_I_VOLUME, 38000);
   set_attack_unarmed(A_BITE, 40, 20, W_IMPALE, 100, "pale fangs");
   set_hitloc_unarmed(H_HEAD, (({ 20, 40, 45, 35 })), 20, "head");
   set_hitloc_unarmed(H_BODY, (({ 15, 35, 40, 30 })), 80, "body");
   set_alarm(0.0,0.0,"snake_dive");
}
snake_move() {
   command("up");
   set_alarm(15.0,0.0,"snake_dive");
}
snake_dive() {
   command("swim underwater");
   set_alarm(10.0,0.0,"snake_move");
}
