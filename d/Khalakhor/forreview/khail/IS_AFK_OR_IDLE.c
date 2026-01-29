
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define NAME_WIZ capitalize(creator(this_object()))
#define TO this_object()
#define TP this_player()
#define NF(x) notify_fail(x)

public int
block_mortals()
{
    if (!this_player()->query_wiz_level())
        return 1;
    return 0;
}

void
create_room()
{
    set_short(NAME_WIZ + "'s workroom");
    set_long("You are on a vast battlefield.  The ground has risen slightly "+
	"here, you are atop a rocky hill which stands about thirty feet "+
	"above the battlefield.  Strewn about the battlefield like the "+
	"crumpled remains of warriors, some of demonic proportions. Broken "+
	"weapons and shattered armour lie scattered about, creating an "+
	"eerie blood-stained glow about the field from the reflections off "+
	"the setting sun.\n");
    add_exit("/d/Calia/khail/eldoral/mountain/mshore2", "shore", 
        "@@block_mortals@@");
    add_exit("/d/Genesis/start/human/town/tower","lobby");
    add_exit("/d/Calia/gelan/rooms/t_par", "tattoos",
        "@@block_mortals@@");
    add_exit("/d/Calia/khail/eldoral/ruins/south_entry", "castle",
        "@@block_mortals@@");
    add_exit("/d/Khalakhor/se_speir/port/room/th_1", "macdunn",
        "@@block_mortals@@");
}    

int
do_removeshadow(string str)
{
    this_player()->remove_autoshadow(str);
    return 1;
}

public int
do_battlefield(string str)
{
    object panel;

    NF("Battlefield what command?\n");
    if (!str || !strlen(str))
        return 0;

    str = lower_case(str);

    TP->command("say Battlefield " + str);

    reset_euid();

    if (str == "eldoral control")
    {
        write("Battlefield: Summoning Eldoral control panel.\n");
        tell_room(TO, "A strange panel rises out of the ground before " + 
            QTNAME(TP) + ".\n");
        panel = clone_object("/d/Khalakhor/khail/private/eldoral_control");
        panel->move(TO);
        return 1;
    }
    else if (str == "remove eldoral control")
    {
        panel = present("_eldoral_control_panel", TO);
        if (!panel)
        {
            NF("Eldoral control panel not present.\n");
            return 0;
        }
        write("Battlefield: Removing Eldoral control panel.\n");
        tell_room(TO, "The sinks into the ground and vanishes.\n");
        panel->remove_object();
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_removeshadow,"removeshadow");
    add_action(do_battlefield, "battlefield");
}

