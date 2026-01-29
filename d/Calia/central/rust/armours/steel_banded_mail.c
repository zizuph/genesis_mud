/* This is a banded mail for the elite gnome guards of
Rust. Made by Bishop of Calia, 11/11/98 */


inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 36

void
create_armour()
{
    set_name("mail");

    set_adj("banded");
    set_adj("polished");

    set_short("polished banded mail");
    set_pshort("banded mails");

    set_long("This suit of banded mail would cover your arms and chest," +
        " and is constructed out of many overlapping steel plates." +
        " It's got quite a few combat scratches, but is well polished" +
        " and looks like excellent combat armour.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_at(A_ARMS);

    set_am(({ 0,0,0 }));

    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));

}