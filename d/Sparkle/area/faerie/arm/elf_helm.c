/*
 * Helm for orc lord
 * -- Finwe, February 2008
 */
inherit "/std/armour";

#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ADJ1        "twisted"
#define ADJ2        "elven"
#define ARMOUR      "skull"
#define BOD_TYPE    A_HEAD
#define AC_MOD      0,0,0
#define AC          40


void create_armour()
{
    setuid(); 
    seteuid(getuid());
    
    set_name("armour");
    add_name("helmet");
    add_name("helm");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This is a " + short() + ". It was ripped from an elven corpse. It is lined with iron to make it stronger and durable. The skin has dried on the skull and the features sunken in, making the helmet look more grisly.\n");
 
    set_at(BOD_TYPE);
    set_ac(AC);
    set_af(TO);
    set_am(({AC_MOD}));

    add_prop(OBJ_I_VOLUME,350);
    add_prop(OBJ_I_WEIGHT,2500+random(1000));
    add_prop(OBJ_I_VALUE,500+random(200));

}
