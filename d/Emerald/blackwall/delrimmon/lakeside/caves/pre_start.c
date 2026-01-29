#include "defs.h"

inherit MIST_TOWER_BASE;

#include "/d/Emerald/common/guild/vamp/guild.h"

#include <macros.h>

#define VOID ("/d/Emerald/blackwall/delrimmon/lakeside/caves/void")

void
create_tower_room()
{
    set_long("");
    set_short("");
    add_prop(OBJ_S_WIZINFO, "This is a staging area for vampires logging " +
        "in.  They are immediately moved out of this room once they enter.\n");
}

public void
move_out()
{
    object v, *vs;

    if (!(v = find_object(VOID)) || !sizeof(vs = filter(object_clones(v),
        &operator(==)(this_player()->query_real_name()) @ &->query_owner())))
    {
        setuid();
        seteuid(getuid());
        v = clone_object(VOID);
    }
    else
    {
        v = vs[0];
    }

    this_player()->move_living("M", v, 1, 1);
}
    
public void
init()
{
    ::init();

    move_out();
}
