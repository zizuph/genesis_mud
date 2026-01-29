#include "defs.h"

inherit CERAL_ROOM;

#include <options.h>

#define SCRNWDTH(ob) ((int)ob->query_option(OPT_SCREEN_WIDTH))

public static string dock_name = "";

string
dock_banner(string capname)
{
    return sprintf("%|" + SCRNWDTH(this_player()) + "s", capname);
}

string
dock_long(string capname, string name)
{
    return "\n" + dock_banner(capname) +
        "\n\n...the prominent sign reads, indicating that the ship to " +
        name + " lands at this dock.  Beyond, you can see that the " +
        "shores of this small island are almost entirely occupied by " +
        "docks.  Toward the center of the island stands a large " +
        "pavilion.\n";
}

string
dock_sign(string capname, string name)
{
    return "\n" + dock_banner(capname) + "\n\n" + sprintf("%|" + 
        SCRNWDTH(this_player()) + "s\n", 
        "The ship to " + name + " lands here.");
}

void
mkdock(string name)
{
    string capname = implode(map(explode(name, ""), capitalize), "");
    set_short(name + " dock");
    set_long(&dock_long(capname, name));

    add_item("dock", "The dock is laid with huge wooden planks, " +
        "extending out to the deeper waters beyond the shores " +
        "of the island where ships are able to anchor.  This " +
        "particular dock services the ship to " + name + ".\n");
    add_item(({ "sign", "prominent sign" }), &dock_sign(capname, name));
    add_cmd_item(({ "sign", "prominent sign" }), "read",
        &dock_sign(capname, name));

    dock_name = name;

    setuid();
    seteuid(getuid());
    SHIP_MGR->add_shipline(name, this_object());
}

void
create_dock_room()
{
}

nomask void
create_ceral_room()
{
    create_dock_room();
}

public void
ship_arrived(mixed to)
{
    SHIP_MGR->dock_ship(previous_object(), dock_name);
    all_inventory(this_object())->ship_arrived();
}

public void
ship_left(mixed from, mixed to)
{
    SHIP_MGR->undock_ship(previous_object(), dock_name);
    all_inventory(this_object())->ship_left();
}

public int
query_ceral_dock()
{
    return 1;
}

public string
query_dock_name()
{
    return dock_name;
}
