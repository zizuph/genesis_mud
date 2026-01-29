/*
 * /d/Sparkle/area/spiderlair/drops/epic/1_bp.c
 *
 * magical resistance breastplate vs light and life.
 * Nerull, 21/2/09.
 */


#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../../defs.h";

inherit "/std/armour";


// The creation of the armour.
void create_armour()
{

    set_name("breastplate");    
    set_adj("dimly");
    set_adj("violet-glowing");
    set_short("dimly violet-glowing breastplate");
    set_long("This dimly violet-glowing breastplate appears to give " +
    "very good protection for the torso.\n");
    set_ac(50);
    set_at(A_CHEST);
        
    add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
    "resistance to light and life magic.\n");
        
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
    add_prop(MAGIC_AM_ID_INFO, ({
    "This breastplate is enchanted by a protection " +
    "spell.\n", 10,
    "This breastplate protects the wearer from both " +
    "light and life magic.\n", 50}));
   
    set_af(TO);

    add_prop(OBJ_I_VALUE, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);   

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}


mixed query_magic_protection(string prop, object what)
{
    if (!worn || what != wearer || !stringp(prop))
        return 0;

    if (prop == MAGIC_I_RES_LIFE || prop == MAGIC_I_RES_LIGHT)
    {    		 
    		return ({MAGIC_SP_RESIST, 1});
    }
    		

		return 0;
}
	

int wear(object to)
{
    TP->catch_msg("You feel more shielded vs magical spells.\n");
    
    if (wearer)
        wearer->remove_magic_effect(TO);

    TP->add_magic_effect(TO);
    return 0;
}


int remove(object to)
{
    if (wearer == TP)
        wearer->catch_tell("You feel more vurneable to magical spells.\n");

    wearer->remove_magic_effect(TO);


    return 0;
}


void leave_env(object to, object from)
{
    ::leave_env(to, from);

    if (!living(from))
        return;

    from->remove_magic_effect(TO);
}


// If the item is dispelled/disenchanted.
int dispel_magic(int power)
{
    if (power < query_prop(MAGIC_I_RES_MAGIC))
        return 0;

    query_worn()->catch_tell("Your "+short()+" fades away!\n");    
    remove_broken(1);
    remove_object();
    return 1;
}