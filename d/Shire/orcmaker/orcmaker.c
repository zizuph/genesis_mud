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
 * Sep 2004
 * Updated orcs so they don't smash feet into flapjacks (not good RP), 
 * but instead charges player.
 * - Finwe
 */
#pragma save_binary

inherit "/d/Shire/orcmaker/team";
inherit "/std/act/attack";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "/d/Shire/prestige.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define LIVE_I_KILL_ORCS  "_live_i_kill_shire_orcs"
#define NUM_TYPES 10  /* Number of types of Orcmaker orcs */
#define ORC_WEP ORCMAKER_DIR + "wep/"
#define ORC_ARM ORCMAKER_DIR + "arm/"
#define ORC_OBJ ORCMAKER_DIR + "obj/"

// Allowable types of orcs to be set with set_type when cloning
#define SLAVE      0 
#define GUARD      1
#define WARRIOR    2
#define SCOUT      3
#define WARG_RIDER 4
#define MORIA_ORC  9

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
#define MISC_OBJ ({ "kbones","bone","pebble","20bone" })

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
void mount_steed();
int  my_aggressive();
void set_orc_skills();
void arm_me();

// Global variables.
int npc_power,    /* Power level: stats, skills, strength of
		     equipment, and amount of coins depend on this */
ran_num,      /* Random number provides some variety in stats */
npc_type;     /* Type of orc created from list defined above  */
int release_id;

object stunned;  /* Plyer we stunned */
object gMount;

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
    add_prop(LIVE_I_NEVERKNOWN,1);

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

    set_intoxicated(500);
    set_aggressive(my_aggressive);
    add_prop(LIVE_I_SEE_DARK, 50 ); 

    create_orc();
}

int
my_aggressive()
{
    string race = TP->query_race();
    // Leave the poor wizards alone.
    if (TP->query_wiz_level())
	return 0;
    // Oooh bad orc killer, we have to kill this bastard
    if (TP->query_prop(LIVE_I_KILL_ORCS))
	return 1;
    // Hmmm Dinner!!
    if (race == "hobbit" || race == "elf")
	return 1;
    // Goblins are our friends
    if (race == "goblin")
	return 0;
    // So are evil folk
    if (TP->query_alignment() <= -500)
	return 0;
    // Kill the rest and let the Vala sort them out ;-)
    return 1;
}


string 
physlook()
{
    string *physlooks;

    physlooks = ({"big", "black-eyed", "black-haired", "bow-legged", 
    "broad", "dark-eyed", "dark-skinned", "dirty", "large", "long-armed", 
    "long-fanged", "long-tusked", "massive", "powerful", "reeking", 
    "short", "small", "smelly", "squat", "squinty-eyed", "strong", 
    "sturdy", "swarthy", "tall", "towering", "ugly", "yellow-eyed", 
    "yellow-tusked"});
    return physlooks[random(sizeof(physlooks))];
}

