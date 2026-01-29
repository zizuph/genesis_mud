/*
 *  /d/Gondor/minas/obj/throne_stair_key.c
 *
 *  Key to the door of the White Tower of Ecthelion
 *
 *  Last modified by Alto, 20 April 2001
 *  Serif, April 21 2002: Modified not to fit on keyrings.
 */


inherit "/std/key";

#include <stdproperties.h>

public void
create_key()
{
   ::create_key();
   set_adj("small");
   add_adj("stone");
   set_pshort("small stone keys");
   set_long("This small stone key has a tree with seven stars upon the hasp.\n");
   set_key("New_Key_To_Tower_Stair");
   add_prop(OBJ_M_NO_STEAL, 1);
   add_prop("_key_i_no_keyring", 1);
}
