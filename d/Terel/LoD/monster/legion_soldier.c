/*
 * legion_soldier.c
 *
 * A generic legion soldier.  All legion of darkness humaniods should
 * inherit this file.

    Modified: 15 Sep 2003, by Bleys
        - These guys mocked a set of guilds that was current back
            in '95. I updated the mockery a bit.

 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

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
"The legion of darkness army is the best there is in the world.",
"The legion army will smash everything that comes in its way.",
"The legion army will soon go to war.",
"The legion will spread darkness all over the world.",
"The legion of darkness will spread the darkness of death all over the world.",
"Evil will rule in the world.",
"The legion of darkness will rule the world.",
"Killing you will be easy.",
"I'll finish you off now so you don't need to suffer anymore.",
"Ahhh! I will kill you slowly until you beg me to finish you off.",
"I hate Calian wankerettes.",
"Soon we are going to mobilize our troops!",
"@@berate_wankers",
"The stinking minstrels make me wanna throw up. Do they really think " +
"those silly ballads are going to hurt us?",
"I'm not just gonna knock you down, I'm gonna pound you right into the ground!",
"Aren't those monks just stupid? They must have hit their heads one time " +
"too many.",
"Are there rangers here? I hope not, we have better things to do than to " +
"baby-sit them.",
"I wonder where all these bats came from?",
"Hail Melkor? Send him here and we'll have bits and pieces of " +
"that poor fella hailing down all over the place.",
"I heard these guys talkin' 'bout Grandma's army. What's that?",
"Have you seen those freaking Mercenaries? They can't stop " +
"hiding behind their shields long enough to do any damage!",
"You know what kind of Pirate doesn't have a boat? The kind " +
"that wants you to walk his plank.",
"You know how to tell if somebody is a wuss? They're afraid " +
"to fight unless they're all tanked up on booze.",
"That Thornlin Militia is pretty good at keeping out of a " +
"fight, for a bunch of farmers with pitchforks.",
"You know how you can spot a Gladiator? They're the only " +
"people who run away from the same fight more than once.",
"I saw one of those Dragonarmy freaks. I'd like to see them " +
"try to ride a Terellian dragon! Ha!",
"I heard that an officer of the Red Dragonarmy rode his " +
"dragon into Terel, and Rulucaraz ate them both. Since " +
"then the Dragonarmy dragons don't come to Terel any more.",
"Secret Society? They're a bunch of halfling thieves with " +
"forked staves! What's secret about that?",
"Some elf came in here and told me he was a part of " +
"something called the Shadow Onion. Then he started " +
"throwing his weapons at me, so I killed him.",
"One of the death knights found some woman with a black " +
"robe in here. She said she was a Priestess of Takwhosis. " +
"What the hell is that?",
"Have you seen those Dragon Order titles? What a joke!",
"Look at me! I'm a Splendid Dancing Gymnast upon the Tepid Eastern " +
"Monsoons and Eminent Cardinal Who Is Above Reproach of the Grand " +
"High Dragon Kahedan Monk Order of Dragon Monks and Laypersons!",
"Blademasters, huh? The last one I saw couldn't hit a " +
"thing before he died like a stuck pig.",
"Saying that Calians can maul is like saying that bird " +
"crap flies.",
"Nice udders on that minotaur chick we saw.",
"You should see what happens when you fold a vamp up and " +
"make him bite his own ass.",
"Have you heard of that Neidar Clan? A bunch of country " +
"hick dwarves making moonshine in the hills doesn't scare " +
"me.",
"We found one of those Tricksters in here. We dumped his " +
"itching powder into his eyes before we killed him.",
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
    set_exp_factor(150);

    set_gender(MALE);
    set_alignment(-100);

    set_spell_prop(TO);

    set_act_time(30);
    add_act(({"sigh", "grin evilly"}));

    chats = query_chats();
    set_chat_time(10);
    for (i = 0; i < sizeof(chats); i++) {
        add_chat(chats[i]);
    }

    add_name("legionnaire");
    add_name("soldier");

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop("_LoD_NPC", 1);  /* Used for wielding stilettos */
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
    object wuss;
    hurt = F_PENMOD(30 + (query_stat(SS_STR) + query_stat(SS_DEX))/3,
                    30 + random(2*query_skill(SS_UNARM_COMBAT))/3);

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

    tell_watcher(QCTNAME(TO) + " rushes at " + QTNAME(enemy) + "!\n",
                 enemy, enemy);
    tell_watcher(QCTNAME(enemy) + " is " + how + ".\n", enemy, enemy);

    enemy->catch_msg(QCTNAME(me) + " rushes at you!\n");
    enemy->catch_msg("You are " + how + ".\n");

    wuss = query_smallest_enemy();
    if (wuss != query_attack())
        command("kill " + wuss->query_real_name());
    if(enemy->query_hp() <= 0)
        enemy->do_die(TO);
    set_alarm(itof(15 + random(20)), -1.0, "set_spell_prop", TO);
    return 1;
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(15 + random(20)), -1.0, "set_spell_prop", TO);
}

int
query_knight_prestige()
{
    return 35;
}
