inherit "/std/leftover.c";
#include "/d/Terel/include/Terel.h";

void
create_leftover()
{
   seteuid(geteuid(this_object()));
   
   set_name("skin");
   set_pname("skins");
   set_adj(({"wolf"}));
   set_long("A bloody wolf skin.\n");
   
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,300);
}