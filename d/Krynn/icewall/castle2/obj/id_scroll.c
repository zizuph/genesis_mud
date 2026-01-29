/* Navarre June 11th 2006 Added add_item for handling "cast identify"
 * It gave runtime error before.
 */

inherit "/d/Genesis/specials/new/lib/spell_scroll";

#include "/d/Krynn/icewall/castle2/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>

void
create_spell_scroll()
{
    set_name("scroll");
    add_name("identify_scroll");
    set_adj("old");
    set_long("Some text is written on the old parchment.\n");

    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 254);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This is a scroll of identification.\n", 5,
        "The scroll can be recited over an item.\n", 20,
        "The spell can only be cast once and will require " +
        "a white pearl.\n", 40 }));
    add_prop(OBJ_S_WIZINFO, "An id scroll you can read and recite.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 35, "enchantment"}) );

    add_item("text", "It looks like some magical writing.\n");
    add_item(({"parchment", "old parchment"}), "It is a scroll of some sort.\n");
    set_file(OBJK + "id_txt");
    set_magic_obj_spell(OBJK + "id_spell");

    
    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);
}

public string
query_recover()
{
  return MASTER;
}
