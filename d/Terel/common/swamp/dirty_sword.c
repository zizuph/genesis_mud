/*
 a dirty sword for the swamp redhaek 921103
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword"}));
    set_adj("dirty");
    set_short("dirty sword");
    set_long("A dirty short sword. The hilt is banged and dented, covered "+
                   "with dirt and grime. The blade is slightly tarnished and "+
                   "spots of black pepper it's length.\n");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This sword is made to be a stronger "+
                   "weapon in the hands of smaller players. The hit and "+
                   "pen increase from 20->42 in the hands of players below "+
                   "stat average 75.\n");
    add_prop(MAGIC_AM_MAGIC, ({55,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({ 55, 
                   "This ancient sword was enchanted to perform better "+
                   "in the hands of the small and inexperienced.\n"}));
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}

void enter_env(object into, object from)
{
    ::enter_env(into, from);

    if (!living(into))
        return;

    if(TP->query_average_stat() < 75)
    {
        TO->set_hit(42);
        TO->set_pen(42);
        write("A soft voice says: Wield me, I can help you.\n");
        return;
    }

    TO->set_hit(20);
    TO->set_pen(20);
}
