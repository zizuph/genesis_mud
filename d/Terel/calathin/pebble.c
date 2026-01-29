inherit "/std/object.c";
#include "/d/Terel/include/Terel.h";

void
create_object()
{
   seteuid(geteuid(this_object()));
   
   set_name("pebble");
   add_name("rock");
   add_name("_prot_spell_ingr1_");
   add_name("tomas:pebble");
   add_adj(({"smooth","shiny"}));
   set_pname("pebbles");
   set_short("pebble");
   set_long("A common small rock.\n");
   
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_VALUE,2);
   add_prop(OBJ_I_WEIGHT,5);
   add_prop(OBJ_I_VOLUME,8);
}
