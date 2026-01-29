// -*-C++-*-
// file name: ~Avenir/common/port/mon/immigrant_e.c
// purpose:    NPC for port area

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>

inherit "/std/monster";


void
create_monster() 
{
    add_name("immigrant");
    set_adj(one_of_list(({
	"sullen", "morose", "sulky", "resentful", "grumpy", "surly" })));
    set_race_name(one_of_list(({
	"human", "elf", "half-elf", "gnome", "dwarf", "goblin" })));

    default_config_npc(random(40) + 30);

    set_chat_time(15);
    add_chat("If they kicked me out. I've no where else to go.");
    add_chat("I have heard that Sybarus is a land of plenty.");
    add_chat("Who cares about gods and spirits! I'm the only one who can "+
      "change my fortune.");
    add_chat("I'm not going to stay here much longer.");
    add_chat("If you don't shut up, I'll pin your tongue to the wall "+
      "with my knife.");
    add_chat("You people are pathetic, I hope they don't let you in.");
    add_chat("I just want one night at the Ziggurat.");  
    add_chat("I like darkness best, but I'll settle for shadow.");
    add_chat("Oh, stop your belly-aching.");
    add_chat("Serves you right. All you do is whine.");
    add_chat("Some of these people could use a bath.");
    add_chat("You aren't all that nice either.");
    add_chat("I tried to get one of those dwarven guards drunk. He drew "+
      "his sword and fairly accused me of attempting to bribe him.");
    add_chat("There has to be an easy way to live in comfort here.");
    add_chat("Your endless babbling is annoying me.");
    add_chat("I heard that you can pluck gems from the ground like ripe "+
      "fruit from an orchard.");
    add_chat("I don't know why they wouldn't want me. I've so many valuable "+
      "skills...");
    add_chat("I'll marry first off. Its the best way to gain status.");
    add_chat("Then I'll get myself a couple of slaves to satisfy my every whim.");
    add_chat("Ah, I'm sure their gods are like everyone else's gods: invisible "+
      "and indifferent.");
    add_chat("A little luck, and I'll be running a gambling establishment "+
      "in no time.");
    add_chat("I don't suppose those inquisitors are fools, more's the pity.");

    set_gender(random(2));

    set_act_time(60 + random(99));
    add_act("sigh contempt");
    add_act("stare ");
    add_act("burp rude");
    add_act("flex");
    add_act("scratch behind");
    add_act("leer all");  
    add_act("laugh jeer");
    add_act("chuckle mocking");
    add_act("think unpleasant thoughts..");
    add_act("growl");
    add_act("ffinger all"); 

    set_skill( SS_DEFENSE, 30 );
    set_skill( SS_UNARM_COMBAT, 40 );
    set_skill( SS_AWARENESS, 40 );
}
