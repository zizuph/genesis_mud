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
 */
#pragma save_binary

inherit "/d/Shire/orcmaker/team";
inherit "/std/act/attack";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/prestige.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define NUM_TYPES 10  /* Number of types of Orcmaker orcs */
#define ORC_WEP ORCMAKER_DIR + "wep/"
#define ORC_ARM ORCMAKER_DIR + "arm/"
#define ORC_OBJ ORCMAKER_DIR + "obj/"

// Allowable types of orcs to be set with set_type when cloning
#define SLAVE  0
#define GUARD  1
#define WARRIOR  2
#define SCOUT  3
#define SLAVE_DRIVER  4
#define RED_EYE_ORC  5
#define WHITE_HAND_ORC  6
#define WOLF_RIDER_ORC  7
#define GOBLIN_GATE_ORC  8
#define MORIA_ORC 9

// Arrays storing weapons and armours according to 'strength' and 'type'
#define GUARD_WEP_WEAK ({ "wshort","wjsword","wscimitar","wbroad", \
    "wcaxe","wwclub","wmace","wknife","wspear","wstaff" })
#define GUARD_WEP_AVG ({ "short","jsword","scimitar","broad", \
    "caxe","wclub","mace","knife","spear","staff" })
#define GUARD_WEP_GOOD ({ "gshort","gjsword","gscimitar","gbroad", \
    "gcaxe","gwclub","gmace","gknife","gspear","gstaff" })
#define WAR_WEP_WEAK ({ "wlong","wbroad","wjsword","wthsword","wbaxe", \
    "wsclub","wmace","wglaive","wspear","whalberd" })
#define WAR_WEP_AVG ({ "long","broad","jsword","thsword","baxe", \
    "sclub","mace","glaive","spear","halberd" })
#define WAR_WEP_GOOD ({ "glong","gbroad","gjsword","gthsword","gbaxe", \
    "gsclub","gmace","gglaive","gspear","ghalberd" })
#define MORIA_WEP_WEAK ({ "wlong","wbroad","wjsword","wthsword","wbaxe", \
    "wsclub","wmace","wglaive","wspear","whalberd" })
#define MORIA_WEP_AVG ({ "long","broad","jsword","thsword","baxe", \
    "sclub","mace","glaive","spear","halberd" })
#define MORIA_WEP_GOOD ({ "glong","gbroad","gjsword","gthsword","gbaxe", \
    "gsclub","gmace","gglaive","gspear","ghalberd" })
#define SCOUT_WEP_WEAK ({ "wshort","wscimitar","wcaxe","wwclub","wmace", \
    "wknife","wgauche","wspear" })
#define SCOUT_WEP_AVG ({ "short","scimitar","caxe","wclub","mace", \
    "knife","gauche","spear" })
#define SCOUT_WEP_GOOD ({ "gshort","gscimitar","gcaxe","gwclub","gmace", \
    "gknife","ggauche","gspear" })
#define GUARD_ARM_WEAK ({ "wchain","wsleather","waugmail","wsplint" })
#define GUARD_ARM_AVG ({ "chain","sleather","augmail","splint" })
#define GUARD_ARM_GOOD ({ "gchain","gsleather","gaugmail","gsplint" })
#define WAR_ARM_WEAK ({ "wchain","waugmail","wsplint","wplate", \
    "sleather" })
#define WAR_ARM_AVG ({ "chain","augmail","splint","plate", \
    "gsleather" })
#define WAR_ARM_GOOD ({ "gchain","gaugmail","gsplint","gplate", \
    "gchain" })
#define MORIA_ARM_WEAK ({ "wchain","waugmail","wsplint","wplate", \
    "sleather" })
#define MORIA_ARM_AVG ({ "chain","augmail","splint","plate", \
    "gsleather" })
#define MORIA_ARM_GOOD ({ "gchain","gaugmail","gsplint","gplate", \
    "gchain" })
