/*
 *  /d/Sparkle/area/tutorial/arm/demon_armour.c
 *
 *  The file for armours worn by the demon guards in Kroloks castle.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this armour is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

/* Definitions */
#define        DEMON_AC     20    /* the ac rating of the armour */

/* Global Variables */
public string        Armour_Type = "";   /* what class of armour is it? */

/* Prototypes */
public void        create_demon_armour();
public void        create_armour();
public void        configure_it();

public void        set_da_type(string s) { Armour_Type = s; }
public string      query_da_type() { return Armour_Type; }



/*
 * Function name:        create_demon_armour
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_demon_armour()
{
} /* create_demon_armour */


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour() 
{
    set_name("armour");
    add_name( ({ "_tutorial_demon_armour" }) );
    add_adj( ({ "black", "demonhide" }) );

    create_demon_armour();
    configure_it();
} /* create_armour */


/*
 * Function name:        configure_it
 * Description  :        set up all the properties of the armour.
 */
public void
configure_it()
{
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this armour extra light.\n", 1}));
    switch(Armour_Type)
    {
        case "bracers":
            add_adj( ({ "pair" }) );
            add_name( ({ "bracers", "bracer" }) );
            set_short("pair of demonhide bracers");
            set_long("The hide which comprises the thick bulk of these"
              + " sturdy bracers is like nothing you have ever seen"
              + " before. They are designed to be worn on the"
              + " forearms.\n");
            set_default_armour(DEMON_AC, A_ARMS, ({ 0, 1, -1}), 0);
            add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(
                     DEMON_AC, A_ARMS) / 4));
            add_prop(OBJ_I_VOLUME, 400);
            add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(DEMON_AC) + random(24));
            break;
        case "greaves":
            add_adj( ({ "pair", "pitch-black" }) );
            add_name( ({ "greaves", "leggings" }) );
            set_short("pair of demonhide greaves");
            set_long("Thick, pitch-black hide has been crafted into"
              + " leggings which offer excellent protection in battle."
              + " These greaves are designed to be worn on the shins.\n");
            set_default_armour(DEMON_AC, A_LEGS, ({ 0, 1, -1}), 0);
            add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(
                     DEMON_AC, A_LEGS) / 4));
            add_prop(OBJ_I_VOLUME, 700);
            add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(DEMON_AC) + random(24));
            break;
        case "helm":
            add_name( ({ "helm", "helmet", "cap", "skullcap" }) );
            set_short("demonhide skullcap");
            set_long("Thick and hairy, the black hide of a demon has been"
              + " folded and affixed to a matted cap which ties beneath"
              + " the chin to make up this helm.\n");
            set_default_armour(12, A_HEAD, ({ 0, 1, -1}), 0);
            add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(12, A_HEAD) / 4));
            add_prop(OBJ_I_VOLUME, 200);
            add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12) + random(12));
            break;
        case "shield":
            //add_adj( ({ "sturdy", "wooden", "wood" }) );
            add_name( ({ "shield", "device" }) ); 
            set_short("demonhide shield");
            set_long("Thick demonhide has been stretched over the face"
              + " of already very sturdy wood, adding even more"
              + " protection to the wielder of this device.\n");
            set_default_armour(DEMON_AC, A_SHIELD, ({ 0, 0, 0 }), 0);
            add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(
                     DEMON_AC, A_SHIELD) / 4));
            add_prop(OBJ_I_VOLUME, 800);
            add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(DEMON_AC) + random(24));
            break;
        case "mail":
            add_adj( ({ "thick" }) );
            add_name( ({ "mail", "scale", "scalemail", "coat",
                         "scales" }) ); 
            set_short("demonhide scalemail");
            set_long("Thick pieces of demonhide have been cut in the"
              + " form of scales, and layered on top of one another over"
              + " a thick coat. This armour provides excellent protection"
              + " indeed!\n");
            set_default_armour(25, A_BODY, ({ 0, 1, -1}), 0);
            add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(
                     25, A_BODY) / 4));
            add_prop(OBJ_I_VOLUME, 1100);
            add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(24));
            break;
    }
} /* set_type */

