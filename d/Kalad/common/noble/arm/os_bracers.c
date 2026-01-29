inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("ornate");
    add_adj("steel");
    set_short("pair of ornate steel bracers");
    set_pshort("pairs of ornate steel bracers");
    set_long("These steel pieces of armour go on your arms. They are "+
    "ornately decorated and feel rather heavy.\n");
    set_ac(25);
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,2000);
}

