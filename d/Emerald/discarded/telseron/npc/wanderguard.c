inherit "/d/Emerald/std/emerald_guard.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Emerald/defs.h"

/*#define	MYHIT 2*(random((wep->query_pen() + MYSKILL)/2)*/
#define	MYHIT wep->query_pen() + MYSKILL/4
#define MYSKILL TO->query_skill(wep->query_wt())
#define MYWEP wep->query_pen()
#define EMERALD_PATROL_RANK "_emerald_patrol_rank"
#define EMERALD_ALLIEGANCE "_emerald_alliegance"
#define DEBUGWHO "karath"
#define DEBUGTELL(x) find_player(DEBUGWHO)->catch_msg(x)

mixed my_equip();
mixed statbonus;
int thrust(object enemy);
int my_gender();

void
create_emerald_monster()
{
    string *arr;
    int n;

    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(750);
    set_gender(my_gender());
    set_race_name("elf");
    arr = ({"stoic", 40, "Sergeant of the Guard", "tired", 10,
	"Apprentice Guard", "wary", 30, "Senior Guard", "tough", 40,
	"Sergeant of the Guard", "grim", 30, "Senior Guard", "sleepy",
	 10, "Apprentice Guard", "carefree", 20, "Watchful Guard",
	 "scared", 0, "Training Guard", "majestic", 50, 
	"Captain of the Guard", "lazy", 10, "Apprentice Guard",
	 "stiff", 20, "Watchful Guard",  "limping", 0, "Training Guard"});

    n = random(sizeof(arr)/3)*3;
    if (strlen(arr[n])) add_adj(arr[n]);
    set_long("This elf is one of the members of the Royal Guards of "+
      "Telseron. "+ capitalize(HE_SHE(TO)) + " stands guard, keeping "+
      "everyone that passes by under "+HIS_HER(TO)+" watchful eye. "+
      "The Royal Family of Telseron keep their guards well equipped and "+
      "trained in combat, and are proficient in the use of their weapons. "+
      capitalize(HE_SHE(TO)) + " is a " + arr[n+2] + ".\n");
    statbonus = (arr[n+1]);
    add_prop(EMERALD_PATROL_RANK, statbonus);
    add_equipment(my_equip());
    set_stats(({ statbonus*2+30, statbonus*2+50, statbonus*2+30,
	statbonus/2+50, statbonus/2+50, statbonus+50}));
    set_act_time(8);
    add_act("@@greet_players");
    set_hp(query_max_hp());
    set_skill(SS_DEFENCE, statbonus+40);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, statbonus+50);
    set_skill(SS_WEP_SWORD, statbonus+50);
    set_skill(SS_AWARENESS, statbonus+40);
    set_special_attack_percent(14);
    add_special_attack(thrust, 100, "thrust");
    log_my_kills( HOME_DIR + "telseron/log/kills");
    set_random_move(1);
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

int thrust(object enemy)
{
    object 	wep;

    mixed* hitresult;

    string 	how,
    method;

    int 	method_dt,
    armed,
    phurt;

    wep = query_weapon(W_RIGHT);

    if (objectp(wep))
	armed = 1;

    else 
    {
	wep = TO->query_weapon(W_LEFT);
	armed = 1;
    }
    if (!objectp(wep))
	wep = TO->query_weapon(W_BOTH);
    armed = 1;

    if (!objectp(wep))
	armed = 0;

    if (!armed) 
    {
	this_object()->catch_msg("You dodge your enemy's thrust, "+
	  "flip your body around and flail your unarmed fist unimpressivly "+
	  "at your enemy in a weak attempt to still do some damage.\n");
	enemy->catch_msg(QCTNAME(TO) + " dodges your attack and swings "+
	  query_possessive() + " body around and flails " +
	  query_possessive() + " arms at your body in a weak attempt to do "+
	  "some damage.\n");
	tell_watcher(QCTNAME(TO) + " dodges " + query_possessive() +
	  " enemy's blow, flips " + query_possessive() + " body around, "+
	  "swinging " + query_possessive() + " fists in a vain effort to "+
	  "damage "+HIS_HER(TO)+ " enemy.\n");
	return 1;
    }

    /*
     * Here we see what sort of attack and damagetype to do.
     * We prefer slash, then impale, and lastly bludgeon.
     * I'm not exactly sure what to do if we have an illegal
     * damage-type...
     */
    if (wep->query_dt() & W_SLASH)
	method_dt = W_SLASH;
    else if (wep->query_dt() & W_IMPALE)
	method_dt = W_IMPALE;
    else if (wep->query_dt() & W_BLUDGEON)
	method_dt = W_BLUDGEON;
    else
	method_dt = W_SLASH;


    switch (method_dt)
    {
    case W_SLASH:
	method = "slashes";
	break;
    case W_IMPALE:
	method = "thrusts";
	break;
    case W_BLUDGEON:
	method = "swings";
	break;
    default:
	method = "furbles";
	break;
    }



    hitresult = enemy->hit_me( MYHIT + 3 * random(MYHIT), method_dt, TO, -1, A_TORSO);
    /*
     *	tell_object(find_player("karath"),"hitresult is " + hitresult[0] +
     *		"\nMYSKILL is " + MYSKILL + "\nMYWEP is " + MYWEP + "\n");
     */

    switch (hitresult[0])
    {
    case 0:
	how = "unharmed";
	break;
    case 1..2:
	how = "barely wounded";
	break;
    case 3..5:
	how = "slightly wounded";
	break;
    case 6..10:
	how = "somewhat wounded";
	break;
    case 11..20:
	how = "wounded";
	break;
    case 21..30:
	how = "badly wounded";
	break;
    case 31..50:
	how = "wounded quite badly";
	break;
    case 51..75:
	how = "wounded very badly";
	break;
    case 76..90:
	how = "horribly wounded";
	break;
    case 91..99:
	how = "mortally wounded";
	break;
    default: 
	/* default means 100% damage or more...the target is dead */
	how = "slain";
    }

    TO->catch_msg("You dodge your enemy's attack and flip your body around, "+
      "bringing your "+ wep->query_short() + " into "+ QTNAME(enemy) +
      "'s stomache, leaving " +HIM_HER(enemy)+ " " + how + ".\n"); 
    enemy->catch_msg(QCTNAME(TO) + " dodges your attack and pivots on " +
      HIS_HER(TO)+ " feet and " +method+ " "+HIS_HER(TO)+" "+
      wep->query_short()+ " into your body, leaving you "+how+".\n");
    tell_watcher(QCTNAME(TO) + " dodges "+QTNAME(enemy)+"'s attack, "+
      "pivots on "+HIS_HER(TO)+" feet, and "+method+" "+HIS_HER(TO)+
      " "+wep->query_short()+" into "+QTNAME(enemy)+"'s stomach, leaving "+
      HIM_HER(enemy)+ " " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(TO);

    return 1;
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
