inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Earthsea/atuan/defs.h"

int wood;

void
create_earthsea_monster()
{
  set_name("olarin");
  set_living_name("olarin");
  set_title("the fisherman");
  set_race_name("human");
  add_name("fisherman");
  set_long(BS("He is a old wrinkled man, who has seen"+
			" many a sight on the seas in his time."+
			" His hands are calloused, and his face"+
			" wrinkled from exposure to the sun.\n",70));
  set_adj(({"old","weatherbeaten"}));
  	

default_config_npc(16);
set_random_move(50);
set_restrain_path(GAR);

set_hp(10000);

set_skill(SS_DEFENCE, 26);
set_skill(SS_WEP_POLEARM, 35);
set_stats(({35,25,25,35,40,25}));
add_chat("I have seen sights more horrible than your worst nightmare.");
add_chat("I once caught a fish ...THIS... big!");
add_act("emote whittles away at a piece of wood");


set_act_time(3);
set_chat_time(80);


::create_earthsea_monster();

      if (IS_CLONE)
              call_out("arm_me", 1);

 }

void
arm_me()
{
      seteuid(geteuid(this_object()));

     /* clone_object(ATUAN + "/obj/walking_stick")->move(TO); */

      command("wield all");
      seteuid(getuid(TO)); 

}

