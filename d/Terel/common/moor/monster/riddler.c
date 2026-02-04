/*
 * Based in part on Jorl's doppleganger (~Terel/jorl/ruins/doppleganger)
 * This version doesn't clone the attackers weapons or armour, and
 * hopefully wont crash the gd!
 *
 */

inherit "/std/monster";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"

void
create_monster()
{
    set_long("It is a featureless humanoid.\n");
    add_name("riddler");
	set_race_name("statue");
    set_adj("gray");
    set_gender(2);
    set_alignment(-500);
    set_stats(({ 40, 40, 40, 40, 40, 40}));
}

/*
 * We don't want the player to get much xp for killing the monster,
 * so we mask out do_die
 */

void
do_die(object killer)
{
     command("say I am dead. Leave while you can!");
     environment(TO)->make_an_exit();
     remove_object();
}

/*
 * This function sets the stats of the monster to the those of the attacker.
 * It also clones thier skills.
 * Since the monster does not have the armour or weapons of the player
 * or any special guild attacks, we redude the players hit points
 * by 25%.
 */

global_set_up(object attacker)
{
    /*
     * Set the stats and description of doppleganger to that of the player.
     */
    
    remove_adj(TO->query_adjs());
    set_name("riddler");
    set_long(attacker->query_long());
    set_race_name(attacker->query_race_name());
    set_adj(attacker->query_adjs());
    set_gender(attacker->query_gender());
    set_stats(({attacker->query_stat(0), attacker->query_stat(1),
    		attacker->query_stat(2), attacker->query_stat(3), 
    		attacker->query_stat(4), attacker->query_stat(5)}));
    set_hp(attacker->query_hp());

    /*
     * Sets the doppleganger's combat skills to that of the player.
     */
    
    set_skill(SS_WEP_AXE, (TP->query_skill(SS_WEP_AXE))); 
    set_skill(SS_WEP_SWORD, (TP->query_skill(SS_WEP_SWORD)));
    set_skill(SS_WEP_POLEARM, (TP->query_skill(SS_WEP_POLEARM)));
    set_skill(SS_WEP_KNIFE, (TP->query_skill(SS_WEP_KNIFE)));
    set_skill(SS_WEP_CLUB, (TP->query_skill(SS_WEP_CLUB)));
    set_skill(SS_WEP_MISSILE, (TP->query_skill(SS_WEP_MISSILE)));
    set_skill(SS_WEP_JAVELIN, (TP->query_skill(SS_WEP_JAVELIN)));	
    set_skill(SS_2H_COMBAT, (TP->query_skill(SS_2H_COMBAT)));
    set_skill(SS_PARRY, (TP->query_skill(SS_PARRY)));
    set_skill(SS_DEFENCE, (TP->query_skill(SS_DEFENCE)));
    set_skill(SS_UNARM_COMBAT, (TP->query_skill(SS_UNARM_COMBAT)));

    
    attack_object(attacker);
}

/*
 * This little feature is added as an annoyance to players.
 * It allows the doppleganger to mimic things like hug and 
 * fondle and do them to the player.
 */
void
init_living()
{
    add_action("do_catch", "", 1);
	::init_living();
}

int
do_catch(string str)
{
    string  verb;
    string  mimic_verb;

    if (this_player() == this_object()) return 0;
 
    verb = query_verb();
    if (str == 0)
	str = "";
    if (strlen(verb) && verb[0] == "'"[0])
	return 0;

    mimic_verb=verb + " " + TP->query_real_name();
    
    switch(verb)
    {
	    case "kill":
		case "introduce":
		case "say":
		case "'":
		case "look":
		case "give":
		case "drop":
		case "stop": 
		case "n":
		case "s":
		case "e":
		case "w":
		case "ne":
		case "nw":
		case "se":
		case "sw":
		case "north":
		case "south":
		case "east":
		case "west":
		case "northwest":
		case "northeast":
		case "southwest":
		case "southeast": return 0; break;
	
		default:
	    {
                set_alarm(1.0, 0.0, &command(mimic_verb));
	        return 0;
	    }
    }
}

