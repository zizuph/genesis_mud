/*
 * Ancient Ribbed Platemail
 * Worn by lizardmen from Mere of Dead Men
 * -- Finwe, August 2006
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC 47

void create_faerun_armour()
{
    set_name("platemail");
    set_adj(({"ancient", "ribbed"}));
    set_short("ancient ribbed platemail");
    set_long("This "+short()+" is made of steel plates that overlay each other. The armour  was forged ages ago by long forgotten blacksmiths. Each plate is ribbed and designed to deflect blows during battle. An ancient power surrounds the " + short() + ".\n");
 
    set_at(A_BODY | A_ARMS);
    set_ac(AC);
    set_am(({-2, 3, -1}));
    add_prop(OBJ_S_WIZINFO,
        "This " + short() + " is enhanced with magic to enhance its " +
        "strength. Historically, it was worn by warriors who fought " +
        "during ancient battles in the Mere of Dead Men. This is one " +
        "of the many armours and/or weapons that was embued with magic. " +
        "This armour has an increased AC and magically enhanced and protects against poison and fire.\n");
     add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+"  was forged anciently and worn by warriors " +
            "long dead.", 5,
        "It is stronger than many armours.", 10,
        "The armour has been imbued with ancient magics.", 15,
        "The magic make the armour stronger during battle.", 20,
        "the " + short() + " provides protection against poison and fire", 40}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 1500 + random(250));
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    
    if (protectee == query_worn())
      {
	  if (prop == MAGIC_I_RES_POISON || prop == MAGIC_I_RES_FIRE)
	    return ({ 10, 10}); /* additive */
      } 
    else
      return ::query_magic_protection(prop, protectee);
}
