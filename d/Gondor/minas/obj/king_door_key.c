/*
 *  /d/Gondor/minas/obj/king_door_key.c
 *
 *  Key to the door in the House of Kings
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
  set_adj("ancient");
  add_adj("iron");
  set_pshort("ancient iron keys");
  set_long("An ancient iron key.\n");
  set_key("Key_To_King_Door");
  add_prop(OBJ_M_NO_STEAL, 1);

}
