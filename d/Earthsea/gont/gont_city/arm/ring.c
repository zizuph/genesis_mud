#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("ring");
    set_adj("sapphire");
    add_adj("ornate");
    set_short("ornate sapphire ring");
    set_long("This is a large ring made of filigree silver with "+
        "a fiery star sapphire in a setting designed to resemble the "+
        "talons of a hawk.\n");
    set_at(A_R_FINGER);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 300);
}
