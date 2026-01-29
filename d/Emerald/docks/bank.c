inherit "/d/Emerald/std/room";

#include "defs.h"
#include <stdproperties.h>

public void
create_emerald_room()
{
    object deposit;
    set_short("Gnomes of Genesis Deposit, Ceral Island branch");
    set_em_long("A small, spartan lobby is separated from the vault " +
        "by a thick, stone wall.  Only a barred window provides access " +
        "to the service counter on the other side.\nA large sign is " +
        "prominently displayed.\n");

    add_item(({ "barred window", "window", "small window",
        "small barred window" }),  "A small, barred window opens in the wall " +
        "between the lobby and the vault.  On the other side, sitting at the " +
        "service counter, is a small, wizened gnome.\n");

    add_item(({ "counter", "service counter" }),
        "A small service counter is behind the barred window.  A small, " +
        "wizened gnome sits at it.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_door_exit(DOCK_DIR + "obj/bank_door", "pav4", "west");

    setuid();
    seteuid(getuid());
    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_no_show_composite(1);
    deposit->move(this_object(), 1);
}
