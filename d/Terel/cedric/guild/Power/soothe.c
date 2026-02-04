/**soothe**cedric**/
#pragma save_binary

inherit "/std/object";
#define BASE_HEAL           50
#define BASE_CAST_TIME       5
#define BASE_MANA_COST      10
#define BASE_READ_SKILL     20
#define PURPOSE_DESC        "As you read, you realize that this Song of " \
                          + "Power is designed to heal with a sweet " \
                          + "and soothing tune.\n"
#include "/d/Terel/cedric/guild/Power/power.h"

#define LOG(str) setuid(); seteuid(getuid()); log_file("soothe_log", str + "\n");

int query_mana_cost(int result);

/*                                      **********
 * A Song of Power                      * Soothe *
 * for the Minstrels Guild              **********
 * Cedric 3/93
 */

/*
 * Function name:   do_song
 * Description:     Takes info about the 'caster', processes that data, and
 *                  calls resolve_task to see if the spell succeeds. If so, 
 *                  heals the 
 * Arguments:       performer - the minstrel attempting the song. Should be
 *                              0 if a choir is invoking the song.
 *                  to_be_affected - an object or list of objects to be affected
 *                                   by the song.
 *                  guild - the guild stat of the performer(s)
 *                  dex - the DEX of the performer(s)
 *                  dis - the DIS of the performer(s)
 *                  vocal - the SG_VOCAL skill of the performer(s)
 *                  instrumental - the SG_INSTRUMENTAL skill of the performer(s)
 *                  effect - an effectiveness multiplier..usually from choir, 
 *                           broken instrument, etc. IN PERCENT (i.e. x1 = 100%)
 * Returns:         -1 if the song fails completely;
 *                  0 if the song couldn't be played;
 *                  1-20 if the song succeeds somewhat but with possible 
 *                  accompanying instrument damage.
 *                  >20 if the song succeeds completely.
 */
int
do_song(mixed performer, mixed to_be_affected, int guild, int dex, int dis, 
        int vocal, int instrumental, int effect)
{
    int         result, base_heal_amount, heal_amount, processed, mod_dex, mod_dis, res;

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
    
    if(!to_be_affected)
        to_be_affected = TP();
    if (pointerp(to_be_affected))
    {
        if (sizeof(to_be_affected)==1)
            to_be_affected = to_be_affected[0];
        else
        {
	    TP()->catch_msg("You may only soothe a single being.\n");
	    return 0;
        }
    }
    if (!living(to_be_affected))
    {
        notify_fail("That cannot be soothed!\n");
        return 0;
    }

    if (!present(to_be_affected, environment(this_player())))
    {
        write("The Song of Power dies in your throat when you realize " +
            "that your target is no longer here.\n");
        return 0;
    }

    LOG("Soothe (" + this_player()->query_real_name() + " -> " +
        to_be_affected->query_real_name() + ")");

    mod_dex = (dex > 100 ? 100 + ((dex - 100) / 2) : dex);
    mod_dis = (dis > 100 ? 100 + ((dis - 100) / 2) : dis);

    processed = (mod_dex+instrumental)+(mod_dis+vocal)+guild*2;
    LOG("Proc: " + processed);



    
    LOG(sprintf("Dex: %3d (%3d) Dis: %3d (%3d) Inst: %3d Voc: %3d Guild: %3d Target HPs: %4d",
        mod_dex, dex, mod_dis, dis, instrumental, vocal, guild, to_be_affected->query_max_hp()))

    result = TP()->resolve_task(TASK_ROUTINE - 100, ({ SKILL_VALUE, mod_dex,
						       SKILL_VALUE, mod_dis,
						       SKILL_VALUE, instrumental,
						       SKILL_VALUE, vocal,
						       SKILL_VALUE, guild * 2 }));

    LOG("Res: " + result);
    if (result<0) 
	return -1;
    base_heal_amount = min(200, (BASE_HEAL+processed)*(effect/100));
    res = to_be_affected->query_magic_res("_magic_i_res_healing");
    LOG("Res: " + res);

    heal_amount = base_heal_amount - base_heal_amount * res / 100;

    LOG("Heal: " + heal_amount);
    LOG("Mana: " + query_mana_cost(max(21, base_heal_amount)));

    to_be_affected->heal_hp(heal_amount);
    if (performer)
    {
        to_be_affected->CM(BS("The sweet tune rushes over your body, "
                              + "healing your wounds.\n"));
	tell_room(environment(to_be_affected), QCTNAME(performer)+" plays a "
		  + "soothing melody for "+QTNAME(to_be_affected)
		  + ", who seems to benefit thereby.\n", 
		  ({performer, to_be_affected}));
	if(to_be_affected != performer)
	    performer->catch_msg("You play a soothing melody for "+QTNAME(to_be_affected)+".\n");
    }
    else
    {
        to_be_affected->catch_msg(BS("The soothing music of the choir rolls "
				     + "powerfully over your wounds.\n"));
        tell_room(environment(to_be_affected), "The soothing music of the "
		  + "choir rolls over "+QTNAME(to_be_affected)+".\n", 
		  to_be_affected);
    }

    return max(21, base_heal_amount);
}

/* How much mana does using this song drain? */
int
query_mana_cost(int result = -1) 
{
    if (result == -1)
    {
        // temporary ugly hack until I can come up with a better way to handle
        // pre-cast mana checks.
        int guild,dex, dis, instrumental, vocal, mod_dex, mod_dis, processed,  heal_amount;

        dex = this_player()->query_stat(SS_DEX);
        dis = this_player()->query_stat(SS_DIS);
        instrumental = this_player()->query_skill(SG_INSTRUMENTAL);
        vocal = this_player()->query_skill(SG_VOCAL);
        guild = this_player()->query_stat(SS_LAYMAN);
        
        mod_dex = (dex > 100 ? 100 + ((dex - 100) / 2) : dex);
        mod_dis = (dis > 100 ? 100 + ((dis - 100) / 2) : dis);

        processed = (mod_dex+instrumental)+(mod_dis+vocal)+guild*2;
        heal_amount = max(21, min(200, (BASE_HEAL+processed)));

        return query_mana_cost(heal_amount);
    }
    else
	return BASE_MANA_COST + result / 2;
}

public string
query_name()
{
    return "soothe";
}
