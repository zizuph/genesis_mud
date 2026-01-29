/*
 * This file is /d/Shire/orcmaker/orcmaker.c.  It is supported by
 * /d/Shire/orcmaker/orcmaker.h which needs to be included somehow into
 * rooms cloning the orcmaker, or the coder must know the numeric equivs
 * for the nice text orc types that are allowed.
 * Finishing stage reached 6/7/94
 *
 * Last updated: Sept 9, 1994
 * Dunstable installed the Moria orc definition and arrays.
 * Sept 24, 1994
 * by Mayhem, April 1994
 *
 * Updated 20896, by Odin.
 * Fixed query_see_blood to options.

 * Jan 1998
 * Added Warg riding code to the orcmaker as well
 * as some changes to the argessive routines in the orc
 * -Igneous
 */
#pragma save_binary

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/npc.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/random.h"

inherit STDHUMAN;

#include <const.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define NUM_TYPES 7
// Number of types of humans.

/*
Function prototypes
*/

void disable_noise();
void disable_cnoise();
void add_extra_acts();
void add_extra_chats();
void add_extra_cacts();
void add_extra_cchats();
void set_human_type(int npc_type);
void set_human_stats(int npc_type);
int  my_aggressive();
void set_human_skills();
void arm_me();


// Global variables.
int ran_num;                                   // Random number provides
                                               // variety in stats
int npc_type;                                  // Type of human created
                                               // from list defined above

public void
create_human()
{
    // If you want to change the common human in any way, use this func.
}

public nomask void
create_khalakhor_human()
{
    if(!IS_CLONE) return;                       // Don't bother setting
                                                // up if this is the
                                                // master object.
    ran_num = 1 + random(15);                   // 1 to 15.
    npc_type = -1;                              // Start out as an untype
                                                // for debugging purposes

    add_name("_hummaker_hum");
    set_name("human");
    set_gender(!random(2) ? G_FEMALE : G_MALE); // 1 in 3 chance of being
                                                // female

    set_adj(RANDOM_DETAILED_ADJS(TO));          // See the Khalakhor sys
                                                // random files

    set_random_size_descs();

    set_long("@@human_long@@");

    set_stats(({ 50, 50, 50, 50, 50, 50 }));    // Some default stats.
                                                // Configure these later.

    add_prop(OBJ_S_WIZINFO,"This npc was based off of the Shire Orcmaker, "+
      "but has been heavily modified for Khalakhor. To properly clone " +
      "this npc, call clone_object(), set_type() and arm_me() before " +
      "moving to the room.\n");

    set_chat_time(12+ran_num);
    add_chat("");
    add_chat("There's one thing that stinks worse than a dead dwarf. And "+
      "that's a live one!");
    add_chat("Hey ugly, what are you looking at?");
    add_chat("Nothing tastes better than grain-fed, char-broiled "+
      "hobbit. Too bad they are so small, they hardly make a decent "+
      "snack...");
    add_chat("Men are worthless! Too stringy to eat and too hard to kill "+
      "most of the time to be worth the effort.");
    set_act_time(14+ran_num);
    add_act("emote growls: I hate dwarves and all their stinking friends!");
    add_act("sigh thoughtful");
    add_act("grumble angrily");
    add_act("cough");
    add_act(({"get all from corpse","wield all","wear all"}));
    set_cchat_time(5+ran_num);
    add_cchat("That almost tickled, you better try harder next time wimp!");
    set_cact_time(3+ran_num);
    add_cact(({"get all from corpse","wield all","wear all"}));
    add_cact("spit elves");
    add_cact("poke dwarves eye");
    add_cact("knee humans");
    add_cact("growl");
    add_cact("glare angrily");

    set_aggressive(my_aggressive);

    create_human();
}