#define SCOUT_ARM_WEAK ({ "wchain","wsleather","wleather","wsplint" })
#define SCOUT_ARM_AVG ({ "chain","sleather","leather","splint" })
#define SCOUT_ARM_GOOD ({ "gchain","gsleather","gleather","gsplint" })
#define MISC_ARM_WEAK ({ "wboots","wgaunt","wcloak","whelm" })
#define MISC_ARM_AVG ({ "boots","gaunt","cloak","helm" })
#define MISC_ARM_GOOD ({ "gboots","ggaunt","gcloak","ghelm" })

// Array storing miscellaneous items found on orcs
#define MISC_OBJ ({ "kbones","bone","pebble" })

// Function prototypes
void disable_noise();
void disable_cnoise();
void add_extra_acts();
void add_extra_chats();
void add_extra_cacts();
void add_extra_cchats();
void set_orc_type();
void set_orc_stats(int level);
string physlook();
string alignlook();
void release(object me);

// Global variables.
int npc_power,    /* Power level: stats, skills, strength of
		     equipment, and amount of coins depend on this */
ran_num,      /* Random number provides some variety in stats */
npc_type;     /* Type of orc created from list defined above  */
int release_id;

object stunned;  /* Plyer we stunned */

void create_orc() {}

void
create_shire_monster()
{
    if(!IS_CLONE) return;
    ran_num = 1 + random(15);
    npc_type = 0;

    add_name("_orcmaker_orc");
    set_name("orc");
    set_race_name("orc");
    set_adj(({alignlook(),physlook()}));
    set_long("The "+TO->query_nonmet_name()+" is covered with patches "+
      "of dirty brown fur "+
      "that poke through its clothing. Deeply sunken eyes "+
      "glare out from underneath a cliff-like brow, perched above "+
      "wide, flaring nostrils and stained, yellow tusks.\n");
    set_stats(({ 50, 50, 50, 50, 50, 50 }));
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,2+random(2));
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_S_WIZINFO,"This orc was created using the Orcmaker.  "+
      "To learn more about the Orcmaker, ask a Shire wiz, or RTFSC. "+
      "\nMayhem.\n");

    //  set_tell_active(1);

    set_chat_time(12+random(14));
    add_chat("The only thing elves are good for is dinner!");
    add_chat("There's one thing that stinks worse than a dead dwarf. And "+
      "that's a live one!");
    add_chat("Hey ugly, what are you looking at?");
    add_chat("Nothing tastes better than grain-fed, char-broiled "+
      "hobbit. Too bad they are so small, they hardly make a decent "+
      "snack...");
    add_chat("Men are worthless! Too stringy to eat and too hard to kill "+
      "most of the time to be worth the effort.");
    set_act_time(14+random(20));
    add_act("emote growls: I hate dwarves and all their stinking friends!");
    add_act("growl");
    add_act("emote snorts like a wild animal.");
    add_act("grumble angrily");
    add_act("cough");
    add_act("burp");
    add_act(({"get all from corpse","wield all","wear all"}));
    set_cchat_time(5+random(10));
    add_cchat("That almost tickled, you better try harder next time wimp!");
    set_cact_time(3+random(4));
    add_cact(({"get all from corpse","wield all","wear all"}));
    add_cact("spit elves");
    add_cact("poke dwarves eye");
    add_cact("knee humans");
    add_cact("puke gnomes");
    add_cact("snarl hobbits");

    set_aggressive(1);

    create_orc();
}


string 
physlook()
{
    string *physlooks;

    physlooks = ({"big","large","tall","long-armed","ugly","broad",
      "short","massive","small","strong","swarthy","dark-eyed","powerful", 
      "black-haired","yellow-tusked","yellow-eyed","black-eyed","dirty",
      "sturdy","squat"});
    return physlooks[random(sizeof(physlooks))];
}

string 
alignlook()
{
    string *alignlooks;

    alignlooks = ({"foul","damned","evil","grumpy","grouchy","cruel","sad",
      "deranged","insane","grim","desperate",
      "angry","mean","foul","brutal","savage","cranky","testy","mad",
      "sinister","wicked","nasty","malevolent","beastly","demonic"});
    return alignlooks[random(sizeof(alignlooks))];
}

