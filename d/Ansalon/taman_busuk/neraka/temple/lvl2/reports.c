/* Stralle @ Genesis 050112
 * This room is supposed to be the office of reports for the PoT
 */
#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE + "std_temple.c";
inherit "/d/Ansalon/guild/pot/lib/reports.c";

void
create_temple_room()
{
    ::create_temple_room();
    
    set_short("The Office of Reports");
    set_long("Shelves containing parchments, scrolls and other assorted " +
        "papers line the walls. ");
    
    add_item(({"shelves", "scrolls", "papers"}), "@@exa_shelves");
    add_item(({"", ""}), "");
    add_cmd_item("sign", ({ "read" }), "@@read_sign@@");
    
    set_path(GUILDDIR + "doc/reports");

    add_exit( LVLTWO + "corr1.c", "south");
}

string
exa_shelves()
{
    return list_index(this_player());
}

string
read_sign()
{
    return "The following can be done here.\n";
}

void
init()
{
    ::init();
    
    init_reports();
}
