#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name( ({"armour", "haidate"}) );
    set_short("haidate");
    set_adj(({"oriental", "waist"}));
    set_long("It's an haidate! An Oriental apron-like device worn " +
	     "around the waist to provide protection to the thighs. "+
	     "It is constructed of bamboo splints lashed together by "+
	     "thick cord.\n");
    set_ac(6);
    set_am(({0,-1,1}));
    set_at(A_WAIST);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}

int *
query_slots()
{
    return ({ A_WAIST });
}

int *
query_shield_slots()
{
    return ({ A_LEGS });
}
