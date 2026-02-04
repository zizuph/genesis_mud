inherit "/std/herb";
#include <herb.h>
#include <stdproperties.h>

create_herb(){
   
   set_name("wreath");
   set_adj("evergreen");
   add_name("evergreen_wreath");
   set_short("evergreen wreath");
   set_herb_name("luvico wreath");
   set_herb_name("wreath of holly, laurel, bayberry and luvico");
   set_id_long(
      "This beautiful wreath is woven together with a mix of " +
      "holly, laurel, bayberry and luvico. It has a wonderful fresh smell.\n");
   set_unid_long("A beautiful wreath of different evergreen leaves.\n");
   add_prop(OBJ_I_VALUE, 100);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));
}

