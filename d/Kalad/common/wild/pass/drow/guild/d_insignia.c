// file name:        /d/Avenir/drow/guild/d_reshadow
// creator(s):       Nikklaus, Mar'97
// revision history: Don't expect to have one, this object will be discarded 
//                   after it's no longer necessary.
// purpose:          We're switching the Drow of Undraeth's regular drow_shadow
//                   with new Folger's Crystals. Let's see if they notice the
//                   difference...
// notes:            When we're ready to make the transition, wel'll copy this
//                   over the autoloading d_insignia in Kalad, and members
//                   should seamlessly switch during logon.
// to-do:            Delete this in a few months.
// bug(s):
/*
 * Guild is closed and not returning.
 * New racial was opened in Faerun.
 * 	- Lucius, June 2017
 */
# pragma strict_types
# include <ss_types.h>
# include <macros.h>

# define PREV_SOUL "/d/Kalad/common/wild/pass/drow/guild/drow_soul"
inherit "/std/object";

public void
enter_env(object to, object from)
{
    seteuid(getuid());
    ::enter_env(to, from);
    to->remove_cmdsoul(PREV_SOUL);
    to->remove_guild_race();
    to->clear_bit(4, 5);
    to->clear_guild_stat(SS_RACE);
//    clone_object("/d/Avenir/drow/d_reshadow")->move(to);
    remove_object();
}

#if 0
string
query_auto_load()
{
    return MASTER + ":";
}
#endif
