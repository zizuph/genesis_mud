#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>

#define ROC_TEXT "/d/Earthsea/gont/gont_city/obj/roc_sign.txt"

public void
create_scroll()
{
    set_name("sign");
    set_short("wooden sign");
    set_long("You are looking at a wooden sign planted among "+
        "the boulders. It has some words engraved into the wood.\n");
    set_file(ROC_TEXT);
    add_prop(OBJ_I_NO_GET, 1);
}
