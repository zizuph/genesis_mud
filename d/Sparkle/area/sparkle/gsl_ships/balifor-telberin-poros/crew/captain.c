#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;

void
create_captain()
{
  ::create_captain();
  set_name("mizzen");
  add_name("captain");
  add_name("seaman");
  set_adj(({"old", "grizzled"}));
  set_long("This sea captain is close to retirement age. "+
           "He is old and bent, and his face is like wrinkled leather "+
           "from many years of exposure to the elements.\n");
  set_chat_time(45);

  set_living_name("_ANSALON_GONDOR_EMERALD_CAPTAIN");
  set_race_name("human");
  default_config_npc(60);
  set_skill(SS_SWIM,100);
  set_skill(SS_UNARM_COMBAT,45);
  set_skill(SS_DEFENCE,34);
  
  heal_hp(10000);
  set_hp(50000);
  
  setuid();
  seteuid(getuid());
  
  trig_new("%w 'introduces' %s", "react_introduce");
  
  set_hp(50000);
  
  set_m_in("limps in");
  add_act("emote groans as he rubs his aching back.");
  
}


void
intro_hook(string str)
{
    command("introduce myself");
    command("bow");
}

