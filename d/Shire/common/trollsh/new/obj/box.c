inherit "/std/receptacle";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

void get_letter();

void
create_receptacle()
{
    FIXEUID

    set_name("box");
    set_adj(({"small","wooden"}));
    set_short("small wooden box");
    set_long("This small wooden box looks old and in poor condition. "+
        "It comfortably fits in the palm of your hand and seems to "+
        "have a lid that can be flipped up.\n");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 50);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 1000);
    add_prop(CONT_I_RIGID, 1);

    get_letter();
}

void
get_letter()
{
    object letter = clone_object(NEW_SHAWS_OBJ_DIR+"letter");
    letter->move(TO);
    add_prop(CONT_I_CLOSED, 1);
}
