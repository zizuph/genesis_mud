/* message relay basefile by Milan
 * based on stone.c from arena stuff
 */


/* Navarre September 1st 2006, added stats to
 * avoid runtime error in /std/living.c
 */

#pragma strict_types
#pragma save_binary

inherit "/std/living";

#include <stdproperties.h>
#include <options.h>

public void
create_living()
{
    set_name("msg_relay");
    add_name("test");
    add_prop("_live_i_no_dragonfear", 1);
    add_prop(OBJ_I_NO_GET,1);
    set_no_show();
    /* Needed to avoid runtime error in living. */
    for(int i = 0; i < 6; i++)
        set_base_stat(i, 100);
    setuid();
    seteuid(getuid());
}

void catch_tell(string msg)
{
    catch_msg(msg, 0);
}

int
query_option(int opt)
{
    if(opt == OPT_GAG_MISSES)
	return 1;
    return 0;
}
