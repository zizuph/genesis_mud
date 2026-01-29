inherit "/d/Emerald/std/emerald_guard.c";
inherit "/d/Emerald/std/aid_npc.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Emerald/defs.h"

#define	MYHIT wep->query_pen() + MYSKILL/4
#define MYSKILL TO->query_skill(wep->query_wt())
#define MYWEP wep->query_pen()
#define EMERALD_PATROL_RANK "_emerald_patrol_rank"
#define EMERALD_ALLIEGANCE "_emerald_alliegance"
#define DEBUGWHO "karath"
#define DEBUGTELL(x) find_player(DEBUGWHO)->catch_msg(x)

mixed my_equip();
mixed statbonus;
int tackle(object enemy);
int my_gender();
void do_rescue(object summoner, object aggressor);

void
create_emerald_monster()
{
    string *arr;
    int n;

    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(750);
    set_gender(my_gender());
    set_race_name("elf");
    arr = ({"stoic", 40, "tired", 10, "wary", 30, "tough", 40,
      "grim", 30, "sleepy", 10, "carefree", 20, "scared", 0,
      "majestic", 60, "lazy", 10, "stiff", 20, "limping", 0});

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n])) add_adj(arr[n]);
    set_long("This elf is one of the members of the Emerald patrol. "+
      HE_SHE(TO) + " stands guard, keeping everyone that passes by "+
      "under "+HIS_HER(TO)+" watchful eye. The Emerald patrol is well "+
      "trained in combat, and are proficient in the use of their weapons.\n");
    statbonus = (arr[n+1]);
    add_prop(EMERALD_PATROL_RANK, statbonus);
    add_equipment(my_equip());
    set_stats(({ statbonus*2+30, statbonus*2+50, statbonus*2+30,
	statbonus/2+50, statbonus/2+50, statbonus+100}));
    add_act("@@greet_players");
    set_hp(query_max_hp());
    set_skill(SS_DEFENCE, statbonus+40);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, statbonus+50);
    set_skill(SS_WEP_SWORD, statbonus+50);
    set_skill(SS_AWARENESS, statbonus+40);
    set_special_attack_percent(10);
    add_special_attack(tackle, 100, "tackle");
    set_m_in("rushes to the aid of "+HIS_HER(TO)+" ruler!");

    trig_new("%w 'leaves' / 'sneaks' / 'rides' %s", "follow_attacker");
    set_restrain_path( ({ TELBERIN_DIR + "castle/" }) );

    log_my_kills( HOME_DIR + "log/patrolkills");
    set_cchat_time(4);
    add_cchat("Fool! You shall fall before me!");
}

int my_gender()
{
    int foo = random(5);
	
    switch(foo)
      {
      case 0..3:
	{
	return 0;
	break;
	}
      case 4:
	{
	return 1;
	break;
	}
      }
}

void
greet_players()
{
    object *livings;
    int num;
    livings = FILTER_OTHER_LIVE(all_inventory(environment(TO)));
    for(num = 0; num < sizeof(livings); num++)
      {
	if(livings[num]->query_kot_member())
	  {
		livings[num]->catch_msg(QCTNAME(TO) + " bows respectfully "+
	"to you and says: Greetings Keeper...Well met.\n");
	continue;
	  }
	else
	  {
		livings[num]->catch_msg(QCTNAME(TO) + " nods to you and "+
	"says: Well met stranger.\n");
	continue;
	  }
      }
    return;
}

