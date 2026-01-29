/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"

void
create_object()
{
    set_name("seal");
    set_adj("Leiden's");
    set_short("Leiden's seal");
    set_long(BS("It's a little sticky piece of wax with the letter L "
          +  "marked on it.",SL));
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 4);

}


