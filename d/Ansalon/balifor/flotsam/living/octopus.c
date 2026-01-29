inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_TENT 0
#define A_BEAK 1
#define H_TENT 0
#define H_BODY 1

void
create_creature()
{
   
   if (!IS_CLONE)
      return;
   set_name("octopus");
   set_adj("giant");
   set_race_name("octopus");
   set_short("giant octopus");
   set_long("This is a giant octopus. When angered, " +
      "these creatures become dangerous adversaries, fighting " +
      "with eight large tentacles and a great beak-like maw. " +
      "It is rumoured that these creatures are a bane to even " +
      "large ships, and its only natural enemies are the great " +
      "whales of the Courrain Sea. This particular octopus does " +
      "not seem very happy at your appearance in his domain.\n");
   
   set_aggressive(1);
   
   set_gender(G_NEUTER);
   set_stats(({ 160,160, 160, 100, 100, 100}));
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_AWARENESS, 80);
   
   add_prop(LIVE_I_NO_CORPSE, 1);
   
   set_attack_unarmed(A_TENT,45,40,W_BLUDGEON,90,"great tentacle");
   set_attack_unarmed(A_BEAK, 5, 55, W_SLASH, 10, "great beak-like maw");
   
   set_hitloc_unarmed(H_TENT, ({40,35,35,35}), 60,"body");
   set_hitloc_unarmed(H_BODY, ({ 30, 28, 30, 30}), 40, "great tentacle");
}


public void
do_die(object killer)
{
    object room = E(TO);

    ::do_die(killer);

    tell_room(room, "The corpse of the octopus slowly sinks into "
      + "the depths of the rockpool.\n", ({ TO }));
}
