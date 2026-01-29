// dock worker, travelling between port and outpost in Avenir
// made by Boriska
// Changed: Now starts in port10.c, so he will be loaded more often.
// Revisions:  Lilith, Feb '99: Made changes to eliminate over-
//               abundance of crates in fort6.c He now picks up
//               crates at the fort and re-deposits them in the 
//               ware.c in the port.
//              Lilith Apr 2022: updated this travel path and desc
//               as part of the Fort area makeover. He looks more 
//               like the BOGL goblins on the Necronisi.    

#include "/d/Avenir/common/common.h"

inherit "/std/monster";
#include "money.h";

int start_travelling();

string 
my_long()
{
    string str;
    str = "He is a cheerful sweaty goblin who seems to be "
            + query_exp_title() +" in size.\n";
    str +="He is a proud member of B.O.G.L.\n"
        + "He is a porter of Sybarus.\n"	
        + "His arms are long and his back is strong.\n"
        + "He appears to be remarkably mild-mannered for a goblin.\n"
        + "He seems to take pride in his horns, which are "
        + "painted with stripes and inset with garnets.\n"
        + "His eyes are dark and friendly.\n"
        + "His skin is light brown and surprisingly clean for a "
        + "goblin.\n"
		+ "He smells faintly of his last meal, which was fish.\n";
    return str;
}       
        
void
create_monster()
{
  set_long (my_long);

   set_name(({"jarod" , "worker"}));
   set_race_name("goblin");
   set_adj("cheerful");
   add_adj("sweaty");
   set_living_name("_dock_worker_");


  set_stats (({80,85,80,50,50,50}));
  set_stat_extra(0,300);
    //so he can lift the boxes but not have a massive xp reward

  set_alignment(random(21)-10);
  set_race_name("goblin");

  seteuid(geteuid(this_object()));
  MONEY_MAKE_SC(random(10))->move(this_object());

  set_act_time (15);
    add_act("emote shifts the weight of the box from one are to the other.");
    add_act("emote nearly slipped, but recovered his footing in time.");
    add_act("emote sighs stiredly.");
    add_act("emote pauses for a moment to rest.");
	add_act("say Sair's blessing has given me strength.");

    add_ask(({"sair"}), "say Sair is the goddess of the First Hour. She's "
        +"what keeps walls together and buildings from falling." ,1);
    add_ask(({"sairs blessing", "blessing"}), "say Sair has blessed me "
        +"with strength. I visit her shrine often.", 1);
    add_ask(({"shrine", "sairs shrine"}), "say It's high up in the south "
        +"wall of the port. You can only get there if She brings you.", 1);
    add_ask(({"how to get to shrine"}), "say I can't tell you about that, "
        +"each of us must find our own way.", 1);
    add_ask(({"sairs wall", "sairs walls", "wall", "walls"}), "say If "
        +"you take the time to look carefully, you can find one. Look "
    	+"for octagons.", 1);
    add_ask(({"right wall", "wall to shrine"}), "say Ah well that's not my "
        +"place to tell you that. Find a wall with an octagon and use her "
        +"gem. Keep looking, keep trying, is all I'm going to say.", 1);
    add_ask(({"octagon", "octagons"}), 
        "say The octagon is the symbol of Sair. That and those gemstones "
    	+"are sacred to Her.", 1);
    add_ask(({"gem", "gems", "gemstones", "sacred gemstones"}), "say You're "
        +"not from around here, are you?", 1);	
    add_ask(({"catacombs", "necronisi", "banshee"}), "say The only way to get "
        +"to the Necronisi is in a coffin, you know.", 1);		

  seq_reset();
  seq_new ("travel", 1); // never stop
  start_travelling();

}

int
start_travelling()
{
  seq_addfirst ("travel",
                ({   "shiver", "n", "emote orders a dark cognac.",
                     "emote drinks a glass of dark cognac.",
                     "sigh happ", "emote stands by the fire for a moment.",
                     "hug bakona",
                     "emote grates: Back to work.", "s", "s", "s",
                     "emote leans over the edge and watches the waterfall.",
                     "whistle", "s", "s", "s", "w", "w",
                     "emote grates: Hello!",
                     "stretch", "sigh",
                     "drop std_crate_ware", "get third std_crate_ware",
                     "emote grates: Back to work.",
                     "e" , "e", "n", "n", 2, "e", "s", "se",
                     "s", "s", "se", "s", "s", "se", "se",
                     "se", "se", "se","se", "se", 2, "peer .",
                     "e" , "e" , "s" ,
                     "drop std_crate_ware", "stretch", 
                     "get fifth std_crate_ware","n", "w", 
                     "w", "w", "nw", "nw", "nw",
                     "nw", "nw", "nw", 2, "nw", "n", "n", "nw",
                     "n", "n", "nw", "n", "w", 2, "n", "n", "n",
                     "@@start_travelling@@"}) );
  return 0;
}

int
outpost_act()
{
  command ("shout Hey you, up there, open the gates!");
  // to be filled...
  return 2; // wait a bit at outpost...
}

