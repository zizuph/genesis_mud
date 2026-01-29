inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>



void
create_monster()
{
   set_race_name("shadow");
   set_short("shadow");
   set_long(break_string("A dark grey blur against the background, a "+
         "shadow preys on the living to maintain it's limbotic existence.\n",75));
   
   add_prop(CONT_I_WEIGHT,60000);
   add_prop(CONT_I_HEIGHT,20000);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_NO_CORPSE, 1);
   
   set_gender(2);
   set_alignment(-587);   
   
   set_stats(({34,40,44,33,30,35}));
   heal_hp(20000);
   set_mana(1500);
   
   set_all_attack_unarmed(24,23);
   
   set_skill(SS_BLIND_COMBAT,45);
   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_DEFENCE,40);
   set_skill(SS_AWARENESS,37);
}
