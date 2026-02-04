/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* Chatting monster */

inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public string races();
public string desc1();
public string desc2();

public void
create_monster()
{
   ::create_monster();
   
   set_name("acolyte");
   add_name("mystic");
   set_adj(desc1());
   add_adj(desc2());
   set_race_name(races());
   set_long("This is a young mystic acolyte who serves the shrine.\n");

   set_stats(({15, 23, 18, 27, 24, 16}));
   set_alignment(235);
   
   set_rank(MYSTIC_NOVITIATE);
   set_blessed(1);
   enable_auto_reverence();
   
   set_chat_time(5);
   add_chat("Greetings.");
   add_chat("Peace.");
   add_chat("The ancient ways are the most wise.");
   
   set_act_time(23);
   add_act("msmile");
   add_act("chant");
}

public string
races()
{
   string *races;
   races = ({"elf", "half-elf", "human", "gnome"});

   return races[random(sizeof(races))];
}

public string
desc1()
{
   string *desc;
   desc = ({"humble", "solemn", "pious", "youthful", "joyous"});

   return desc[random(sizeof(desc))];
}

public string
desc2()
{
   string *desc;
   desc = ({"blue-eyed", "silver-haired", "green-eyed", "long-haired",
             "slender", "black-haired"});

   return desc[random(sizeof(desc))];
}
