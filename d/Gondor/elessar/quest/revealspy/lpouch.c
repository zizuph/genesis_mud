/*
 * A small leather pouch, by Lord Elessar Telcontar
 *
 * Revision history:
 * /Mercade, 23 November 1993, changed from container to /std/receptacle
 */

inherit "/std/receptacle";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_container()
{
  set_name("pouch");
  set_adj("leather");
  set_adj("small");
  set_short("leather pouch");
  set_long("A small leather pouch for keeping things in.\n");
  add_prop(CONT_I_IN,1);
  add_prop(CONT_I_WEIGHT,100);
  add_prop(CONT_I_VOLUME,100);
  add_prop(CONT_I_MAX_WEIGHT,500);
  add_prop(CONT_I_MAX_VOLUME,400);
  add_stuff();
}


add_stuff()
{
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/elessar/obj/ruby")->move(this_object());
}
