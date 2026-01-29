//              The Punisher (/bazaar/NPCS/punisher.c)
// creator(s):  Tepisch  August 1994
// last update: May 4 - Made cosmetic/debug changes to make him a 
//                      bit more colourful.
//              Cirion, Feb'96: update for reward_quest function.
//		Denis, Aug'96: Removed the usage of triggers from here.
//		Denis, Nov,99: Some misc updates.
//              Denis, May'00: The scalp code was STILL screwed up.
//                             DAMN THOSE HEAPS!
//              Lucius, Jul'07: Fix the scalp code to reward sybarun
//                tokens at an equal rate whether given 1 scalp or 100.
//              Lilith, Jan 2021: Fixed the drop on the npc so it drops 
//                  all of the objects given instead of just one.
// purpose:     To scare the hell out of people visiting Bazaar
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#include <money.h>
#include <tasks.h>

#define WEP1	(BAZAAR + "Obj/wield/bsword")
#define WEP2	(BAZAAR + "Obj/wield/bmace")

inherit "/d/Avenir/inherit/spy_npc";
inherit "/d/Avenir/inherit/quest";
//don't want him calling for Plalgus since he assists Jadestone.
//inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

private static int busy;

public string my_long(void);
private void set_busy(int num);


public void
create_monster(void)
{

    int i;
    object pouch;
    string *randadj = ({"massive","hairless","fierce","ferocious",
	"terrifying","menacing","brutal","enormous","titanic"});

    ::create_monster();

    set_name("punisher");
    add_name(({"troloby", "monster"}));
    set_race_name("troloby");
    set_adj(randadj[random(sizeof(randadj))]);
    set_long(my_long);

    for (i = 0; i < 6; i++)
	set_base_stat(i, 120 + random(30)); 

    set_alignment(-85);
    set_knight_prestige(750);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 45 + random(10));
    set_skill(SS_PARRY, 80);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS,50);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_spy_ask();
    NEVERKNOWN;

    KILL_THIEF;

    set_cact_time(10);
    add_cact("snarl enemy");
    add_cact("grip mace");
    add_cact("swing sword");
    add_cact("emote growls: I bet you didn't readize what a badass you "
      +"were messing with.");
    add_cact("cackle");
    add_cact("emote snarls: Fear me.");
    add_cact("point enemy");
    add_cact("emote growls: Die. You die now!");
    add_cact("emote tilts his head and appraises the situation.");

    set_act_time(8);
    add_act("hmm");
    add_act("grip mace");
    add_act("swing sword");
    add_act("emote looks around suspiciously.");
    add_act("emote lowers his head for a moment.");

    ::create_monster();

    seteuid(getuid());
    clone_object(WEP1)->move(this_object());
    clone_object(WEP2)->move(this_object());
    command("wield all");

    pouch = clone_object(BAZAAR+"Obj/misc/gem_pouch");
    pouch->move( this_object() );
    pouch->fill_pouch();
    clone_object(BAZAAR +"Obj/worn/pboots")->move(this_object());
    clone_object(BAZAAR +"Obj/worn/harness")->move(this_object());
    clone_object(BAZAAR +"Obj/worn/loincloth")->move(this_object());    
    clone_object(HOLM + "obj/cesti")->move(this_object());
    command("wear all");
    this_object()->add_cmdsoul("/d/Avenir/common/obj/npc_soul");
    this_object()->update_hooks();
}

public string 
my_long(void)
{
    string str;

    str = "He is " + LANG_ADDART(implode(query_adjs(), " ")) + " " +
	query_race_name()+".\n" +
    "An unnatural creature spawned by the breeding "+
    "experiments of the Shadow elves, "+
    "his skin is shiny pink, and so hairless and smooth it looks wet. "+
    "As broad as three humans and half again as tall, this fellow "+
    "has ram's horns curling down over his ears. "+
    "Judging by the grin on his loosely-lipped mouth, it would "+
    "seem he enjoys his job quite a bit.\n";

    if (IS_SYBARITE(this_player()) >= SYB_LAY)
    {
        str += "He appears to be very observant and might have "+
               "something to report if you ask nicely.\n";
    }

    return str;
}

public int
special_attack(object enemy)
{
    switch (random(10))
    {
    case 0: ENV(TO)->being_killed(enemy);
	return 0;
    case 2: command("heal me");
	return 0;        
    case 3: command("neck");
	return 1;
    case 4: command("pommel");
	return 1;
    case 5: command("neck");
	return 0;
    case 7: command("pommel");
	return 1;
    case 8: command("heal me");
	return 0;
    case 9: command("cure me");
	return 0;
    default: 
    }
    return 0;
}

