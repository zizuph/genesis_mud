inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include "../defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>

#define ADJ1 ({"large", "medium", "small"})
#define ADJ2 ({"dirty", "lazy", "haughty"})

#define A_BITE 0
#define A_R_HOOF 1
#define A_L_HOOF 2
#define H_HEAD 0
#define H_BODY 1

#define PIG_CORPSE "/d/Earthsea/roke/thwil/obj/pig_corpse"

void create_creature()
{
   int i, j;
   set_name("pig");
   i = random(sizeof(ADJ1));
   j = random(sizeof(ADJ2));
   add_adj(ADJ1[i]);
   add_adj(ADJ2[j]);
   set_race_name("pig");
   set_short(ADJ1[i] + " " + ADJ2[j] + " " + "pig");
   set_long("The pig looks at you curiously for a moment " +
	    "and then goes back to being lazy.\n");
   set_gender(G_FEMALE);
   
   set_stats(({ 20, 20, 20, 15, 15, 20}));
  
   set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }), 72, "body");
   
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_UNARM_COMBAT, 40);
   set_attack_unarmed(A_BITE, 20, 20, W_IMPALE, 50, "bite");
   set_attack_unarmed(A_R_HOOF, 20, 20, W_BLUDGEON, 25, "right hoof");
   set_attack_unarmed(A_L_HOOF, 20, 20, W_BLUDGEON, 25, "left hoof");
   
   set_cact_time(25);
   add_cact("emote squeals loudly!");
   
   add_prop(LIVE_I_NEVERKNOWN, 1);
}

public object make_corpse()
{
  setuid();
  seteuid(getuid());
  return clone_object(PIG_CORPSE);
}
