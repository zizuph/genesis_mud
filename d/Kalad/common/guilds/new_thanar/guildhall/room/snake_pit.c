/**********************************************************************
 * - snake_pit.c                                                    - *
 * - Holds the messenger snakes - not open to mortals               - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#include "../guild.h"
#include <stdproperties.h>
inherit THANAR_STD_ROOM; 


/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
public void
create_std_thanar()
{
    set_short("a snake pit");
    set_long("This is massive snake pit. Blech.\n");
    add_item(({"room", "area"}), query_long);


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}
