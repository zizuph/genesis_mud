#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(GUILD_ROOMS+"board","west",0);
    clone_object("/d/Genesis/obj/board")->move(TO);

    reset_dwarf_room();
}

string
short_descr()
{
    return "Common board within the Hall of Warriors";
}

string
long_descr()
{
    return "This small stone chamber at the back of the " +
    "Hall of Warriors is the place where notes concerning " +
    "the world of Genesis are placed for the Clan members " +
    "to read.\n";
}
