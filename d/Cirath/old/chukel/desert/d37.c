/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/desert/d35.c
* Comments: updated by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("In the eastern part of a desert");
  set_long("You're in the eastern part of a sand desert. You "+
    "wonder if anybody could live here. West of you "+
    "are some massive mountains and northeast, you can "+
    "see a hill of some kind.\n");

  OUTSIDE;

  add_exit(DES+"d36","west", 0, 6);
  add_exit(DES+"d39","east", 0, 6);
  add_exit(DES+"d38","south", 0, 6);
  	reset_room();
}
