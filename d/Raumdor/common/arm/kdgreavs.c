/*      /d/Raumdor/common/arm/kdgreavs.c
 *      Created by:     Sarr   
 *      Purpose:        
 *      Modified:       Toby, 971008 (fixed typo and plural)
 */

inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("sturdy");
    add_adj("black");
    set_short("pair of sturdy black greaves");
    set_pshort("pairs of sturdy black greaves");
    set_long("As you study these sturdy black greaves, you notice "+
        "a dreadful emblem etched on each leg piece: a grim skull.\n");
    set_ac(43);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,4200);
    add_prop(OBJ_I_VALUE,75);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
    "These greaves have been slightly enchanted.\n", 5,
    "The enchantment on these greaves will add slightly more " +
    "protection to the wearer.\n", 50}));
    
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    
    add_prop(OBJ_S_WIZINFO, "These greaves adds 3 more in ac.\n");
}
