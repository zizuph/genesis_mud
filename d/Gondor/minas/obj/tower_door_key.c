/*
 *  /d/Gondor/minas/obj/tower_door_key.c
 *
 *  Key to the door of the White Tower of Ecthelion
 *
 *  Last modified by Alto, 20 April 2001
 *
 */


inherit "/std/key";

#include <stdproperties.h>


public void
create_key()
{
  ::create_key();
  set_adj("heavy");
  add_adj("golden");
  set_pshort("heavy golden keys");
  set_long("This golden key has a tree with seven stars upon the hasp.\n");
  set_key("Key_To_Tower_Door");
  add_prop(OBJ_M_NO_STEAL, 1);

}
