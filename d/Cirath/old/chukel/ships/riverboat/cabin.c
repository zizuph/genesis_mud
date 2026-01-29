/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ships/riverboat/cabin.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/d/Genesis/ship/cabin";
#include "defs.h"

#define BOATS "/d/Cirath/chukel/ships/"

void
create_cabin()
{
    set_short("A little cabin on a small river boat");
    set_long(", made of wood.");

    add_exit(BOATS+"riverboat/deck", "out", 0);

    add_prop("_room_i_no_dig",1);
}
