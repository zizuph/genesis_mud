/*
 * Standard Maul
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
public int hit = 37;
public int pen = 37;
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
    set_name("club");
    add_name("maul");
    add_name("hammer");
    quality = one_of_list(quality_list);
    set_short(quality + " heavy maul");
    set_adj(quality);
    add_adj("heavy");
    set_long("This " + query_short() + " is difficult to hold due "
        + "to its weight. It looks like it can only be held "
        + "and used effectively with both hands. The handles are made "
        + "of carved wood, with a weighted steel head to deliver "
        + "effective blows. It has seen much use and is "
        + "riddled with scratches and dents.\n");

    set_default_weapon(hit, pen, W_CLUB, W_BLUDGEON, W_BOTH, 0);   

    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_WEAPON(hit, W_CLUB) + random(2500)); 
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
