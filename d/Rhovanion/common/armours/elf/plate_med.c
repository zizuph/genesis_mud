/*
 * plate.c
 * Elven platemail
 * Written by Daneel november 1993
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <formulas.h>
#include "/d/Rhovanion/defs.h"

create_armour()
{
  set_name(({"mail","ringmail","elven"}));
  set_pname(({"mails","ringmails","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(17);
  set_at(A_BODY);
  set_am( ({ -1, 2, -1 }) );
  
  add_prop(OBJ_I_WEIGHT,6000);
  add_prop(OBJ_I_VOLUME,6000);
}

string query_long()
{
  return(BS("This is a green ringmail made of silver. \n"));
}

init()
{
  ::init();
}

