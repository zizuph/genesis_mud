
/*
 * Ceremonial Water
 * No value
 * Only used for ceremonies
 *
 */
 
inherit "/std/object";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()
#define NF notify_fail
 

void create_object() 
{
    set_name(({"ceremonial water","water"}));
    set_adj("ceremonial");
    set_short("vial of ceremonial water");
    set_pshort("vials of ceremonial water");
    set_long("It is a small vial ceremonial water used for ceremonial purposes.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
