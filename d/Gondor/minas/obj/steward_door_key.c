/*
 *  /d/Gondor/minas/obj/steward_door_key.c
 *
 *  Key to the door of the House of Stewards
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
  add_adj("stone");
  set_pshort("ancient stone keys");
  set_long("An ancient stone key.\n");
  set_key("Key_To_Steward_Door");
  add_prop(OBJ_M_NO_STEAL, 1);

}
