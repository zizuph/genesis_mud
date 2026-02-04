/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/container";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define OBJ "/d/Terel/mecien/valley/guild/obj/"

create_container(){

set_name("lamp");
set_adj("silver");
add_name("mystic_lamp");
set_long(
"A small silver lamp, of diamond shape. It is covered with an\n"
+"intricate scroll pattern and tiny stars.\n"
);

add_prop(CONT_I_TRANSP, 1);
add_prop(CONT_I_RIGID, 1);
add_prop(CONT_I_CLOSED, 1);
}

