/*   Temple of Dephonia, Sarcophogas of Necropistis
 *   Location: Crypt; guarded by minotaur in adjacent room
 *   HISTORY:
 *   CODER         DATE             ACTION
 *  ------------ -------- -----------------------------------------------
 *   Zima         5/15/94   Created
 *
 */
 
 
inherit "/std/receptacle";
 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"
 
void
create_container()
{
set_name("sarcophogas");
set_adj("ancient");
set_adj("marble");
set_short("sarcophogas");
set_long(break_string(
     "It is an ancient marble sarcophogas, the tomb of some past " +
     "hero of the order. The lid is encrusted with precious " +
     "gems and embossed with a crested raven wearing a helmet and " +
     "grasping a golden sword and shield in its talons. It is covered " +
     "in dust and doesn't look like it has been bothered in a very long " +
     "while. You see an inscription on the lid.\n", 60));
 
add_prop(CONT_I_WEIGHT,      2000000); /* 2000 kilos */
add_prop(CONT_I_MAX_WEIGHT,  2000000); /* 2000 kilos */
add_prop(CONT_I_VOLUME,       200000); /* 200 liters */
add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
add_prop(CONT_I_RIGID, 1);
add_prop(OBJ_M_NO_GET, "It is too heavy to move.\n");
 
seteuid(getuid());
clone_object(WEAPON_DIR+"nsword")->move(this_object());
clone_object(ARMOUR_DIR+"nhelmet")->move(this_object());
clone_object(ARMOUR_DIR+"nshield")->move(this_object());
clone_object(OBJ_DIR+"skeleton")->move(this_object());
}
