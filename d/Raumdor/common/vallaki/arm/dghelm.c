inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#pragma strict_types

void
create_armour()
{
    ::create_armour();
    set_name("silver helm");
    add_name("helm");
    set_pname("helms");
    set_short("silver helm");
    set_pshort("silver helms");
    set_long("This helm is strong and shiny. It gleams in the light. A "+
      "symbol of a golden cross adorns the forehead part.\n"); 
    set_ac(35);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 240);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 1500);
}
