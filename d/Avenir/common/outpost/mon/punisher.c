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

#define WEP2	(BAZAAR + "Obj/wield/bmace")

inherit "/d/Avenir/inherit/spy_npc";
inherit "/d/Avenir/inherit/quest";

public string my_long(void);

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
	set_base_stat(i, 200 + random(30)); 

    set_alignment(0);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 45 + random(10));
    set_skill(SS_PARRY, 80);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS,100);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_VOLUME, 100000);
	add_prop(CONT_I_WEIGHT, 100000);
	add_prop(CONT_I_HEIGHT, 250);
    add_spy_ask();
    NEVERKNOWN;
    KILL_THIEF;

    set_cact_time(100);
    add_cact("emote tilts his head and appraises the situation.");

    set_act_time(120);
    add_act("hmm");
    add_act("grip mace");
    add_act("emote looks around suspiciously.\n"+
        "You do your best to look innocent.");
    add_act("emote lowers his head for a moment.");
    add_act("emote scratches himself idly.");
    add_act("emote sharpens the tip of his horn.");
    add_act("emote eyes you as if appraising how much trouble "+
        "you are going to be.\nYou do your best to look like "+
        "you are no trouble at all.");
    add_act("emote emits a noise that sounds like an empty stomach "+
        "rumbling.\nA hungry troloby probably isn't a good thing.");	
	
    seteuid(getuid());
    clone_object(WEP2)->move(this_object());
    command("wield all");

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
    "An unnatural creature, "+
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

public void 
init_living(void)
{
	object *enemies;

    ::init_living();

    if (interactive(this_player()))
    {
        enemies = this_player()->query_enemy(-1);
        this_player()->stop_fight(enemies);
        enemies->stop_fight(this_player());
    }           
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
	      "leave before you end up in the gaol.");
	    command("emote crosses his arms and frowns.");
	    break;
	}
    }
}


public string
race_sound(void)
{
    return "booms";
}

/* He said NO fighting */
int 
query_not_attack_me(object who, int aid)
{
	object *enemies;
    who->catch_msg(QCTNAME(this_object()) +" easily blocks your "+
    "attack and shuts your nonsense down. Yikes!\n");   
    enemies = TO->query_enemy(-1);
    TO->stop_fight(enemies);
    enemies->stop_fight(TO);
    return 1;
}