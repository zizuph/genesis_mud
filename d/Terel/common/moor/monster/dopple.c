/*
 * Based on Jorl's doppleganger (~Terel/jorl/ruins/doppleganger)
 */

inherit "/std/monster";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "../local.h" 


object* weplist;
object *armlist;

/*
 * A nasty little monster with 100% of the skills and the stats of
 * any player that attacks it.  Also clones weapons and armour 
 * identical to its attackers.  As a side feature it mimics emotes
 * and commands given by the players in the room with it.
 * Jorl 3/93
 */
 
#define pobj    previous_object();

void
create_monster()
{
    set_long("It is a featureless humanoid.\n");
    add_name("doppleganger");
	set_race_name("doppleganger");
    set_adj("gray");
    set_gender(2);
    set_alignment(-500);
    set_stats(({ 40, 40, 40, 40, 40, 40}));
}

void
arm_me(object att)
{
    object   weapon, armour;
    string   wepname, armname;
    int      i;
    
    seteuid(getuid(TO));
    
    for (i=0;i<sizeof(weplist);i++)
    {
	    wepname = MASTER_OB(weplist[i]);
		weapon =  clone_object(wepname);
		weapon->move(TO);
    }
    command("wield all");
    
    for (i=0;i<sizeof(armlist);i++)
    {
		armname = MASTER_OB(armlist[i]);
		armour =  clone_object(armname);
		armour->move(TO);
    }
    command("wear all");
}

void
transform_stats(object attacker)
{   
    object  *weplist, *armlist;

    /*
     * Set the stats and description of doppleganger to that of the player.
     */
    
    remove_adj(TO->query_adjs());
    set_name(attacker->query_real_name());
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
    
    /*
     *  Gets the weapon and armour the player is using.
     */
    
    weplist = ({}); 
    weplist += attacker->query_weapon(-1);
    armlist = ({}); 
    armlist += attacker->query_armour(-1);
/*    arm_me(weplist, armlist);*/
}

/* 
 * Intercepts the kill doppleganger and sends the call to transform.
 * Also keeps all but the original attacker(bad) from attacking...
 * nasty but it keeps the doppleganger from changing back and forth.
 * It also prevents newbies from attacking so that big characters
 * could kill it easily.
 * 
 * Note:  If a fight stops for magical reasons (ie. Peace spells.), 
 *	  whoever attacks the doppleganger next will cause it to change
 *	  again.
 */

void
attacked_by(object bad)
{
    object *temp;
    
    temp = ({});
    temp += TO->query_enemy(-1);
    
    
	if (!sizeof(temp))
    {    
	 write("The statue changes before your eyes...it looks like YOU!!\n");
	 say("The statue transforms itself before your eyes...it "
			+ "looks like " + QCTNAME(bad) + ".\n");	
		transform_stats(bad);
	    write((temp[0]) + "**" + (temp[1]));
	    ::attacked_by(bad);
	    return;
    }
    if (member_array(bad, temp) != -1)&&
		(TO->query_real_name()==bad->query_real_name());
    {
	    ::attacked_by(bad);
	    return;
    }
    
	else if (present(pobj->attacked_by()));
    {
	    bad->catch_msg("In your confusion, you aren't sure who to attack!\n");
	    say(QCTNAME(bad) + " withdraws " + bad->query_possessive() 
	    + " attack...unsure of " + bad->query_possessive() + " target.\n");
	
	    bad->stop_fight(TO);
	    TO->stop_fight(bad);
    }
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
	        set_alarmv(1.0, -1.0, "command",({mimic_verb}));
	        return 0;
	    }
    }
}