void 
disable_noise()
{
    clear_chat();
    set_act_time(10000);
}

void 
disable_cnoise()
{
    clear_cchat();
    set_cact_time(10000);
}

void 
set_power(int level)
{
    if(level > 300)
    {
	level = 300;
    }

    set_orc_stats(level);
}

void 
set_orc_stats(int level)
{
    int   *npc_stats,
    initial_stat,
    is;

    initial_stat = level / 2;

    npc_stats = allocate(6);

    npc_stats[0] = initial_stat + (ran_num * 2); // STR
    npc_stats[1] = initial_stat + ran_num;       // DEX
    npc_stats[2] = initial_stat + (ran_num * 3); // CON
    npc_stats[3] = initial_stat - (ran_num * 2); // INT
    npc_stats[4] = initial_stat / 10; //WIS
    npc_stats[5] = 2 * initial_stat; //DIS

    for (is = 0; is < 6; is++)
    {
	if (npc_stats[is] < 5)
	    npc_stats[is] = 5;
    }
    if (npc_stats[3] > 70)
	npc_stats[3] = 70;
    if(npc_stats[4] > 75)
	npc_stats[4] = 75;

    set_stats(npc_stats);
    set_alarm(0.5,0.0,"set_orc_skills");
    REFRESH;
}


/* 
 * function: set_orc_skills()
 * Sets an skills in the Orcmaker orc according to stat average.
 * Sets the 5 implemented weapon skills, special combat skills,
 * and some general skills useful to all orcs.
 *
 * Check the 'sman' files for the standard format of documentation on
 * functions
 */
int 
set_orc_skills()
{
    int     ran_num2,
    npc_stat_avg = query_average_stat(),
    mod_skills,
    com_skill,
    spe_skill,
    gen_skill;

    ran_num2 = random(6) + 5;

    set_alignment(-75 - 2 * npc_stat_avg);

    if(npc_stat_avg > 50)
    {
	mod_skills = npc_stat_avg/3 + 100;
    }
    else
    {
	mod_skills = npc_stat_avg * 2;
    }

    com_skill = mod_skills * 45 / 100;
    spe_skill = mod_skills * 50 / 100;
    gen_skill = mod_skills * 40 / 100;

    if(spe_skill > 70)
    {
	spe_skill += ran_num2 * 3;
	if(spe_skill > 100)
	    spe_skill = 100;
    }
    else if(spe_skill < 1)
	spe_skill = 1;

    if(com_skill > 60)
    {
	com_skill = com_skill + ran_num2 * 2;
	if(com_skill > 100) 
	    com_skill = 100;
    }
    else if(com_skill < 1)
	com_skill = 1;

    if(gen_skill > 55)
    {
	gen_skill = gen_skill + ran_num2;
	if(gen_skill > 100)
	    gen_skill = 100;
    }
    else if(gen_skill < 1)
	gen_skill = 1;

    set_skill(SS_WEP_SWORD,spe_skill);
    set_skill(SS_WEP_CLUB,spe_skill);
    set_skill(SS_WEP_KNIFE,spe_skill);
    set_skill(SS_WEP_POLEARM,spe_skill);
    set_skill(SS_WEP_AXE,spe_skill);
    set_skill(SS_PARRY,com_skill);
    set_skill(SS_DEFENCE,com_skill);
    set_skill(SS_2H_COMBAT,com_skill);
    set_skill(SS_SNEAK,gen_skill);
    set_skill(SS_HIDE,gen_skill);
    set_skill(SS_AWARENESS,gen_skill);
    set_skill(SS_ACROBAT,gen_skill);
}


