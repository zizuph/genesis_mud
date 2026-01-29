inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("horn");
   
    set_no_show_composite(1);
 
    add_prop(OBJ_M_NO_GET, "The horn is securely fastened to the post.\n");
}

public void
summon_eagle()
{
    object eagle;

    if ((sizeof(filter(all_inventory(environment()),
        &->query_kot_eagle())) >= 2) || !environment()->query_landing_open())
    {
        return;
    }

    setuid();
    seteuid(getuid());

    eagle = clone_object(KOT_EAGLE_DIR + "eagle");
    eagle->move_living(" lands", environment());
}

public int
blow(string str)
{
    if (str != "horn")
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    write("You blow the horn as loudly as you can.\n");
    say(QCTNAME(this_player()) + " blows the horn.\n");

    set_alarm(4.0, 0.0, summon_eagle);

    return 1;
}

public void
init()
{
    ::init();
    add_action(blow, "blow");
}
   
