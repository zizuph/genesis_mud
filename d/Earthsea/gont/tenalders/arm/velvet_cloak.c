#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_armour()
{
    set_name("cloak");
    set_pname("cloaks");
    set_adj(({"red", "velvet"}));
    set_short("red velvet cloak");
    set_pshort("red velvet cloaks");
    set_long("A long flowing red velvet cloak. "+
        "When worn it extends from the high neck collar, all "+
        "the way down to the ankles. It can be swirled, to "+
        "flourish it around yourself.\n");
    set_default_armour(15, A_ROBE, ({-1, -1, -1}));
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200 + random(50));
}

public int
swirl_this(string str)
{
    object tp = this_player(), to = this_object();

    if(!present(to, tp))
        return 0;

    if(!id(str))
        return notify_fail("Swirl what?\n");

    if(to->query_worn() == tp)
    {
        write("You swirl the red velvet cloak around "+
            "yourself with a dramatic flourish.\n");
        tell_room(environment(tp), QCTNAME(tp) + " swirls the "+
            "ankle-length red velvet cloak around "+
            tp->query_objective() + "self, with a dramatic "+
            "flourish.\n", ({ tp }));
        return 1;
    }

    return notify_fail("You are not wearing the cloak.\n");
}

public void
init()
{
    ::init();
    add_action(swirl_this, "swirl");
}
