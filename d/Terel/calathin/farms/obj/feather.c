inherit "/std/object.c";
#include "/d/Terel/include/Terel.h";

void
create_object()
{
   seteuid(geteuid(this_object()));
   
   set_name("feather");
   set_pname("feathers");
   set_short("feather");
   set_adj(({"white","small","chicken"}));
   set_long("A small white chicken feather.\n");
   
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_VALUE,2);
   add_prop(OBJ_I_WEIGHT,0);
   add_prop(OBJ_I_VOLUME,0);
}
