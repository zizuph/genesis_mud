/*
 * A sack
 *
 * Coded by Lord Elessar Telcontar
 *
 * Revision history:
 * /Mercade, 23 November 1993; changed from container to /std/receptacle
 */

inherit "/std/receptacle";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_container()
{
  set_name("sack");
  add_name("large sack","big sack");
  set_adj("large");
  set_short("large sack");
  set_pshort("large sacks");
  set_long("This large sack is excellent for putting things in.\n");
  add_prop(CONT_I_IN,1);
  add_prop(CONT_I_WEIGHT,500);
  add_prop(CONT_I_VOLUME,500);
  add_prop(CONT_I_MAX_WEIGHT,3000);
  add_prop(CONT_I_MAX_VOLUME,3500);
}
