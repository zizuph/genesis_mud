/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()

public void
create_monster()
{
   ::create_monster();
   
   set_name("phandor");
   add_name("mystic");
   set_adj("blue-eyed");
   add_adj("silver-haired");
   set_race_name("elf");

   set_stats(({109, 113, 91, 89, 110, 91}));

   set_hp(9999);
   set_mana(9999);
   set_alignment(712);
   set_random_move(10, 1);
   set_all_attack_unarmed(56, 40);
   set_all_hitloc_unarmed(67);

   set_rank(MYSTIC_CANTOR);
   set_skill(SS_LANGUAGE, 76);
   set_blessed(1);
   enable_intro();
   enable_auto_salute();
   
   set_chat_time(5);
   add_chat("The soot of our sacred fire has many blessings!");
   add_chat("I often pray for peace");
   add_chat("Twelve are they that watch this place, beware");
   add_chat("Mystery abides everywhere");
   add_chat("We will bring darkness and light");
   
   set_act_time(11);
   add_act("chant");
}
