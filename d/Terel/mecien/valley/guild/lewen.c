/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/* Chatting monster */

inherit "/d/Terel/std/mystic";

#include <ss_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"
#include <stdproperties.h>

public string races();
public string desc1();
public string desc2();

public void
create_monster()
{
   ::create_monster();
   
  set_living_name("lewen");
   set_short("Lewen the Acolyte");
   set_name("lewen");
  add_prop(LIVE_I_ALWAYSKNOWN, 1);
   add_name("mystic");
   set_adj(desc1());
   add_adj(desc2());
  set_race_name("human");
   set_long("He is a young man, hazel eyes, blond haired. A great sense of piety emanates from him, as if he serves some great purpose.\n");

   set_stats(({ 56, 76, 81, 90, 90, 90 }));
   set_alignment(766);
   
   set_rank(MYSTIC_NOVITIATE);
   set_blessed(1);
   enable_auto_reverence();
   
  set_skill(130008, 1);
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
