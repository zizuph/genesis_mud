/*
 * Greaves worn by the Elf leader
 * This is the basic armour worn by the elves who travel.
 * They are not magical
 * - Finwe, January 2018
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>

#define AC  30
void
create_armour()
{
    set_name("greaves");
    add_name(({ "pair of greaves" }));
    set_adj(({"plain", "high-steel"}));
    set_short("pair of plain high-steel greaves");
    set_pshort("pairs of plain high-steel greaves");
    set_pname("greaveses");
    set_long("This " + short() + " was forged by elves in Middle-earth. It is made of thin, overlapping plates of extra hard steel. They protect the legs and are plain and unadorned.\n");
    set_at(A_LEGS);
    set_ac(AC);
    set_am(({0, 0, 0}));
    set_keep(1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, 1200 + random(500));
}
