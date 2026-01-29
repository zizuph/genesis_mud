#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <language.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
   set_name("mushroom");
   set_short("red mushroom");
   set_herb_name("coccinea");
   set_pshort("red mushrooms");
   set_adj("red");
   set_id_long("This is a red mushroom of the family Hygrocybe and species " 
	       + "coccinea. It has a red top and blood-red flesh the lamells "
	       + "are quite broad and widespaced. It is rumoured to have "+
	       "properties that make it needed when making invisibility " +
	       "potions.\n");
   set_unid_long("A small red mushroom with large lamells, it is a little "+
	         "slimy. The flesh has a blood-red colour it looks " +
                 "quite beautiful.\n");

   set_id_diff(20);
   set_find_diff(4);
   set_amount(10);
   set_decay_time(7200);
   set_herb_value(144);
   set_dryable();
}
