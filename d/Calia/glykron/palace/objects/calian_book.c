/* 	This is the Calian guild book.

    coder(s):   Glykron
    history:
                 5. 9.93    updated                         Glykron

    purpose:    to explain calian abilities

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
    set_short("book chained to the wall");
    set_long("This book has a while cover.\n" +
        "Its title is Calian Abilities.\n");
    set_file(TEXT("calian_abilities"));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
        "The book cannot be taken, as it is chained to the wall.\n");
}