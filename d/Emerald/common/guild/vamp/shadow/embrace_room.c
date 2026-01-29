/**
* This room is just an object to do the shadow add
* Louie  2006
*/

#pragma strict_types

inherit "/std/room.c";

#include "../guild.h"

//proto
varargs int make_new_vamp(object who, mixed sire, int offset, string coven);

void
create_room()
{
    set_short("vampire embrace room");

    set_long("This room is just an object to add the vampire shadow.  "+
        "\n");
    
}

/**
 *  set_alarm call to do the actual embrace.  We delay it to fix a bug
 *  with trying to shadow something from inside another shadow (or something
 *  to that effect).
 */
varargs void
make_new_vamp_delayed(object who, mixed sire, int offset, string coven) {
    set_alarm(0.5, 0.0, &make_new_vamp(who, sire, offset, coven));
}

/*
 * The actual making of a vampire.
 */
varargs void
make_new_vamp(object who, mixed sire, int offset, string coven) {
    object sh;
    int result;

    setuid();
    seteuid(getuid());
    
    catch(sh = clone_object(VAMP_SHADOW));
    if (sh)
    {
        result = sh->make_new_vamp(who, sire, offset, coven);
    }

    if (result != 1) {
        sh->remove_shadow();
        who->log_embrace("SHADOW FAILED - RESULT: "+result);
    }
}