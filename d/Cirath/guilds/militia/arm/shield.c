/* shield: A shield made from scrap pieces of armours. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("shield");
    set_short("long narrow shield");
    set_long("Made from scraps of other armours, this shield is an "+
             "excellent starting shield for the militia.\n");
    set_adj("long");
    add_adj("narrow");

    set_ac(25);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 200);
}

public int *
query_shield_slots()
{
return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}