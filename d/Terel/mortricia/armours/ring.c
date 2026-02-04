/*
    A gold ring. Mortricia 920910
 */

inherit "/std/armour";
#include "/sys/wa_types.h"

#include "/d/Terel/common/terel_defs.h"

#define BS(message)          break_string(message, 70)
#define TO                   this_object()
#define TP                   this_player()

create_armour()
{
    set_name("ring");
    set_short("golden ring");
    set_adj("golden");
    set_long(BS(
        "It's a golden ring, suitable for a finger.\n"
        ));

    set_default_armour(1, A_FINGERS, 0, 0);
}
