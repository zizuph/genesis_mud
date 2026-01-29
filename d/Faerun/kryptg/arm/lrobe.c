/*
 * Robe for sale in the leather shop in the mountains
 * -- Finwe, November 2007
 */

//inherit "/std/armour.c";
//inherit "/lib/keep";
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "long"
#define ADJ2        "leather"
#define ARMOUR      "robe"
#define BOD_TYPE    A_ROBE
#define AC_MOD      ({0,1,1})

int ac =  35 + random(5);

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 

    set_long("This is a " + query_short() + ". It is made from tanned leather and is heavy. It hangs from the neck down to the  ground, and keeps you warm and protects you during battles.\n");

    set_default_armour(ac,BOD_TYPE,AC_MOD,0);    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);
    add_prop(OBJ_I_VALUE,500);
}