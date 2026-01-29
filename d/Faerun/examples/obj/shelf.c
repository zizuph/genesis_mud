/* shelf
 * Cirion 011398
 * from /d/Avenir/union/room/alcove.c
 * This is a surface on which items can be placed. It is based on
 * the Shadow Union bookshelf. Thanks to Lilith!
 * - Finwe, April 2004
 */
#pragma strict_types

inherit "/std/container";

#include "/d/Faerun/defs.h"
#include <ss_types.h>

void create_surface() {}

void create_container() 
{
  if(!IS_CLONE)
      return;

  set_name("shelf");
  set_adj(({"east","wide","wood","sturdy"}));
  set_short("sturdy shelf");
  set_long("A wide shelf made of wood. It is quite deep and looks "+
      "like it is capable of carrying a good deal of weight without "+
      "collapsing. ");

  remove_prop(CONT_I_TRANSP);
  add_prop(CONT_I_MAX_WEIGHT, 500000);
  add_prop(CONT_I_MAX_VOLUME, 500000);
  add_prop(CONT_I_WEIGHT, 100000);
  add_prop(CONT_I_VOLUME, 100000);
  add_prop(OBJ_I_VALUE, 1934);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_M_NO_GET, "You can't take it.\n");
  add_prop(CONT_I_ATTACH, 1);

  set_no_show_composite(1);

  setuid(); 
  seteuid(getuid());
  create_surface();

}
