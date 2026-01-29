/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/r03.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("On a desert path");  
  set_long("You are travelling on a small path in the desert canyon. North of here, the desert "+
           "becomes greener of vegetation. Perhaps there is water there.\n");  

  add_item("path","It's small and narrow.\n");
  add_item("canyon","It's deep and impressive.\n");
  add_item("desert","You get thirsty just thinking on it...\n");
  add_item(({"rock","rocks"}),"Some are large and many are small and there's a lot of them "+
    "here!\n");

  OUTSIDE;

  add_exit(NOMAD+"r04","north", 0, 1);
  add_exit(NOMAD+"r02","south", 0, 1);
  reset_room();
}
