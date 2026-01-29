// moccasin boots   /d/Avenir/common/holm/obj/boots.c
// creator(s):      Lilith, 1/25/97
// purpose:         To be worn by humanoids on the Holm
// last update:     Lilith, 3/1/97    
// note:            These are lightweight but sturdy.
// bug(s):
// to-do:
// ====== ========= ========= ========= ========= ========= ========= =====

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

void wv_update();

void
create_armour()
{
    set_name("boots");
    set_adj("moccasin");
    add_adj(({"leather"}));
    set_short("pair of moccasin boots");
    set_pshort("pairs of moccasin boots");
    set_long("These boots are soft-soled, made of supple leather. "+
        "They are knee-length, and the fold-over tops are fringed."+
        "\n");

    set_default_armour(11, A_FEET, 0, 0);
    set_am(({ 2, -1, -1}));
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    set_alarm(1.0, 0.0, wv_update);  
}

void 
wv_update()
{
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(11) * 2);
}
