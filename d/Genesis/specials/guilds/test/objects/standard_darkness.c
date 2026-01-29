/*
 * Standard Darkness Item for testing
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("standard_darkness_item");
    set_short("standard darkness item");
    set_long("This is a standard darkness item for use in testing.\n");
    add_prop(OBJ_I_LIGHT, -1);                     
}
