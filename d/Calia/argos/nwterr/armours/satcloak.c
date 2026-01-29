 /*****************************************************************************
*  /d/Calia/argos/nwterr/armours/satcloak.c
*
*  Description: Satyr Cloak
*
*  Created Sept 2021, Greneth
*
*  Changes:      
*
 *****************************************************************************/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>

#define COLOR ({"red","brown","black","white","green","blue","yellow"})
#define ENGS ({"leaves","flutes","hearts","vines","trees","mystic symbols"})
 
void create_armour() {
    string color=COLOR[(random(sizeof(COLOR)))];
    set_name("cloak");
    set_adj(({"short",color}));
    set_short("short "+color+" cloak");
    set_long("It is a common cloak made of "+color+" dyed wool and is "
	+ "decorated with "+
       (ENGS[(random(sizeof(ENGS)))])+"\n");
    set_ac(5);
    set_at(TS_ROBE);
}