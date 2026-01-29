/* Hammer for the Ten Alders smith Pele
*/

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("hammer");
    add_name("__es_hammer__");
    add_adj(({"great", "black", "iron"}));
    set_short("great black iron hammer");
    set_long("A massive heavy hammer, blackened by soot and time.\n");
    set_keep(1);
    set_default_weapon(35, 35, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VALUE, 750);
}
