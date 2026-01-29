/* Rusty dagger by Teth, April 9, 96 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
    set_name(({"dagger", "knife"}));
    set_short("rusty dagger");
    set_adj("rusty");
    set_pshort("rusty daggers");
    set_long("This rusty dagger looks like it has been unused for years. "+
             "It's probably not worth much, but it appears that it might "+
             "still be a useful weapon.\n");
   set_default_weapon(10, 10, W_KNIFE, W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 700);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10));
}


