/*
 * /d/Krynn/raceguild/obj/race_hider.c
 *
 * This is a tracker object for the guild to test if we are
 * suppressing the display of the racial guild subloc.
 */
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "../guild.h"

#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

public nomask void
create_object()
{
    set_no_show();

    set_name(RACE_HIDER_NAME);
    set_short(RACE_HIDER_NAME);
    set_long("This should not be visible, please <mail krynn> if you "+
        "are able to view this.\n");

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_S_WIZINFO,
	"Some Krynn Racial Guild types can hide their extra subloc "+
        "descriptions when this object is present.\n");
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function prevents all other objects from shadowing
 *                this object.
 * Returns      : int 1 - always.
 */
public nomask int
query_prevent_shadow()
{
    return 1;
}

/*
 * Function name: query_auto_load
 * Description  : Returns the path to the master object plus a dummy
 *                argument to ensure init_arg gets called.
 * Returns      : string - the path + arguments.
 */
public nomask string
query_auto_load()
{
    return MASTER + ":0";
}

/*
 * Function name: init_arg
 * Description  : Set the parameters of the object when auto-loading.
 * Arguments    : string arg - the argument to init.
 * Returns      : int 1 - delete upon recovery, 0 - keep.
 */
public nomask int
init_arg(string arg)
{
#ifndef ALLOW_SUBLOC_HIDING
    return 1;
#endif

    if (this_player()->query_guild_name_race() != GUILD_NAME)
        return 1;

    return 0;
}
