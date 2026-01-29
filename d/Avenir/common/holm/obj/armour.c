// -*-C++-*-
// elven chainmail  /d/Avenir/common/holm/obj/armour.c
// creator(s):      Lilith  01/18/97
// purpose:         Elven-make chainmail for a Hunter shadow-elf
// last update:
// note:
// bug(s):
// to-do:

inherit "/std/armour";
#include "/d/Avenir/common/holm/holm.h"
#include <wa_types.h>
#include <formulas.h>


void
create_armour()
{
    set_name("mail");
    add_name(({"shirt", "chainmail"}));
    set_short("elven chainmail shirt");
    add_adj(({"steel", "chainmail", "chain", "link", "silk", "elven"}));
    set_long ("This chainmail shirt, expertly fashioned from tiny "+
        "links of steel looped intricately together, should provide "+
        "good protection from bladed weapons.  Its lightness "+
        "and obvious quality reveal it to be of elven make. It is lined "+
        "with finest silk.\n");
           /* I  S  B */
    set_am(({ 1, 2, -3}));
    set_at(A_BODY);
    set_ac(15 + random (5));
    
}

