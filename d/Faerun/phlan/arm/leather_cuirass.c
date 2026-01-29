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
*   description
*/

#define ADJ1    	"hardened"
#define ADJ2    	"leather"
#define ARMOUR      "cuirass"
#define ARMOURS     "cuirasses"
#define BOD_TYPE    A_BODY

/*
*                   P S B  common leather properties
*/

#define AC_MOD      1,-1,0

/*
 *   10 +/- 5
 */
 
int AC =  5 + random(10);


void create_faerun_armour()
{
    int tmp;
    set_name("armour");
    add_name("cuirass");
    set_adj("hardened");
    set_adj("leather");
    set_short("hardened leather cuirass");    
	set_long("This is a hardened leather cuirass, protecting your torso, chest" 
        +" and back. The stiff soaked leather is dark brown with simple black"
        +" trim. It is light and effective.\n");
   
set_at(A_BODY);
    set_ac(AC);
    set_am(({AC_MOD}));    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

}