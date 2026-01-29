inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
    set_name("talisman");
    add_name("wyvern_talisman");
    set_short("feathered talisman");
    set_long("This strange talisman made of a dark wood " +
      "is carved to resemble a mythical winged beast of some " +
      "kind. Ancient runes run up along the serpents tail, and " +
      "are inlaid with silver. Eagle feathers have been attached " +
      "to the talisman strips of leather.\n");

    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 3500);
}
