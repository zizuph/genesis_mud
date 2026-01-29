/*
 * The code for this shield was borrowed from
 * /d/Krynn/solamn/vin/armour/s_shield.c
 *
 *  Arman 11/5/99
 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>


public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj("dwarven");
    add_adj(({"large","steel"}));
    set_short("dwarven kite shield");
    set_pshort("dwarven kite shields");
    set_ac(40);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This dwarven kite shield is that that was worn by " +
      "the mighty dwarven hero of the hill dwarves, Teregul Stormbolt. " +
      "It is very large and heavy, covering ones body and legs. On the " +
      "front of it is the device of an axe crossed over a white lightning " +
      "bolt.\n");
    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(36) + (random(200)));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
