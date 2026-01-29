/*
 *      /d/Gondor/morgul/obj/ithil_weapon.c
 *
 *      Weapons forged by Ghashdurub of Minas Morgul
 *
 *      Olorin, 13-mar-1997
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Modification log:
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define WEAPONS	([ \
    "falchion"	:	({ 22, 26, W_SWORD, W_SLASH|W_IMPALE, W_ANYH }),    \
    "scimitar"	:	({ 31, 22, W_SWORD, W_SLASH, W_ANYH }),	            \
    "longsword"	:	({ 30, 26, W_SWORD, W_IMPALE|W_SLASH, W_ANYH }),    \
    "two-handed sword":	({ 33, 33, W_SWORD, W_SLASH, W_BOTH }),             \
    "battle axe":	({ 24, 31, W_AXE,   W_SLASH, W_ANYH }),             \
    "broad axe"	:	({ 24, 40, W_AXE,   W_SLASH, W_BOTH }),             \
    "mattock"   :       ({ 28, 39, W_AXE,   W_SLASH|W_IMPALE, W_BOTH }),    \
    "glaive"	:	({ 22, 29, W_POLEARM, W_SLASH,  W_BOTH }),          \
    "halberd"	:	({ 28, 40, W_POLEARM, W_IMPALE|W_SLASH, W_BOTH }),  \
    "mace"      :       ({ 31, 22, W_CLUB,  W_BLUDGEON, W_ANYH }),          \
    "warhammer" :       ({ 23, 32, W_CLUB,  W_IMPALE|W_BLUDGEON, W_ANYH }), \
    "club"      :       ({ 23, 29, W_CLUB,  W_IMPALE|W_BLUDGEON, W_BOTH }), \
    "morningstar" :     ({ 26, 37, W_CLUB,  W_BLUDGEON, W_BOTH }),          \
    "dagger"	:	({ 16, 16, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH }),    \
    "main gauche" :	({ 16, 16, W_KNIFE, W_IMPALE, W_LEFT }),            \
    "stiletto"	:	({ 14, 18, W_KNIFE, W_IMPALE, W_ANYH }),            \
    "dirk"	:	({ 16, 15, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH }),    \
])

#define LONG	([ \
    "falchion"	: "This heavy curved sword has a single-edged blade for " + \
        "slashing deep wounds. The blade is a little over two feet in " +   \
        "length.", \
    "scimitar"	: "A curved slashing sword with a single edge.", \
    "longsword" : "An ordinary longsword, more than a yard in length, " +   \
        "two-edged and deadly if wielded with skill.", \
    "two-handed sword": "A heavy double-edged sword, to be wielded in both hands.", \
    "battle axe": "A well balanced battle axe with a wooden shaft and " + \
        "a large steel blade.", \
    "broad axe"	: "A heavy two-handed axe with a wooden shaft and a " +   \
        "a large steel blade.", \
    "mattock"   : "This mattock is a heavy steel axe with a handle made " + \
        "out of hard black wood. It has two blades, one horizontal, and " + \
        "a large vertical one.", \
    "glaive"	: "A single-edged blade mounted on a long wooden pole. ", \
    "halberd"	: "A long halberd with a large axe blade, a spear-head " + \
        "at the top, and a hook at the back. ", \
    "mace"      : "The winged head of the mace is made of iron and is " + \
        "studded with knobs.", \
    "warhammer" : "On one side the iron head of this warhammer is large and " + \
        "flat, well suited for smashing helmets and legs. On the other " + \
        "side, the head has a beak to punch through armour.", \
    "club"      : "This two-handed club has a large round head of " + \
        "iron, studded with sharp steel spikes.", \
    "morningstar" : "An iron chain connects a heavy spiked iron ball " + \
        "to an iron handle. The spikes of the ball are sharp and of " + \
        "varying lengths, between two and five inches long.", \
    "dagger"	: "A short bladed weapon with two cutting edges and a " + \
        "blade tapering to a point.", \
    "main gauche" : "A sharp dagger with a large downward curved " + \
        "crossguard, to be wielded in the left hand.", \
    "stiletto"	: "A thin and narrow bladed dagger.", \
    "dirk"	: "A thin single-edged dagger with a large crossguard.",  \
		])

#define ADJS	([ "falchion"	: ({ "curved", "slashing", "heavy", }), \
		   "scimitar"	: ({ "curved", "slashing", "single-edged", }), \
 		   "longsword"	: ({ "ordinary", "long", "two-edged", }), \
		   "two-handed sword": ({ "heavy", "double-edged", "two-handed", }), \
                   "battle axe"	: ({ "steel", "wooden", "well balanced", "battle", }), \
		   "broad axe"	: ({ "steel", "wooden", "two-handed", "broad", }), \
		   "mattock"	: ({ "heavy", "steel", "two-handed", "wooden", }), \
		   "glaive"	: ({ "long", "single-edged", }), \
		   "halberd"	: ({ "long", "large", "two-handed", }), \
                   "mace"       : ({ "studded", "iron", }), \
                   "warhammer"  : ({ "beaked", "iron", }), \
                   "club"       : ({ "spiked", "iron", "two-handed", }), \
                   "morningstar": ({ "iron", "spiked", }), \
		   "dagger"	: ({ "short", }), \
		   "main gauche" : ({ "sharp", "left-handed", }), \
		   "stiletto"	: ({ "thin", "narrow", }), \
		   "dirk"	: ({ "thin", "single-edged", }), \
		])

#define WNAME	([ W_SWORD	: "sword",   \
		   W_AXE	: "axe",     \
                   W_CLUB	: "club", \
		   W_POLEARM	: "polearm", \
		   W_KNIFE	: "knife",   \
		])

static mapping	Weapons = WEAPONS;
static string   WType;

public void
create_ithil_weapon()
{
    mixed   *arr;

    set_name(WType);

    arr = Weapons[WType];
    add_name(WNAME[arr[2]]);

    set_short(ADJS[WType][0]+" "+query_name());
    set_long(BSN(LONG[WType] + " The picture of a Moon disfigured " +
        "with a ghastly face of death has been etched into the " +
        ( (arr[2] == W_CLUB) ? "handle " : "blade ") +
        "of the " + query_name() + ". Below the picture, there are " +
        "some letters."));
    set_adj(ADJS[WType]);

    add_item( ({ (arr[2] == W_CLUB ? "handle" : "blade"), 
                     "letters", "picture", }),
        BSN("Some letters are etched into the " +
            ( (arr[2] == W_CLUB) ? "handle " : "blade ") +
            "of the " +short() + " below the picture of a Moon " +
            "disfigured by a ghastly face of death. The letters " +
            "read: Ghashdurub, Morgul army."));

    add_cmd_item( ({ (arr[2] == W_CLUB ? "handle" : "blade"), 
                     "letters", "picture", }),
	({ "read" }),
        BSN("Some letters are etched into the " +
            ( (arr[2] == W_CLUB) ? "handle " : "blade ") +
            "of the " +short() + " below the picture of a Moon " +
            "disfigured by a ghastly face of death. The letters " +
            "read: Ghashdurub, Morgul army."));

    set_default_weapon(arr[0], arr[1], arr[2], arr[3], arr[4]);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(arr[0], arr[1]) + random(400) - 100);
    add_prop(OBJ_I_WEIGHT, 
	(F_WEIGHT_DEFAULT_WEAPON(arr[0], arr[2]) + random(750) - 250));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

public void
create_weapon()
{
    add_name("_ithil_weapon");
    set_default_weapon(0, 0, 0, 0, 0);
}

public int
set_weapon_type(string name)
{
    if (member_array(name, m_indexes(Weapons)) < 0)
        return 0;

    WType = name;
    create_ithil_weapon();
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

    create_ithil_weapon();
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

