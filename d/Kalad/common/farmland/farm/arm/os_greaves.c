inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("ornate");
    add_adj("steel");
    set_short("pair of ornate steel greaves");
    set_pshort("pairs of ornate steel greaves");
    set_long("These are a pair of ornately decorated, heavy steel "+
    "plate greaves. They look very sturdy.\n");
    /* Changed AC by Zignur 2016-01-28 */
    set_ac(25);    
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,7200);
    add_prop(OBJ_I_VOLUME,6000);
}

