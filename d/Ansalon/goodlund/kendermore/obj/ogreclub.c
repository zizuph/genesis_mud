/* Very heavy club for Vincint the ogre, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"
inherit "/lib/keep";
inherit "/std/weapon";

create_weapon()
{
    set_name("mace");
    set_adj("spiked");
    add_adj("heavy");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("heavy spiked mace");
    set_long("This is a very heavy mace. It looks like it would take an " + 
        "ogre to wield it effectively.\n");
    set_default_weapon(28, 48, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({ "The weapon is enchanted.\n", 5, "It has been enchanted to " + 
           "strike deadly blows on the enemy.\n", 20}));
    add_prop(OBJ_M_NO_BUY, "The shopkeeper refuses to sell you the " + 
        "heavy spiked mace.\n");
    add_prop(OBJ_I_WEIGHT, 37000);
    add_prop(OBJ_I_VOLUME, 9000);
    set_keep(1);
}

