/*
 * disabled imprisoning players. Jail is buggy.
 * -- Finwe, August 2001
 */
#include "defs.h"

inherit "/std/monster";
inherit IM_TELL_FILE;

#include <const.h>
#include <stdproperties.h>
#include <macros.h>

void arm_me();
void try_kill_me(object who);
void persuit(object who);


string
short() { return "very evil Uruk-Hai"; }

string
query_nonmet_name() { return "Uruk guard"; }

create_monster()
{
    set_name("guard");
    set_race_name("uruk");
    add_adj("Uruk-Hai");
    add_adj("evil");
    add_name("Uruk-Hai");

    set_long("This is a large and ugly guardian troll, a " +
        "Uruk-Hai. It is as tall as a man with black skin and " +
        "slanting eyes. It looks like a cross between a troll " +
        "and an orc, and was probably bred by as soldiers for " +
        "Sauron. As such, it is a ferocious fighter and a deadly " +
        "foe.\n");

    set_alignment(-450);
    set_gender(G_NEUTER);

    add_prop(CONT_I_WEIGHT, 300*1000);
    add_prop(CONT_I_HEIGHT, 400);
    set_stats( ({ 134, 93, 140, 76, 69, 134 }) );
    set_hp(10000);

    set_skill(SS_UNARM_COMBAT,	30);
    set_skill(SS_WEP_SWORD,    95);
    set_skill(SS_WEP_AXE,      95);
    set_skill(SS_WEP_CLUB,	95);
    set_skill(SS_WEP_KNIFE,	95);
    set_skill(SS_DEFENCE,	100);
    set_skill(SS_PARRY,        100);
    set_skill(SS_AWARENESS,	90);
    set_skill(SS_BLIND_COMBAT, 100);
    add_prop(LIVE_I_SEE_DARK, 90); /* Night vision. */
    /* Sees invisible lions and tigers and bears, oh my! but not wizards :)*/
    add_prop(LIVE_I_SEE_INVIS, 90);


    set_alarm(1.0, 0.0, &arm_me());
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_aggressive(1);
}

arm_me()
{
    clone_object(MORIA_WEP+"urukscim")->move(TO);
    command("wield scimitar");
}

void
go_home()
{
    (MINES_DIR+"bighalln")->get_back();
}

int
special_attack(object who)
{
    if(file_name(ETO)==MINES_DIR+"bighalln")
      set_alarm(0.0, 0.0, &try_kill_me(who));
    else
        set_alarm(0.0, 0.0, &persuit(who));
    return 1;
}
/*
imprison(object who)
{
    who->stop_fight();
    stop_fight();
    who->move_living("M", MINES_DIR+"deep/prison", 1, 1);
    who->catch_msg(
	"\nThe Uruk-Hai carries you through endlessly long passages. "+
	"In the end you are dumped into a dungeon, a prison hole.\n");
}
*/
persuit(object who)
{
    int ran_num;

    ran_num=random(8);
    if(CAN_SEE(TO, who)) 
    {
	who->catch_msg(
	   	"The "+short()+" stares at you with deadly eyes and lifts "+
	    "his weapon ready to kill!\n");

	switch(ran_num)
	{
	    case 0:
		who->catch_msg(
		    "The Uruk-Hai says something a ugly troll language " +
            "and walks away.\n");
		break;
	    case 1:
		who->catch_msg(
		    "The Uruk-Hai throws his scimitar at you!!\n"+
		    "You scream in terror as crashes into your stomach!!!\n");
		who->heal_me(-500);
//		if (who->query_hp()<=0)
//		    who->do_die(TO);
//		go_home();
		break;
	    case 2:
        case 3:
		who->catch_msg(
		    "The Uruk-Hai attack you with renewed hate!\n");
/*
        imprison(who);
		go_home();
*/
		break;
	    case 4:case 5:case 6:case 7:
		who->catch_msg(
		    "The Uruk-Hai approaches you slowly.\n");
		break;
    }
    }
    else 
    {

	who->catch_msg(
	    "The Uruk-Hai swear some ugly curses and runs past you.\n");
	go_home();
    }
}

try_kill_me(object who)
{
    if(who && present(who, ETO) && CAN_SEE(TO, who)) {
	who->heal_hp(-500);
	if (who->query_hp() <= 0) {
	    tellem(who, TO,
		   "The ugly Uruk-Hai blocks $n's way!\n" +
		   "He then wounds $o with a " +
		   "deadly slash across the chest!!\n", 1);
	    who->do_die(TO);
	} else {
	    tellem(who, TO,
		   "The ugly Uruk-Hai blocks $n's way!\n" +
		   "One of them slashes $n with a deadly slash across " +
           "the chest!\n"+
		   "You get *very* hurt!!\n");
	}
    }
    else
	tellem(who, TO, "#N #curse violently!\n" +
	                "#N #snorl: I thought I could hear something!\n");
}

int
query_knight_prestige() { return 1200; }
