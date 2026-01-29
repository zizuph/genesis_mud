/*
 * Genesis Magic System Gem Converted Object.
 *
 * An object converted from a gem. This can be replaced by any object.
 * 
 * Created by Navarre, October 2010.
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    set_name("converted_object");
    set_short("simple converted object");

    set_long("This a simple object that was converted from a gem.\n");

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE, 1500);
}
