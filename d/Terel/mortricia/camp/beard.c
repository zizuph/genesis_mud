/*
  A beard. Mortricia 920927
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
    set_name("hair");
    set_short("piece of hair");
    set_pshort("pieces of hair");
    set_long(BSN(
        "It's human hair, it looks as if it used to be a beard."
        ));
    set_adj("human");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}
