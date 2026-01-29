/*
 * * /d/Sparkle/area/spiderlair/drops/uncommon/res_breastplate.c
 *
 * magical resistance breastplate.
 * Nerull, 21/2/09.
 */


#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../../defs.h";

inherit "/std/armour";

int dice_roll;

void create_armour()
{

    dice_roll = random(7) + 1;
    
    if (dice_roll == 1)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("black");
        set_short("black tungsten breastplate");
        set_long("This black tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to fire and water.\n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical fire and waterspells.\n", 50}));
    }
    
    if (dice_roll == 2)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("black");
        set_short("black tungsten breastplate");
        set_long("This black tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to light and life magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical light and life magic.\n", 50}));
    }
    
    if (dice_roll == 3)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("white");
        set_short("white tungsten breastplate");
        set_long("This white tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to death and cold magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical death and cold magic.\n", 50}));
    }
    
    if (dice_roll == 4)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("grey");
        set_short("grey tungsten breastplate");
        set_long("This grey tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to earth and air magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical earth and air magic.\n", 50}));
    }
    
    if (dice_roll == 5)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("green");
        set_short("green tungsten breastplate");
        set_long("This green tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to poison and illusion magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical poison and illusion magic.\n", 50}));
    }
    
    if (dice_roll == 6)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("blue");
        set_short("blue tungsten breastplate");
        set_long("This blue tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 30 magical "+
        "resistance to acid and electricity magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from both " +
        "magical acid and electricity magic.\n", 50}));
    }
    
    if (dice_roll == 7)
    {
        set_name("breastplate");    
        set_adj("tungsten");
        set_adj("silvery");
        set_short("silvery tungsten breastplate");
        set_long("This silvery tungsten breastplate appears to give " +
        "very good protection for the torso.\n");
        set_ac(50);
        set_at(A_BODY);
        
        add_prop(OBJ_S_WIZINFO, "This breastplate adds 20 magical "+
        "resistance to all magic.n");
        
        add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
        
        add_prop(MAGIC_AM_ID_INFO, ({
        "This breastplate is enchanted by a protection " +
        "spell.\n", 10,
        "This breastplate protects the wearer from all " +
        "magic.\n", 50}));
    }
    
    set_af(TO);

    add_prop(OBJ_I_VALUE, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);   

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}


void
query_dice()
{
	 write("Dice-roll was "+dice_roll+".\n");
	 return;
}
	 

mixed query_magic_protection(string prop, object what)
{
    if (!worn || what != wearer || !stringp(prop))
        return 0;


    if (dice_roll == 1)
    {    		
    		if (prop == MAGIC_I_RES_FIRE || MAGIC_I_RES_WATER)
    		{
    			 wearer->catch_tell("FIRE AND WATER.\n");       
    		 		  return ({30, 1});
    		}
    		return 0;
    }
    else
    
    if (dice_roll == 2)
    {    		
    		if (prop == MAGIC_I_RES_LIFE || MAGIC_I_RES_LIGHT)
    		{
    			    wearer->catch_tell("LIFE AND LIGHT.\n");
    		 		  return ({30, 1});
    		}
    		return 0;
    }
    else
    
    if (dice_roll == 3)
    {    		
    		if (prop == MAGIC_I_RES_DEATH || MAGIC_I_RES_COLD)
    		{
    			    wearer->catch_tell("DEATH AND COLD.\n");
    		 		  return ({30, 1});
    		}
    		return 0;
    }
    else
    
    if (dice_roll == 4)
    {    		
    		if (prop == MAGIC_I_RES_EARTH || MAGIC_I_RES_AIR)
    		{
    			    wearer->catch_tell("EARTH AND AIR.\n");
    		 		  return ({30, 1});
    		}
    		return 0;
    }
    else
    
    if (dice_roll == 5)
    {    		
    		if (prop == MAGIC_I_RES_POISON || MAGIC_I_RES_ILLUSION)
    		{
    			    wearer->catch_tell("POISON AND ILLUSION.\n");
    		 		  return ({30, 1});
    		}
    		return 0;
    }
    else
    
    if (dice_roll == 6)
    {    		
    		if (prop == MAGIC_I_RES_ACID || MAGIC_I_RES_ELECTRICITY)
    		{
    			    wearer->catch_tell("ACID AND ELECTRICITY.\n");
    		 		  return ({30, 1});
    		}
    	  return 0;
    }
    else
    
    if (dice_roll == 7)
    {    		
    		if (prop == MAGIC_I_RES_MAGIC)
    		{
    			    wearer->catch_tell("MAGICRESISTANCE.\n");
    		 		  return ({20, 1});
    		}
    		return 0;
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





int dispel_magic(int power)
{
    if (power < query_prop(MAGIC_I_RES_MAGIC))
        return 0;

    query_worn()->catch_tell("Your breastplate looses its enchant!\n");    
    remove_broken(1);
    return 1;
}