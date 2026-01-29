#pragma save_binary

inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void    add_stuff();
object  ranger;

void
create_room()
{
    set_short("A dark winding passage");
    set_long(BS("You are in a dark and narrow passage, with walls rough and "+
        "uneven. A set of stone steps descend into the dark passage here, while "+
        "the passage continues east. It is quite cold and dark here.\n"));

    add_exit(RANGER_ITH_DIR+"passage3","down","@@check_ranger");
    add_exit(RANGER_ITH_DIR+"passage5","east",0);
    add_item("walls","They are rough and unevenly cut.\n");
    add_item("passage","The passage continues in darkness east, but you see a\n"+
        "little light to the north.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_stuff();
}

void
add_stuff()
{
    if (!ranger)
    {
        ranger = clone_object(NPC_DIR+"i_ranger");
        ranger->move(this_object());
    }
}

void
reset_room()
{
    add_stuff();
}

void
accept_passage(object pl)
{
    if (present(ranger, TO))
        ranger->command("bow "+pl->query_real_name());
}

int
deny_passage(object pl)
{
    if (present(ranger, TO))
    {
        ranger->command("say Thou art not allowed to pass!");
        return 1;
    }
    return 0;
}

int
check_ranger()
{
    if (TP->query_wiz_level() || IS_RANGER(TP) ||
        TP->query_prop("ranger_ithilien_visitor"))
    {
        accept_passage(TP);
        return 0;
    }
    return deny_passage(TP);
}
