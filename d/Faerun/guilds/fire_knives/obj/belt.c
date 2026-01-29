/*
* /d/Faerun/guilds/fire_knives/rooms/obj/belt.c
*
*
*
*/
#include <macros.h>
#include <wa_types.h>
inherit "/std/armour";
inherit "/lib/keep";

public void
create_armour()
{
    set_name("belt");
    
    set_adj("black");
    
    add_adj(({"leather"}));
    
    set_short("black leather belt");
    set_pshort("black leather belts");
    
    set_long("A black leather belt made from the softest "
    +"deerskin, otherwise unadorned aside from a buckle "
    +"and holes to fasten it.\n");
    
    set_ac(4);
    set_am(({1, -1, 0}));
    set_at(A_WAIST);
    add_prop(OBJ_I_VOLUME, 100 + random(20));
    add_prop(OBJ_I_WEIGHT, 200 + random(40));
    add_prop(OBJ_I_VALUE, 2000);
}