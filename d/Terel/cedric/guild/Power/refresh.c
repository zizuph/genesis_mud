/**refresh**cedric**/
#pragma save_binary

inherit "/std/object";

/*				   ***********
 * A Song of Power 		   * Refresh *
 * for the Minstrels Guild	   ***********
 * Cedric 3/93
 */

#define BASE_FATIGUE_HEAL   10
#define BASE_CAST_TIME	    10
#define BASE_MANA_COST	    50
#define BASE_READ_SKILL	    10
#define PURPOSE_DESC    "As you read, you realize that this Song of Power is designed to refresh the recipient, draining away the day's fatigue with the sweet sound of music.\n"

#define LOG(str) setuid(); seteuid(getuid()); log_file("refresh_log", str + "\n");

#include "/d/Terel/cedric/guild/Power/power.h"

int query_mana_cost(int result);

/*
 * Function name:   do_song
 * Description:	    Takes info about the 'caster', processes that data, and
 *		    calls resolve_task to see if the spell succeeds. If so, 
 *		    heals the 
 * Arguments:	    performer - the minstrel attempting the song. Should be
 *				0 if a choir is invoking the song.
 *		    to_be_affected - object or list of objects to be affected
 *				     by the song.
 *		    guild - the guild stat of the performer(s)
 *		    dex - the DEX of the performer(s)
 *		    dis - the DIS of the performer(s)
 *		    vocal - the SG_VOCAL skill of the performer(s)
 *		    instrumental - the SG_INSTRUMENTAL skill of the performer
 *		    effect - an effectiveness multiplier..usually from choir, 
 *			     broken instrument, etc. IN PERCENT (ie x1 = 100%)
 * Returns:	    -1 if the song fails completely;
 *		    0 if the song couldn't be played;
 *		    1-20 if the song succeeds somewhat but with possible 
 *		    accompanying instrument damage.
 *		    >20 if the song succeeds completely.
 */
int do_song(mixed performer, mixed to_be_affected, int guild, int dex, 
	    int dis, int vocal, int instrumental, int effect)
{
    int	result, heal_amount, processed;
    object recipient;

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

    if (sizeof(to_be_affected) == 0)
    {
        recipient = performer;
    }
    else if (sizeof(to_be_affected) == 1)
    {
	recipient = to_be_affected[0];
    }
    else /* sizeof(to_be_affected) > 1 */
    {
	notify_fail("You may only refresh a single being.\n");
	return 0;
    }
    if (!living(recipient))
    {
	notify_fail("That cannot be refreshed!\n");
	return 0;
    }

    if (!present(recipient, environment(this_player())))
    {
        write("The Song of power dies in your throat when you realize " +
            "that your target is no longer here.\n");
        return 0;
    }

    LOG("Refresh (" + this_player()->query_real_name() + ")");
    LOG(sprintf("Dex: %3d Inst: %2d Dis: %3d Voc: %2d Guild: %3d", dex, instrumental, dis, vocal, guild));
    processed = (dex+instrumental)/2+(dis+vocal)/2+guild*2;
    LOG("Proc: " + processed);
    result = TP()->resolve_task(TASK_ROUTINE, ({ SKILL_VALUE, processed }));
    LOG("Res: " + result);
    if (result<0) return -1;
    recipient->add_fatigue(heal_amount =
			   (BASE_FATIGUE_HEAL+processed/10)*(effect/100));
    LOG("Heal: " + heal_amount);
    LOG("Mana: " + query_mana_cost(max(20, heal_amount)));

    if (performer)
    {
	recipient->CM("An uplifting melody drifts lightly upon the air, "
		      + "refreshing you in body and soul.\n");
	tell_room(environment(recipient),
		  QCTNAME(performer)+" plays an uplifting melody, and "
		  + QTNAME(recipient) + " seems "
		  + "refreshed by the music.\n", recipient);
    }
    else
    	recipient->catch_msg(BS("The uplifting music of the choir "
				+ "thunders through the air, recharging "
				+ "you in body and soul.\n"));

    return max(20, heal_amount);
}

/* How much mana does using this song drain? */
int
query_mana_cost(int result = -1) 
{
    if (result == -1)
	return BASE_MANA_COST;
    else
	return BASE_MANA_COST + result / 2;
}

public string
query_name()
{
    return "refresh";
}
