/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/nomads/p09.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"


void
create_room()
{
  set_short("On a path");  
  set_long("You're travelling a path in a very bushy area. There is a large mountain to "+
           "the northeast and from the south, you hear the sound of streaming water.\n");  

  add_item("path","It's small and narrow.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  add_item(({"bush","bushes"}),"The bushes are high and hinders the sight.\n");

  OUTSIDE;

  add_exit(W_TRADE+"r05","northeast", 0, 1);
  add_exit(NOMAD+"p08","northwest", 0, 1);
  reset_room();
}
