/*
 * monster.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary

inherit "/std/monster";

/*****************************************************************************

SOME KIND OF EXCUSE FOR DOCUMENTATION

void introduce_me(){}      -- redefine this function to do some kind
                              of introduce when someone introduces themselves
                              to this monster

ROKE_I_RUN_FROM_DISEASE    -- if this prop is set, the monster will run away
                              from people affected by the whorehouse virus

help_friend(object ob)     -- called if someone attacks the monsters team.
                              redefine if you don't want it, or want
                              some other action


*****************************************************************************/



#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

string 	extra_long; 	/* Any extra long description set */
int has_introduced;

/*
 * Function name: create_monster
 * Description:   The standard create, do ::create_monster() to get these
 * 		  features
 */
void
create_monster()
{
    stats_to_acc_exp(); /* Set up correct xp */
    add_fatigue(30000); /* Not tired when starting */
    set_hp(50000); /* Fully healed when starting */
    set_mana(50000); /* Mana also full */

    remove_prop(NPC_M_NO_ACCEPT_GIVE); /* let them give stuff to us */

    add_leftover(ROKEDIR + "obj/skin", "skin", 1, "", 1, 1);
}

void introduce_me(){}
void remove_int(){}

void
add_introduced(string name)
{
    if (query_prop(LIVE_I_NEVERKNOWN))
        return;

    if (!has_introduced)
    {
        has_introduced = 1;
        set_alarm(6.0, 0.0, introduce_me);
        set_alarm(30.0, 0.0, remove_int);
    }
}


/*
 * Function name: attacked_by
 * Description:	  This function is called when somebody attacks this object
 * Arguments:	  ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
	arr[i]->notify_ob_attacked_me(this_object(), ob);    
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
	command("say Hey! Stop attacking my friends!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *		  attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(10))
	set_alarm(1.0, 0.0, &help_friend(attacker));
}
