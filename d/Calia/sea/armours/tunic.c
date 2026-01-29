/*  file:  /d/Calia/sea/armours/tunic.c
 *  description:  Tunic worn by the unlucky fisherman on beach
 *  coder:  Tigerlily
 *  date:  2002-02-25
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("tunic");
    set_short("brown homespun tunic");
    set_long("A short-sleeved tunic that is made from"+
      " some kind of brown homespun fabric. It is old and"+
      " has been crudely patched in spots. It covers the"+
      " upper part of the body and extends to the knees.\n");
    add_adj(({"brown", "homespun"}));
    set_ac(4);
    set_am(({   -2,     1,      1 }));
    set_at(A_ROBE); 
    add_prop(OBJ_I_VALUE, 123);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
}



