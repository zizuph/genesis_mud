/* Originally: A witch. Mortricia 920720  - around the end of 19th ceuntry.*/
/* Recoded by Udana 03/2006 */
/*
 * Lucius, 2021-03: Silently remove the quest ring instead of dropping it.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#include "../include/defs.h"
#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

public void arm_me();
public void right_msg(object me, object ob);
public void right_msg2(object me);

public void create_terel_monster()
{
    set_name("regata");
    add_name("hag");
    add_name("witch");
    set_living_name("regata");
    set_short("crooked old hag");
    set_long("Humped and twisted, women standing before you, looks like she's 100 years old "+
      "at least. Long, clawlike fingers, hooked nose, wrinkled hideous face - all fits the "+
      "description of what you've been scared with as a child.\n");
    set_adj(({"crooked", "old"}));
    set_race_name("human");
    set_gender(1);

    set_stats(({100,100,100,100,100,100}));
    set_alignment(random(50) - 300);
    set_skill(SS_DEFENCE, random(10) + 25);
    set_skill(SS_AWARENESS, random(10) + 25);
    set_skill(SS_WEP_KNIFE, random(10) + 30);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    enable_intro();

    set_act_time(10);
    add_act(({"spit", "cough", "sniff"}));

    set_chat_time(5);
    add_chat("Woe betide you!");
    add_chat("You don't angree old Regata, or ye'll be a to toady.");
    add_chat("Hav you seen a bracelet, a rings of mine, booby?");
    add_chat("Regata's making stews, deliciousss stew needs, some "+
      "guano, some flying mouse droppings. For the flavors.");
    add_chat("Ye be good booby, you bring that here, oi?");
    add_ask(({"task", "quest"}), "@@give_quest");

    set_hp(query_max_hp());
    set_mana(query_max_mana());
    arm_me();
}

string give_quest()
{
    if(!TP->test_bit("Terel", QUEST_JJ5_GROUP, QUEST_JJ5_BIT))
	return "Bring Regata some flyingmousess droppings, will ye booby?\n";
    if(!TP->test_bit("Terel", QUEST_WIT_GROUP, QUEST_WIT_BIT))
	return "She lost a finger bracelet, a ring Regata grunny gave her, "+
	"she needs that back, oi?\n";
    if(!TP->test_bit("Terel", QUEST_CRYPT_GROUP, QUEST_CRYPT_BIT))
    {
	set_alarm(1.0, 0.0, &command("say Cesar, the kitty will help ye."));
	return "Oh booby, he helps Regata a lot, bandits helps her not, "+
	"ungreatful halflingses. Ye knock their stone, ye utter their secret word.\n";
    }
    return "Don't ye interrupt Regata, or ye might find your eyes in her stew, oi booby?\n";
}

public void arm_me()
{
    FIX_EUID;

    clone_object(HAG + "cloak")->move(TO);
    clone_object(HAG + "hat")->move(TO);
    clone_object(HAG + "knife")->move(TO);
    command("wear armours");
    command("wield knife");
}

public void
close_shut()
{
    command("close door");
    command("lock door with key");
}

public void wrong_msg()
{
    command("ponder");
    command("say What you bring to old Regata booby, useless, shiny, "+
      "give it to a young lass, oi?");
    command("drop ring");
}

public void wrong_msg2()
{
    command("ponder");
    command("say Is too old, is too stale, no good for ol' Regata stews booby!");
    command("drop batguano");
}

public void enter_inv(object ob, object from)
{
    if(ob->id("batguano"))
    {
	if (ob->query_prop("_shit_picker") == TP->query_name())
	{
	    ob->remove_prop("_shit_picker");
	    set_alarm(2.0, -1.0, &right_msg2(TP));
	    ob->remove_object();
	}
	else
	    set_alarm(2.0, -1.0, wrong_msg2);
    }
    if(ob->id("ring"))
    {
	if (ob->query_prop("_skull_finder") == TP->query_name())
	{
	    ob->remove_prop("_skull_finder");
	    set_alarm(2.0, -1.0, &right_msg(TP, ob));
	}
	else
	    set_alarm(2.0, -1.0, wrong_msg);
    }
    if(!ob->id("_regata_eq"))
	/* Quest items will be removed by then anyway. */
	set_alarm(3.0, 0.0, &command("drop " + ob->query_name()));
}

public void
right_msg(object me, object ob)
{
    string name;

    if (!me || ETO != environment(me))
        return;

    name = me->query_real_name();
    command("wear ring");
    command("smile " + name);
    if (me -> test_bit("Terel", QUEST_WIT_GROUP, QUEST_WIT_BIT)) {
	tell_object(me, "Ye bring no more jewels, oi? " +
	  "One you brot was great enough, wousn't it booby?\n");
    } else {
	me->add_exp_quest(QUEST_WIT_EXP);
	me->set_bit(QUEST_WIT_GROUP, QUEST_WIT_BIT);
	me->catch_tell("You suddenly feel more experienced.\n");
	tell_room(ETO, QCTNAME(me) +
	  " has become more experienced.\n", me);
	seteuid(getuid());
	write_file(QUEST_LOG, capitalize(name) +
	  " solved the witch quest (" + ctime(time()) + ")\n");
    }
    /* Make way for new rings from other players, but do it silently */
    ob->remove_broken(1);
    ob->remove_object();
}

public void
right_msg2(object me)
{
    string name;

    if (!me || ETO != environment(me)) return;

    name = me->query_real_name();
    command("smile " + name);
    if (me->test_bit("Terel", QUEST_JJ5_GROUP, QUEST_JJ5_BIT)) {
	tell_object(me, "Nu, shuh! Regats needs no more of those, " +
	  "ye wonna help, you be quicker, oi?");
    } else {
	if (me->query_exp() <= QUEST_JJ5_EXP ) {
	    me->add_exp_quest(me->query_exp());
	} else {
	    me->add_exp_quest(QUEST_JJ5_EXP);
	}
	me->set_bit(QUEST_JJ5_GROUP, QUEST_JJ5_BIT);
	me->catch_msg("You get a tingly feeling, things seems more " +
	  "clear now.\n");
	tell_room(ETO, QCTNAME(me) +
	  " looks more experienced.\n", me);
	seteuid(getuid());
	write_file(QUEST_LOG, name +
	  " solved the batshit quest (" + ctime(time()) + ")\n");
    }
}

void notify_attacked()
{
    command("say Ye has no place here! Nu, ghosts are calling ye booby, Regata hear em, she pleases them!");
    tell_room(E(TO), "Which suddenly grows, her face starts to change, her fingernails grows into beastial claws!\n");
    tell_room(E(TO), "As she utters some arcane words, you notice her robes moving, like if they were filled with "+
      "insects.\n");
}

public void attacked_by(object attacker)
{
    ::attacked_by(attacker);
    set_alarm(0.5, 0.0, &notify_attacked());
}

varargs public mixed hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc)
{
    object victim;
    if(random(5))
    {
	if(sizeof(attacker->query_team_others()))
	    victim = attacker->query_team_others()[random(sizeof(attacker->query_team_others()))];
	else
	    victim = TO;
	attacker->catch_msg("You feel no resistance as you hit the dark robes, suddenly, you feel "+
	  "a horrible pain in your chest.\n");
	tell_room(E(TO), QCTNAME(attacker) + " suddenly winces in pain.\n", attacker);
	return attacker->hit_me(wcpen, dt, victim, -1, target_hitloc);
    }
    return (::hit_me(wcpen, dt, attacker, attack_id, A_HEAD));
}