public string
human_long()
{
    string str;

    str = (TP->query_met(TO) ? TO->query_met_name() :
      "The "+TO->query_nonmet_name());

    switch(npc_type)
    {
    case -1:
        str += " isn't properly set up. Please make a bug report.\n";
        break;
    case HUMCITIZEN:
        str += " busies " +HIM_HER(TO)+"self with the day to day " +
          "tasks of a common citizen.\n";
        break;
    case HUMTRADES:
        str += " concentrates on "+HIS_HER(TO)+" chosen trade, quietly " +
          "going about "+HIS_HER(TO)+ " work.\n";
        break;
    case HUMPATROL:
        str += " seems very aware of " +HIS_HER(TO)+ " surroundings, as " +
          HE_SHE(TO) + " patrols the local area.\n";
        break;
    case HUMGUARD:
        str += " stands guard over the local area.\n";
        break;
    case HUMWARRIOR:
        str += " has the look of a practiced warrior.\n";
        break;
    case HUMELITE:
        str += " has the look of an elite warrior.\n";
        break;
    case HUMSUPREME:
        str += " appears to have the battle-readiness of a supreme " +
          "warrior.\n";
        break;
    default:
        str += " is a typical human citizen of Khalakhor.\n";
        break;
    }
    return str;
}

public int
my_aggressive()
{

    // Leave the poor wizards alone.
    if (TP->query_wiz_level())
	return 0;
// Oooh bad orc killer, we have to kill this bastard
//    if (TP->query_prop(LIVE_I_KILL_ORCS))
//	return 1;
    // They can be aggressive to people with really poor reputations!
    if (TP->query_alignment() <= -500)  // Just an align test until rep skill
                                        // is set up.
	return 1;
    // Humans are neutral to most races, so won't autoattack based on race.
    return 0;
}


public void 
disable_noise()
{
    clear_chat();
    set_act_time(10000);
}

public void 
disable_cnoise()
{
    clear_cchat();
    set_cact_time(10000);
}

public void 
set_human_stats(int npc_type)
{
    int   *npc_stats;
    int    initial_stat;
    int    is;

    initial_stat = npc_type * (18 + random(10));

    npc_stats = allocate(6);

    npc_stats[0] = initial_stat + ran_num + random(5); // STR
    npc_stats[1] = initial_stat + ran_num + random(5); // DEX
    npc_stats[2] = initial_stat + ran_num + random(5); // CON
    npc_stats[3] = initial_stat + ran_num + random(5); // INT
    npc_stats[4] = initial_stat + ran_num + random(5); // WIS
    npc_stats[5] = initial_stat + ran_num + random(5); // DIS

    for (is = 0; is < 6; is++)
    {
	if (npc_stats[is] < 5)
	    npc_stats[is] = 5;
    }

    set_stats(npc_stats);
    set_alarm(0.5,0.0, set_human_skills);
    refresh_living();
}


/* 
 * function: set_human_skills()
 * Sets an skills in the humanmaker human according to stat average.
 * Sets the 5 implemented weapon skills, special combat skills,
 * and some general skills useful to all humans.
 *
 * Check the 'sman' files for the standard format of documentation on
 * functions
 */
public int 
set_human_skills()
{
// Npcs range from 0 to 6. Skills range from 0 to 100. 
// Npc type * 8 = 0 to 48 + 24 + random(29)
    int my_skills;
    int npc_stat_avg = query_average_stat();
    
    my_skills = 24; // Base skills.
    my_skills = npc_type * 8 + my_skills;
    
    set_alignment(0 + 7 * npc_stat_avg);     // max is 1162
                                             // Set it here because we need
                                             // the stats to complete setting
                                             // up first, since we base it off
                                             // that.

    set_skill(SS_WEP_SWORD, my_skills + random(29));
    set_skill(SS_WEP_CLUB, my_skills + random(29));
    set_skill(SS_WEP_KNIFE, my_skills + random(29));
    set_skill(SS_WEP_POLEARM, my_skills + random(29));
    set_skill(SS_WEP_AXE, my_skills + random(29));
    set_skill(SS_PARRY, my_skills + random(29));
    set_skill(SS_DEFENCE, my_skills + random(29));
    set_skill(SS_2H_COMBAT, my_skills + random(29));
    set_skill(SS_UNARM_COMBAT, my_skills + random(29)); 
    set_skill(SS_SNEAK, my_skills + random(29));
    set_skill(SS_HIDE, my_skills + random(29));
    set_skill(SS_AWARENESS, my_skills + random(29));
    set_skill(SS_ACROBAT, my_skills + random(29));
    set_skill(SS_ANI_HANDL, my_skills + random(29));

}


