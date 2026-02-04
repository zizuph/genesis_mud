/*
 * std_goblin_grd.c
 * Goblin Warrior for mountains/goblincave
 * Tomas -- Nov. 1999
 *
 * Modified June 2008 by Lilith
 * Experimenting with scalable npcs
 *
 * Modified Aug 2008
 *  Tweaked healing and native armour
 *  Updated logging to log healing
 *
 * Aug 24, 2008 Lilith
 *  Updated the logging of heals and the frequency
 *
 * Dec 27, 2008 Cotillion
 *  Added skill for all weapon types.
 *
 * May 2009 Petros
 *  Removed scalability from goblins, added different random levels
 *  Removed resistances
 *  Base special attacks on stat_based_specials in /d/Genesis/specials
 *  Removed money as treasure. EQ is enough.
 *  Reduced special hit percentage, reduced heal percentage, upped
 *    exp_factor to 115 based on hard hitting specials.
 *  Added up to 7 levels of possible goblins
 *
 * September 2009 Petros
 *   Changed random type generation scheme to generate the least available
 *   type always. This allows for more even distribution throughout
 *   Armageddon.
 *
 * Jan 2021 Lucius
 *   Cleaned up and modernized.
 *   Add auto-teaming with other cave goblins.
 *
 */
#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define ARM_DIR  (MOUNTAIN_DIR + "goblincave/armour/")
#define WEP_DIR  (MOUNTAIN_DIR + "goblincave/weapon/")

#define KILL_FILE  (MOUNTAIN_DIR + "goblincave/log/gob_deaths")
#define HEAL_FILE  (MOUNTAIN_DIR + "goblincave/log/gob_heals")

// Global Variables
public int alarm_id = 0;
public int Strength = 0;

private string *adjs = ({
    "black-haired","bald","muscular", "massive",
    "thick-armed","scarred","green-haired", "silver-haired",
    "red-haired", "pock-marked", "wiry", "angry",
    "blue-skinned", "black-eyed", "brown-skinned",
    "red-eyed","red-skinned","purple-skinned",
    "tanned","dark-skinned","light-skinned","grey-eyed"
});

// Define the different guard types
#define GOBLIN_FEEBLE    0
#define GOBLIN_WEAK      1
#define GOBLIN_STRONG    2
#define GOBLIN_FOUL      3
#define GOBLIN_POWERFUL  4
#define GOBLIN_HEINOUS   5
#define GOBLIN_NEFARIOUS 6

/*
 * Function:    set_goblin_strength
 * Description: Called inside of setup_random_goblin, it indicates
 *              which goblin type this is.
 */
public void
set_goblin_strength(int strength)
{
    Strength = strength;
}

/*
 * Function:    get_goblin_strength
 * Description: Returns the value set during the random generation.
 */
public int
get_goblin_strength()
{
    return Strength;
}

/*
 * Function:    setup_random_goblin
 * Description: This function randomly selects a type of goblin
 *              to create. They range from 100-200 stat at 25
 *              stat intervals. They will get a special adjective
 *              to help mortals identify which ones they want to
 *              fight.
 */
public void
setup_random_goblin()
{
    int base_stat;
    int goblin_type;

    // The random generation type will take all the existing goblins
    // and try to do an equal distribution.
    object * instances = object_clones(find_object(MASTER));
    if (!sizeof(instances))
    {
	goblin_type = random(7);
    }
    else
    {
	int *counts = ({ 0, 0, 0, 0, 0, 0, 0 });
	foreach (object instance : instances)
	{
	    int strength = instance->get_goblin_strength();
	    ++counts[strength];
	}
	int mincount = applyv(min, counts);
	goblin_type = max(0, member_array(mincount, counts));
    }
    // Set the strength so that it can be looked up later.
    set_goblin_strength(goblin_type);

    switch (goblin_type)
    {
    case GOBLIN_FEEBLE:
	add_adj("feeble");
	break;

    case GOBLIN_WEAK:
	add_adj("weak");
	break;

    case GOBLIN_STRONG:
	add_adj("strong");
	break;

    case GOBLIN_FOUL:
	add_adj("foul");
	break;

    case GOBLIN_POWERFUL:
	add_adj("powerful");
	break;

    case GOBLIN_HEINOUS:
	add_adj("heinous");
	break;

    case GOBLIN_NEFARIOUS:
	add_adj("nefarious");
	break;
    }

    set_short(0);

    // Set up the actual stats
    base_stat = 50 + (goblin_type * 25) + random(25);
    default_config_npc(base_stat);
}

