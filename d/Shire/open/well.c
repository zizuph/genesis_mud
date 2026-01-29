/*
 * This is a basic well where players can drink from it. It is based on the 
 * Greyflood river code in Gondor, /d/Gondor/tharbad/ford/f04
 * -- Finwe, July 2005
 */


/* This file contains all the necessary code to drink */
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void	drink_message(string from);

create_room()
{
    set_short("A grassy meadow");
    set_long("This is a grassy meadow. It looks nice and green. A large stone well stands in the middle of the grass.\nA large stone well.\n");
    
    add_item(({"meadow"}),
        "It is nice and grassy, with a large stone well in the center.\n");
    add_item(({"grass"}),
        "The grass is a rich green color and fills the meadow.\n");
    add_item(({"well", "stone well", "large well", "large stone well"}),
        "The well looks old but still useable. Perhaps you can drink from it if you are thirsty.\n");

/* sets where they can drink from, and the props to tell the 
 * game there is water here
 */
    set_drink_from( ({ "well", "stone well", "large stone well", 
        "large well", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
}

/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
    init_drink();

} 

/*
 * Function name:	drink_message
 * Description	:	do the msgs for drinking from river
 */
public void
drink_message(string from)
{
    write("You drink water from the well. It tastes cool and refreshing.\n");
    say(" drinks some water from well.");
} 

