/* A dwarven warrior out on a quest for troll treasure hoards */
/* Created by Igneous */

#include "../local.h"
#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit SHIRE_MONSTER;

#define STUN_OB  EROBJ_DIR + "stun"
#define WEP_ARR ({ERWEP_DIR + "battleaxe", ERWEP_DIR + "battlehammer"})

static int Chair = 1;

// Prototypes
string get_attitude_desc();
string get_beard_desc();
void assist_friend(object ob);
void get_booze();


void create_dwarf() {}

nomask void
create_shire_monster()
{
    set_race_name("dwarf");
    set_gender(G_MALE);
    set_adj(({get_attitude_desc(), get_beard_desc()}));
    set_long("This "+query_nonmet_name()+" is a member of "+
      "Khaaz's troll hunting party. "+CAP(HE_SHE(TO))+" has followed "+
      "Khaaz all the way from the Blue Mountains in hopes of coming home "+
      "with a pile of troll treasure horde.  Well armed and armoured "+
      "this dwarf looks like a capable fighter.\n");

    set_base_stat(SS_STR, 95 + random(30));
    set_base_stat(SS_DEX, 75 + random(20));
    set_base_stat(SS_CON, 110 + random(30));
    set_base_stat(SS_INT, 60 + random(10));
    set_base_stat(SS_WIS, 70 + random(10));
    set_base_stat(SS_DIS, 90 + random(20));

    set_skill(SS_WEP_CLUB, 65 + random(21));
    set_skill(SS_WEP_AXE, 70 + random(26));
    set_skill(SS_WEP_POLEARM, 60 + random(16));
    set_skill(SS_PARRY, 50 + random(16));
    set_skill(SS_DEFENCE, 75 + random(16));
    set_skill(SS_BLIND_COMBAT, 70 + random(21));
    set_skill(SS_AWARENESS, 50 + random(21));

    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(OBJ_I_RES_POISON, 30);
    add_prop(OBJ_I_RES_EARTH, 20);


    set_alignment(600 + random(300));
    set_intoxicated(1000);
    add_prop(LIVE_I_NEVERKNOWN, 1);


    //  time for the emotes and chats/cchats
    set_chat_time(5 + random(3));
    add_chat("This brandy is the smoothest I've ever 'ad!");
    add_chat("I hopes we'll be able to carry all that gold home!");
    add_chat("Maybe there'll be some goblins for us to get "+
      "warmed up on along the way.");
    add_chat("Me weapon is polished and I'z itchin for blood!");

    set_act_time(6 + random(4));
    add_act("emote chugs down some of his brandy.");
    add_act("emote strokes his beard.");
    add_act("grumble");
    add_act("hiccup");

    set_cchat_time(10 + random(4));
    add_cchat("Finally some action!");
    add_cchat("You'll pay for this!");
    add_cchat("I'm gunna knock ya head from ya rott'n corpse!");
    add_cchat("HA! is dat the best you can do!");
    add_cchat("To battle and victory lads!");

    set_cact_time(5 + random(8));
    add_cact("emote screams an ancient battle cry!");
    add_cact("knee goblins");
    add_cact("grumble");
    add_cact("emote reaches for another bottle.");
    add_cact("shout Die stinking bastards!");

    add_equipment(({ONE_OF(WEP_ARR), ERARM_DIR + "d_boots",
	ERARM_DIR + "d_chainmail",ERARM_DIR + "d_helm"}));
    get_booze();
    create_dwarf();
}

string
get_beard_desc()
{
    return ONE_OF(({"grey-bearded", "long-bearded", "black-bearded",
	"white-bearded","thin-bearded","blond-bearded"}));
}

string
get_attitude_desc()
{
    return ONE_OF(({"old", "grumpy", "grumbling", "stout", "fat",
	"drunken", "big-nosed", "red-nosed"}));
}

varargs public string
short(object for_obj)
{
    string old_short = ::short(for_obj);

    if (Chair && !query_attack())
	return old_short + ", sitting in a chair";

    return old_short;
}

void
get_booze() 
{
    object booze;

    booze = clone_object(EROBJ_DIR + "wine");
    booze->set_heap_size(6);
    booze->move(TO,1);
}

