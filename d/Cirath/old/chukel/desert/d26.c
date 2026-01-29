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
  set_short("In the middle of a desert");
  set_long("You're in the middle of a sand desert. You "+
    "wonder if anybody could live here. West of you "+
    "are some massive mountains and far east you can "+
    "see a hill of some kind.\n");

  OUTSIDE;

  add_exit(DES+"d20","west", 0, 6);
  add_exit(DES+"d27","south", 0, 6);
  	reset_room();
}
