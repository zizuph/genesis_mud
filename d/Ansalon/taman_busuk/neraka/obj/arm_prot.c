/* 
 * arm_prot.c
 *
 * This is an example enchantment for armours, it raises the
 * AC with enchantment strength / 5
 *
 * Ashlar, 12 Jul 98
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

static int gMod = 0;

/* These do not require calling of the inherited function */
string wizinfo_extra() { return "Raises the AC of the armour."; }
mixed enchant_object(object obj)
{
    if (query_enchanted_object_type() != ET_ARMOUR)
        return "Protection can only be used on armours!";
        
    if (!gMod)
        gMod = query_enchantment_strength() / 5;
    obj->set_ac(obj->query_ac() + gMod);
    obj->add_prop(MAGIC_AM_ID_INFO, obj->query_prop(MAGIC_AM_ID_INFO) +
        ({ "The armour is enchanted by a Priest of Takhisis to offer " +
           "extra protection in battle.", 15 }));
    return 0;
}
varargs void remove_enchantment(int quiet)
{
    object obj = query_enchanted();
    
    obj->set_ac(obj->query_ac() - gMod);
}

string query_enchantment_recover() { return sprintf("%d",gMod); }
void init_enchantment_recover(string arg)
{
    if(sscanf(arg,"%d", gMod) != 1)
        gMod = 0;
}

