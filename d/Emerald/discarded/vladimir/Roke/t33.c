/*  Ged  & Gresolle */

inherit "/std/room";

object knight;

#include "/d/Roke/common/defs.h"
#include <macros.h>

create_room() {
 
  set_short("Castle in Re Albi");
  set_long("This is a small room in the tower. Above you is the lookout,\n"+
	   "which you can reach by climbing the small wooden ladder that\n"+
	   "is placed in the middle of the room.\n");

  add_item("ladder","It's a small ladder, made of wood. It looks very old.\n");
  add_exit(CASTLE+"c9","northeast",0);
  add_exit(CASTLE+"t43","up","@@block");
  call_out("reset_room",1);
}
reset_room()
{
  if(knight) return;
  
  tell_room(TO,"You feel slightly uncomfortable as the guard arrives.\n");

  knight = clone_object(CASTLE+"monster/towerg3");
  knight->move(TO);
}
int block()
{
  if(knight)
    {
      write("You try to climb the ladder, but the guard stops you!\n");
      say(QCTNAME(TP)+" tries to climb the ladder, but is brutally\n"+
          "stopped by the guard.\n");
      return 1;
    }
  return 0;
}
