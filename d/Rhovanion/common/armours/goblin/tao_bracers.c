/* Bracers 30 AC            */
/* 18-Apr-2001 Dimitry@Igor */

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

void
create_armour()
{
  set_name("bracers");
  set_short("pair of rusty elven bracers");
  set_pshort("rusty elven bracers");
  set_adj(({"rusty","elven"}));
  set_long("These are old and rusty elven bracers which are made of light silvery "+
           "metal. The bracers are quite light and dirty. It is a part " +
           "of the equipment of some unlucky elven warrior who has dared " +
           "to mess with mighty goblin warriors.\n");
  set_ac(30);
  set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, 4000);
}
