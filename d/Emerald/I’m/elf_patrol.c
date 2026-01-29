inherit "/d/Emerald/std/emerald_guard.c";
inherit "/d/Emerald/std/aid_npc.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Emerald/sys/paths.h"

#define	MYHIT wep->query_pen() + MYSKILL/4
#define MYSKILL query_skill(wep->query_wt())
#define MYWEP wep->query_pen()

#define EMERALD_PATROL_RANK "_emerald_patrol_rank"
#define EMERALD_ALLIEGANCE "_emerald_alliegance"

int statbonus;

mixed my_equip();
int slam(object enemy);
void set_me_up(object setter);

void
create_emerald_monster()
{
    mixed *arr;
    int n;

    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alignment(750);

    set_gender(((random(5) < 4) ? G_MALE : G_FEMALE));

    set_race_name("elf");

    arr = ({"stoic", 40, "tired", 10, "wary", 30, "tough", 40,
      "grim", 30, "sleepy", 10, "carefree", 20, "scared", 0,
      "majestic", 50, "lazy", 10, "stiff", 20, "limping", 0});

    n = random(sizeof(arr) / 2) * 2;
    if (strlen(arr[n]))
    {
        add_adj(arr[n]);
    }

    statbonus = (arr[n+1]);
    add_prop(EMERALD_PATROL_RANK, statbonus);

    set_long("This elf is one of the members of the Emerald patrol. "+
        capitalize(query_pronoun()) + " stands guard, keeping everyone " +
        "that passes by under " + query_possessive() + " watchful eye. " +
        "The Emerald patrol is well trained in combat, and are proficient " +
        "in the use of their weapons.\n");

    add_equipment(my_equip());

    set_stats(({ statbonus * 2 + 30, statbonus * 2 + 50, statbonus * 2 + 30,
	statbonus / 2 + 50, statbonus / 2 + 50, statbonus + 50 }));


    set_skill(SS_DEFENCE, statbonus + 40);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, statbonus + 50);
    set_skill(SS_WEP_SWORD, statbonus + 50);
    set_skill(SS_AWARENESS, statbonus + 40);

    set_special_attack_percent(14);
    add_special_attack(slam, 100, "slam");

    set_alarm(1.0, 0.0, &set_me_up(this_object()));

    set_random_move(1);

    set_chat_time(7);
    add_chat("I fear that the roads are not as safe as they used to be.");
    add_chat("Welcome to Emerald.");

    set_act_time(9);
    add_act("@@greet_players@@");
    add_act("frown");
    add_act("emote looks up and down the road for troublemakers.");
    add_act("emote looks around in admiration of the lovely "+
	    "lands of Emerald.");


    set_cchat_time(4);
    add_cchat("Fool! You shall fall before me!");
    add_cchat("For Emerald!!");

    trig_new("%w 'leaves' / 'sneaks' / 'starts crying and runs' %s", "follow_attacker");
}

void
set_me_up(object setter)
{
    string room, roomdir, *roomarr;
    int i;
    room = file_name(environment(setter));
    
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
	   setter->set_restrain_path( ({ TELSERON_DIR }) );
	   break;
        case TELSERON_DIR + "garden/":
	   setter->set_restrain_path( ({ TELSERON_DIR + "garden/" }) );
	   break;
        case TELBERIN_DIR:
	   setter->set_restrain_path( ({ TELBERIN_DIR }) );
	   break;
        case KROAD_DIR:
	   setter->set_restrain_path( ({ KROAD_DIR }) );
	   break;
        default:
	    setter->set_restrain_path(({ "/d/Emerald/" }));
    }
}

void
greet_players()
{
    object *livings;
    int num;

    if (!CAN_SEE_IN_ROOM(this_object()))
    {
        return;
    }

    livings = FILTER_OTHER_LIVE(all_inventory(environment()));
    for(num = 0; num < sizeof(livings); num++)
    {
        if (!CAN_SEE(this_object(), livings[num]))
	{ 
            continue;
	}

	if (livings[num]->query_kot_member())
	{
            livings[num]->catch_tell(query_The_name(livings[num]) + 
                " bows respectfully "+	"to you and says: Greetings, " +
                "Keeper...Well met.\n");
	}
	else
	{
	    livings[num]->catch_tell(query_The_name(livings[num]) +
                " nods to you and says: Well met stranger.\n");
	}
    }
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
	wep = query_weapon(W_LEFT);
	armed = 1;
    }
    if (!objectp(wep))
	wep = query_weapon(W_BOTH);
    armed = 1;

    if (!objectp(wep))
	armed = 0;

    if (!armed) 
    {
	enemy->catch_msg(QCTNAME(this_object()) + " rears up with " +
	  query_possessive() + " hands above " + query_possessive() +
	  " head. Just as " + query_pronoun() + " is about to bring " +
	  "them down in a crushing blow, " + query_pronoun() +
	  " sheepishly realizes that " + query_pronoun() + " has no "+
	  "wielded weapon.\n");
	tell_watcher(QCTNAME(this_object()) + " rears up with " +
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

    hitresult = enemy->hit_me( MYHIT + 3 * random(MYHIT), method_dt, this_object(), -1, A_HEAD);
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

    enemy->catch_msg(QCTNAME(this_object()) + " rears up with " + query_possessive() +
      " " + wep->query_short() + " high above " + query_possessive() +
      " head and " + method + " it down on you! You are " +
      how + ".\n");
    tell_watcher(QCTNAME(this_object()) + " rears up with " + query_possessive() +
      " " +wep->query_short() + " high above " + query_possessive() +
      " head and " + method + " it down on " + QTNAME(enemy) + ". " +
      capitalize(enemy->query_pronoun()) + " is " +
      how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(this_object());

    return 1;
}

my_equip()
{
    switch (query_prop(EMERALD_PATROL_RANK))
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
	if (random(2))
	  {
	    return ({"/d/Emerald/wep/patrol_longsword", "/d/Emerald/arm/patrol_helm", "/d/Emerald/arm/patrol_plate"});
	    break;
	  }
	return ({"/d/Emerald/wep/patrol_mace", "/d/Emerald/arm/patrol_helm", "/d/Emerald/arm/patrol_plate"});
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

    if (!(query_attack()))
    {
    	switch(random(3))
        {
    	    case 0:
		command("shout Aid me!");
		break;
    	    case 1:
		command("emote cries out for assistance!");
		break;
    	    case 2:
	      command("command say What the...??");
	      break;
        }
    }

    get_assistance(enemy);
}
