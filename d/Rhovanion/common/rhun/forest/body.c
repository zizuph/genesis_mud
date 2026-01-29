
inherit "/std/container";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>

reset_container()
{
if (present("_sw_quest_badge",TO)) return;
clone_object(RHUN+"forest/badge")->move(TO,1);
}

create_container()
{
  set_short("bloodied corpse");
  set_long("This is the bloodied"
	+" corpse of a Easterling officer.  It is torn and tattered."
	+"  He seems to have been dead only a little while.  His uniform"
	+" portrays him as a figure of some importance.\n");
set_name("corpse"); add_name("body"); set_adj("bloodied");

add_prop(CONT_M_NO_INS,1);
add_prop(CONT_I_ATTACH,1);
add_prop(CONT_I_RIGID,1);
add_prop(OBJ_M_NO_GET,1);

SGT
clone_object(RHUN+"forest/badge")->move(TO,1);

}
