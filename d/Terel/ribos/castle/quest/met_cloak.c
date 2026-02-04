/*
   A cloak, suitable for a witch. Mortricia 920720
 */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include <macros.h>
create_armour()
{
    set_name("cloak");
    set_short("black cloak");
    set_adj(({"black"}));
    set_long(
   "This is a thin, black cloak that was once the property of " +
   "the great wizard Metaprat.  It was magical, but since the " +
   "great wizard Metaprat is gone, the magic that powers this cloak " +
   "is gone too.\n");

    set_default_armour(5, A_ROBE, 0, 0);
}