/* functions: set_type() and set_orc_type()
 * Remarkably, these functions pretty much do what they say.
 * I allow certain types of orcs (as defined near the top of the code)
 * and those types of orcs get specific pieces of equipment and/or 
 * chats/acts/cchats/cacts, so I put them in here (and so do other
 * wizards, just by putting set_type(TYPE); in whatever file 
 * creates the orc using the Orcmaker.
 * Default orc type will be HUMCITIZEN, which receives no (0!) extras.
 *
 * Check 'sman' for standard format of documentation!
 */

public void
set_type(int some_num)
{
    if(some_num < 0 || some_num > NUM_TYPES)
	some_num = 0;

    npc_type = some_num;

	FIX_EUID;

/*
    if(!random(4))
	clone_object(ORC_OBJ + ONE_OF_LIST(MISC_OBJ))->move(TO);
*/	
    set_human_type(npc_type);
    set_human_stats(npc_type);
}

int arm_me()
{
    object wep, arm;
    int arm_num;

    switch(npc_type)
    {
    case HUMCITIZEN:
	break;
    case HUMTRADES:
/*
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMTRADES_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMTRADES_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMTRADES_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMTRADES_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMTRADES_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMTRADES_ARM_GOOD));
	    break;
	}
*/
	break;
    case HUMPATROL:
	    wep=clone_object(HUWEP + one_of_list(HUMPATROL_WEP));

/*
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(WAR_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(WAR_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(WAR_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(WAR_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(WAR_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(WAR_ARM_GOOD));
	    break;
	}
*/
	break;
    case HUMGUARD:
/*
	switch(TO->query_average_stat())
	{
	    TO->set_aggressive(0);
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMGUARD_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMGUARD_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMGUARD_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMGUARD_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMGUARD_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMGUARD_ARM_GOOD));
	    break;
	}
*/
	break;
    case HUMWARRIOR:
/*
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMTRADES_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMTRADES_ARM_AVG));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(HUMTRADES_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(HUMTRADES_ARM_GOOD));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(WAR_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(WAR_ARM_GOOD));
	    break;
	}
*/
	break;
    case HUMELITE:
/*
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(MORIA_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(MORIA_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(MORIA_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(MORIA_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(MORIA_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(MORIA_ARM_GOOD));
	    break;
	}
*/
	break;
	case HUMSUPREME:
	break;
	default:
	break;
    }
    wep->move(TO);
    arm->move(TO);
    command("wield all");
    command("wear all");
}

nomask public int
query_human_type()
{
    return npc_type;
}

public void 
set_human_type(int npc_type)
{
    switch(npc_type)
    {
    case HUMCITIZEN:
	add_name("citizen");
	break;
    case HUMTRADES:
	add_name("tradesman");
	break;
    case HUMPATROL:
	add_name("patrolman");
	add_name("patrol");
	break;
    case HUMGUARD:
	add_name("guard");
	break;
    case HUMWARRIOR:
	add_name("warrior");
	break;
    case HUMELITE:
	add_name("elite");
	break;
	case HUMSUPREME:
	add_name("supreme");
    }

    add_extra_chats();
    add_extra_acts();
    add_extra_cchats();
    add_extra_cacts();
}

