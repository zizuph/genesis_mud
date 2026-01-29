/*
 *  /d/Gondor/minas/obj/fen_hollen_key.c
 *
 *  Key to the Fen Hollen of Minas Tirith
 *
 *  Original code by Elessar (1992)
 *
 *  Last modified by Alto, 08 April 2001
 *       Minor descriptive changes.
 */


inherit "/std/key";
#include <stdproperties.h>


create_key()
{
  ::create_key();
  set_adj("iron");
  set_adj("large");
  set_pshort("iron keys");
  set_long("This iron key has almost no scratches on it from lack of use.\n");
  set_key("Key_To_Fen_Hollen");
  add_prop(OBJ_M_NO_STEAL, 1);
  add_name("_fen_hollen_key_");


}
