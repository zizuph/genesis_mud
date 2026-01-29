/* Crown of a dead king for the barrow downs
 * By Finwe, January 2002
 */

#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

// Global Vars
string crown_descr = "is encrusted with gems and looks old";

void
create_armour()
{
    set_name("crown");
    add_adj(({"ancient" ,"gold"}));
    add_name("_shire_wight_crown_");
    set_short("ancient gold crown");
    set_long("This "+short()+" was once worn by long forgotten " +
        "royal men and women of Middle-earth. The crown "+crown_descr+", " +
        "despite being worn for countless ages by evil spirits " +
        "of the Downs.\n");

    set_keep(1); 
    set_am(({-1,1,0}));
    set_at(A_HEAD);


    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_VALUE,   500+random(500));

}
