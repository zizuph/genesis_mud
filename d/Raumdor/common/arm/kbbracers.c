inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* dirty black bracers, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("sturdy");
    add_adj("black");
    set_short("pair of sturdy black bracers");
    set_pshort("pairs of sturdy black bracers");
    set_long("As you study these sturdy black bracers, you notice "+
        "a dreadful emblem etched on each arm piece: a grim skull.\n");
    set_ac(43);
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,4200);
    add_prop(OBJ_I_VALUE,75);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "These bracers have been slightly enchanted.\n", 5,
    "The enchantment on these bracers will add slightly more " +
    "protection to the wearer.\n", 50}));
    
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "These bracers adds 3 more in ac.\n");
}
