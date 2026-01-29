/* A hole to bury the bones in. This object
 * wins the quest.
 *     Cirion 041096
 */
#pragma strict_types

inherit "/std/container";
inherit "/d/Avenir/inherit/quest";

#include "../dead.h"
#include "/d/Avenir/common/port/bury_bones.h"

void create_container()
{
  set_name("hole");
  add_name(HOLE_ID);
  set_short("large hole");
  set_long("It is a large hole, dug into the soil "
     +"beneath the gnarled oak tree.\n");

  set_no_show_composite(1);

  add_prop(OBJ_M_NO_GET, 1);
  add_prop(CONT_I_MAX_VOLUME, 100000);
  add_prop(CONT_I_MAX_WEIGHT, 100000);
  add_prop(CONT_I_WEIGHT, 5000);
  add_prop(CONT_I_VOLUME, 5000);
  add_prop(CONT_M_NO_INS, "@@check@@");
}

mixed check()
{
  return ENV(TO)->check_bury();
}
