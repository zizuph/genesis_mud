#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include "goblin.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/d/Khalakhor/std/npc/goblin";
inherit (GOBLIN_PATH + "personal");
inherit (GOBLIN_PATH + "special");

// Global Vars
static int Goblin_type, Goblin_power;

public void create_goblin() {}

nomask void
create_khalakhor_goblin()
{
    set_name("goblin");
    set_long("For some reason this poor goblin hasn't been "+
      "configured right, please leave a bug report.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Yes we are an aggressive creature!!
    set_aggressive(1);

    create_goblin();
}

public void
arm_goblin()
{
    setuid(); seteuid(getuid());
    if (Goblin_type == WOLF_RIDER)
    {
	// A safety check.
	if (ENV(TO))
	{
	    clone_object(WOLF)->move_living("void", ENV(TO));
	    command("mount wolf");
	}
    }
    command("wield all");
    command("wear all");
}

public void
set_up_goblin()
{
    int attack_skills, defensive_skills, general_skills, *stats, i;

    if (!Goblin_power || !Goblin_type)
	return;
    // Okay configure the goblin personality based on goblin type
    configure_personality(Goblin_type);

    // Set up the goblins stats here and alter them somewhat to 
    // reflect goblinoid nature.
    stats = allocate(6);
    stats[0] = Goblin_power * 130 / 100;  // SS_STR
    stats[1] = Goblin_power * 110 / 100;  // SS_DEX
    stats[2] = Goblin_power * 140 / 100;  // SS_CON
    stats[3] = Goblin_power * 50 / 100;   // SS_INT
    stats[4] = Goblin_power * 60 / 100;   // SS_WIS
    stats[5] = Goblin_power * 110 / 100;  // SS_DIS
    i = -1;
    while(++i < sizeof(stats))
	set_base_stat(i, stats[i]);

    // Make sure the npc has full health and mana, etc..
    refresh_living();
    // Set up the values we want to use for skills based off the npcs stats.
    attack_skills =    ((stats[0] + stats[1]) / 2) * 40 / 100;
    defensive_skills = ((stats[1] + stats[3]) / 2) * 50 / 100;
    general_skills =   ((stats[1] + stats[4]) / 2) * 45 / 100;

    // Certain goblins are better skilled at certain things.    
    switch (Goblin_type)
    {
    case SCOUT:
	general_skills = 3 * general_skills / 2;
	break;
    case GUARD:
	attack_skills = attack_skills * 110 / 100;
	defensive_skills = 5 * general_skills / 3;
	break;
    case WARRIOR:
	attack_skills = 3 * general_skills / 2;
	defensive_skills = defensive_skills * 120 / 100;
	general_skills = general_skills * 60 /  100;
	break;
    case WOLF_RIDER:
	attack_skills = attack_skills * 120 / 100;;
	general_skills = 3 * general_skills / 2;
	break;
    case BERSERKER:
	attack_skills = 2 * attack_skills;
	defensive_skills = 2 * defensive_skills / 3;
	general_skills = MIN(20, general_skills);
	break;
    case CHIEFTAIN:
	attack_skills = 3 * attack_skills / 2;
	defensive_skills = 3 * defensive_skills / 2;
	general_skills = general_skills * 120 / 100;
	break;
    }

    // Some skill sanity checks.
    attack_skills = MIN(85, MAX(30, attack_skills));
    defensive_skills = MIN(75, MAX(35, defensive_skills));
    general_skills = MIN(70, MAX(20, general_skills));

    set_skill(SS_WEP_SWORD, attack_skills + 10);
    set_skill(SS_WEP_POLEARM, attack_skills - 5);
    set_skill(SS_WEP_AXE, attack_skills);
    set_skill(SS_WEP_KNIFE, attack_skills + 5);
    set_skill(SS_WEP_CLUB, attack_skills);

    set_skill(SS_BLIND_COMBAT, defensive_skills - 10);
    set_skill(SS_2H_COMBAT,    defensive_skills -  5);
    set_skill(SS_PARRY, defensive_skills - 5);
    set_skill(SS_DEFENCE, defensive_skills + 10);

    set_skill(SS_SNEAK, general_skills);
    set_skill(SS_HIDE, general_skills + 10);
    set_skill(SS_AWARENESS, general_skills + 5);
    set_skill(SS_FR_TRAP, general_skills + 5);
    set_skill(SS_ACROBAT, general_skills);
    set_skill(SS_SWIM, general_skills - 10);
    set_skill(SS_CLIMB, general_skills + 15);
    set_skill(SS_LOC_SENSE, general_skills - 5);
    set_skill(SS_TRACKING, general_skills + 10);
    set_skill(SS_HUNTING, general_skills + 15);

    // Some goblins are skilled in certain skills others are not.
    // Or we want to set Goblin type specific bonuses.
    // And add a specific name to the goblin on their type
    switch (Goblin_type)
    {
    case CITIZEN:
	add_name("citizen");
	break;
    case SCOUT:
	add_name("scout");
	set_skill(SS_AWARENESS, MIN(90, query_skill(SS_AWARENESS) + 20));
	break;
    case GUARD:
	add_name("guard");
	break;
    case WARRIOR:
	add_name("warrior");
	break;
    case WOLF_RIDER:
	add_name("rider");
	set_skill(SS_MOUNTED_COMBAT, defensive_skills + 20);
	set_skill(SS_RIDING, general_skills + 30);   
	set_skill(SS_ANI_HANDL, general_skills + 20);
	break;
    case BERSERKER:
	add_name("berserker");
	set_skill(SS_WEP_AXE, MIN(100, query_skill(SS_WEP_AXE) + 20));
	set_skill(SS_WEP_CLUB, MIN(100, query_skill(SS_WEP_CLUB) + 20));
	set_skill(SS_BLIND_COMBAT,MIN(100,query_skill(SS_BLIND_COMBAT)+35));
	set_skill(SS_2H_COMBAT, MIN(100, query_skill(SS_2H_COMBAT) + 30));
	break;
    case CHIEFTAIN:
	add_name(({"chief", "chieftain"}));
	break;
    }
    // if we have an environment arm ourselves, if we don't arm with a delay
    if (environment(this_object()))
	arm_goblin();
    else
	set_alarm(1.0, 0.0, arm_goblin);
}

public void
set_type(int type)
{
    if (type < CITIZEN || type > CHIEFTAIN)
	type = CITIZEN;
    Goblin_type = type;
    set_up_goblin();
}

public void
set_average_stat(int stat)
{
    // Wow a stat average less than 10 is a bit low.
    if (stat < 10)
	stat = 10;
    // A stat average greater than 120 is too good for a std npc
    if (stat > 120)
	stat = 120;
    Goblin_power = stat;
    set_up_goblin();    
}

public int
query_goblin_type()
{
    return Goblin_type;
}

public int
query_goblin_power()
{
    return Goblin_power;
}

public int
query_khalakhor_goblin()
{
    return 1;
}

/* Teaming and Combat Special realated Functions Below */
void
help_me(object ob)
{
    /*
	if (objectp(query_attack()) || attack_id)
	    return;
    */
    /* Add an alarm to the assisting fucntion here */
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    /* if they attack us they are branded a goblin killer! */
    if (!attacker->query_prop(GOBLIN_KILLER))
	attacker->add_prop(GOBLIN_KILLER, 1);
    get_my_friends()->help_me(attacker);
}

void
attack_object(object victim)
{
    ::attack_object(victim);
    get_my_friends()->help_me(victim);
}

void
do_die(object killer)
{
    if (query_hp() > 0)
	return;

    killer->add_prop(GOBLIN_KILLER, killer->query_prop(GOBLIN_KILLER) + 1);
    return ::do_die(killer);
}

//  All the special attack functions are inherited from another file.
int
special_attack(object enemy)
{
    object *friends, *enemies;
    int res;

    friends = get_my_friends();
    enemies = get_present_enemies();

    if (random(2))
	check_status(TO, friends, enemies, Goblin_type);

    if (random(8))
	return 0;

    enemies = enemies - ({enemy});
    switch (Goblin_type)
    {
    case CITIZEN:
    case SCOUT:
	if (sizeof(friends))
	{
	    res = shove_attack(TO, enemy, friends);
	    if (!res)
		res = pummel(TO, enemy, friends);
	}
	break;
    case GUARD:
    case WARRIOR:
	if (sizeof(friends))
	    res = shove_attack(TO, enemy, friends);
	if (!res)
	    res = hack(TO, enemy);
    case WOLF_RIDER:
	if (objectp(query_prop(LIVE_O_STEED)))
	    res = wolf_attack(TO, enemy, query_prop(LIVE_O_STEED));
	if (!res && sizeof(friends))
	    res = shove_attack(TO, enemy, friends);
	if (!res)
	    res = hack(TO, enemy);
	break;
    case BERSERKER:
	if (sizeof(enemies))
	    res = hack_many(TO, enemies + ({enemy}));
	else
	    res = hack(TO, enemy);
	if (!res && sizeof(friends))
	    res = shove_attack(TO, enemy, friends);
	break;
    case CHIEFTAIN:
	if (sizeof(enemies) && sizeof(friends))
	    res = ordered_attack(TO, enemies + ({enemy}), friends);
	if (!res && sizeof(friends))
	    res = surround(TO, enemy, friends);
	if (!res)
	    res = hack(TO, enemy);
	break;
    }
    // Do an unarmed attack if no previous attack worked
    if (!res)
	res = punch(TO, enemy);

    return res;
}
