inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("vest");
   set_adj("leather");
   add_adj("spiked");
   set_short("spiked leather vest");
   set_long("This looks to be made from some sort of hide "
   	+"that has been tanned and formed into leather.  From "
   	+"the tattered edges around the shoulders, you can tell "
   	+"there used to be sleeves on it, but were removed, most "
   	+"likely for comfort.  Small spikes of obsidian and "
   	+"chitin stud the vest, offering some protection.\n");
   set_ac(25);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,1000);
}

