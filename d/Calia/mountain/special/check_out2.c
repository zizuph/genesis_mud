/* 
   Enter check for tunnel guards.

   Coded by Amelia and Maniac

   History:
         15/11/00      updated for better efficiency/elegance    Maniac 
         24/7/00       refined protection for Calians            Maniac 
          9/7/00       introduced protection for Calians         Maniac 
          31/7/98      check for applicants with tunnel access   Maniac 
          2/10/95      check for enemy now                       Maniac 
          16.5.95      enter_check changed to accept argument    Maniac 
          ??.??.??     created                                   Amelia 
*/ 


#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#define GUILD_NAME "Calian warrior's guild"
#define COUNCIL_CODE "/d/Calia/glykron/palace/specials/council_code"
#define RECRUITER_CODE "/d/Calia/glykron/palace/specials/recruiter_code"
#define LIVE_I_CALIAN_GUARD_CHECK_HP "_live_i_calian_guard_check_hp"

static int protect_calians_alarm = 0; 
static int no_attack_prop_checked = 0; 


int
is_calian(object living)
{
	return living->query_guild_member(GUILD_NAME);
}


int
enter_check(object player)
{
	object *team;
	int i;

	seteuid(getuid());

	if (COUNCIL_CODE->is_upstairs_banned(player) ||
          COUNCIL_CODE->is_enemy(player->query_real_name()))
	    return 0;

	if (is_calian(player) ||
          RECRUITER_CODE->query_tunnel_access(player->query_real_name()))
          return 1;

	/*	else, for all non-calians, check to see
		if they're teamed with a calian
	*/

	if (sizeof(team = player->query_team_others()))
		for (i = 0; i < sizeof(team); i++)
		{
			if ((is_calian(team[i]))&&
			(!COUNCIL_CODE->is_upstairs_banned(team[i])))
			    return 1;
		}

	return 0;
}


int
enter_live_check(object ob)
{
    return (living(ob) && enter_check(ob)); 
}


/* 
 * Function:     pulls_in
 * Description:  A hook, this function is called to move a player into
 *               the destination room on the other side of the door. 
 */
/*
   Commented out until this is converted to an inherited file
void
pulls_in(object player)
{
} 
*/ 


/* 
 * Function:     query_in_serious_danger 
 * Description:  returns 1 if the living is in serious danger, 0 
 *               otherwise. 
 * 
 */ 
int 
query_in_serious_danger(object living) 
{ 
     int last_hp = living->query_prop(LIVE_I_CALIAN_GUARD_CHECK_HP); 
     int now_hp = living->query_hp(); 
     int max_hp = living->query_max_hp(); 

     living->add_prop(LIVE_I_CALIAN_GUARD_CHECK_HP, now_hp); 

     return 
         (((last_hp - now_hp) >= ((max_hp * 3) / 10)) || 
          (((now_hp * 100) / max_hp) <= 37)); 
} 


/* 
 * Function:     protect_calians 
 * Description:  Get the guard to pull Calians and their team-mates 
 *               into the secret entrance if they are in danger. 
 */ 
void 
protect_calians() 
{ 
    int i; 
    object *liv = filter(all_inventory(this_object()), enter_live_check); 

    for (i = 0; i < sizeof(liv); i++) { 
        if (objectp(liv[i]->query_attack())) { 
            if (query_in_serious_danger(liv[i])) { 
                this_object()->pulls_in(liv[i]); 
                liv[i] = 0; 
            } 
        } 
        else {
            liv[i] = 0; 
        } 
    } 

    if (sizeof(filter(liv, objectp))) 
        protect_calians_alarm = set_alarm(6.0, 0.0, protect_calians); 
    else 
        protect_calians_alarm = 0; 
} 


/* 
 * Function:     attack_check 
 * Description:  called when there is an attempted attack or someone 
 *               enters the room, this sets an alarm to check whether 
 *               Calians in the room need protecting, and returns 0. 
 * 
 */ 
int 
attack_check() 
{ 
    if (!protect_calians_alarm) 
        protect_calians_alarm = set_alarm(6.0, 0.0, protect_calians); 
    return 0; 
} 


/* 
 * Function:    enter_calian_protection_room 
 * Description: called when an object enters this room. This 
 *              instance checks whether Calians need protecting 
 *              in combat. 
 */ 
void 
enter_calian_protection_room(object ob, object from) 
{ 
    if (living(ob)) { 
        if (enter_check(ob)) { 
            if (!no_attack_prop_checked) { 
                no_attack_prop_checked = 1; 
                if (!this_object()->query_prop_setting(ROOM_M_NO_ATTACK)) 
                    this_object()->add_prop(ROOM_M_NO_ATTACK, attack_check); 
            } 
            ob->add_prop(LIVE_I_CALIAN_GUARD_CHECK_HP, ob->query_hp()); 
        } 
        attack_check(); 
    } 
} 
