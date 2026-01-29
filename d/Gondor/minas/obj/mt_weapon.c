/*
 *      /d/Gondor/minas/obj/mt_weapon.c
 *
 *      Weapons forged by Herumegil of Minas Tirith
 *
 *      Olorin, 16-nov-1994
 *
 *      Copyright (c) 1994, 1997 by Christian Markus
 *
 *      Modification log:
 *      13-mar-1997, Olorin:    General revision.
 *	8-oct-1998, Gnadnar:	don't put spaces in name (e.g., don't do
 *				set_name("bastard sword")), because then
 *				"put bastard sword into <container>" 
 *				will fail.
 */
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define WEAPONS	([ "eket"	:	({ 23, 18, W_SWORD, W_SLASH|W_IMPALE, W_ANYH }), \
		   "scimitar"	:	({ 32, 23, W_SWORD, W_SLASH, W_ANYH }),	         \
		   "longsword"	:	({ 31, 27, W_SWORD, W_IMPALE|W_SLASH, W_ANYH }), \
		   "bastard sword":	({ 35, 30, W_SWORD, W_IMPALE|W_SLASH, W_BOTH }), \
                   "two-handed sword":	({ 35, 35, W_SWORD, W_SLASH, W_BOTH }),          \
		   "broadsword"	:	({ 30, 29, W_SWORD, W_SLASH, W_ANYH }),          \
		   "rapier"	:	({ 35, 22, W_SWORD, W_IMPALE, W_ANYH }),         \
		   "hand axe"	:	({ 18, 22, W_AXE,   W_SLASH, W_ANYH }),          \
                   "battle axe"	:	({ 25, 32, W_AXE,   W_SLASH, W_ANYH }),          \
		   "broad axe"	:	({ 24, 40, W_AXE,   W_SLASH, W_BOTH }),          \
		   "spear"	:	({ 24, 18, W_POLEARM, W_IMPALE, W_BOTH }),       \
		   "glaive"	:	({ 23, 30, W_POLEARM, W_SLASH,  W_BOTH }),       \
		   "halberd"	:	({ 29, 40, W_POLEARM, W_IMPALE|W_SLASH,  W_BOTH }), \
		   "dagger"	:	({ 14, 14, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH }), \
		   "main gauche" :	({ 14, 14, W_KNIFE, W_IMPALE, W_LEFT }),         \
		   "stilleto"	:	({ 12, 16, W_KNIFE, W_IMPALE, W_ANYH }),         \
		   "dirk"	:	({ 14, 13, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH }), \
		])

#define LONG	([ "eket"	: "A short stabbing sword with a broad blade, pointed " + \
                                  "and two-edged, a little over one foot in length.",     \
		   "scimitar"	: "A curved slashing sword with a single edge.",          \
                   "longsword"  : "An ordinary longsword, more than a yard in length, " + \
                                  "two-edged, deadly if wielded with skill.",             \
		   "bastard sword": "A broad, double-edged two-handed sword.",            \
		   "two-handed sword": "A heavy double-edged sword, to be wielded in both hands.", \
		   "broadsword"	: "A slashing sword with a broad, one-edged blade.",      \
                   "rapier"	: "A light sword with a sharp narrow blade.",             \
		   "hand axe"	: "A normal axe, more a tool than a weapon.",             \
                   "battle axe"	: "A well balanced battle axe with a wooden shaft and " + \
				  "a large steel blade.",                                 \
		   "broad axe"	: "A heavy two-handed axe with a wooden shaft and a " +   \
				  "a large steel blade.",                                 \
		   "spear"	: "A standard spear with a long wooden shaft and a " +    \
				  "sharp metal head.",                                    \
		   "glaive"	: "A single-edged blade mounted on a long wooden pole. ", \
		   "halberd"	: "A long halberd with a large axe blade, a " +           \
				  "spear-head at the top, and a hook at the back. ",      \
		   "dagger"	: "A short bladed weapon with two cutting edges and a " + \
				  "blade tapering to a point.",                           \
		   "main gauche" : "A sharp dagger with a large downward curved crossguard, " + \
				  "to be wielded in the left hand.",                      \
		   "stilleto"	: "A thin and narrow bladed dagger.",                     \
		   "dirk"	: "A thin single-edged dagger with a large crossguard.",  \
		])

