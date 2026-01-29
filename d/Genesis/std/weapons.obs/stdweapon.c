/*
 * /d/Genesis/std/weapons/stdweapon.c
 *
 * Base file for all Genesis standard weapons.  
 *
 * Supports materials and magic for weapons.
 */

#pragma save_binary

inherit "/std/weapon.c";

#include "materials.h"
#include <wa_types.h>
#include <stdproperties.h>

mapping materials;
int magic;
string material;
mixed *matdata;

varargs void set_material(string type);

/*
 * Function name: create_stdweapon
 * Description: If we got called, we are a direct clone, and should be 
 * unconfigured.
 */
void
create_stdweapon()
{
    ::create_weapon();
    add_adj("unconfigured");
    set_long("The coding wizard should have configured this weapon.\n");
    add_prop(OBJ_I_WEIGHT, "@@query_weight");
}

/*
 * Function Name: query_weight
 * Description: Used VBFC to ascertain the weight of the weapon.
 * Returns: current weight = density*volume.
 */
int
query_weight()
{
    return matdata[M_DENSITY]*query_prop(OBJ_I_VOLUME)/100;
}

/*
 * Function Name: query_value
 * Description: Used VBFC to ascertain the value of the weapon.
 * Returns: current value.
 */
int
query_value()
{
    return ::query_value()*(magic + 10)/10 + 
        query_prop(OBJ_I_VOLUME)*matdata[M_VALUE];
}

/*
 * Function name: create_weapon
 * Description: We make sure everything is properly intialized before our
 * child makes its weapon.
 */
nomask void
create_weapon()
{
    materials = MATERIAL_DATA;
    set_material("iron");
    magic = 0;
    create_stdweapon();
}

/*
 * Function name: set_material
 * Description: sets a material type for the weapon.
 * Arguments: m - a string with the type to set.
 */
void
set_material(string m)
{
    remove_adj(material);
    add_adj(m);
    set_short(0);

    matdata = materials[m];

    if(matdata)
    {
        set_likely_corr(matdata[0] - magic/10);
        set_likely_dull(matdata[1] - magic/10);
        set_likely_break(matdata[2] - magic/10);
    }
    else
        matdata = M_DEFAULT_MATERIAL_DATA;

    material = m;
}

/*
 * Function name: query_material
 * Returns: The current material type
 */
string
query_material()
{
    return material;
}

/*
 * Function name: set_magic
 * Description: sets a %enchantment and type of spell for the weapon.
 * Arguments: m, the amount of magic in the weapon.
 *            type, a string declaring exactly what type of magic is used.
 */
varargs void
set_magic(int m, string type)
{
    if(!type)
        type = "enchantment";

    if(magic)
        remove_prop(MAGIC_AM_MAGIC);

    if(m)
        add_prop(MAGIC_AM_MAGIC, ({type, m}));

    magic = m;
}

/*
 * Function name: query_magic
 * Returns: amount of magic in the object.  (See property MAGIC_AM_MAGIC for
 *    the type)
 */
query_magic()
{
    return magic;
}

/*
 * Function name: query_hit
 * Returns: tohit stat of weapon, modified for magic and materials.
 */
int
query_hit()
{
    int hit;
    hit = ::query_hit() + matdata[M_TO_HIT];
    return magic + hit - magic*hit/100;
}

/* 
 * Function name: query_modified_pen
 * Returns: array of penmods for each damage type, modified for magic and 
 *     materials.
 */
int *
query_modified_pen()
{
    int i,*p;
    mixed *m;

    p = ::query_modified_pen();
    m = matdata[M_PENMOD];

    for (i = sizeof(p) - 1; i >= 0; i--)
    {
        p[i] += m[i];
        p[i] = p[i] + magic - p[i]*magic/100;
    }

    return p;
}