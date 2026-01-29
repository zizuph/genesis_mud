/*  fixed \n at end of set_long  Amelia October 15, 1997 */

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("badge");
    set_short("badge");
    set_long("This is an authorization badge.\n");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    remove_prop(OBJ_I_VALUE);
}
