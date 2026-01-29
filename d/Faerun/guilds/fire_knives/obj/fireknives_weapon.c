/*
 * /d/Faerun/guilds/fire_knives/obj/fireknives_weapon.c
 *
 *  Borrowed from the Morgul smith weapon object.
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../guild.h";

#define WEAPONS	([ \
    "shiv"	:	({ 20, 20, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH }),    \
    "main-gauche" :	({ 20, 20, W_KNIFE, W_IMPALE, W_ANYH }),            \
    "kukri"	:	({ 20, 20, W_KNIFE, W_SLASH, W_ANYH }),            \
    ])

#define LONG	([ \
        "shiv"	: "A simple metal stick, Sharpened and pointed to " + \
        "provide a simple but quite lethal shiv. The handle is " + \
        "wrapped with black leather and the gleam is painted to " + \
        "provide a dulled surface wich gives no reflection.", \
        "main-gauche" : "This knife has a long thin blade and at the " + \
        "crossguard a basket is attached to protect the wielders hand. The " + \
        "entire construction is made from steel, with the hilt being " + \
        "made of tightly wrapped metal wire", \
        "kukri"	: "This is a oddly bent blade giving it the " + \
        "Kukri design, its sharp and coloured to be very " + \
        "dull as if to not give off a sheen.", \
		])

#define ADJS	([ "shiv"	: ({ "long", "blackened" }), \
		           "main-gauche" : ({ "basket-hilt", "steel", }), \
		           "kukri"	: ({ "curved", "dull", }), \
		])

#define WNAME	([ W_KNIFE	: "knife",   \
		])

static mapping	Weapons = WEAPONS;
static string   WType;



public void
create_fireknives_weapon()
{
    mixed   *arr;

    set_name(WType);

    arr = Weapons[WType];
    
    add_name(WNAME[arr[2]]);

    set_short(ADJS[WType][0]+" "+query_name());
    
    set_long(BSN(LONG[WType] + " The hilt of the " + query_name() + " is wrapped in blackened leatherstraps "
    +"and the pummel marked with the emblem of the Fire Knives."));
        
    set_adj(ADJS[WType]);

    set_default_weapon(arr[0], arr[1], arr[2], arr[3], arr[4]);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(arr[0], arr[1]) + random(400) - 100);
    
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(arr[0], arr[2]) + random(750) - 250));
    
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}


public void
create_weapon()
{
    add_name("_fireknives_weapon");
    set_default_weapon(0, 0, 0, 0, 0);
}


public int
set_weapon_type(string name)
{
    if (member_array(name, m_indexes(Weapons)) < 0)
        return 0;

    WType = name;
    create_fireknives_weapon();
    return 1;
}


public string
query_recover()
{
    return MASTER + ":" + "#WT#" + WType + "#"
                  + query_wep_recover();
}


public void
init_recover(string arg)
{
    string  dummy;

    sscanf(arg, "%s#WT#%s#%s", dummy, WType, dummy);
    init_wep_recover(arg);

    create_fireknives_weapon();
}


public string *
query_weapon_types()
{
    return m_indexes(Weapons);
}


public int
query_price(string wt)
{
    set_weapon_type(wt);

    return (F_VALUE_WEAPON(wep_hit, wep_pen) * 11) / 10;
}


string
query_weapon_long(string wt)
{
    return LONG[wt];
}


string
query_weapon_short(string wt)
{
    return (ADJS[wt][0]+" "+wt);
}

