/* Mirror in VK, by Teth, Jan 15 1997 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

public void
create_object()
{
    set_name("mirror");
    set_short("framed, silvered mirror");
    set_adj(({"framed","silvered"}));
    set_long("This silvered mirror is elegantly framed, with sweeping " +
        "scrolls of bronze surrounding it. It is leaning against the wall. " +
        "This mirror is frequently stared into, by those wishing to " +
        "inspect themselves. It is about two meters high.\n");
    AI(({"frame","elegant frame"}),"The elegant frame is made of bronze, " +
        "with a scrolled pattern.\n");
    AI(({"sweeping scrolls","scrolls","scrolled pattern","pattern"}),
        "Bronze and elegant, the scrolls surround the mirror.\n");
    AI("silver","The silver is flawless on the surface of the mirror.\n");
    AI(({"surface","mirror surface","silvered surface"}),"The surface " +
        "of the mirror reflects all light that enters it.\n");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_GET, "It is attached to the wall at the top, and the " +
        "floor at the bottom.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
}

init()
{
    ::init();
    ADA("stare");
}

int stare(string str)
{
    if ((str=="mirror")||(str=="into mirror")) 
    {
        write("Staring into the mirror, you see a reflection of " + 
            LANG_ADDART(TP->query_nonmet_name()) + " stareing back " + 
            "at you.\n");
        say(QCTNAME(TP)+ " stares into the mirror, seeing a reflection.\n");
        return 1;
    }
    NF("Stare where?\n");
    return 0;
}



