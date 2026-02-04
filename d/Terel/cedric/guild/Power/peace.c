/**pax**horatio**/

// 2004/03/20 Last update
// 2011/07/23 Lavellan - Fixed runtimes, hopefully.

#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/newmagic/resist";
#include <filter_funs.h>

#define BASE_CAST_TIME     10
#define BASE_MANA_COST     50
#define BASE_READ_SKILL    20
#define PURPOSE_DESC       "As you read the song, you see that the beauty of this music will bring peace to the room.\n"

#define LOG(str) setuid(); seteuid(getuid()); log_file("pax_log", str + "\n");

#include "/d/Terel/cedric/guild/Power/power.h"
/*                                *********
* A Song of Power                 *  Pax  *
* for the Minstrels Guild         *********
* Horatio Oliveira 11/93
* Substantial modifcations necessary because of more stringent
* guild regulations. Weakened Pax so that it only stops a single fight at
* a time, instead of enforcing peace throughout the room.
* 	-- Cedric 7/94
*/

/*
 * Function:   	do_song
 * Description: Takes info about the 'caster', processes that data, and
 *    		calls resolve_task to see if the spell succeeds. If so, 
 *   		stops all fights in the room.
 * Arguments:	performer - the minstrel attempting the song. Should be
 *			    0 if a choir is invoking the song.
 *    		to_be_affected - an object or list of objects to be affected
 *     				 by the song. If 0, player didn't specify..
 *     				 so either it doesn't apply (area effect)
 *     				 or the player meant himself/herself, or
 *     				 (in this case) player means current enemy.
 *    		guild - the guild stat of the performer(s)
 *    		dex - the DEX of the performer(s)
 *    		dis - the DIS of the performer(s)
 *    		vocal - the SG_VOCAL skill of the performer(s)
 *    		instrumental - the SG_INSTRUMENTAL skill of the performer(s)
 *    		effect - an effectiveness multiplier..usually from choir, 
 *     			 broken instrument, etc. IN PERCENT (i.e. x1 = 100%)
 * Returns:    -1 if the song fails completely;
 *    		0 if the song couldn't be played;
 *    		1-20 if the song succeeds somewhat but with possible 
 *    			accompanying instrument damage.
 *    		>20 if the song succeeds completely.
 */
int
do_song(mixed performer, mixed to_be_affected, int guild, int dex, int dis, 
	int vocal, int instrumental, int effect)
{
    object enemy, friend;
    int i,k;
    int result, processed, dis_amount;
    int resist;

    if(performer->query_prop(LIVE_I_STUNNED))
    {
        performer->catch_msg("You are too stunned to properly play your " +
            "instrument.\n");
        return 0;
    }

    if ((environment(performer)->query_prop(ROOM_M_NO_MAGIC_ATTACK)) ||
        (environment(performer)->query_prop(ROOM_I_NO_ATTACK))) {
        performer->catch_msg("Something about this place prevents you from "
                        + "completing your song.\n");
        return 0;       
    }

    setuid(); seteuid(getuid());
    LOG("Pax (" + this_player()->query_real_name() + ")");
    LOG(sprintf("Dex: %3d Inst: %2d Dis: %3d Voc: %2d Guild: %3d", dex, instrumental, dis, vocal, guild));
    processed = (dex+instrumental)+(dis+vocal)+guild*2;
    LOG("Proc: " + processed);
    performer->set_skill(SG_FAKE_SKILL, processed);
    result = performer->resolve_task(TASK_SIMPLE, ({ SG_FAKE_SKILL }));
    LOG("Res: " + result);
    performer->set_skill(SG_FAKE_SKILL, 0);
    if (result<0)
	return -1;

    /* New Pax Lite: */

    if (pointerp(to_be_affected) && (sizeof(to_be_affected) > 0))
    {
	if (sizeof(to_be_affected) > 1)
	{
	    performer->CM("You realize somewhat belatedly that Pax may "
		      + "only be played for a single being.\n");
            return -1;
	}
        
        if (objectp(to_be_affected[0]))
        {
            enemy = to_be_affected[0];
        }
    }

    else if (objectp(to_be_affected))
    {
        enemy = to_be_affected;
        if (!(enemy->query_attack()))
        {
            tell_room(environment(performer),
	          "Beautiful music fills the air, and a great peace "
	         + "falls over "+QTNAME(enemy)+". Then again, "
	         + enemy->query_pronoun()+" wasn't fighting to "
	         + "begin with...\n");
	    return 21;
        }
    }

    else
    {
	enemy = performer->query_attack();
    }

    if (!objectp(enemy))
    {
	performer->CM("Beautiful music fills the air, and a great peace "
		      + "descends upon you. Then again, you weren't fighting "
		      + "to begin with...\n");
	tell_room(environment(performer),
		  "Beautiful music fills the air, and a great peace "
		  + "seems to emanate from "+QTNAME(performer)+". "
		  + "Then again, " + performer->query_pronoun() +
		  " wasn't fighting to begin with...\n", performer);
	return 21;
    }

    resist = spell_resist(this_player(),
			  enemy,
			  SS_ELEMENT_AIR,
			  TASK_FORMIDABLE);

    friend = enemy->query_attack();
//    if ((friend = enemy->query_attack()) != performer)
    if ((friend) && (friend != performer))
    {
    // This is just here for debugging - Lavellan
    log_file("pax_debug ",sprintf("%s performer: %O  enemy: %O  friend: %O\n\n",
        ctime(time()),performer, enemy, friend));
	performer->stop_fight(enemy);
	enemy->stop_fight(performer);

	friend->stop_fight(enemy);
	enemy->stop_fight(friend);
	friend->CM("Beautiful music fills the air, and a great peace descends "
		   + "upon you and "+QTNAME(enemy)+".\n");
	enemy->CM("Beautiful music fills the air, and a great peace descends "
		  + "upon you and "+QTNAME(friend)+".\n");
	tell_room(environment(performer),
		  "Beautiful music fills the air, and a "
		  + "great peace descends upon "+QTNAME(friend)+" and "
		  + QTNAME(enemy)+".\n", friend, enemy);
    }
    else
    {
	performer->stop_fight(enemy);
	enemy->stop_fight(performer);

	performer->CM("Beautiful music fills the air, and a great peace "
		      + "descends upon you and "+QTNAME(enemy)+".\n");
	tell_room(environment(performer), "Beautiful music fills the air, and "
		  + "a great peace descends upon "+QTNAME(performer)+" and "
		  + QTNAME(enemy)+".\n", performer);
    }
    return result;
}

/* How much mana does using this song drain? */
int
query_mana_cost(int result) 
{
    return BASE_MANA_COST;
}

public string
query_name()
{
    return "pax";
}
