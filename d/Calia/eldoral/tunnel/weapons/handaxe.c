/*
 * Standard Handaxe
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
public int hit = 30;
public int pen = 30;

public string * quality_list = ({ 
    "sturdy", "rusty", "dirty", "warped", "balanced",
});

create_weapon()
{
    string quality;
    
    set_name("axe");
    add_name("handaxe");
    quality = one_of_list(quality_list);
    set_short("light " + quality + " handaxe");
    set_adj("light");
    add_adj(quality);
    set_long("This " + query_short() + " fits easily into any "
        + "hand to make an effective weapon. The wood handle "
        + "contributes to its light weight. The handle look "
        + "newly cut, and the axe itself seems like it is "
        + "quite " + quality + ".\n");

    set_default_weapon(hit, pen, W_AXE, W_SLASH, W_ANYH, 0);   

    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_WEAPON(hit, W_AXE) + random(2500)); 
    add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON + random(201)); 
    add_prop(OBJ_I_VALUE, 
        F_VALUE_WEAPON(hit, pen) * (110 + random(21)) / 100);
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