string 
alignlook()
{
    string *alignlooks;

    alignlooks = ({"angry", "barbaric", "beastly", "bloodthirsty", "brutal", 
    "cold-blooded", "cold-hearted", "cranky", "cruel", "damned", "dangerous", 
    "demonic", "deranged", "desperate", "evil", "ferocious", "fierce", 
    "foul", "grim", "grouchy", "grumpy", "insane", "mad", "malevolent", 
    "mean", "murderous", "nasty", "rabid", "raging", "ravening", "sad", 
    "savage", "sinister", "testy", "wicked", "wild", "wretched"});
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
    npc_stats[4] = initial_stat / 2; //WIS
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
    set_alarm(0.5,0.0, set_orc_skills);
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

    set_alignment(-99 - 3 * npc_stat_avg);

    if (npc_stat_avg > 50)
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

    if (spe_skill > 70)
    {
	spe_skill += ran_num2 * 3;
	if (spe_skill > 100)
	    spe_skill = 100;
    }
    else if (spe_skill < 1)
	spe_skill = 1;

    if (com_skill > 60)
    {
	com_skill = com_skill + ran_num2 * 2;
	if (com_skill > 100) 
	    com_skill = 100;
    }
    else if (com_skill < 1)
	com_skill = 1;

    if (gen_skill > 55)
    {
	gen_skill = gen_skill + ran_num2;
	if (gen_skill > 100)
	    gen_skill = 100;
    }
    else if( gen_skill < 1)
	gen_skill = 1;

    set_skill(SS_WEP_SWORD,spe_skill);
    set_skill(SS_WEP_CLUB,spe_skill);
    set_skill(SS_WEP_KNIFE,spe_skill);
    set_skill(SS_WEP_POLEARM,spe_skill);
    set_skill(SS_WEP_AXE,spe_skill);
    set_skill(SS_PARRY,com_skill);
    set_skill(SS_DEFENCE,com_skill);
    set_skill(SS_2H_COMBAT,com_skill);
    set_skill(SS_MOUNTED_COMBAT, com_skill);
    set_skill(SS_RIDING, gen_skill);
    set_skill(SS_SNEAK,gen_skill);
    set_skill(SS_HIDE,gen_skill);
    set_skill(SS_AWARENESS,MIN(55, gen_skill));
    set_skill(SS_ACROBAT,gen_skill);

    // Now that we have our skills set we arm the npc
    arm_me();
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
	FIXEUID;
    if(!random(4))
	clone_object(ORC_OBJ + ONE_OF_LIST(MISC_OBJ))->move(TO);

    set_orc_type();
}



void
mount_steed()
{
    gMount->move(ENV(TO), 1);
    TO->command("mount warg");
}

void
get_mount()
{
    setuid(); seteuid(getuid());
    gMount = clone_object(ORC_OBJ + "warg");
}

int arm_me()
{
    object wep, arm;
    int arm_num;
    FIXEUID;

    switch(npc_type)
    {
    case SLAVE:
	break;
    case GUARD:
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
    case WARRIOR:
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
    case SCOUT:
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
    case WARG_RIDER:
	switch(TO->query_average_stat())
	{
	case 1..49:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(GUARD_WEP_AVG));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(GUARD_ARM_AVG));
	    break;
	case 50..99:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(GUARD_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(GUARD_ARM_GOOD));
	    break;
	case 100..300:
	    wep=clone_object(ORC_WEP + ONE_OF_LIST(WAR_WEP_GOOD));
	    arm=clone_object(ORC_ARM + ONE_OF_LIST(WAR_ARM_GOOD));
	    break;
	}
	get_mount();
	break;
    case MORIA_ORC:
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
    if (objectp(gMount) && objectp(ENV(TO)))
    {
	mount_steed();
    }
    else
	set_alarm(1.0,0.0,mount_steed);
    command("wield all");
    command("wear all");
}

void 
set_orc_type()
{
    switch(npc_type)
    {
    case SLAVE:
	add_name("slave");
	break;
    case GUARD:
	add_name("guard");
	break;
    case WARRIOR:
	add_name("warrior");
	break;
    case SCOUT:
	add_name("scout");
	break;
    case WARG_RIDER:
	add_name("wolf_rider");
	break;
    case MORIA_ORC:
	add_name("moria_orc");
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
    case SLAVE:
	add_chat("I hate those bully boys, always giving orders and "+
	  "cracking those whips. How I'd love to strangle them "+
	  "with their damn whips.");
	break;
    case GUARD:
	add_chat("Standing around here all day is so boring.");
	add_chat("When can we go, I'm bored!");
	break;
    case WARRIOR:
	add_chat("I can't wait for the next battle!");
	add_chat("I hope we get orders soon, I want to kill!");
	break;
    case SCOUT:
	add_chat("They better not send us on any more scouting missions "+
	  "during the day, my eyes are killing me.");
	add_chat("Night missions are the most fun.");
	break;
    case WARG_RIDER:
	break;
    case MORIA_ORC:
	break;
    }
}


