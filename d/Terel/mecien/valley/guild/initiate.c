/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public void
create_monster()
{
   ::create_monster();
   
   set_name("novitiate");
   add_name("mystic");
   add_adj(({"blue-eyed", "blond-haired"}));
   set_race_name("human");
   set_short("mystic novitiate");
   set_long("A young mystic, he has but recently joined the "
      + "shrine and the Order. He wears the white robe of the "
      + "mystics, over which he wears a gray surplice.\n");

   set_stats(({12, 15, 11, 18, 19, 11}));
   set_alignment(145);
   set_random_move(3, 1);
   
   set_rank(MYSTIC_NOVITIATE);
   set_blessed(1);
   enable_auto_reverence();
   
   set_act_time(3);
   add_act("emote sings the prayers of the ancient spirits.");
   add_act("chant");
   
   set_chat_time(5);
   add_chat("Peace");
}

