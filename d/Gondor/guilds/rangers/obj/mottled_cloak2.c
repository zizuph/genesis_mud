/*
 *  RANGERS_OBJ + "mottled_cloak.c"
 *    
 *  Original code by Elessar
 *  Modification log:
 *    Alto, February 2002. Modified for ranger recode.
 *    Gwyneth, June 2004. Common cloak for all 3 guild houses.
 *    Tigerlily, Dec. 2004: mottled cloak, added concealment
 *        functions when cloak is pinned.
 */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#include <macros.h>
#include <stdproperties.h>

inherit (RANGERS_OBJ + "conceal_cloak_base2");

string extraline();

public void
create_robe()
{
    string extra_line;

    set_name("cloak");
    set_adj("mottled");
    add_name("_mottled_cloak_");
    set_short("mottled cloak");
    set_colour("");
    set_long("This is a hooded cloak made of heavy cloth. " +
        "To help the wearer to walk unseen in dark forests and " +
        "wilderness, the cloak is mottled with spots of colour " +
        "in grey, green and brown for better camouflage. It is " +
        "large enough to fit over a normal cloak or cape." +
        extraline());

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

string
extraline()
{
    object tp = this_player();
    if (RANGERS_FULL_MEMBER(tp))
        return
        " There is a mask attached within the hood " +
        "for concealment of the face and head.\n";
    return "\n";
}