void 
add_extra_acts()
{
    switch(npc_type)
    {
    case SLAVE:
	add_act("emote grumbles: 'Cook dinner!' 'Dig here!' " +
	  "'Clean this up!'. Wait til they fall asleep and " +
	  "then we shall see who gets cooked and what gets buried!");
	add_act("cringe");
	add_act("moan pitif");
	add_act("emote groans in pain.");
	add_act("sniff pitif");
	break;
    case GUARD:
	add_act("snore");
	add_act("emote blinks sleep from his eyes.");
	add_act("emote stands as still as possible.");
	add_act("hiccup");
	break;
    case WARRIOR:
	add_act("shout Let me at em!");
	add_act("strut");
	add_act("emote flexes his arms intimidatingly.");
	add_act("emote grunts.");
	break;
    case SCOUT:
	add_act("emote pads around stealthily.");
	add_act("emote peers about cautiously.");
	add_act("emote shades his eyes as he peers into the distance.");
	break;
    case WARG_RIDER:
	break;
    case MORIA_ORC:
	break;
    }
}

void 
add_extra_cchats()
{
    switch(npc_type)
    {
    case SLAVE:
	add_cchat("Why do you bother with me? Go kill the masters, they "+
	  "have much treasure!");
	break;
    case GUARD:
	add_cchat("Hey you, get out of here before I hurt you!");
	add_cchat("Leave me alone, I'm busy!");
	break;
    case WARRIOR:
	add_cchat("You fool! You can't stop me!");
	add_cchat("I can break you like a dead twig, puny fool.");
	break;
    case SCOUT:
	add_cchat("You'll never kill us all!");
	add_cchat("If I wasn't stuck in this damn camp I could win "+
	  "this fight!");
    case WARG_RIDER:
	break;
    case MORIA_ORC: 
	break;
    }
}


