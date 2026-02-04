/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO    this_object()

public void
create_monster()
{
   ::create_monster();
   
   set_name("salyasin");
   add_name("mystic");
   set_adj("blue-eyed");
   add_adj("melancholy");
   set_race_name("human");

   set_stats(({78, 34, 56, 78, 88, 103}));

   set_hp(9999);
   set_mana(9999);
   set_alignment(578);
   set_random_move(10, 1);
   
   set_rank(MYSTIC_CIRCLE);
   set_blessed(1);
   enable_intro();
   enable_auto_reverence();
   
   set_all_attack_unarmed(25, 20);
   set_all_hitloc_unarmed(40);
   
   set_chat_time(5);
   add_chat("I bid you peace");
   add_chat("Through Wisdom even those things that are deadly can be made Holy");
   add_chat("I pray that Glory shall always reside here");
   add_chat("Call to the stars and they shall hear you");
   add_chat("In Elnoven there are many things of Wisdom");
   add_chat("Glory and Truth be with us all");
   
   set_act_time(17);
   add_act("reflect");
   add_act("smile");
}
