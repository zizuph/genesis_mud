/*
 * PELDOOR + h1key.c
 *
 * Varian - Aug 2021
 *
 */

#pragma strict_types
#pragma save_binary 

inherit "/std/key";
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";
inherit "/lib/keep";

#include <files.h>      
#include <macros.h>      
#include <std.h>           
#include <stdproperties.h>
#include "defs.h"    

#define OWNER     "varian"

/*public int            enter_env(object to, object from);*/

public void
create_key()
{
    ::create_key();

    set_name("key");
    add_name( ({"pel_h1_key", "pelargir key"}) );
    set_adj("steel");
    set_long("This appears to be a key to your house " +
        "in the city of Pelargir.\n");
    set_key("pel_h1_key");

    set_keep(1);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VALUE,   0);
}

/*
 * Function name: enter_env
 * Description  : Mask enter_env to remove the key if the key shouldn't
 *                be with this player. Allows wizards to clone keys.
 * Arguments    : object to - the destination
 *                object from - where it came from
 */
/*
public int
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(from))
        return 1;

    if (!MANAGER->query_is_breeh1(to->query_real_name()))
    {
        to->catch_tell("Oops! That iron key isn't yours! " +
          "It has been taken away for safe keeping!\n");
        set_alarm(0.3, 0.0, &remove_object());

        return 0;
    }

    return 1;
}
*/