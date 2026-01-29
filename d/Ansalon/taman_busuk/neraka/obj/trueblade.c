/* 
 * trueblade.c
 *
 * This is an example enchantment for weapons, it raises the
 * to_hit with enchantment strength / 5
 *
 * Ashlar, 31 Jul 97
 */

#pragma strict_types

#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ENCHANTMENT_OBJ NOBJ + "enchantment"

inherit ENCHANTMENT_OBJ;

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define ET_WEAPON   1
#define ET_ARMOUR   2
#define ET_OBJECT   4

static int gMod;

/* These do not require calling of the inherited function */
string wizinfo_extra() { return "Raises the to_hit of the weapon."; }
mixed enchant_object(object obj)
{
    if (query_enchanted_object_type() != ET_WEAPON)
        return "Trueblade can only be used on weapons!";
        
    if (!gMod)
        gMod = query_enchantment_strength() / 5;
    obj->set_hit(obj->query_hit() + gMod);
    obj->add_prop(MAGIC_AM_ID_INFO, obj->query_prop(MAGIC_AM_ID_INFO) +
        ({ "The weapon is very easy to hit with, compared with a normal " +
           "weapon", 10 }));
    return 0;
}
varargs void remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    
    obj->set_hit(obj->query_hit() - gMod);
}
string query_enchantment_recover() { return sprintf("%d",gMod); }
void init_enchantment_recover(string arg)
{
    if(sscanf(arg,"%d", gMod) != 1)
        gMod = 0;
}

/* To redefine these, you must call the inherited function (::wear etc.) */
mixed
wield(object what)
{
    int r;
    r = ::wield(what);
    if (intp(r) && (r >= 0))
    {
        write("You feel confident in your ability to hit with the " +
            what->short() + ".\n");
    }
    return r;
}

