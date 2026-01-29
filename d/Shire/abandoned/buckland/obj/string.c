inherit "std/rope.c";
#include "/sys/stdproperties.h"
void
create_rope()
{
   set_name("string");
   set_pname("strings");
   set_short("piece of string");
   set_pshort("pieces of string");
   set_long("An ordinary piece of string. You could tie things with it.\n");
   
   add_prop(OBJ_I_VALUE, 12);
   add_prop(OBJ_I_WEIGHT, 40);
   add_prop(OBJ_I_VOLUME, 50);
   
}
