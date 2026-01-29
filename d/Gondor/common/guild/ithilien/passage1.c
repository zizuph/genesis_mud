/*
 * /d/Gondor/common/guild/ithilien/passage1
 *
 * Modification log:
 *  3-Dec-1996, Olorin: Typo fix, some cosmetic changes.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
private int    check_passage();

static object  Ranger;

public void
create_room()
{
    set_short("a dark winding passage");
    set_long(BS("You are in a dark and narrow passage, with walls rough and "
      +	"uneven. The passage turns around a corner here, leading north and "
      + "east. You hear the sound of water to the north, rushing and splashing. "
      +	"A flight of wet steps leads up here.\n"));
    add_prop(ROOM_I_INSIDE,1);
    add_exit(RANGER_ITH_DIR+"window",   "north", check_passage, 0);
    add_exit(RANGER_ITH_DIR+"passage2", "east",  0);
    add_exit(RANGER_ITH_DIR+"post",     "up",    0, 2);
    add_item("walls","They are rough and unevenly cut.\n");
    add_item("passage","The passage continues in darkness east, but you see a "+
	     "little light to the north.\n");
    add_item("steps","The steep flight of steps lead up from here. The steps "+
	     "are quite wet.\n");
    add_prop(ROOM_I_LIGHT,0);
    reset_room();
}

public void
reset_room()
{
    if (!objectp(Ranger))
    {
        Ranger = clone_object(NPC_DIR+"i_ranger");
	Ranger->add_prop(LIVE_I_SEE_DARK, 1);
        Ranger->move_living("down", TO);
    }
}

private void
accept_passage(object pl)
{
    if (present(Ranger, TO))
        Ranger->command("bow "+pl->query_real_name());
}

private int
deny_passage(object pl)
{
    if (present(Ranger, TO) && CAN_SEE_IN_ROOM(Ranger) && CAN_SEE(Ranger, pl))
    {
        Ranger->command("say Thou art not allowed to enter here!");
        return 1;
    }
    return 0;
}

public int
check_passage()
{
    if (TP->query_wiz_level() || IS_RANGER(TP) ||
        TP->query_prop("ranger_ithilien_visitor"))
    {
        accept_passage(TP);
        return 0;
    }
    return deny_passage(TP);
}
