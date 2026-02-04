#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <money.h>
#include <ss_types.h>
#include <macros.h> 
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDCAPTAIN;

#define HUNTING_TREVIN "_i_hunting_trevin"

public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
           command("say Yeah, I took him north to Last lastnight.");
           command("say Stomped on board and demanded I take him to Last");
           command("say He had the gold to make it worth my while though.");
           command("say I haven't seen him since he left the ship.");
           return "";
    }
    return "";
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */

public void
create_captain()
{

  int power;
  ::create_captain();
  
  power = 30+random(70);
  set_name("harlan");
  add_name("captain");
  set_living_name("harlan");
  set_race_name("human");
  set_adj("cold");
  add_adj("hardened");
  set_title("the grumpy one");
  
  default_config_npc(power);
  heal_hp(10000);
  set_skill(SS_AWARENESS, power);
  set_skill(SS_WEP_KNIFE, power);
  set_skill(SS_DEFENCE, power);
  set_skill(SS_PARRY, power);
  
  add_ask("tall wiry male human", reply_assassin, 1);
}
