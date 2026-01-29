/* Bracers for Jaryx */

inherit "/std/armour";
inherit "/lib/keep";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <macros.h>

void create_armour()
{
  set_name("gloves");
  set_pname("gloves");
  set_short("pair of leather gloves");
  set_pshort("pairs of leather gloves");
  set_long("These gloves are made from hardened leather. "
  	+"They appear to have steel shanks in then. These "
  	+"would hurt someone if you hit them.\n");

  set_adj("leather");
  
  set_at(A_ARMS);
  set_ac(15);
  set_am(({ -2, 0, 2 }));
  set_af(this_object());

  add_prop(OBJ_I_WEIGHT,  800);
  add_prop(OBJ_I_VOLUME,  400);
}

