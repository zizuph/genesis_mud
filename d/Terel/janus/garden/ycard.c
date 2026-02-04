/*  sskin.c */
/*  janus 920701 */

inherit "/std/object";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>
//#include "/d/Terel/common/terel_std_rec.h"

#define EXPIRATION_DAYS     1

int expiration, first_received;

create_object()
{
    set_name("warning");
    set_long("This is a warning. Do it again and you will regret it.\n");
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 1);
}

/*
 * Function name: destroy_me
 * Description  : Destroys the item when it expires
 */
void
destroy_me(object player)
{   
    player->catch_vbfc("The " + short() + " slips out of " +
        "your hands and floats away on the wind.\n");

    set_alarm(0.5, 0.0, &remove_object());
}


/*
 * Function name: enter_env
 * Description  : Called when we enter an environment.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we are leaving.
 */
void
enter_env(object player, object from)
{
    ::enter_inv(player, from);
    if (first_received == 0)
    {
        expiration = time() + (EXPIRATION_DAYS*24*60*60);
        first_received = 1;
    }
    if (expiration < time())
    {
        set_alarm(0.2, 0.0, &destroy_me(player));
    }
}

/*
 * Function name: query_recover
 * Description  : Sets the keep state as well as the expiration
 *              : and first_received values so they are recovered properly.
 * Returns      : string - the recovery string.
 */
public string
query_auto_load()
{
    return MASTER + ":" + "&&" + expiration + "&&" + first_received;
}

/*
 * Function name: init_recover
 * Description  : Restores the initial expiration and first_received values
 * Arguments    : string - the recovery string.
 */
public void
init_arg(string arg)
{
    string *a = explode(arg, "&&");
    
    if (sizeof(a) > 1)
    {
        expiration = atoi(a[1]);
        first_received = atoi(a[2]);
    }
}
