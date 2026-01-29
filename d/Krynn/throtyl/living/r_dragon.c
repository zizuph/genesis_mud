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
    add_name("flamerage");
    add_name("_throtyl_dragon_");
    set_long("Before you is a creature of myth and legend! A dragon, something " +
      "that the storytellers scare children with in the late hours of the evening... " +
      "a creature that you now note is very real as it stands threateningly over " +
      "you. Its scales are a deep red colour, its eyes are an blood red like " +
      "the centre of a volcano.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_aggressive(1);

    set_act_time(12);
    add_act("emote twirls its long slender tail in the air " +
      "in a slow, sinuous motion.");
    add_act("emote begins to prowl, its eyes flashing ominously like " +
      "an active volcano.");
    add_act("emote flexes its enormous batlike wings.");
    add_act("emote stares intensely at you.");

    set_cact_time(8);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");
}

