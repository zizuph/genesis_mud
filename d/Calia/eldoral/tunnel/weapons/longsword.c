/*
 * Standard Longsword
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
public int pen = 25;
public string * quality_list = ({
    "dull",
    "rusty",
    "warped",
    "chipped",
    "dirty",
});

create_weapon()
{
    string quality;
    
    set_name("sword");
    add_name("longsword");
    set_pname("swords");
    
    quality = one_of_list(quality_list);
    set_short(quality + " longsword");
    set_pshort(quality + " longswords");
    set_adj(quality);
    set_long("This " + query_short() + " is a straight double-edged sword "
        + "with a cruciform hilt. Every part of the sword can be used in "
        + "an offensive manner, including the crossguard and pommel. "
        + "It looks very old, and at one time must have been very "
        + "dangerous.\n");

    set_default_weapon(hit, pen, W_SWORD, W_IMPALE | W_SLASH, W_ANYH, 0);   
    // impale, slashing, bludgeoning
    set_pm(({-2, 2, 0}));

    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_WEAPON(hit,W_SWORD) + random(1500)); 
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
