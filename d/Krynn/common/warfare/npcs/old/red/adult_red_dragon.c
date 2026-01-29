inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_age("adult");
    set_colour("red");
    add_name("adult_red");
    set_long("Before you crouches a creature of myth and legend! " +
	     "An adult red dragon, something that the storytellers " +
	     "scare children with in the late hours of the " +
	     "evening... a creature that you now note is very real " +
	     "as it stands threateningly " +
	     "over you. Its scales are a shiny red " +
	     "colour, its eyes are an angry amber that glow " +
	     "malevolently like volcanoes.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(4);
    add_act("emote twirls its long slender tail in the air " +
	    "in a slow, sinuous motion.");
    add_act("emote begins to prowl, its eyes flashing ominously like " +
	    "angry volcanoes.");
    add_act("emote flexes its enormous batlike wings and launches itself into the air!");
    add_act("emote hisses at you... dark smoke billows from the back of its throat.");
    add_act("emote stares intensely at you.");
    
    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
	     "terrifying roar!");
    add_cact("grin");

}

