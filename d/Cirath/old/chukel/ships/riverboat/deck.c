/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ships/riverboat/cabin.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/d/Genesis/ship/deck";
#include "defs.h"

#define BOATS "/d/Cirath/chukel/ships/"

void
create_deck()
{
  set_short("On the puny river boat");
  set_name("water");
  set_long("You are standing on the deck of the puny riverboat. The boat is "+
    "made of wood and doesn't look very safe. But then, what could go "+
    "wrong on this little journey across the river?\n");

  add_exit(BOATS+"riverboat/cabin", "aft", 0, 1);

  add_prop("_room_i_no_dig",1);
}

