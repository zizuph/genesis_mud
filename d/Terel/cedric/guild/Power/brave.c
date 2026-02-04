/**bravuro**horatio**/
#pragma save_binary

inherit "/std/object";
#include <ss_types.h>
#define BASE_DIS     		10
#define BASE_CAST_TIME     	5
#define BASE_MANA_COST     	20
#define BASE_READ_SKILL    	20
#define PURPOSE_DESC       	"As you read through the song, you realize that this Song of Power will encourage you and your companions before battle.\n"

#include "/d/Terel/cedric/guild/Power/power.h"
/*                                *********
 * A Song of Power                 *Bravuro*
 * for the Minstrels Guild         *********
 * Horatio Oliveira 10/93
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
    object *tt;
    int i,jm,low_dis;
    int result, processed, dis_amount;
    mixed joe;
   
    if(performer->query_attack())
    {
	performer->catch_msg("The Muses will not answer this song while "
			     + "in battle.\n");
	return 0;
    }

    if(performer->query_prop(LIVE_I_STUNNED))
    {
        performer->catch_msg("You are too stunned to properly play your " +
            "instrument.\n");
        return 0;
    }

    if ((environment(performer)->query_prop(ROOM_M_NO_MAGIC)))
    {
        performer->catch_msg("Something about this place prevents you from "
                        + "completing your song.\n");
        return 0;       
    }

    if(!to_be_affected)
    {
	to_be_affected = allocate(1);
	tt = performer->query_team_others();
	if(sizeof(tt)>0)
	{
        to_be_affected = filter(tt, &present(, environment(this_player())));
	    to_be_affected += ({TP()});
	    jm = 0;
	}
	if(sizeof(tt)==0)
        {
	    to_be_affected = TP();
	    jm = 1;
        }
    }
    processed = (dex+instrumental)+(dis+vocal)+guild*2;
    TP()->set_skill(SG_FAKE_SKILL, processed);
    result = TP()->resolve_task(TASK_SIMPLE, ({ SG_FAKE_SKILL }));
    TP()->set_skill(SG_FAKE_SKILL, 0);
    if (result<=0) return -1;
    dis_amount = BASE_DIS * result / 100 * effect / 100;

    if(!jm)
    {
	for(i=0;i<sizeof(to_be_affected);i++)
	{
	    //low_dis = (to_be_affected[i]->query_stat(5))-1;
        low_dis = 10 + to_be_affected[i]->query_base_stat(SS_DIS) / 10;
	    if(low_dis < dis_amount)
		to_be_affected[i]->add_tmp_stat(5,low_dis,(guild*2)/5);
	    else
		to_be_affected[i]->add_tmp_stat(5,dis_amount,(guild*2)/5);
	}
    }
    if(jm)
    {
        low_dis = 10 + to_be_affected->query_base_stat(SS_DIS) / 10;
	if(low_dis < dis_amount)
	    to_be_affected->add_tmp_stat(5,low_dis,(guild*2)/5);
	else
	    to_be_affected->add_tmp_stat(5,dis_amount,(guild*2)/5);
    }

    if(performer)
    {
	if(jm)
	{
	    performer->catch_msg("You feel the power of the Muses fill your "
				 + "heart as you prepare for battle.\n");
	    tell_room(environment(performer),QCTNAME(performer)
		      + " plays a powerful Battle Song as "
		      + performer->query_pronoun()
		      + " prepares for battle.\n", performer);
	}
	if(!jm)
	{
	    to_be_affected->catch_msg("A powerful Song of Battle fills the "
				      + "air and strengthens your heart as "
				      + "you and your companions prepare for "
				      + "battle.\n");
	    tell_room(environment(performer),QCTNAME(performer)
		      + " plays a powerful Battle song in preparation for "
		      + "battle.\n",to_be_affected);
	}
    }
    
    return dis_amount;
}

/* How much mana does using this song drain? */
int
query_mana_cost(int result) 
{
    if (result == -1)
	return BASE_MANA_COST;
    else
	return BASE_MANA_COST + result;
}


public string
query_name()
{
    return "bravuro";
}
