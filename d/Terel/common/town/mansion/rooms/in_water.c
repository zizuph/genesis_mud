/* Under the lattice, room filled with water. Mortricia 930501 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 72)
#define TP             this_player()
#define TO             this_object()
#define SCEPTRE        MORTRICIADIR+"camp/house/sceptre"

object sceptre;

init()
{
    ::init();
    add_action("do_swim", "swim");
}

void
create_room()
{
    set_short("Under water");
    set_long(BS(
        "You are under water.\n"
    ));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    seteuid(getuid(TO));
    sceptre = clone_object(SCEPTRE);
    sceptre -> move(TO);
    MONEY_MAKE_CC(1)->move(TO);
    MONEY_MAKE_SC(1)->move(TO);
    MONEY_MAKE_GC(1)->move(TO);
    MONEY_MAKE_PC(1)->move(TO);
}

do_swim(string where)
{
    if (strlen(where)) return 0;
    write("You swim around in the water.\n");
    say(QCTNAME(TP)+" swims around in the water.\n");
    return 1;
}
