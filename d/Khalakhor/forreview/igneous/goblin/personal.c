/* 
 *   Goblin Personality modual
 *
 *   This file contains all the functions for a goblins
 *   personality.  The chats, acts, emote_hooks etc...
 *
 *   Created by Igneous@Genesis, aka Chad Richardson
 *   July 1998
 */
  
inherit "/cmd/std/command_driver";

#include "goblin.h"
#include "/d/Khalakhor/sys/defs.h"

//  Global Vars
static string eyes, hair;

public string
query_eyes()
{
    return eyes;
}

public string
query_hair()
{
    return hair;
}

public void
configure_personality(int type)
{
    string adj1, adj2;

    adj1 = "dirty";
    adj2 = "stinking";
    hair = ONE_OF(({"dirty", "jet", "wild,", "unkept,", "ragged,"})) 
    + " black coloured hair";
    eyes = ONE_OF(({"smokey", "pitch", "glittering", "dead", "abysmal"}))
    + " black coloured eyes";

    TO->set_adj(({adj1, adj2}));
    TO->set_long("This "+adj1+" "+adj2+" creature is known as a goblin.\n" +
      capitalize(HE_SHE(TO)) + " has "+eyes+".\n" +
      capitalize(HE_SHE(TO)) + " has "+hair+".\n");
}

/* Abverb Functions below */

public string
agressive_adverb()
{
    return ONE_OF(({"agressively", "alertly", "angryly", "annoyedly", 
	"arrogantly", "barely", "bitterly", "bloodthurstily", "bravely",
	"confidently", "crazily","courageously", "dangerously", "defiantly",
	"delightedly", "determinedly", "disdainfully", "dutifully"})); 
}

public string
happy_adverb()
{
    return ONE_OF(({"adoringly", "affectionately",  "brightly", "charmingly",
	"cheerfully", "compassionately", "coyly", "delightfully", "descreetly", 
	"dreamily", "drunkenly"}));
}

public string
upset_adverb()
{
    return ONE_OF(({"angryly", "annoyedly", "bitterly", "briefly", "coldly", 
	"contemptuously", "cynically", "dangerously", "demonically", 
	"devilishly", "diabolically",  "disappointedly", "disgustedly", 
	"dryly"}));
}

/* Some helpful filters */

public object *
get_my_friends()
{
    return filter(all_inventory(ENV(TO))-({TO}), &->query_khalakhor_goblin());
}

public object
get_one_friend()
{
    object *ob = get_my_friends();

    if (!sizeof(ob))
	return 0;

    return ONE_OF(ob);
}

public object *
get_present_enemies()
{   
    return filter(TO->query_enemy(-1), &operator(==)(ENV(TO)) @ environment);
}

public object
get_random_player()
{
    object *ob;

    ob = filter(filter(all_inventory(ENV(TO)), interactive), &->check_seen(TO));
    if (!sizeof(ob))
	return 0;

    return ONE_OF(ob);
}

public object
get_random_enemy()
{
    object *ob = get_present_enemies();

    if (!sizeof(ob))
	return 0;

    return ONE_OF(ob);
}

/* Actual personality functions, chats, acts emote hooks etc.. */
