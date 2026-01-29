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
  set_short("In a desert close to a hill");
  set_long("You're in a desert, west of a large, but not "+
    "so very high, hill with boulders scattered all "+
    "over it.\n");

  OUTSIDE;

  add_exit(DES+"d33","west", 0, 6);
  add_exit(DES+"d32","northwest", 0, 6);
 // add_exit(HILL+"h01","northeast", 0, 6);
  	reset_room();
}
