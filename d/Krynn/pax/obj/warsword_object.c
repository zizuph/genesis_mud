/*
 Jet black war-sword's special object. It lowers the wielder's 
 parry and defence skills for one minute (it is added to the
 wielder after he perform the swing).

 Coded by: Blizzard, 28/06/2003
 
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

#define  SKILL_EXTRA    5

int      time, alarm_id, skills_reduced;
int      parry, defence;

object       victim;
public void  restore_skills(object victim);
public void  reduce_skills(object victim);

create_object() 
{
    seteuid(getuid());
    set_name("War_Sword_Special");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

void
remove_warsword_special(object victim)
{
    object vict = victim; 

    if ( skills_reduced )
    {
        vict->catch_msg("You recover your firm defensive position.\n");
        restore_skills(vict);
        skills_reduced = 0;
    }
    
    remove_object();
}

/* Function name: remove_it_and_set_new_stun
 * Description: Almost the same what above, but not printing the message.
 *              Used, to set new stun object, when the player has one 
 *              already. 
 */
void
remove_it_and_set_new_penalty(object victim)
{
    object vict = victim; 

    if ( skills_reduced )
    {
        restore_skills(vict);
        skills_reduced = 0;
    }
    
    remove_object();
}

/* Function name: reduce_skills
 * Description  : This function lowers the wielder's skills.
 */
public void
reduce_skills(object victim)
{
    parry    = victim->query_skill(SS_PARRY);
    defence  = victim->query_skill(SS_DEFENCE);

    if ( (parry > 15) && (defence > 15) ) 
    {
        victim->set_skill_extra(SS_PARRY, 
            victim->query_skill_extra(SS_PARRY) - SKILL_EXTRA );
        victim->set_skill_extra(SS_DEFENCE, 
            victim->query_skill_extra(SS_DEFENCE) - SKILL_EXTRA );

        skills_reduced = 1;
    }        
    
}

/* Function name: restore_skills
 * Description  : This function restores skills of the wielder
 */               
public void
restore_skills(object victim)
{
    if ( skills_reduced )
    {
        victim->set_skill_extra(SS_PARRY, 
            victim->query_skill_extra(SS_PARRY) + SKILL_EXTRA);

        victim->set_skill_extra(SS_DEFENCE, 
            victim->query_skill_extra(SS_DEFENCE) + SKILL_EXTRA);
    }
    
}

void
do_warsword_special()
{
    int time;
    time = 60;     /* 1 minute */

    reduce_skills(victim);
    alarm_id = set_alarm(itof(time), 0.0, &remove_warsword_special(victim));

    time = 0;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
	remove_object();
	return;
    }

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
    do_warsword_special();
}
