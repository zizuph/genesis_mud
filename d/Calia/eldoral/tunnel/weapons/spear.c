/*
 * Standard Spear
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
public int pen = 25;
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
    set_name("polearm");
    add_name("spear");
    quality = one_of_list(quality_list);
    set_short(quality + " short spear");
    set_adj(quality);
    add_adj("short");
    set_long("This " + query_short() + " is extremely short. It "
        + "is easily held in one hand. The spear is made of "
        + "a long wooden pole with a iron tip at the end tied "
        + "together with some rope. It looks to be quickly "
        + "crafted, but dangerous nonetheless.\n");

    set_default_weapon(hit, pen, W_POLEARM, W_IMPALE, W_ANYH, 0);   

    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_WEAPON(hit, W_POLEARM) + random(2500)); 
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
