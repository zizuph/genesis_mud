/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * legion_soldier.c
 *
 * A generic legion soldier.  All legion of darkness humaniods should
 * inherit this file.
 */

#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/sorgum/monster";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <money.h>

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    string *chats =
	({
"The legion of darkness army is the best there is in the world",
"The legion army will smash everything that comes in its way.",
"The legion army will soon go to war.",
"The legion will spread darkness all over the world.",
"The legion of darkness will spread the darkness of death all over the world.",
"Evil will rule in the world.",
"The legion of darkness will rule the world.",
"killing you will be easy",
"I'll finish you off now so you don't need to suffer anymore.",
"Ahhh! I will kill you slowly until you beg me to finish you off.",
"I hate Calian wankerettes.",
"Soon we are going to mobilize our troops!",
"@@berate_wankers",
"I'm not just gonna knock you down, I'm gonna pound you right into the ground!"
    
});
    
    return chats;
    
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    int i;
    string *chats;
    
    ::create_monster();

    set_living_name("freak");
    set_gender(MALE);
    set_alignment(-100);

    set_spell_prop(TO);
   
    set_act_time(30);
    add_act(({"sigh","grin"}));

    chats = query_chats();
    set_chat_time(10);
    for (i = 0; i < sizeof(chats); i++) {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }
    enable_intro();
}

/*
 * Function name: spell_attack
 * Description:   This is called by the combat system.
 * Arguments:     me -    This object
 *                enemy - The enemy we are fighting.
 */
public int
spell_attack(object me, object enemy)
{
    mixed *hitresult;
    string how;
    int hurt;
    int damage;
    mixed wuss;

    hurt = F_PENMOD(30 + (query_stat(SS_STR) + query_stat(SS_DEX)) / 3,
		    35 + random(query_skill(SS_UNARM_COMBAT)));
    
    hitresult = enemy->hit_me(hurt, W_BLUDGEON, TO, -1);

    how = "unharmed";
    
    if (hitresult[0] > 0)
	how = "hit hard";

    if (hitresult[0] > 10)
	how = "hit with a crushing blow";

    if (hitresult[0] > 25)
	how = "slammed brutally";

    if (hitresult[0] > 40)
	how = "beat senseless";

    if (hitresult[0] > 60)
	how = "pummeled viciously";

    if (hitresult[0] > 100)
	how = "pounded into oblivion";

    tell_watcher(QCTNAME(TO) + " rushes at " + QCTNAME(enemy) + "!\n",
		 enemy, enemy);
    tell_watcher(QCTNAME(enemy) + " is " + how + ".\n", enemy, enemy);

    enemy->catch_msg(QCTNAME(me) + " rushes at you!\n");
    enemy->catch_msg("You are " + how + ".\n");
    
    wuss = query_smallest_enemy();
    attack_object(wuss);

    set_alarm(itof(10 + random(20)), -1.0, "set_spell_prop", TO);    
    return 1;
}