/* functions: set_type() and set_orc_type()
 * Remarkably, these functions pretty much do what they say.
 * I allow certain types of orcs (as defined near the top of the code)
 * and those types of orcs get specific pieces of equipment and/or 
 * chats/acts/cchats/cacts, so I put them in here (and so do other
 * wizards, just by putting set_type(TYPE); in whatever file 
 * creates the orc using the Orcmaker.
 * Default orc type will be SLAVE, which receives no (0!) extras.
 *
 * Check 'sman' for standard format of documentation!
 */
void set_type(int some_num)
{
    if(some_num < 0 || some_num > NUM_TYPES)
	some_num = 0;

    npc_type = some_num;

    if(npc_type > 0)
	MAKE_MONEY;
    FIXEUID;
    if(!random(4))
	clone_object(ORC_OBJ + ONE_OF_LIST(MISC_OBJ))->move(TO);

    set_orc_type();
}


int arm_me()
{
    object wep, arm;
    int arm_num;
    FIXEUID;

    switch(npc_type)
    {
    case 0:
	break;
    case 1:
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(GUARD_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(GUARD_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(GUARD_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(GUARD_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(GUARD_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(GUARD_ARM_GOOD));
	    break;
	}
	break;
    case 2:
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
	break;
    case 3:
	switch(TO->query_average_stat())
	{
	    TO->set_aggressive(0);
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(SCOUT_WEP_WEAK));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(SCOUT_ARM_WEAK));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(SCOUT_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(SCOUT_ARM_AVG));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(SCOUT_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(SCOUT_ARM_GOOD));
	    break;
	}
	break;
    case 4:
	break;
    case 5:
	break;
    case 6:
	break;
    case 7:
	break;
    case 8:
	break;
    case 9:
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
	break;
    }
    wep->move(TO);
    arm->move(TO);

    switch(TO->query_average_stat())
    {
    case 1..49:
	arm=clone_object(ORC_ARM + ONE_OF_LIST(MISC_ARM_WEAK));
	break;
    case 50..99:
	arm=clone_object(ORC_ARM + ONE_OF_LIST(MISC_ARM_AVG));
	break;
    case 100..300:
	arm=clone_object(ORC_ARM + ONE_OF_LIST(MISC_ARM_GOOD));
	break;
    }
    arm->move(TO);
    command("wield all");
    command("wear all");
}

void 
set_orc_type()
{
    switch(npc_type)
    {
    case 0:
	add_name("slave");
	break;
    case 1:
	add_name("guard");
	break;
    case 2:
	add_name("warrior");
	add_prop(LIVE_O_ENEMY_CLING,1);
	break;
    case 3:
	add_name("scout");
	break;
    case 4:
	add_name("driver");
	break;
    case 5:
	add_name("red_eye");
	break;
    case 6:
	add_name("white_hand");
	break;
    case 6:
	add_name("wolf_rider");
	break;
    case 6:
	add_name("goblin_gate");
	break;
    case 9:
	add_name("moria_orc");
	add_prop(LIVE_O_ENEMY_CLING, 1);
	set_restrain_path("/d/Shire/moria/mines");
    }
    add_extra_chats();
    add_extra_acts();
    add_extra_cchats();
    add_extra_cacts();
    set_alarm(1.0,0.0,"arm_me");
}

void 
add_extra_chats()
{
    switch(npc_type)
    {
    case 0 :
	add_chat("I hate those bully boys, always giving orders and "+
	  "cracking those whips. How I'd love to strangle them "+
	  "with their damn whips.");
	break;
    case 1 :
	add_chat("Standing around here all day is so boring.");
	add_chat("When can we go, I'm bored!");
	break;
    case 2 :
	add_chat("I can't wait for the next battle!");
	add_chat("I hope we get orders soon, I want to kill!");
	break;
    case 3 :
	add_chat("They better not send us on any more scouting missions "+
	  "during the day, my eyes are killing me.");
	add_chat("Night missions are the most fun.");
	break;
    case 4 :
	add_chat("Get moving, you lazy curs!");
	break;
    case 5 :
	add_chat("Insert something here.");
	break;
    case 6 :
	add_chat("Insert something here.");
	break;
    case 7 :
	add_chat("Insert something here.");
	break;
    case 8 :
	add_chat("Insert something here.");
	break;
    }
}


void 
add_extra_acts()
{
    switch(npc_type)
    {
    case 0:
	add_act("emote grumbles: 'Cook dinner!' 'Dig here!' " +
	  "'Clean this up!'. Wait til they fall asleep and " +
	  "then we shall see who gets cooked and what gets buried!");
	add_act("cringe");
	add_act("moan pitif");
	add_act("emote groans in pain.");
	add_act("sniff pitif");
	break;
    case 1 :
	add_act("snore");
	add_act("emote blinks sleep from his eyes.");
	add_act("emote stands as still as possible.");
	add_act("hiccup");
	break;
    case 2 :
	add_act("shout Let me at em!");
	add_act("strut");
	add_act("emote flexes his arms intimidatingly.");
	add_act("emote grunts.");
	break;
    case 3 :
	add_act("emote pads around stealthily.");
	add_act("emote peers about cautiously.");
	add_act("emote shades his eyes as he peers into the distance.");
	break;
    case 4 :
	add_act("emote cracks his whip at you.");
	add_act("emote snarls savagely.");
	add_act("emote smiles cruely");
	break;
    case 5 :
	add_act("emote don't forget to insert something here.");
	break;
    case 6 :
	add_act("emote don't forget to insert something here.");
	break;
    case 7 :
	add_act("emote don't forget to insert something here.");
	break;
    case 8 :
	add_act("emote don't forget to insert something here.");
	break;
    }
}

void 
add_extra_cchats()
{
    switch(npc_type)
    {
    case 0 :
	add_cchat("Why do you bother with me? Go kill the masters, they "+
	  "have much treasure!");
	break;
    case 1 :
	add_cchat("Hey you, get out of here before I hurt you!");
	add_cchat("Leave me alone, I'm busy!");
	break;
    case 2 :
	add_cchat("You fool! You can't stop me!");
	add_cchat("I can break you like a dead twig, puny fool.");
	break;
    case 3 :
	add_cchat("You'll never kill us all!");
	add_cchat("If I wasn't stuck in this damn camp I could win "+
	  "this fight!");
    case 4 :
	add_cchat("You've got spirit for a slave, but don't worry, "+
	  "I'll fix that.");
	add_cchat("Ha! Hold still, slave! I'll finish this quick enough.");
	break;
    case 5 :
	add_cchat("I need something else to say.");
	break;
    case 6 :
	add_cchat("I need something else to say.");
	break;
    case 7 :
	add_cchat("I need something else to say.");
	break;
    case 8 :
	add_cchat("I need something else to say.");
	break;
    }
}


string 
add_extra_cacts()
{
    switch(npc_type)
    {
    case 0 :
	add_cact("grovel");
	add_cact("scream");
	break;
    case 1 :
	add_cact("laugh");
	add_cact("cackle");
	add_cact("shout Intruders! Intruders!");
	break;
    case 2 :
	add_cact("spit");
	add_cact("emote bares his yellowed tusks.");
	add_cact("grumble");
	add_cact("shout You call this fighting?");
	break;
    case 3 :
	add_cact("emote tries to sneak around behind you.");
	add_cact("emote looks for an opening.");
	add_cact("emote looks for a handy escape route.");
	add_cact("smirk");
	break;
    case 4 :
	add_cact("emote thinks his creator is running out of creativity.");
	break;
    case 5 :
	add_cact("emote thinks his creator is running out of creativity.");
	break;
    case 6 :
	add_cact("emote thinks his creator is running out of creativity.");
	break;
    case 7 :
	add_cact("emote thinks his creator is running out of creativity.");
	break;
    case 8 :
	add_cact("emote thinks his creator is running out of creativity.");
	break;
    }
}

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_option(OPT_BLOOD))
	    ob[i]->catch_msg(str);
}

