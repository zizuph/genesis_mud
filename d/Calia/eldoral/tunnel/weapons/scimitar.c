/*
 * Standard Scimitar
 *
 * This scimitar is a pretty basic weapon. Scimitars are often used in
 * mounted combat, so this particular weapon gets a slight boost when
 * the wielder is mounted.
 *
 * Created by Petros, November 2008
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "defs.h"
#include <macros.h>
#include <formulas.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5


// Global Variables
public int hit = 35;
public int pen = 30;
public string * quality_list = ({
    "dull",
    "rusty",
    "warped",
    "dented",
    "chipped",
    "dirty",
});

create_weapon()
{
    string quality;
    set_name("sword");
    add_name("scimitar");
    set_pname("swords");
    quality = one_of_list(quality_list);
    set_short(quality + " scimitar");
    set_pshort(quality + " scimitars");
    set_adj(quality);
    set_long("This " + query_short() + " is a well-crafted curved blade "
        + "looks ideal for slicing things and has been known to be "
        + "more effective when used in mounted combat. It looks quite old "
        + "and used, leading to its current " + quality + " state.\n");

    set_default_weapon(hit, pen, W_SWORD, W_SLASH, W_ANYH, 0);   

    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_WEAPON(hit,W_SWORD) + random(1500)); 
    add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON + random(201)); 
    add_prop(OBJ_I_VALUE, 
        F_VALUE_WEAPON(hit, pen) * (110 + random(21)) / 100);
    add_prop(OBJ_S_WIZINFO,
        "This " + query_short() + " is especially effective in mounted "
      + "combat. When the wielder is mounted, it gives a small boost to "
      + "both hit and pen.\n");
      
    set_keep(0);
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}

/*
 * Function name: query_hit
 * Description  : Query the to hit value in the weapon.
 * Returns      : int - the hit value.
 */
public int
query_hit()
{
    object wielder;
    
    wielder = query_wielded();
    if (objectp(wielder) && objectp(wielder->query_prop(LIVE_O_STEED)))
    {
        return hit + 5;
    }
    
    return hit;        
}

/*
 * Function name: query_pen
 * Description  : Query penetration value of the weapon.
 * Returns      : int - the pen value.
 */
public int
query_pen()
{
    object wielder;
    
    wielder = query_wielded();
    if (objectp(wielder) && objectp(wielder->query_prop(LIVE_O_STEED)))
    {
        return pen + 5;
    }
    
    return pen;        
}
