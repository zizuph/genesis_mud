/*
gem.c
-----

Coded ........: 95/05/09
By ...........: Jeremiah

Latest update : 95/05/09
By ...........: Jeremiah


*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
    set_name(({"idol","_ansalon_wizard_idol_"}));
    set_adj("silver");
    add_adj("kraken");
    set_short("silver kraken idol");
    set_long("This foot high silver statue depicts one of the " +
      "evil denizens of the deep, the mythical kraken.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 7000);
}
