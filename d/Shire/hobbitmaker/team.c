/*
 *   /d/Shire/hobbitmaker/team.c
 *
 *   This is the file that takes care of the teaming functions of the
 *   Shire hobbitmaker (assisting each other adding the hobbit_killer prop
 *   to players that attack hobbits making them outlaws wanted by the milita :)
 *   etc...)  This file was taken from /d/Shire/orcmaker/team.c and changed
 *   to fit the hobbit mentality rather than the original orc one.  Thanks 
 *   to Mayhem for coding the orcmaker and thus giving me the blueprints to 
 *   code this hobbitmaker.
 *
 *   Copyright (C)  Chad Richardson (a.k.a. Igneous)   Jan/21/96
 *
 *   Revisions:
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Shire/std/monster";

#include "/d/Shire/common/defs.h"
#include <formulas.h>
#include "hobbitmaker.h"

/* Prototypes */
void do_attack(object ob);
void help_friend(object ob);
void help_hobbit(object ob, object friend);
void call_for_friends(object ob);
void check_for_murderer(object player);
void check_status(string attacker);

//   Gobal Vars
int battle_alarm;

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    if (query_attack())
    {   
	::attacked_by(ob);
	return;
    }
    if (!ob->query_prop(HOBBIT_KILLER))
	ob->add_prop(HOBBIT_KILLER,1);
    command("shout Help this " + ob->query_nonmet_name() + " attacked me!!");
    command("wield all");
    call_for_friends(ob);
    if (!battle_alarm)
	battle_alarm = set_alarm(10.0,20.0,&check_status(ob->query_nonmet_name()));
    ::attacked_by(ob);
}

/*
 * Function name: attack_object
 * Description:   This function is called when we attack an object
 * Arguments:     ob - The object being attacked
 */
void
attack_object(object ob)
{
    command("wield all");
    if (!battle_alarm)
	battle_alarm = set_alarm(10.0,20.0,&check_status(ob->query_nonmet_name()));         ::attack_object(ob);
}

/*
 * Function name: call_for_friends
 * Description:   This function gets all this objects friends to help him.
 * Arguments:     ob - The attacker
 */
void 
call_for_friends(object ob)
{
    int i;
    object room, *arr;

    room = ENV(TO);
    while (!room->query_prop(ROOM_I_IS)) 
	room = ENV(room);
    arr = all_inventory(room);
    arr = filter(arr,"shire_hobbit_filter",TO);
    if (!sizeof(arr))
	return;
    for (i = 0; i < sizeof(arr); i++)
	arr[i]->notify_ob_attacked_friend(TO,ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - A friendly hobbit
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(10))
	set_alarm(itof(random(3)), 0.0, &help_friend(attacker));
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	if (!F_DARE_ATTACK(TO,ob))
	{
	    command("shout Help!! This "+ob->query_nonmet_name()+" is killing hobbits!");
	    return;
	}
	switch(random(5))
	{
	case 0:
	    command("say For all the "+TO->query_family_name()+"s of the Shire!!");
	    break;
	case 1:
	    command("say I do not like to fight, but I will defend myself and my kin"+
	      "from ruffians like you, my dear "+query_nonmet_name()+"!");
	    break;
	case 2:
	    command("say Leave at once I do not wish to harm you!");
	    break;
	case 3:
	    command("shout For the Shire!");
	    break;
	case 4:
	    command("say You shall regret this attack foul "+ob->query_race_name()+"!!");
	    break;
	}
	command("assist _hobbitmaker_hobbit");
    }
}


/*
 * Function name: shire_hobbit_filter
 * Description:   This function filter all the hobbitmaker hobbits in a room
 * Arguments:     hobbit - The object we want it figure out is a hobbit?
 */
int 
shire_hobbit_filter(object hobbit)
{
    if(hobbit->id("_hobbitmaker_hobbit")) return 1;
    return 0;
}


int 
query_not_attack_me(object att, int att_id)
{
    if (!random(10))
	call_for_friends(att);
    return 0;
}

