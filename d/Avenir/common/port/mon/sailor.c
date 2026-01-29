// -*-C++-*-
// file name: ~Avenir/common/port/mon/sailor.c
// creator(s): Boriska, Aug 1995
// last update:
// purpose:    NPC for port area, carries brass knuckles for right hand.
// note:       
// bug(s):
// to-do:     

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include "/d/Avenir/common/common.h"

inherit "/std/monster";

private int alarm_id;

static void remove_knuckles();
static void wear_knuckles();

void
create_monster() {
  if (!IS_CLONE)
    return;
  set_name("sailor");
  set_adj("weathered");
  add_adj("sad");
  set_race_name("sailor");
  set_stats(({80, 90, 90, 70, 70, 70}));
  set_alignment(1000);

  set_chat_time(3);
  add_chat("I have seen times, I have seen places!");
  add_chat("Beware of the port thieves!");
  add_chat("Skippers do not want me on their ships, they say I'm too old.");
  add_chat("Bakona runs the best pub around here, the place is worth "
      +"visiting.");
  add_chat("Sair's Wall is around here somewhere, I know it.");
  set_act_time(4);
  add_act("sigh");
  add_act("stare");

    add_ask(({"sair"}), "say Sair is the goddess of the First Hour. She's "
	    +"the one what keeps walls together and buildings from falling "
		+"over.", 1);
	add_ask(({"sairs blessing", "blessing"}), "say Sair has blessed me "
	    +"with strength. I visit her shrine often.", 1);
	add_ask(({"shrine", "sairs shrine"}), "say It's high up in the south "
        +"wall of the port, but can only get there if She brings you "
		+"with her own hand. Scared the piss out of me the first time, I "
		+"will admit.", 1);
    add_ask(({"how to get to shrine"}), "say I am trying to remember that, "
        +"myself. Being on land confuses me.", 1);
    add_ask(({"sairs wall", "sairs walls", "wall", "walls"}), "say Look "
	    +"for octagons on the walls is what Bakona told me.", 1);
    add_ask(({"right wall", "wall to shrine"}), "say I'm looking for "
	    +"the right place myself.", 1);
    add_ask(({"octagon", "octagons"}), 
	    "say The octagon is the symbol of Sair. Builders carve it into "
		+"walls hoping She will make them strong and make them last. ", 1);
    add_ask(({"gem", "gems", "gemstones", "sacred gemstones"}), "say You're "
        +"not from around here, are you?", 1);	
    add_ask(({"catacombs", "necronisi", "banshee"}), "say The only way to get "
        +"to the Necronisi is in a coffin, you know.", 1);	
    add_ask(({"bazaar", "sybarus"}), "say You follow the path to the southeast. "
        +"It leads down to the fort that guards the entrance to the islands "
        +"of Sybarus.", 1);		


  set_random_move(2);
  
  set_skill( SS_DEFENSE, 100 );
  set_skill( SS_UNARM_COMBAT, 100 );
  set_skill( SS_AWARENESS, 40 );
}

void
equip_me() {
  object knuckles;
  int i;
  
  seteuid(getuid());
  
  MONEY_MAKE_SC(random(25))->move(this_object(), 1);
  clone_object(PORT + "obj/jacket")->move(this_object(),1);
  clone_object(PORT + "obj/oilskin_cloak")->move(this_object(),1);
  command("wear all");
  knuckles = clone_object(PORT + "obj/knuckles");
  knuckles->configure_me(A_R_HAND);
  knuckles->move(this_object(), 1);

  for (i = 0; i < 5; i++)
    clone_object(PORT + "obj/rum")->move(this_object(),1);
}

void
attacked_by(object ob) {
  ::attacked_by(ob);
  set_alarm(1.0, 0.0, wear_knuckles);
}

static void
wear_knuckles() {
  command("wear knuckles");
  command("say I shall grind your bones into dust!");
  command("drink all");
  command("burp");
  if (!alarm_id)
    // check whether we're fighting once for a while and remove knuckles
    // if we are not.
    alarm_id = set_alarm(60.0, 60.0, remove_knuckles);
}

static void
remove_knuckles() {
  if (objectp(query_attack())) {
    command("drink all"); //keep drunk while fighting
    return;
  }
  command("remove knuckles");
  remove_alarm(alarm_id);
  alarm_id = 0;
}


