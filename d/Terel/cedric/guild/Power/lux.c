/**lux**cedric**/
#pragma save_binary

inherit "/std/object";
#define BASE_DURATION       60
#define BASE_ADD_LIGHT       2
#define BASE_CAST_TIME       5
#define BASE_MANA_COST      15
#define BASE_READ_SKILL     15
#define PURPOSE_DESC        "As you read, you realize that this Song of " \
                          + "Power is designed to brighten the area with an " \
                          + "enlightening tune.\n"

#define LOG(str) setuid(); seteuid(getuid()); log_file("lux_log", str + "\n");

#include "/d/Terel/cedric/guild/Power/power.h"
#include <stdproperties.h>

/*                                      *******
 * A Song of Power                      * Lux *
 * for the Minstrels Guild              *******
 * Cedric 3/93
 * Modified by Mortricia, June 1996, changed call_out to set_alarm
 */

/*
 * Function: remove_light
 * Eventually this will have to be replace with a more sophisticated
 * spell_effect object that provides the light while it's there and
 * goes away when the duration runs out or it gets dispelled.
 * Arguments - where = the room in which light was created.
 *           - light = the amount of light created.
 */
void
remove_light(object where, int light)
{
    tell_room(where, "The light fades away.\n");
    where->change_prop(ROOM_I_LIGHT,
                       where->query_prop(ROOM_I_LIGHT)-light);
    where->update_light(1);
}

/*
 * Function name:   do_song
 * Description:     Takes info about the 'caster', processes that data, and
 *                  calls resolve_task to see if the spell succeeds. If so,
 *                  heals the
 * Arguments:       performer - the minstrel attempting the song. Should be
 *                              0 if a choir is invoking the song.
 *                  to_be_affected - an object or list of objects to be
 *                                   affected by the song.
 *                  guild - the guild stat of the performer(s)
 *                  dex - the DEX of the performer(s)
 *                  dis - the DIS of the performer(s)
 *                  vocal - the SG_VOCAL skill of the performer(s)
 *                  instrumental - the SG_INSTRUMENTAL skill of the performer
 *                  effect - an effectiveness multiplier..usually from choir,
 *                          broken instrument, etc. IN PERCENT (i.e. x1 = 100%)
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
    int         result, light_created, processed;

    NF("Lux cannot be cast on an object or creature!\n");
    if (pointerp(to_be_affected))
    {
        if (sizeof(to_be_affected))
            return 0;
        to_be_affected = 0;
    }
    if (to_be_affected)
        return 0;

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

    LOG("Soothe (" + this_player()->query_real_name() + ")");
    LOG(sprintf("Dex: %3d Inst: %2d Dis: %3d Voc: %2d Guild: %3d", dex, instrumental, dis, vocal, guild));
    processed = (dex+instrumental)+(dis+vocal)+guild*2;
    LOG("Proc: " + processed);
    TP()->set_skill(SG_FAKE_SKILL, processed);
    result = TP()->resolve_task(TASK_ROUTINE, ({ SG_FAKE_SKILL }));
    LOG("Res: " + result);
    TP()->set_skill(SG_FAKE_SKILL, 0);
    if (result<0)
        return -1;
    environment(performer)->add_prop(ROOM_I_LIGHT,
                            environment(performer)->query_prop(ROOM_I_LIGHT)
                            + (light_created = (BASE_ADD_LIGHT*effect)/100));
    environment(performer)->update_light(1);
    if (performer)
    {
        performer->CM("As you play the enlightening tune, the very "
                      + "air around you begins to softly glow. With careful "
                      + "notes you coax the phosphorescence, teasing the "
                      + "light from the air, gradually expanding your Song "
                      + "to fill this place with the light of the Muses.\n");
        tell_room(environment(performer),
                  QCTNAME(performer)+" plays an "
                  + "enlightening tune, and the air around "
                  + TP()->query_objective()
                  + " begins to softly glow. "
                  + QCTNAME(TP()) + " plays on, seeming to "
                  + "coax the phosphorescence out of the very music. The "
                  + "Song of Power builds, and reaches a crescendo, and "
                  + "suddenly this place glows with a divine light!\n",
                  performer);
    }
    else
    {
        tell_room(environment(performer), "The choir plays an "
                  + "enlightening tune, and the air around "
                  + TP()->query_objective()
                  + " begins to glow. On plays the choir, and it seems "
                  + "as if they "
                  + "coax the phosphorescence out of the very power of the "
                  + "music. The "
                  + "Song of Power swells, and reaches a crescendo, and "
                  + "suddenly this "
                  + "place is filled with a divine light!\n");
    }
    set_alarm(itof((BASE_DURATION*effect)/100), -1.0,
              &remove_light(environment(performer), light_created));
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
    return "lux";
}
