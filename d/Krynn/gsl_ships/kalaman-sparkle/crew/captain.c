#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDCAPTAIN;

int intro = 0;

void
create_captain()
{
  ::create_captain();
  set_name("klaus");
  add_name("captain");
  set_living_name("klaus");
  set_race_name("half-elf");
  add_adj("leather-skinned");
  set_adj("cheery");
  set_stats(({ 80, 80, 100, 60, 60, 90 }));
  set_skill(SS_SWIM, 100);
  set_skill(SS_LOC_SENSE,100);
  set_skill(SS_UNARM_COMBAT,80);
  set_skill(SS_DEFENCE,50);
  heal_hp(10000);
  set_chat_time(9);
  
  add_chat("My minotaurs work hard.");
  add_chat("How nice it is travelling by sea.");
  add_chat("I really like Palanthas. As soon as I have earned enough money I'll retire there.");
  add_chat("The proprietor of the Inn in Palanthas is a good friend of mine. He's always having problems though.");
  add_chat("Hmmph. I think we're behind schedule again.");
  add_chat("How nice it is travelling by sea.");
  add_chat("We better watch out for Ergothian Pirates.");
  add_chat("I wish my ship was as fine as those made by Cirdan the Shipwright.");
  
  add_ask(({"palanthas","inn","proprietor"}),"say I know Leiden since we both were kids! Just go and ask him for a job.",1);
  add_ask(({"greyhavens", "mithlond", "elves"}),"say I no longer sail there. I barely get to Palanthas.\n");
  add_ask(({"kalaman"}), "say I like it there almost as good as Palanthas.\n");
  add_ask(({"sparkle"}), "say I am honored to finally captain a ship that goes to the capital of the Donut.\n");
  
  set_cchat_time(11);
  add_cchat("Stop it, you pestering dog!");
  add_cchat("Right, you'll pay for that!");
  add_cchat("Come on! I'll beat the living daylights out of you!");
  add_cchat("Right! I'm really gonna stump you this time!");
  add_cchat("Give it to me, big-nose!");
  add_cchat("I'm gonna smack you so hard....");
  
  trig_new("%w 'introduces' %s", "react_introduce");
  
  add_prop(OBJ_M_NO_ATTACK,
           "You feel this man is under strong protection.\n");
  
}    

string
query_my_title()
{
    return "the Off-coast Skipper";
}

void
react_introduce(string person,string who)
{
    if (!intro)
      intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
    tell_room(ENVX(TO),QCTNAME(TO) + " introduces himself as:\n" +
	      "Captain Klaus " + query_my_title() + ", male half-elf.\n");
    FILTER_LIVE(all_inventory(ENVX(TO)))->add_introduced("klaus");
    intro = 0;
}

