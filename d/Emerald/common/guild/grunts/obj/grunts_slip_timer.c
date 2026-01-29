/* This object controls whether you can slip in a pile of crap or not.  */
/* Coded 13/08/95 by Tulix III for use in the Grunts guild.             */

inherit "/std/object";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"

/* Prototype function */
public void do_notice_crap();

create_object()
{
    set_name("grunts_slip_timer");
    set_no_show();
}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       dest: destination environment
 *                  old:  previous environment
 */

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    dest->add_prop(LIVE_I_SLIP_POSSIBLE, 1);
    set_alarm( 4.0, 0.0, do_notice_crap);
    return;
}

/*
 * Function name:   do_notice_crap
 * Description:     prevent player from slipping in the goblin dung
 */
public void
do_notice_crap()
{
    set_this_player(ENV(TO));
    
    if (TP->query_prop(LIVE_I_SLIP_POSSIBLE))
    {
        TP->remove_prop(LIVE_I_SLIP_POSSIBLE);
        write("You realise that you might've slipped on that steaming " +
            "pile of goblin dung.\n");
    }
    TO->remove_object();    

    return;
}
