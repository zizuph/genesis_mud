/* 	This is the Calian history book.

    coder(s):   Glykron
    history:
                30.11.94    book made non-gettable          Maniac
                 5. 9.93    updated                         Glykron

    purpose:    to elucidate Calian history

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "defs.h"

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_scroll()
{
    set_name("book");
    set_adj("old");
    set_short("very old book");
    set_long("This old book is falling apart from age.\n" +
        "It is about Calian history.\n");
    set_file(TEXT("Calia_history"));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "The book seems to be fixed here by magic.\n");
}