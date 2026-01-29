// file name: /d/Avenir/common/dead/obj/rotted_cloth.c
// creator(s): Lilith, June 2021
// purpose:  for the crypt residents to drop
// note: 
// updates: 

inherit "/std/object";
#include "../dead.h"

void
create_object()
{
    set_name("cloth");
	set_adj("rotted");
	set_short("piece of rotted cloth");
	set_pshort("pieces of rotted cloth");
    set_long("This is a piece of cloth so old and dirty that "
	    +"it has rotted. It is mostly worthless, but could "
		+"probably be wrapped around a stick to make a "
		+"torch.\n");

  add_prop(OBJ_I_VALUE, 4);
  add_prop(OBJ_I_VOLUME, 500);
  add_prop(OBJ_I_WEIGHT, 10);

}
