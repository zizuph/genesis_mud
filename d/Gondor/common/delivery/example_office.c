/* This is a small example of what an office could look like. */

#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit DOFFICE;
inherit R_FILE

void
create_room()
{
    set_short("Office example room");
    set_long("You are in the delivery office example room. Here you can " +
	     "'ask for delivery tour', or 'deliver packet' or 'return packet'. " +
	     "There's an extra feature which allows you to pretend you're in " +
	     "another office, just type 'rename <new name>'.\n");
    office_name = "Neraka";
}

init()
{
    init_office();
    ::init();
    add_action("rename","rename");
}


int
rename(string str)
{
    office_name = str;
    write("Office name set to: '" + str + "'.\n");
    return 1;
}
