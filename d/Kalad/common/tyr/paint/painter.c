/* Body painter */

#pragma strict_types

inherit "/d/Cirath/std/monster.c";
#include "defs.h"

void
create_monster()
{
   ::create_monster();
   set_name("alstor");
   set_race_name("human");
   set_title("the Master of Body Painting");
   set_adj("filthy");
   add_adj("paint-stained");

   set_long("This is a paint-stained human. He is dipping a brush in a tin "
	+"of paint. He probably wants to paint your body with different "
	+"colours.\n");

   set_stats(({50,50,75,40,40,30}));
   set_alignment(100);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,30);

   add_prop(OBJ_M_NO_ATTACK, "Are you stupid, if you kill this guy who will "
	+"then paint your body?\n");
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "Are you stupid, if you kill this guy who "
	+"will then paint your body?\n");

   set_act_time(3);
   add_act("emote looks like he wants to paint your body in various "
	+"colours.");
   add_act("emote starts to search here for some lost jars of paint.");
   add_act("say You want me to paint you for a small fee? It will only cost "
	+"you one platinum coin.");
   add_act("say Oh I really love this job. I can paint all day.");
   add_act("say Hmm... I wonder where I put my white colours.");
   add_ask(({"paint", "colour", "colours", "color", "colors", "buy", 
	"paint me", "body",}), 
	 "The filthy paint-stained human says: If you want me to paint you "
	+"you'll have to 'buycolour <colour>'. But first you'll have to "
	+"choose on of the colours on the picture that is posted on the "
	+"sign. It will cost you one platinum to have it done.\n");
   add_ask(({"remove", "remove paint", "remove colour", "remove the paint", 
	"remove the colour", "clean skin", "remove colours",
	"remove the colours"}), 
	 "Well then you'll just have to choose 'none' as a colour and I will "
	+"clean your skin in notime. But it will still cost you a platinum "
	+"coin. Thinner is expensive you know.\n");

   set_default_answer("What? Did you want me to paint your body?\n");
   set_speak("You probably would look better with a different body colour.\n");
}