void 
add_extra_chats()
{
    switch(npc_type)
    {
    case HUMCITIZEN:
	add_chat("'Tis a bonnie day!");
	break;
    case HUMTRADES:
	add_chat("Business is poor, these days!");
	add_chat("I hae heard strange rumours of the north, but I will nae " +
	  "speak of them.");
	break;
    case HUMPATROL:
	add_chat("I hae been told to keep my eyes open for feral goblins!");
	break;
    case HUMGUARD:
	add_chat("Dwarves are better suited for guard duty.");
	break;
    case HUMWARRIOR:
	add_chat("Cannae tha goblins of the north leave well enough alone?");
	break;
    case HUMELITE:
    add_chat("Woe! The clans fight amongst themselves while the goblins " +
      "of the north gather!");
	break;
	case HUMSUPREME:
	add_chat("The goblins of the north are amassing their forces. I fear " +
	  "a war is nigh.");
	break;
	default:
	break;
    }
}


public string
add_extra_acts()
{
    switch(npc_type)
    {
    case HUMCITIZEN:
	add_act("emote grumbles: 'Cook dinner!' 'Dig here!' " +
	  "'Clean this up!'. Wait til they fall asleep and " +
	  "then we shall see who gets cooked and what gets buried!");
	add_act("hum quietly");
	add_act("moan pitif");
	add_act("emote groans in pain.");
	add_act("sniff pitif");
	break;
    case HUMTRADES:
	add_act("snore");
	add_act("emote blinks sleep from his eyes.");
	add_act("emote stands as still as possible.");
	add_act("hiccup");
	break;
    case HUMPATROL:
    switch(random(7))
    {
    case 0:
    return "emote "+(sizeof(query_weapon(-1)) ? "polishes "+HIS_HER(TO) +
              " "+query_weapon(-1)[0]->short()+"." : "stands at " + 
              HIS_HER(TO)+" post.");
    case 1:
    return "emote "+(sizeof(query_armour(-1)) ? "attends to " +
              HIS_HER(TO)+" "+query_armour(-1)[0]->short()+" with pride "+
              "and skill." : "searches "+HIS_HER(TO)+" pockets for some "+
              "pipe-weed.");
    case 2:
	return "shout Let me at em!";
	case 3:
	return "strut";
    case 4:
	return "emote flexes his arms intimidatingly.";
    case 5:
	return "emote grunts.";
    case 6:
    return "emote bleh.";
	}
	break;
    case HUMGUARD:
	add_act("emote pads around stealthily.");
	add_act("emote peers about cautiously.");
	add_act("emote shades his eyes as he peers into the distance.");
	break;
    case HUMWARRIOR:
	break;
    case HUMELITE:
	break;
	case HUMSUPREME:
	break;
	default:
	break;
    }
}

void 
add_extra_cchats()
{
    switch(npc_type)
    {
    case HUMCITIZEN:
	add_cchat("Why do you bother with me? Go kill the masters, they "+
	  "have much treasure!");
	break;
    case HUMTRADES:
	add_cchat("Hey you, get out of here before I hurt you!");
	add_cchat("Leave me alone, I'm busy!");
	break;
    case HUMPATROL:
	add_cchat("You fool! You can't stop me!");
	add_cchat("I can break you like a dead twig, puny fool.");
	break;
    case HUMGUARD:
	add_cchat("You'll never kill us all!");
	add_cchat("If I wasn't stuck in this damn camp I could win "+
	  "this fight!");
    case HUMWARRIOR:
	break;
    case HUMELITE: 
	break;
	case HUMSUPREME:
	break;
	default:
	break;
    }
}


string 
add_extra_cacts()
{
    switch(npc_type)
    {
    case HUMCITIZEN:
	add_cact("grovel");
	add_cact("scream");
	break;
    case HUMTRADES:
	add_cact("laugh");
	add_cact("cackle");
	add_cact("shout Intruders! Intruders!");
	break;
    case HUMPATROL:
	add_cact("spit");
	add_cact("emote bares his yellowed tusks.");
	add_cact("grumble");
	add_cact("shout You call this fighting?");
	break;
    case HUMGUARD:
	add_cact("emote tries to sneak around behind you.");
	add_cact("emote looks for an opening.");
	add_cact("emote looks for a handy escape route.");
	add_cact("smirk");
	break;
    case HUMWARRIOR:
	break;
    case HUMELITE:
	break;
	case HUMSUPREME:
	break;
	default:
	break;
    }
}
