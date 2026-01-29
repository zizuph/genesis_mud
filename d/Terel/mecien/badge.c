inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

create_armour(){

set_name("badge");
set_adj("conservative");

set_long("I love Rush Limbaugh\n");

set_at(A_R_ARM);

add_prop(OBJ_I_NO_DROP, 1);
}

query_auto_load(){
return MASTER + ":";
}

