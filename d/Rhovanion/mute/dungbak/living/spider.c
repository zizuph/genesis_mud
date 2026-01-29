inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Rhovanion/defs.h"
#define A_BITE  0
#define A_SPIT 1
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#include <ss_types.h>
void
create_monster() {
   int i;
   set_name("the spider");
   add_name("spider");
   add_name("mute_spider");
   set_adj("black-carapaced");
   set_adj("hairy");
   set_short("hairy, black-carapaced spider");
   set_long("This spider is of giant proportions and this particular one" +
      "happens to be as large as a pony.  The creature is entirely black" +
      "with black eyes that don't appear to be looking at anything, yet" +
      "seeing all.  Its carapace looks particularly sturdy and shiny" +
      "capable of withstanding some pretty devastating blows you figure.\n");
   set_gender(G_NEUTER);
   set_stats(({ 70, 40, 40, 25, 50, 100 }));
   set_alignment(0);
   set_aggressive(1);
   set_hp(300);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(CONT_I_WEIGHT, 120000);
   add_prop(CONT_I_HEIGHT, 10000);
   add_prop(CONT_I_VOLUME, 145000);
   set_attack_unarmed(A_BITE, 45, 15, W_IMPALE, 67, "pincing bite");
   set_attack_unarmed(A_SPIT, 75,  5, W_IMPALE | W_SLASH |
      W_BLUDGEON, 33, "venomous spit");
   set_hitloc_unarmed(H_HEAD, ({ 20, 25,  5, 30 }), 30, "head");
   set_hitloc_unarmed(H_BODY, ({ 45, 60, 30, 50 }), 35, "body");
   set_hitloc_unarmed(H_LEGS, ({ 60, 40, 35, 50 }), 35, "legs");
   set_act_time(10);
   add_act("@@get_corpse");
}
string
get_corpse() {
   command("get corpse");
   command("south");
   command("put corpse in webs");
   command("north");
}
