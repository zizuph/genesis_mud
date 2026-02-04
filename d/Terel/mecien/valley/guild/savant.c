/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public void
create_monster()
{
   ::create_monster();
   
   set_name("allorhal");
   set_adj("gray-bearded");
   add_adj("austere");
   add_name("human");
   add_name("savant");
   add_name("teacher");
   set_race_name("human");
   set_title("the White Savant");
   
   set_stats(({76, 54, 76, 98, 118, 69}));
   set_hp(9999);
   set_mana(9999);
   
   set_rank(MYSTIC_EXARCH);
   set_blessed(1);
   enable_intro();
   enable_auto_salute();
   
   set_alignment(790);
   
   set_all_attack_unarmed(40, 38);
   set_all_hitloc_unarmed(55);
   
   set_act_time(13);
   add_act("msmile");
   add_act("ms You cannot lose knowledge, but you can lose wealth.");
   add_act("ms Mystic knowledge is the essence of Life.");
}