void
create_terel_monster()
{
    set_name("warrior");
    add_name("_terel_cave_goblin");

    set_race_name("goblin");
    set_adj(one_of_list(adjs));
    setup_random_goblin();
    set_long("A goblin warrior of the black feather tribe.\n");

    // Set up the skills after the avg stat has been set
    int avg_stat = query_average_stat();
    set_skill(SS_WEP_SWORD, query_skill_by_stat(avg_stat));
    set_skill(SS_WEP_AXE, query_skill_by_stat(avg_stat));
    set_skill(SS_WEP_CLUB, query_skill_by_stat(avg_stat));
    set_skill(SS_WEP_POLEARM, query_skill_by_stat(avg_stat));
    set_skill(SS_DEFENCE, query_skill_by_stat(avg_stat));
    set_skill(SS_PARRY, query_skill_by_stat(avg_stat));
    set_skill(SS_AWARENESS, query_skill_by_stat(avg_stat));
    set_skill(SS_2H_COMBAT, query_skill_by_stat(avg_stat));

    set_all_hitloc_unarmed(40);
    set_alignment(-500 - random(200));
    set_gender(MALE);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_UNARMED, 1);
    set_exp_factor(115); // based on healing and special attacks

    set_act_time(5 + random(20));
    add_act("emote grunts.");
    add_act("emote puts a finger to "+ query_possessive() +
        " nose and blows.");
    add_act("rsay What you want!");
    add_act("glare");
    add_act("rsay You go now!");
    add_act("fart");
    add_act("glare confident");
    add_act("rsay Black Feather tribe is strong!");
    add_act("rsay Grow tired of waiting for ice to break. " +
      "Black Feather should strike ugly stupid huuman now!");
}

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    string * equip_list = ({
        ARM_DIR + "chainmail",
        ARM_DIR + "skullcap",
        ARM_DIR + "furs",
        ARM_DIR + "boots"
    });

    switch(random(3))
    {
    case 0:
	equip_list += ({ WEP_DIR + "goblinsword",
                         WEP_DIR + "goblinaxe" });
	break;

    case 1:
	equip_list += ({ WEP_DIR + "goblinspear" });
	break;

    case 2:
	equip_list += ({ WEP_DIR + "goblinclub" });
	break;
    }

    return equip_list;
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield all");
    TO->command("wear all");
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    object *arr = (object *)query_team_others();
    for (int i = 0; i < sizeof(arr); i++)
	arr[i]->notify_ob_attacked_me(this_object(), ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    set_alarmv(1.0, -1.0, "help_friend", ({ attacker }));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
	command("kill " + OB_NAME(ob));
}

int
benice(object victim)
{
    /* Lets not attack our kind */
    if (victim->query_race_name() == "goblin")
	return 0;

    /* Lets try to stop resets in combat. */
    if (this_object()->query_hp() < this_object()->query_max_hp())
	return 0;

    set_alarm(itof(random(1) + 1), 0.0,
        &command("emote shouts a warcry!"));
    command("kill "+ OB_NAME(victim));
    return 1;

}

/* When I run into a living, this func is called */
void
init_living()
{
    ::init_living();

    /* If the living is a player and I can see him ... */
    if (query_interactive(TP) && CAN_SEE(TO, TP))
    {
	/* Only one person, so as not to spam a team */
	if (!get_alarm(alarm_id))
            alarm_id = set_alarm(1.0, 0.0, &benice(TP));
    }

    if (TP->id("_terel_cave_goblin"))
    {
        team_join(TP);
        TP->set_leader(TO);
    }
}

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 * Most of these specials are from the ~Avenir/inherit/sybarite.c
 */
int
special_attack(object victim)
{
    mixed *hitresult;
    string how, hdesc;
    int avg_stat;

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
	TO->stop_fight(victim);
	return 1;
    }

    if (random(5))
    {   // 20% chance of a normal attack.
	return 0;
    }

    if (!(hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON)))
    {   // Could not attack the target, or they evaded.
	return 1;
    }

    if (!strlen(hitresult[1]))
    {   // Handle misses.
	tell_watcher(QCTNAME(TO) + " tries to claw " + QTNAME(victim)
	  + " but misses completely.\n", victim);
	victim->catch_msg(QCTNAME(TO) + " tries to claw you but misses "
	  + "completely!\n");
	return 1;
    }

    how = "unharmed";
    if (hitresult[0] > 0)
	how = "slightly hurt";
    if (hitresult[0] > 20)
	how = "rather hurt";
    if (hitresult[0] > 50)
	how = "crushed";
    if (hitresult[0] > 100)
	how = "devastated";

    hdesc = hitresult[1];
    tell_watcher(QCTNAME(TO) + " claws " + QTNAME(victim) +
        " on the " + hdesc + ".\n", victim);
    victim->catch_msg(QCTNAME(TO) + " claws you on the " + hdesc + "!\n");
    victim->catch_msg("You feel " + how + ".\n");

    /* Lets heal me to draw out the fight.
     * Since it goes off every 5 seconds make it a bit random.
     */
    if (!random(3)) /* heal with 33% chance */
    {
	int heal = (query_max_hp() / 30);
	TO->heal_hp(heal);
	write_file(HEAL_FILE, ctime(time())+" "+ TO->query_name() +
            "("+ TO->query_average_stat() +")"+
            " healed "+ heal +" points.\n");
    }

    // Special already hit. We shouldn't hit again.
    return 1;
}