/* Redefined the special attack called in the combat routine to give
 * all orcs created with this master npc maker a nice foot stomping
 * special attack, or 'stunning' move if teamed.
 * Mayhem, 11 April 1994
 */
int 
special_attack(object enemy)
{
    int     delay,npc_str = query_stat(SS_STR);
    object  me = this_object();
    mixed  *hitresult;
    string  limb, how;

    if(random(10))
	return 0;
    // If I am teamed and the enemy isn't held we hold him :)
    if (sizeof(FILTER_PRESENT_LIVE(me->query_team_others()))
      && !enemy->query_prop(LIVE_I_ATTACK_DELAY))
    {
	switch(random(4))
	{
	case 0:
	    limb = "arm";
	    break;
	case 1:
	    limb = "leg";
	    break;
	case 2:
	    limb = "head";
	    break;
	case 3:
	    limb = "body";
	    break;
	} 

	delay = 10 + random(6);
	enemy->add_attack_delay(delay, 1);
	me->add_attack_delay(delay,1);  // I am holding onto their legs!
	release_id = set_alarm(itof(delay),0.0, &release(me));
	stunned = enemy;

	me->catch_msg("You grab the "+limb+" of "+QCTNAME(enemy)+" and hold "+
	  "it as still as you can.\n");
	enemy->catch_msg(QCTNAME(me)+" grabs hold of your "+limb+" and "+
	  "hinders your movement.\n");
	tell_watcher(QCTNAME(me)+" grabs hold of "+QCTNAME(enemy)+
	  " and attempts to keep "+HIM_HER(enemy)+
	  " from moving.\n",enemy);
	return 1;
    }
    else
    {
	hitresult = enemy->hit_me(npc_str*2 + random(26), W_BLUDGEON, me, -1);

	if (hitresult[0] > 12) /* hitresult[0] yields the % hurt. */
	    how = " and it seems you've seen flapjacks thicker than your foot";
	else if (hitresult[0] > 9)
	    /* Does the hit actually hit the foot??? (or at least the legs???) */
	    how = " and you think your foot is badly broken";
	else if (hitresult[0] > 6)
	    how = " and your whole leg feels black and blue";
	else if (hitresult[0] > 4)
	    how = " and a crushing pain shoots through your foot";
	else if (hitresult[0] > 2)
	    how = " and your whole foot tingles with pain";
	else if (hitresult[0] > 0)
	    how = " and your toes feel a bit numb";
	else
	    how = " but it doesn't hurt";

	me->catch_msg("You stomp on "+capitalize(enemy->query_possessive())+
	  " foot.\n");
	enemy->catch_msg(QCTNAME(me)+" stomps on your foot"+ how +".\n");
	tell_watcher(QCTNAME(me)+" stomps on "+QTNAME(enemy)+
	  "'s foot.\n",enemy);

	if(enemy->query_hp() <= 0)
	    enemy->do_die(me);
	return 1;

    }
}

void
release(object me)
{
    if (!me)
	return;
    if (present(stunned,ENV(me)))
    {
	stunned->catch_msg(QCTNAME(me) + " releases "+HIS_HER(me)+" grip on you.\n");
	tell_watcher(QCTNAME(me) +" releases "+ HIS_HER(me) +" grip on "+
	  QTNAME(stunned)+".\n", stunned);
    }
    stunned = 0;
    remove_alarm(release_id);
    release_id = 0;
}

public void
do_die(object killer)
{
    if (release_id)
    {
	remove_alarm(release_id);
	release_id = 0;
    }
    if (objectp(stunned) && objectp(TO))
	if (present(stunned, ENV(TO)))
	    stunned->catch_msg(QCTNAME(TO)+" releases "+HIS_HER(TO)+" grip on you "+
	      "as it dies.\n");

    if (stunned)
    {
	if (stunned->query_prop(LIVE_I_ATTACK_DELAY))
	    stunned->remove_prop(LIVE_I_ATTACK_DELAY);
	stunned = 0;
    }
    ::do_die(killer);
}
