inherit "/std/object.c";
#include "/d/Kalad/defs.h"

void
create_object()
{
   set_name("bath");
   set_adj("ornate");
   add_adj("huge");
   set_short("huge ornate bath");
   set_long("This bath is HUGE it is made of adamant and looks as if can hold hundreds of gallons of water. "+
   "There is a sweet plesant smell rising from the steaming water. The "+
   "outside of the bath is covered in gems, and there are glowing runes "+
   "visiable through the slightly bubbly water.\n");
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,100000);
   add_prop(OBJ_I_VALUE,5000000);
}
