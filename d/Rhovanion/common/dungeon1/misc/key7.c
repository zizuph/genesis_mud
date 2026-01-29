inherit "/std/key";
#include <stdproperties.h>

create_key()
{
   set_name("key");
   set_pname("keys");
   set_short("ornate copper key");
   set_pshort("ornate copper keys");
   set_adj(({"copper","ornate"}));
   set_key(100);
   set_long("This is a small, ornately smithed, copper " +
      "key.\n");
   add_prop(OBJ_I_WEIGHT, 500);
}