string 
add_extra_cacts()
{
    switch(npc_type)
    {
    case SLAVE:
	add_cact("grovel");
	add_cact("scream");
	break;
    case GUARD:
	add_cact("laugh");
	add_cact("cackle");
	add_cact("shout Intruders! Intruders!");
	break;
    case WARRIOR:
	add_cact("spit");
	add_cact("emote bares his yellowed tusks.");
	add_cact("grumble");
	add_cact("shout You call this fighting?");
	break;
    case SCOUT:
	add_cact("emote tries to sneak around behind you.");
	add_cact("emote looks for an opening.");
	add_cact("emote looks for a handy escape route.");
	add_cact("smirk");
	break;
    case WARG_RIDER:
	break;
    case MORIA_ORC:
	break;
    }
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

    if (random(5))
	return 0;
    if (objectp(gMount) && gMount == me->query_prop(LIVE_O_STEED))
    {
	hitresult = enemy->hit_me(npc_str * 2 + me->query_skill(SS_MOUNTED_COMBAT) +
	  random(31), W_SLASH, me, -1);
	switch(hitresult[0])
	{
	case -1:
	case 0:
	    how = "unharmed";
	    break;
	case 1..5:
	    how = "a little hurt";
	    break;
	case 6..10:
	    how = "slightly hurt";
	    break;
	case 11..25:
	    how = "somewhat hurt";
	    break;
	case 26..40:
	    how = "injured";
	    break;
	default:
	    how = "badly wounded";
	    break;
	}
	// The attack stuns the enemy for 1 combat round
	enemy->add_attack_delay(5);
	// Send no msg to the npc
	enemy->catch_tell("The "+me->query_nonmet_name()+"'s "+
	  gMount->query_nonmet_name() + " jumps at you knocking you to the "+
	  (ENV(enemy)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
	  " stunning you briefly.  Then suddenly the "+me->query_race_name()+
	  (sizeof(me->query_weapon(-1)) ? " hacks wildy at your prone body "+
	    "with his "+query_weapon(-1)[0]->short() : "'s "+
	    gMount->query_race_name()+" mauls you with it's razor-sharp, "+
	    "tooth-filled maw ")+ " leaving you feeling "+how+
	  " from the attack.\n");
	me->tell_watcher(QCTNAME(me)+"'s "+QTNAME(gMount)+" jumps at "+
	  QTNAME(enemy)+" knocking "+HIM_HER(enemy)+" to the "+
	  (ENV(enemy)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
	  " stunning "+HIM_HER(enemy)+" briefly.  Then suddenly the "+
	  me->query_race_name()+ ((sizeof(query_weapon(-1))) ?
	    " hacks wildly at "+QTNAME(enemy)+"'s prone body with his "+
	    query_weapon(-1)[0]->short() : "'s "+gMount->query_race_name()+
	    " mauls "+QTNAME(enemy)+" with it's razor_sharp, tooth-filled maw")+
	  "leaving "+QTNAME(enemy)+" feeling "+how+" from the attack.\n", enemy);

	return 1;
    }
    // If I am teamed and the enemy isn't held we hold him :)
    if (sizeof(filter(me->query_team_others(), &operator(==)(environment(me)) @
	  environment)) && !enemy->query_prop(LIVE_I_STUNNED))
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

	delay = 10 + random(6);  // 2-3 combat rounds.
	enemy->add_stun();
	me->add_stun();  // I am holding onto their legs!
	release_id = set_alarm(itof(delay),0.0, &release(me));
	stunned = enemy;

	// Send no msgs to the npc
	enemy->catch_msg(QCTNAME(me)+" grabs hold of your "+limb+" and "+
	  "hinders your movement.\n");
	me->tell_watcher(QCTNAME(me)+" grabs hold of "+QCTNAME(enemy)+
	  " and attempts to keep "+HIM_HER(enemy)+
	  " from moving.\n",enemy);
	return 1;
    }
    else
    {
	hitresult = enemy->hit_me(npc_str*2 + random(26), W_BLUDGEON, me, -1);

	if (hitresult[0] > 12) /* hitresult[0] yields the % hurt. */
	    how = "with fists swinging, and pounds you terribly";
	else if (hitresult[0] > 9)
	    how = "with fists swinging, and beats you hard";
	else if (hitresult[0] > 6)
	    how = "and hugs you you tightly. You hear bones snap";
	else if (hitresult[0] > 4)
	    how = "and hugs you tightly, cracking bones";
	else if (hitresult[0] > 2)
	    how = "headlong and hurts you slightly";
	else if (hitresult[0] > 0)
	    how = "headlong and pushes you back slightly";
	else
	    how = "headlong and bounces off you";

	// Send no msgs to the npc
	enemy->catch_msg(QCTNAME(me)+" charges you "+ how +".\n");
	me->tell_watcher(QCTNAME(me)+" charges "+QTNAME(enemy) + ".\n",enemy);

	if(enemy->query_hp() <= 0)
	    enemy->do_die(me);
	return 1;

    }
}

void
release(object me)
{
    if (!stunned)
	return;

    stunned->remove_stun();
    if (!me)
	return;
    me->remove_stun();
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
    if (!TO->query_hp() <= 0)
	return;
    if (release_id)
    {
	remove_alarm(release_id);
	release_id = 0;
    }
    if (objectp(gMount))
	gMount->notify_rider_killed(killer);
    if (objectp(stunned) && objectp(TO))
	if (present(stunned, ENV(TO)))
	    stunned->catch_msg(QCTNAME(TO)+" releases "+HIS_HER(TO)+" grip on you "+
	      "as it dies.\n");

    if (stunned)
    {
	if (stunned->query_prop(LIVE_I_STUNNED))
	    stunned->remove_stun();
	stunned = 0;
    }
    killer->add_prop(LIVE_I_KILL_ORCS, 1);
    return ::do_die(killer);
}
