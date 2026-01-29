/*
 *  /d/Gondor/minas/obj/gate_seven_key.c
 *
 *  Key to the Seventh Gate
 *
 *  Last modified by Alto, 28 April 2001
 *
 */


inherit "/std/key";

#include <stdproperties.h>



public void
create_key()
{
  ::create_key();
  set_adj("tree-shaped");
  add_adj("silver");
  set_pshort("tree-shaped silver keys");
  set_long("This silver key is designed to resemble a tree.\n");
  set_key("Key_To_Seventh_Gate");
  add_prop(OBJ_M_NO_STEAL, 1);


}