public  int 
down(string str)
{
    if (query_attack() != TP || !interactive(TP) ||
        !CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
	return 0;

    if (TP->resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_SNEAK, SS_DEFENCE }),
	TO, ({TS_DEX}) ) > 0 )
	return 0;

    command("emote roars with delight.");
    TP->catch_msg(QCTNAME(TO)+" stands in your way.\n");
    say(QCTNAME(TO)+" blocks "+QTPNAME(TP)+" retreat.\n");
    return 1;
}

public void 
init_living(void)
{
    ::init_living();
    add_action(down, "down");
}

private void 
return_introduce(string who)
{
    object obj = present(find_player(who), environment());

    if (objectp(obj))
    {
	switch(random(3))
	{
	case 0:
	    command("emote gives a toothsome grin in lieu of an introduction.");
	    break;
	case 1:
	    command("emote doesn't seem to hear.\n");
	    break;
	default:
	    command("say Names have power, fool. " + obj->query_name() +
	      ", you are obviously a stranger here. You had better "+
	      "leave before you end up in the pillory.");
	    command("emote crosses his arms and frowns.");
	    break;
	}
    }
}

public void 
add_introduced(string who)
{
    ::add_introduced(who);
    who = lower_case(who);
    set_alarm(3.0, 0.0, &return_introduce(who));
}

public void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(5))
	set_alarm(1.0, 0.0, &help_friend(attacker));
}

public void
help_friend(object ob)
{
    if ( ob && !query_attack() && present(ob, environment()))
    {
	command("say Do you think I would let you kill a " +
	  "Sybarite while I stood and watched?");
	command("kill " + lower_case(ob->query_real_name()));
	command("kill " + lower_case(ob->query_real_name()));
    }
}

private void
give_coins(object who, object coins, int num)
{
    int toks;
    string str;

    if (!present(who, ENV(TO)))
    {
	coins->remove_object();
	return;
    }

    str = coins->short();
    if (!coins->move(who))
    {
        who->catch_msg(QCTNAME(TO) + " gives you " + str + ".\n");
        tell_room(ENV(TO), QCTNAME(TO) + " gives " + str + " to "
	      + QTNAME(who) + ".\n", ({ who }));
    }

    while(--num >= 0)
    {
	if (random(4) > 2)
	    toks++;
    }

    if (toks)
    {
	object token = clone_object("/d/Avenir/common/obj/syb_coin");

	token->set_heap_size(toks);
        token->move(who);
        str = token->short();

        who->catch_msg(QCTNAME(TO) + " seems to think for a moment, then "+
            "gives you " + str + ".\n");
        tell_room(ENV(TO), QCTNAME(TO) + " hesitates a moment, then gives " 
            + str + " to " + QTNAME(who) + ".\n", ({ who }));
    }
}

private void
destruct_scalps(void)
{
    if (objectp(present("avenir_infidel_scalp", this_object())))
        present("avenir_infidel_scalp", this_object())->remove_object();
}

public void
enter_inv(object obj, object from)
{
    int num_scalps;
    object coins;

    ::enter_inv(obj, from);

    if (!interactive(from))
	return;

    if (!obj->id("avenir_infidel_scalp"))
    {
	set_alarm(1.0, 0.0, &command("spit"));
	set_alarm(3.0, 0.0, &command("drop all "+ OB_NAME(obj)));
	return;
    }

    /* I'm an infidel */
    if (IS_INFIDEL(from))
    {
        command("kill "+ OB_NAME(from));
        return;
    }   

    num_scalps = obj->num_heap();

    if (!num_scalps)
	num_scalps = 1;

    seteuid(getuid(this_object()));
    coins = MONEY_MAKE_GC(num_scalps * 3);
    
    if (!busy)
    {
	busy = 1;
	set_alarm(1.0, 0.0, &command("say Ahhhh!"));
	set_alarm(2.0, 0.0, &command("grin " + OB_NAME(from)));
	set_alarm(2.2, 0.0, &set_busy(0));
    }

    set_alarm(3.0, 0.0, &give_coins(from, coins, num_scalps));
    set_alarm(5.0, 0.0, &destruct_scalps());
}

public void
set_busy(int num)
{
    busy = num;
}

public string
race_sound(void)
{
    return "booms";
}

