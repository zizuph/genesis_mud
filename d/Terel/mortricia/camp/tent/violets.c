/*
  A bouquet of violets. Mortricia 920927
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

create_object()
{
    set_name("violets");
    set_pname("violets");
    set_short("bouquet of violets");
    set_pshort("bouquets of violets");
    set_long(BSN(
        "It's a lovely bouquet, and it smells good too."
        ));

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
}
