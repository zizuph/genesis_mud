 /* The common board room in Tyr.
  * Decius, December 1997
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";

object board;
void reset_room();


void
create_room()
{
  ::create_room();
  set_short("A small dark cellar");
  set_long("This is a small cramped room hidden underneath the "+
           "draqoman headquarters. Hidden in the corner of the "+
           "cellar among the fluttering shadows is a board.\n");


  add_prop(ROOM_I_IS,1);
  add_prop(ROOM_M_NO_ATTACK,1);
  add_prop(ROOM_M_NO_MAGIC_ATTACK,1);
  add_prop(ROOM_I_NO_TELEPORT,1);
  add_prop(ROOM_I_NO_STEAL,1);

  add_exit(TYR_CARAVAN+"dragoman.c","up",0,1);

  reset_room();

}

void
reset_room()
{


  if(!board)
  {
    seteuid(getuid(this_object()));
    board=clone_object("/d/Genesis/obj/board");
    board->move(this_object());
  }

}


