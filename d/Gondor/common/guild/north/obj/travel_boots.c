/*  The travel-boots of the Rangers of the North */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("ranger");
    add_adj(({"high","leather"}));
    set_short("pair of high boots");
    set_pshort("pairs of high boots");
    set_long(BS("These high boots are nicely made of supple leather, but "+ 
    "have seen much wear, and are now caked with mud.\n"));
    set_af(TO);
    set_default_armour(5, A_LEGS | A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);
    add_prop(OBJ_I_WEIGHT, 360);   /* 260 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(20));
}

wear(object ob)
{
    write("You wear the " + query_short(TO) + " on your feet and "+
    "legs.\n");
    say(QCTNAME(TP) + " wears the " + query_short(TO) + ".\n");
    return 1;
}