/*
 * Function name: notify_ob_attacked_friend
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - A friendly hobbit
 *                attacker - The attacker
 */
void
notify_ob_attacked_friend(object friend, object attacker)
{
    if (query_attack())
	return;

    set_alarm(3.0,0.0,&help_hobbit(attacker,TO));
}

/*
 * Function name: help_hobbit
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_hobbit(object ob, object friend)
{
    if(ob && !query_attack() && present(ob, ENV(TO)) && CAN_SEE(TO,ob))
    {
	if (random(2))
	    command("shout For the Shire!!");
	else
	    command("shout For all the "+TO->query_family_name()+ 
	      (extract(TO->query_family_name(), -1) == "s" ? "" : "s" )+
	      " of the Shire!");

	set_alarm(1.0, 0.0, &do_attack(ob));
    }
}

/*
 * Function name: do_attack
 * Description:   Make this object attack 
 * Arguments:     victim - The object we are attacking
 */
void
do_attack(object victim)
{
    if (query_attack()) 
	return;
    if (victim->query_npc()) 
	return;
    if (!present(victim,ENV(TO)) || !CAN_SEE(TO,victim)) 
    {
	command("say Hey where did that "+victim->query_nonmet_name()+ " run off to?");
	return;
    }
    if (!F_DARE_ATTACK(TO,victim))
	command("cower");
    else
	command("kill "+ victim->query_real_name());
}

/*
 * Function name: init_living
 * Description:   Initilizes when a living comes around this object
 */
void
init_living()
{
    ::init_living();

    if (TO->query_hobbit_type() != MILITA && 
      TO->query_hobbit_type() != SHIRRIFFE)
	return;
    set_alarm(0.5,0.0,&check_for_murderer(this_player()));
}

/*
 * Function name: check_for_murderer
 * Description:   This function checks to see if we have a hobbit murderer
 * Arguments:     player - The player we are checking
 */
void
check_for_murderer(object player)
{
    if (player->query_prop(HOBBIT_KILLER) && CAN_SEE(TO,player))
    {
	switch(random(5))
	{
	case 0:
	    command("shout I've found, that "+player->query_nonmet_name()+
	      " that's been killing hobbits we were warned about!!!");
	    break;
	case 1:
	    command("say You will pay for your murdering ways sinster "+
	      player->query_nonmet_name()+"!!");
	    break;
	case 2:
	    command("say Kill this "+player->query_nonmet_name()+" "+
	      HE_SHE(player)+" has been known to kill our kin!");
	    break;
	case 3:
	    command("shout For the Shire!");
	    break;
	case 4:
	    command("say You will pay for your crimes, foul "+
	      player->query_nonmet_name()+".");
	    break;
	}
	do_attack(player);
	call_for_friends(player);
    }
}

/*
 * Function name: check_status
 * Description:   This function checks to see if the hobbit survived the battle :)
 * Arguments:     attacker - The non-met name of the attacker
 */
void
check_status(string attacker)
{
    object *arr;

    if (query_attack())
	return;

    remove_alarm(battle_alarm);
    battle_alarm = 0;
    arr = all_inventory(ENV(TO));
    arr = filter(arr,"shire_hobbit_filter",TO);
    arr -= ({TO});
    if (sizeof(arr))
    {
	command("cheer");
	tell_room(ENV(TO),QCTNAME(TO)+" gives "+QTNAME(arr[random(sizeof(arr))])+
	  " a high five.\n");
	command("say We teached that "+attacker+" a lesson or two!");
    }
    else
    {
	command("cheer");
	command("say That will teach that foul "+attacker+" to attack a hobbit.");
    }

    // Normal citizens etc.. don't wander around with weapons wielded.

    if (TO->query_hobbit_type() != MILITA && TO->query_hobbit_type() != FARMER &&
      TO->query_hobbit_type() != SHIRRIFFE)
    {
	command("unwield all");
    }
}




