inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <std_properties.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <composite.h>
#include <money.h>
#include <cmdparse.h>

void light_on(object where);
void create_monster()
{
   if(!IS_CLONE)
      return;
   
   set_name("trolloc");
   set_adj("ugly");
   set_race_name("trolloc");
   set_short("An ugly Trolloc warrior");
   set_long(
      "This Trolloc has to be the ugliest thing you've ever seen! Its " +
      "long, pig-like snout sniffs the air to catch your scent, and its " +
      "beady eyes scan the area looking for dinner.\n");
   set_act_time(20);
   add_act("emote sniffs the air hungrily.");
   add_act("say I wonder if I will kill enough to fill my cookpot?");
   add_act("emote looks at you appraisingly, and growls, 'Maybe you'll " +
      "make a decent appetizer.'\n");
add_act("emote grabs you by the arm roughly, testing to see " +
"how fat you are.\n");

set_cact_time(20);
add_cact("sniff hungr");
add_cact("lick all");
add_cact("say This one will be just enough for a midnight snack!\n");
add_cact("say I may have to lop off your head to make you fit into my pot.\n");

set_stats(({15,13,19,3,3,70}));
set_hp(1000);
set_skill(SS_WEP_SWORD, 20);
set_alignment(200);
set_agressive(0);

add_prop(CONT_I_WEIGHT, 100000);
