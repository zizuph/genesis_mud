
/* 
 * A black dragon of the warfare system.
 */

inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Krynn/common/warfare/warfare.h"

string dragon_age;

string
random_dragon_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..5:
            dragon_age = "young"; // 60% 'young' (150ish stat average)
        break;
        case 6..8:
            dragon_age = "adult"; // 30% 'adult' (189 stat average) 
        break;
        default:
            dragon_age = "ancient"; // 10% 'ancient' (232 stat average)
        break;
    }

    return dragon_age;
}

void
create_dragon_npc()
{
    string type = random_dragon_type();

    ::create_dragon_npc();

    set_age(type);
    set_colour("black");
    add_name("warfare_black_dragon");
    set_long("Before you crouches a creature of myth and legend! " +
	     capitalize(LANG_ADDART(type))+ " black dragon, something " +
             "that the storytellers scare children with in the late " +
             "hours of the evening... " +
	     "a creature that you now note is very real as it stands " + 
	     "threateningly over you. Its scales are black as night, " +
	     "and its vicious eyes are framed by two great horns that " +
             "wrap from the side of its head to project forward.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_act_time(8);
    add_act("emote twirls its long slender tail in the air " +
	    "in a slow, sinuous motion.");
    add_act("emote begins to prowl, its eyes flashing viciously like " +
	    "a black storm.");
    add_act("emote flexes its enormous batlike wings and launches itself into the air!");
    add_act("emote hisses at you... its foul breath reminding you of rotting " +
        "vegetation and the fumes of powerful acids.");
    add_act("emote stares intensely at you.");
    
    set_cact_time(7);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
	     "terrifying roar!");
    add_cact("grin");

}

public void
do_die(object killer)
{
    string killer_army;

    if(WAR_CLUB_ADMIN->query_is_member(killer))
    {
        WAR_CLUB_ADMIN->add_warfare_enemy_vanquished(killer, 
            10, "black");

        killer_army = WAR_CLUB_ADMIN->query_warfare_army(killer);
        WAR_CLUB_ADMIN->increase_krynn_war_kills(killer_army, 1);
        WAR_CLUB_ADMIN->increase_krynn_war_player_kills(killer, 1);

        // Dragonarmy members don't get an alignment penalty for
        // killing other dragonarmy members
        if(WAR_CLUB_ADMIN->query_warfare_dragonarmy(killer))
        {
            set_alignment(0);
        }
    }

    ::do_die(killer);
}
 