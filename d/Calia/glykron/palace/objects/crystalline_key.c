/*      This is an object of the crystalline palace.

    coder(s):   Glykron
    history:
                 1.10.94    created                         Glykron
                28/9/96     made valueless                  Maniac

    purpose:    to give the council the ability to lock the front door

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/key";
#include <stdproperties.h>
#include "defs.h"

void
create_key()
{
    add_name("crystalline_key");
    set_key(CRYSTALLINE_KEY);
    set_adj("crystalline");
    set_long(
        "It is a large key made of crystalline.  " +
        "A faint white light glows from within.  " +
        "There is an inscription on the key.  " +
        "\n");
    add_prop(OBJ_I_VALUE, 0); 
}

int
do_read(string str)
{
    if (str != "inscription" && str != "inscription on key" &&
        str != "inscription on crystalline key")
        return 0;

    write(
        "Use this key only for the protection of Calians and their allies.  " +
        "Those who bring the key forth are responsible for any misuse.  " +
        "Only give this key to those who will keep it safe.  " +
        "\n\nCaliana\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}
