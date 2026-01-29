inherit "/d/Emerald/std/emerald_guard.c";
inherit "/d/Emerald/std/aid_npc.c";

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
int slam(object enemy);
int my_gender();
void set_me_up(object setter);

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
      "majestic", 50, "lazy", 10, "stiff", 20, "limping", 0});

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n])) add_adj(arr[n]);
    set_long("This elf is one of the members of the Emerald patrol. "+
             capitalize(HE_SHE(TO)) +
             " stands guard, keeping everyone that passes by "+
      "under "+HIS_HER(TO)+" watchful eye. The Emerald patrol is well "+
      "trained in combat, and are proficient in the use of their weapons.\n");
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
    add_special_attack(slam, 100, "slam");
    set_alarm(1.0, 0.0, &set_me_up(TO));
    log_my_kills( HOME_DIR + "log/patrolkills");
    set_random_move(1);
    set_chat_time(7);
    add_chat("I fear that the roads are not as safe as they used to be.");
    set_act_time(9);
    add_act("frown");
    add_act("emote looks up and down the road for troublemakers.");
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
set_me_up(object setter)
{
    string room, roomdir, *roomarr;
    int i;
    room = file_name(ENV(setter));
    
    roomarr = explode(room, "/");

    roomdir = "";

    for( i = 0; i < (sizeof(roomarr) -1); i++ )
    {
	roomdir += roomarr[i];
	roomdir += "/";
    }

    switch(roomdir)
      {
      case TELSERON_DIR:
	{
	   setter->set_restrain_path( ({ TELSERON_DIR }) );
	   setter->add_prop(EMERALD_ALLIEGANCE, "Telseron");
    	   setter->trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
	   return;
	   break;
	}
      case TELSERON_DIR + "garden/":
	{
	   setter->set_restrain_path( ({ TELSERON_DIR + "garden/" }) );
	   setter->add_prop(EMERALD_ALLIEGANCE, "Telseron");
    	   setter->trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
	   return;
	   break;
	}
      case TELBERIN_DIR:
	{
	   setter->set_restrain_path( ({ TELBERIN_DIR }) );
	   setter->add_prop(EMERALD_ALLIEGANCE, "Telberin");
    	   setter->trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
	   return;
	   break;
	}
      case KROAD_DIR:
	{
	   setter->set_restrain_path( ({ KROAD_DIR }) );
	   setter->add_prop(EMERALD_ALLIEGANCE, "Telberin");
    	   setter->trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
	   return;
	   break;
	}
      case WROAD_DIR:
	{
	   setter->set_restrain_path( ({ WROAD_DIR }) );
	   setter->add_prop(EMERALD_ALLIEGANCE, "Telberin");
    	   setter->trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
	   return;
	   break;
	}
      default:
	return;
	break;
      }
      switch(TO->query_prop(EMERALD_ALLIEGANCE))
	     {
	     case "Telberin":
	       {
		add_act("emote looks around in admiration of the lovely "+
			"lands of Emerald.");
		add_chat("Welcome to Emerald.");
		add_cchat("for Telberin!!");
	       }
	     case "Telseron":
	       {
		add_act("emote looks around in admiration of the lovely "+
			"city of Telseron.");
		add_cchat("for Telseron!!");
		add_chat("Welcome to Telseron.");
	       }
	     default:
	       {
		add_chat("Welcome to Emerald.");
		add_act("emote surveys the lands about "+HIM_HER(TO)+".");
		add_cchat("For Emerald!!");
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

int slam(object enemy)
{
    object 	wep,
    headgear;

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
	this_object()->catch_msg("You rear up with your hands high above your head "+
	  "and just as you are about to bring them down in a crushing "+
	  "blow, you sheepishly realize that you have no wielded weapon.\n");
	enemy->catch_msg(QCTNAME(TO) + " rears up with " +
	  query_possessive() + " hands above " + query_possessive() +
	  " head. Just as " + query_pronoun() + " is about to bring " +
	  "them down in a crushing blow, " + query_pronoun() +
	  " sheepishly realizes that " + query_pronoun() + " has no "+
	  "wielded weapon.\n");
	tell_watcher(QCTNAME(TO) + " rears up with " +
	  query_possessive() + " hands high above " +
	  query_possessive() + " head. Just as " + query_pronoun() +
	  " is about to bring them down in a crushing blow, " +
	  query_pronoun() + " sheepishly realizes that " + 
	  query_pronoun() + " has no wielded weapon.\n", enemy);
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



    /*	headgear = (enemy->query_worn(A_HEAD)); */
    /* Fun code to either break headgear or weapon */
    /*	if (random(100) && (headgear != 0)  */

    hitresult = enemy->hit_me( MYHIT + 3 * random(MYHIT), method_dt, TO, -1, A_HEAD);
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

    TO->catch_msg("You rear up with your " + wep->query_short() + 
      " high above your head and " + method + " it down on " + 
      QTNAME(enemy) + "'s head. " + capitalize(enemy->query_pronoun()) + 
      " is " + how + ".\n"); 
    enemy->catch_msg(QCTNAME(TO) + " rears up with " + TO->query_possessive() +
      " " + wep->query_short() + " high above " + query_possessive() +
      " head and " + method + " it down on you! You are " +
      how + ".\n");
    tell_watcher(QCTNAME(TO) + " rears up with " + query_possessive() +
      " " +wep->query_short() + " high above " + query_possessive() +
      " head and " + method + " it down on " + QTNAME(enemy) + ". " +
      capitalize(enemy->query_pronoun()) + " is " +
      how + ".\n", enemy);

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
  if (!(TO->query_attack()))
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
