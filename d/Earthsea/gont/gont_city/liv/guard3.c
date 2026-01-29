/* 
* Standard guard for Gont Port
*
* Coded by Porta, Dec 97
* updated by Amelia to use basic_guard.c  2/98
*/

#pragma strict_types

inherit "/d/Earthsea/gont/gont_city/liv/basic_guard";

#include "basic_guard.h"
#include <money.h>

public void
create_guard()
{
    add_name("_guard3_");
    set_gender(random(1));
    set_levels(2);
    set_long(query_long() + capitalize(query_pronoun()) +
        " is a private first-class.\n");
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({ WEAPONS[random(sizeof(WEAPONS))], 
        HELM, RINGMAIL }));
}