#define ADJS	([ "eket"	: ({ "short", "stabbing", }), \
		   "scimitar"	: ({ "curved", "slashing", "single-edged", }), \
 		   "longsword"	: ({ "ordinary", "long", "two-edged", }), \
	        "bastard sword" : ({ "bastard", "double-edged", "broad", "two-handed", }), \
	     "two-handed sword" : ({ "two-handed", "heavy", "double-edged", }), \
		   "broadsword"	: ({ "one-edged", "slashing", "broad", }), \
		   "rapier"	: ({ "sharp", "narrow", "light", }), \
		   "hand axe"	: ({ "hand", "normal", "standard", }), \
                   "battle axe"	: ({ "battle", "steel", "wooden", "well balanced", }), \
		   "broad axe"	: ({ "broad", "steel", "wooden", "two-handed", }), \
		   "spear"	: ({ "long", "standard", "metal", }), \
		   "glaive"	: ({ "long", "single-edged", }), \
		   "halberd"	: ({ "long", "large", "two-handed", }), \
		   "dagger"	: ({ "short", }), \
		   "main gauche" : ({ "main", "sharp", "left-handed", }), \
		   "stilleto"	: ({ "thin", "narrow", }), \
		   "dirk"	: ({ "thin", "single-edged", }), \
		])

#define WNAME	([ W_SWORD	: "sword",   \
		   W_AXE	: "axe",     \
		   W_POLEARM	: "polearm", \
		   W_KNIFE	: "knife",   \
		])

mapping	weapons = WEAPONS;
string  wtype;

void
create_mt_weapon()
{
    mixed   *arr;
    string  adj, name;

    if (sscanf(wtype, "%s %s", adj, name) != 2)
    {
	name = wtype;
    }
    set_name(name);

    /* N.B. we assume that the first adjective in ADJS is identical
     * to the adj in wtype if it contains adj + name (e.g., "bastard sword")
     */
    set_short(ADJS[wtype][0]+" "+name);
    set_long(BSN(LONG[wtype]
      + " Some letters have been etched into the blade."));
    set_adj(ADJS[wtype]);

    add_item(({"blade", "letters"}), BSN(
        "Some letters are etched into the blade of the "+short()
      + ". They read: "
      + "Im Herumegil Hador Minas Tirith hain echant."));

    arr = weapons[wtype];
    add_name(WNAME[arr[2]]);

    set_default_weapon(arr[0], arr[1], arr[2], arr[3], arr[4]);
    add_prop(OBJ_I_VALUE,
	(F_VALUE_WEAPON(arr[0], arr[1]) + random(200) - 100));
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(arr[0], arr[2]) + random(500) - 250));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

void
create_weapon()
{
    add_name("_mt_weapon");
    set_default_weapon(0, 0, 0, 0, 0);
}

int
set_weapon_type(string name)
{
    if (member_array(name, m_indexes(weapons)) < 0)
        return 0;

    wtype = name;
    create_mt_weapon();
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + "#WT#" + wtype + "#"
                  + query_wep_recover();
}

void
init_recover(string arg)
{
    string  dummy;

    sscanf(arg, "%s#WT#%s#%s", dummy, wtype, dummy);
    init_wep_recover(arg);

    create_mt_weapon();
}

string *
query_weapon_types()
{
    return m_indexes(weapons);
}

int
query_price(string wt)
{
    set_weapon_type(wt);

    return F_VALUE_WEAPON(wep_hit, wep_pen);
    return query_prop(OBJ_I_VALUE);
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
