/* Some nice monster help functions, and specific functions for Krynn
 *
 * //Nick
 */

inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>

int 	prestige; 	/* The prestige changing variable */
string 	extra_long; 	/* Any extra long description set */

#define GRAVE_CONTROLLER "/d/Krynn/solace/graves/controller"
#define SUBLOC		"_my_extra_long_for_monster"

/*
 * Function name: create_monster
 * Description:   The standard create, do ::create_monster() to get these
 * 		  features
 */
void
create_monster()
{
    if (IS_CLONE)
	set_alarm(2.0,0.0,"add_emote");
    stats_to_acc_exp(); /* Set up correct xp */
    add_fatigue(30000); /* Not tired when starting */
    set_hp(50000); /* Fully healed when starting */
    set_mana(50000); /* Mana also full */
}

/*
 * Function name: emote
 * Description:   Monsters should know how to emote
 * Arguments:     str - string to emote
 * Returns:       1
 */
int
emote(string str)
{
    write("You " + str + "\n");
    say(QCTNAME(this_object()) + " " + str + "\n");
    return 1;
}

/*
 * Function name: add_emote
 * Description:   obvious
 */
void
add_emote() 
{
    set_this_player(this_object());
    add_action("emote", "emote"); /* A monster must emote ofcourse :) */
}

/*
 * Function name: notify_you_killed_me
 * Description:   This functions is called when 'I' kill something
 * Arguments:     ob - The object I killed
 */
void
notify_you_killed_me(object ob)
{
    seteuid(getuid(this_object()));

    GRAVE_CONTROLLER->killed(this_object(), capitalize(ob->query_real_name()));
}

/*
 * Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:	  pres - the prestige, if > 0 it will add to the acc, if < 0
 *		  	 it will add to the stat.
 */
void set_knight_prestige(int pres) { prestige = pres; }

/*
 * Function name: query_knight_prestige
 * Description:	  Return the prestige this monster will affect a knight.
 * Returns:	  The prestige.
 */
int query_knight_prestige() { return prestige; }

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
	set_alarm(1.0,0.0,"help_friend", attacker);
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
	command("say You scum, stop fighting my friend!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}

/*
 * Function name: set_extra_long
 * Description:   Add an extra long description to the mobile 
 * Arguments:     str - The string
 */
void
set_extra_long(string str)
{
    extra_long = str;
    add_subloc(SUBLOC, this_object());
}

/*
 * Function name: show_subloc
 * Description:   This function is called to get the extra str
 * Arguments:     subloc  - The name of this sublocation
 *		  me      - this_object()
 * 		  for_obj - Who wants this description
 * Returns:	  The extra string to write
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return check_call(extra_long);
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

