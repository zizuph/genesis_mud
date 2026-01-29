/* enemy list for dragonarmy guild
 * by Torqual
 * Description:
 * 		- 10 slots on each division's list
 * 		- no name check (if given by player) the fields
 * 		  can be empty if player will not fill 'em
 * 		- simple commands "report enemy to clerk",i
 * 		  "list enemies", "ask clerk to remove entry <nr>"
 * 		  "ask clerk to clear the whole list" :)i
 * 		  I know they are long but ...
 * 		- clerk in the office will ask questions and feel upi
 * 		  the papers (player will answer his
 * 		  questions in order to add enemy)
 * 		- wizzards (lords and GM) can change listi
 * 		  calling proper functions
 */

#pragma save_binary
#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "../guild.h"

#include <std.h>

/* defines */
#define GUILDMASTER	    (DRAGONARMY_LOG + "guildmaster")
#define ENEMYLIST_SAVE           (DRAGONARMY_LOG + "enemylist")
#define OBJ_ENEMYLIST_SAVE	    (DRAGONARMY_LOG + "obj_enemylist")
/* end of defines */
/* prototypes */
private mixed query_enemy(string div, int nr=0); // second arg can be ommited 
				   // it gives the whole list
private int add_enemy(string div, string name, string description,
		string guild, string level, string reason, mixed by_whom);
private int remove_enemy(string div, int nr);
private int clear_list(string div);
private int check_permission(mixed who);
/* end of prototypes */



/* THE CODE STARTS HERE */

/* Enemy maping:
 *
 * "div" : ([ "nr" : ({"name", "description", "guild", "level", "date", "reason", "by_whom",  ... })
 *
 *  where:
 *  	div		- div of reporting player
 *  			  (used to sort out the lists and proper display)
 *  	nr 		- entry number from 1 to 10
 *  	name		- given by reporting player
 *  			  (NO check if the name exist)
 *  	description	- as above
 *  	guild		- possible guild affiliations of enemy
 *  	level		- mortal level of enemy
 *  	date		- take automagicaly by function when enemy
 *  			  is reported (only wizzards will
 *  			  see it
 *  	reason		- why do they want him dead? short line
 *  	by_whom		- reporting player (auto)
 */
static mapping enemies = ([]); 

/*
 * Function:    save
 * Description: This function saves variables to savefiles.
 */
void
save()
{
    setuid();
    seteuid(getuid());
    save_object(OBJ_ENEMYLIST_SAVE);
    save_map(enemies, ENEMYLIST_SAVE);
}
/*
 * Function:    create
 * Description: This function is called when object is created.
 *    		It restores variables form savefiles and updates them.
 */
void 
create()
{
    setuid();
    seteuid(getuid());

    restore_object(OBJ_ENEMYLIST_SAVE);
    enemies = restore_map(ENEMYLIST_SAVE);
}
/* Function: load_list
 * Desc:     emergency load of the list
 */
void
load_enemies()
{
    setuid();
    seteuid(getuid());

    restore_object(OBJ_ENEMYLIST_SAVE);
    enemies = restore_map(ENEMYLIST_SAVE);

}
/* Function: check_permission
 * Description: we see if player/wiz has the right to toy with that object
 */
private int check_permission(mixed who)
{
	return 0;
}

/* Function: query_enemy
 * Desc:     here we check what do we have
 */
private mixed query_enemy(string div, int nr=0)
{
}
/* Function: add_enemy
 * Desc: wow, now they will be on our list and trembling.
 */

private int add_enemy(string div, string name, string description,
		string guild, string level, string reason, mixed by_whom)
{
}
/* Function: remove_enemy
 * Desc:     lets pardon the bastard, he will be more then happy
 */
private int remove_enemy(string div, int nr)
{
}
/* Function: clear_list
 * Desc: from time to time we need to clear things out
 */
private int clear_list(string div)
{
}