void
attacked_by_hook(object ob) 
{
    command("say "+ONE_OF(({"Alright, about time we got some action!",
	  "Dat was a stupid mistake "+ob->query_race_name()+"!",
	  "To battle lads!"})));
}

void
attacked_by(object ob)
{
    if (!objectp(query_attack()))
    {
	attacked_by_hook(ob);
    }
    ::attacked_by(ob);
    query_team_others()->notify_friend_attacked_by(ob);
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    query_team_others()->notify_friend_attacked_by(ob);
}

void
notify_friend_attacked_by(object ob)
{
    if (!present(ob, environment()) || objectp(query_attack()))
	return;
    set_alarm(itof(random(3) + 1), 0.0, &assist_friend(ob));
}

void
do_chair_attack(object victim) 
{
    mixed res;
    int pen;
    object stun;

    TO->attack_object(victim);
    command("shout Stupid "+victim->query_race_name()+"!!  I'll "+
      "smash yer skull open!");
    victim->catch_msg(QCTNAME(TO) +" picks up "+HIS_HER(TO)+
      " chair and breaks it on your head!!\n");
    TO->tell_watcher(QCTNAME(TO) + " picks up "+HIS_HER(TO)+
      " chair and breaks it on "+QTNAME(victim)+"'s head.\n", victim);
    pen = query_stat(SS_STR) / 2 + query_skill(SS_WEP_CLUB) / 7;
    pen = F_PENMOD(pen, query_skill(SS_WEP_CLUB));
    res = victim->hit_me(pen, W_BLUDGEON, TO, -1, TS_HEAD);
    Chair = 0;
    if (victim->query_wiz_level())
	victim->catch_tell("DAMAGE: "+res[3]+"\n");
    if (victim->query_hp() < 1)
    {
	victim->do_die(TO);
	return;
    }
    if (res[0] <= 0)
	return;
    if (present("_Shire_chair_stun", victim))
	return;
    setuid(); seteuid(getuid());
    stun = clone_object(STUN_OB);
    stun->move(victim, 1);
    // Stun object takes care of all the messages.
}

void
assist_friend(object ob)
{
    if (!present(ob, environment()) || objectp(query_attack()))
	return;
    if (Chair && !present("_Shire_chair_stun", ob))
	do_chair_attack(ob);
    else
	command("shout You'll pay for this "+ob->query_nonmet_name()+"!");

    if (!command("kill "+ob->query_real_name()))
	if (!command("assist"))
	    attack_object(ob);   // Ok we cheat here ;-)
}

