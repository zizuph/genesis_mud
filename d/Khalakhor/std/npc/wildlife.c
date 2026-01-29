/* File         : /d/Khalakhor/std/npc/wildlife.c
 * Creator      : Teth@Genesis
 * Copyright    : Daniel Mosquin
 * Date         : March 1, 1999
 * Purpose      : A base wildlife file, for land-based animals.
 * Related Files: /std/creature.c
 *                /d/Khalakhor/std/creature.c
 * Comments     :      
 * Modifications: Improved and updated - Teth, Jan 27 2002
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/properties.h"

inherit STDCREATURE;

public void
reset_khalakhor_wildlife()
{
}

public nomask void
reset_khalakhor_creature()
{
    reset_khalakhor_wildlife();
}

/* Function name:  create_khalakhor_wildlife
 * Description:    The constructor function
 *                 used to create the wildlife
 */
public void
create_khalakhor_wildlife()
{
}

/* Function name:  create_khalakhor_creature (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_wildlife to
 *                 create your creature.
 */
public nomask void
create_khalakhor_creature()
{
    set_name("_Khalakhor_wildlife");
    add_name("wildlife");
    add_name("animal");
    add_pname("animals");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);

    add_prop(LIVE_I_WILDLIFE, 1);

    create_khalakhor_wildlife();
    reset_khalakhor_creature();

}

/*
 * Function name: query_khalakhor_wildlife
 * Description  : Check to see if this is a Khalakhor wildlife.
 * Arguments    : n/a
 * Returns      : 1 - if a wildlife
 */
public int
query_khalakhor_wildlife()
{
    return 1;
}


