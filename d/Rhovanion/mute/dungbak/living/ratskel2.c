inherit "/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Rhovanion/defs.h"
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
   set_adj("skeletal");
   set_adj("demonic");
   set_long("This foul undead creature appears as if it were " +
      "at one time a very large rat.  Now all that remains of it " +
      "are its pale, grimey bones and a bit of rotted flesh here " +
      "and there that managed to cling on.  A pair of dirty white " +
      "fangs stained by years of kills extend skewed from the " +
      "creature's mouth.\n");
   set_gender(G_NEUTER);
   set_alignment(-175);
   set_aggressive(1);
   set_hp(175);
   set_stats(({ 20, 25, 35, 1, 30, 150 }));
   add_prop(CONT_I_WEIGHT, 4500);
   add_prop(CONT_I_HEIGHT, 125);
   add_prop(CONT_I_VOLUME, 2000);
   set_attack_unarmed(A_BITE, 20, 15, W_IMPALE, 75, "fangs");
   set_attack_unarmed(A_LCLAW, 15, 11, W_SLASH, 13, "left paw");
   set_attack_unarmed(A_RCLAW, 15, 11, W_SLASH, 12, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15, 10 }), 15, "head");
   set_hitloc_unarmed(H_BODY, ({  5,  9, 10, 10 }), 85, "body");
   trig_new("%s 'died.' %s","part_kill");
}
part_kill() {
   write("Another skeletal rat pops out of the dirt!\n");
   clone_object("/d/Rhovanion/mute/dungeon1/ratskel.c")->move(TO);
   return 1;
}
