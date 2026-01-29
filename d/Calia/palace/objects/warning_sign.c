/* 	gold armour for the gold room in the crystalline palace

    coder(s):   Glykron

    history:     9. 2.92    created                         Glykron
                 9. 2.92    modified                        Glykron

*/

#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>

string message;

int
read(string str)
{
    if(str != "sign")
    { 
	notify_fail("Read what ?\n");
	return 0;
    }
    write(message);
    return 1;
}

string
long()
{
    return message;
}

void
init()
{
    ::init();
    add_action("read", "read");
}

void
create_object()
{
    set_name("sign");
    set_short("sign by the north door");
    add_prop(OBJ_I_NO_GET, 1);
    message = "The sign reads:\nNo admittance!\n";
} 