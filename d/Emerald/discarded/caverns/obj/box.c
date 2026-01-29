
inherit "/std/receptacle";
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

int i;

void
create_container()
{
   set_name("box");
   set_adj("cigar");
   set_short("cigar box");
   set_long("A rather large cigar box.\n");
   
   add_prop(CONT_I_WEIGHT, 500);
   add_prop(CONT_I_MAX_WEIGHT, 2000);
   add_prop(CONT_I_MAX_VOLUME, 25000);
   add_prop(CONT_I_VOLUME, 1000);
   seteuid(getuid());
   for(i=0; i<5; i++)
   {
      object cigar;
      cigar=clone_object(PIRATES_DIR + "obj/cigar");
      cigar->move(this_object());
   }
   add_prop(CONT_I_CLOSED, 1);
   
}