int
special_attack(object enemy)
{
    mixed hit_res;
    int pen;
    string text1, text2;
    object weapon, bottles;

    if (random(6))
	return 0;

    if (sizeof(query_weapon(-1)))
	weapon = query_weapon(-1)[0];
    if ((!random(3) || !objectp(weapon)) &&
      (!present("_Shire_chair_stun", enemy)) &&
      (objectp(bottles = present("_Shire_bottle", TO))))
    {
	// We fight dirty :)
	if (Chair)
	    do_chair_attack(enemy);
	else
	{
	    setuid(); seteuid(getuid());
	    weapon = clone_object(MASTER_OB(bottles));
	    bottles->set_heap_size(bottles->num_heap() - 1);
	    // Tell them he got hit with something.
	    enemy->catch_msg(QCTNAME(TO) + " takes grip on "+LANG_ASHORT(weapon)+
	      " and hit you on your head with it!\n");
	    TO->tell_watcher(QCTNAME(TO) + " takes grip on "+LANG_ASHORT(weapon)+
	      " and hits "+QTNAME(enemy)+" on "+HIS_HER(enemy)+" head!\n", 
	      enemy);

	    pen = weapon->query_prop(HEAP_I_UNIT_WEIGHT) / 20 + 
	    query_stat(SS_STR) / 20;
	    pen = F_PENMOD(pen, query_skill(SS_WEP_CLUB));
	    hit_res = enemy->hit_me(pen, W_BLUDGEON, TO, -1, TS_HEAD);

	    // Bottle breaks
	    weapon->remove_object();
	    // Is he dead?
	    if (enemy->query_hp() < 1)
	    {
		enemy->do_die(TO);
		return 1;
	    }
	    // If he hit him hard enough we stun him
	    if (hit_res[3] >= 20)
	    {
		clone_object(STUN_OB)->move(enemy, 1);
	    }
	}

    }
    else
    {
	if (!objectp(weapon))
	    return 0;

	if (weapon->query_wt() == W_AXE)
	{
	    pen = weapon->query_pen() + SS_DEX / 5;
	    pen = F_PENMOD(pen, query_skill(SS_WEP_AXE)); 
	    hit_res = enemy->hit_me(pen, W_SLASH, TO, -1);
	    switch (hit_res[0])
	    {
	    case -1:
		text1 = "missing you entirely.";
		text2 = "missing "+QTNAME(enemy)+" entirely.";
		break;
	    case 0:
		text1 = "barely missing your "+hit_res[1]+".";
		text2 = "barely missing "+QTNAME(enemy)+"'s "+hit_res[1]+".";
		break;
	    case 1..15:
		text1 = "striking your "+hit_res[1]+" leaving a minor gash.";
		text2 = "striking "+QTNAME(enemy)+"'s "+hit_res[1]+" leaving a minor gash.";
		break;
	    case 16..35:
		text1 = "connecting into your "+hit_res[1]+" cutting deeply.";
		text2 = "connecting into "+QTNAME(enemy)+"'s "+hit_res[1]+" cutting deeply.";
		break;
	    case 36..55:
		text1 = "cleaving into your "+hit_res[1]+"!";
		text2 = "cleaving into "+QTNAME(enemy)+" "+hit_res[1]+"!";
		break;
	    case 56..80:
		text1 = "cleaving deeply into your "+hit_res[1]+"!";
		text2 = "cleaving deeply into "+QTNAME(enemy)+"'s "+hit_res[1]+"!";
		break;
	    default:
		text1 = "which practically cleaves your "+hit_res[1]+" "+
		(hit_res[1] == "body" ? "in half" : "from your body")+"!";
		text2 = "which practically cleaves "+QTNAME(enemy)+"'s "+hit_res[1]+
		(hit_res[1] == "body" ? "in half" : "from "+HIS_HER(enemy)+" body")+"!";
		break;
	    }
	}
	else
	{
	    pen = weapon->query_pen() + SS_STR / 4;
	    pen = F_PENMOD(pen, (weapon->query_wt() == W_CLUB ?
		query_skill(SS_WEP_CLUB) : query_skill(SS_WEP_POLEARM)));

	    hit_res = enemy->hit_me(pen, W_BLUDGEON, TO, -1);
	    switch (hit_res[0])
	    {
	    case -1:
		text1 = "missing you entirely.";
		text2 = "missing "+QTNAME(enemy)+" entirely.";
		break;
	    case 0:
		text1 = "narrowly missing your "+hit_res[1]+".";
		text2 = "narrowly missing "+QTNAME(enemy)+"'s "+hit_res[1]+".";
		break;
	    case 1..15:
		text1 = "striking your "+hit_res[1]+" with a soft thump.";
		text2 = "striking "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with a soft thump.";
		break;
	    case 16..35:
		text1 = "striking your "+hit_res[1]+" with a solid thump.";
		text2 = "striking "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with a solid thump.";
		break;
	    case 36..55:
		text1 = "brusing your "+hit_res[1]+" slightly.";
		text2 = "brusing "+QTNAME(enemy)+"'s "+hit_res[1]+" slightly.";
		break;
	    case 56..80:
		text1 = "hitting your "+hit_res[1]+" with a crushing blow!";
		text2 = "hitting "+QTNAME(enemy)+"'s "+hit_res[1]+" with "+
		"a crushing blow!";
		break;
	    default:
		text1 = "smashing into your "+hit_res[1]+" with sicking force!!";
		text2 = "smashing into "+QTNAME(enemy)+"'s "+hit_res[1]+
		" with sicking force!!";
		break;
	    }
	}
	enemy->catch_msg(QCTNAME(TO) + " swings "+HIS_HER(TO)+" "+
	  weapon->short() +" around, "+ text1 +"\n");
	TO->tell_watcher(QCTNAME(TO) + " swings "+HIS_HER(TO)+ " "+
	  weapon->short() + " around "+ text2 + "\n", enemy);        
	if (enemy->query_hp() < 1)
	    enemy->do_die(TO);

    }
    if (enemy->query_wiz_level())
	enemy->catch_tell("DAMAGE: "+hit_res[3]+"\n");
    return 1;
}