int tackle(object enemy)
{
    string how;

    int delay;

    int success = random(query_stat(SS_DEX) + (2*statbonus)) -
		  random(enemy->query_stat(SS_DEX) - query_skill(SS_ACROBAT));

    if (success < 1) 
    {
	this_object()->catch_msg("You dive at your enemy and miss!\n");
	enemy->catch_msg(QCTNAME(TO) + " dives at you, trying to tackle "+
	  "you, but lands in an ungraceful sprawl at your feet!\n");
	tell_watcher(QCTNAME(TO) + " dives at "+QTNAME(enemy)+" in an "+
	  "attempt to tackle "+HIM_HER(enemy)+", but lands in an "+
	  "ungraceful sprawl at "+HIM_HER(enemy)+" feet.\n", enemy);
	return 1;
    }

    switch (success)
      {
    case 1..19:
	how = "weak grasp";
	delay = 5;
	break;
    case 20..39:
	how = "tentitive hold";
	delay = 8;
	break;
    case 40..59:
	how = "quick grab";
	delay = 10;
	break;
    case 60..79:
	how = "strong armtackle";
	delay = 14;
	break;
    case 80..99:
	how = "powerful grasp";
	delay = 17;
	break;
    default: 
	how = "enveloping bearhug";
	delay = 20;
	break;
      }

    TO->catch_msg("You rush forward and grab your enemy's shoulders in "+
        "a "+how+"!\n");
    enemy->catch_msg(QCTNAME(TO) + " rushes at you and grabs your "+
	"shoulders in a "+how+", holding you back and preventing your "+
	"attacks!\n");
    enemy->catch_msg(QCTNAME(TO)+" gets in the way of your blows!\n");
    enemy->attack_object(TO);
    tell_watcher(QCTNAME(TO) + " rushes at "+QTNAME(enemy)+" and grabs "+
	HIS_HER(enemy)+" shoulders in a "+how+", preventing "+HIS_HER(enemy)+
	" attacks!\n", enemy);

    enemy->add_attack_delay(delay, 1);

    return 1;
}

public void
do_rescue(object summoner, object aggressor)
{
    command("assist "+summoner->query_name());
    command("shout Die "+aggressor->query_nonmet_name());
}

my_equip()
{
    switch (TO->query_prop(EMERALD_PATROL_RANK))
    {
    case 0:
	return ({"/d/Emerald/wep/patrol_shortsword", "/d/Emerald/arm/patrol_cap", "/d/Emerald/arm/patrol_lplate"});
	break;
    case 10:
	return ({"/d/Emerald/wep/patrol_spear", "/d/Emerald/arm/patrol_cap", "/d/Emerald/arm/patrol_lplate"});
	break;
    case 20:
	return ({"/d/Emerald/wep/patrol_broadsword", "/d/Emerald/arm/patrol_coif", "/d/Emerald/arm/patrol_chain"});
	break;
    case 30:
	return ({"/d/Emerald/wep/patrol_halberd", "/d/Emerald/arm/patrol_coif", "/d/Emerald/arm/patrol_chain"});
	break;
    case 40:
	return ({"/d/Emerald/wep/patrol_longsword", "/d/Emerald/arm/patrol_helm", "/d/Emerald/arm/patrol_plate"});
	break;
    case 50:
	return ({"/d/Emerald/wep/patrol_claymore", "/d/Emerald/arm/patrol_helm", "/d/Emerald/arm/patrol_plate"});
	break;
    default:
	return ;
	break;
    }

}

public void
add_introduced(string str)
{
  if(find_player(str)->query_npc())
        return;
  switch(random(5))
    {
    case 0:
      {
        command("say to "+str+" Greetings! I am happy to know you.");
        command("smile "+str);
        return;
        break;
      }
    case 1:
      {
        command("say to "+str+" Greetings...Do not start any trouble.");
        command("nod "+str);
        return;
        break;
      }
    case 2:
      {
        command("say to "+str+" Hello there. I'm on watch you know.");
        command("smile "+str);
        return;
        break;
      }
    case 3:
      {
        command("say to "+str+" Be careful "+
		find_player(str)->query_race_name()+
		", the roads are not as safe as they once were.");
        command("nod "+str);
        return;
        break;
      }
    case 4:
      {
        command("say to "+str+" Well aren't you a friendly traveller?");
        command("smile amusedly");
        return;
        break;
      }
    }
}

void
assist(object enemy)
{
    switch (random(3))
      {
      case 0:
        command("say Couldn't restrain yourself eh?! Neither shall I!");
        break;
      case 1:
        command("shout Thou shalt not be such a nuisance decapitated!!");
        break;
      case 2:
        command("shout Thy evil deed will be thy doom!!");
        break;
      }
    command("emote enters the battle!");
}

attacked_by(object enemy)
{
  ::attacked_by(enemy);
  switch(random(3))
    {
    case 0:
      {
  	command("shout Aid me!");
	break;
      }
    case 1:
      {
  	command("emote cries out for assistance!");
	break;
      }
    case 2:
      {
  	command("command say What the...??");
	break;
      }
    }
  get_assistance(enemy);
}
