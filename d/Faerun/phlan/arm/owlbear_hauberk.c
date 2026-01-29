/*
 *   Armour from Phlan armour shop
 *   Tharizdun, 2021
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

/*
*                   P S B  additional padding vs. blunt
*/

#define AC_MOD      -1,0,1

/*
* 40+/-5
*/

int AC = 35+random(10);

void create_faerun_armour()
{
/*
*   description
*/    
    int tmp;
    set_name("armour");
    add_name("hauberk");
    set_adj("feathered");
    set_adj("owlbear-hide");
    set_short("feathered owlbear-hide hauberk");    
	set_long("This is a tunic of feathered owlbear hide that"
        +" protects your torso, chest, back, neck and arms. The feathers are dun," 
        +" brown and black, giving a natural camouflage. The feathers are thick"
        +" but light giving an extra layer of padding versus blunt weapons. The"
        +" feathers layer tightly to the hide almost like an arboreal chainmail.\n");
   
set_at(A_BODY | A_ARMS | A_NECK);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY | A_ARMS | A_NECK));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    
/*
* guaranteed - the price will never be lower than 3/4 of F_VALUE_ARMOUR(ac)
* but might be up to 2 times higher, with semi-gaussian distribution 
* around F_VALUE_ARMOUR 
*/
 
    add_prop(OBJ_I_VALUE, min(tmp*3/2, random(tmp) + random(tmp) + random(tmp) + random(tmp)));    

/*
*   Adding magical documentation.
*/

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({"This armour as made from an enchanted owlbear hide. It retains"
         +" a small portion of the creature's ability to hide and move"
         +" silently in natural surroundings.\n", 50}) );
    add_prop(MAGIC_AM_MAGIC, ({10, "enchantment"}) );
}

/*
*   Adding magical skill adjustment
*/

mixed
wear(object what)
{
    TP->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) + 5);
    TP->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) + 5);

    wearer = TP;
    return 0;
}
mixed
remove(object what)
{
    wearer->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) -5);
    wearer->set_skill_extra(SS_HIDE, TP->query_skill_extra(SS_HIDE) -5);

    wearer = 0;
    return 0;
}