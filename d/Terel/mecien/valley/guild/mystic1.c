/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO    this_object()
#define TP    this_player()

public void
create_monster()
{
   ::create_monster();
   
   set_name("derivas");
   add_name("mystic");
   set_adj("tall");
   add_adj("solemn");
   set_race_name("human");

   set_stats(({56, 34, 56, 78, 88, 99}));

   set_hp(9999);
   set_mana(9999);
   
   set_rank(MYSTIC_STAR);
   set_skill(SS_LANGUAGE, 76);
   set_blessed(1);
   enable_intro();
   enable_auto_salute();
   
   set_alignment(256);
   set_random_move(10, 1);
   set_chat_time(6);
    add_chat("If you seek the sacred fire, you must have a suitable presentation");
   add_chat("Life brings Truth and Healing");
   add_chat("If ye seek Life ask the Holy Cantor");
   add_chat("Within the crypt lay the Archons of old");
   add_chat("Praised be the Ancients");
   add_chat("Peace");
   
   set_act_time(23);
   add_act("msmile");
   add_act("ms Mystery! Of uttermost importance!");
   
   set_all_attack_unarmed(25, 20);
   set_all_hitloc_unarmed(40);
}
