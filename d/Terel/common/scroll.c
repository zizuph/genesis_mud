inherit "std/object";
#include <stdproperties.h>

create_object(){
set_name("scroll");
set_short("small chromatic scroll");
set_long("A beautiful scroll of fine parchment, upon which is a script\n"
  + "of strange chromatic hues.\n");
add_prop(OBJ_I_VALUE, 8);
add_cmd_item("scroll", "read",
 "I, Siydella de Avenchir, invite you to visit my beautiful home,\n"
+"which lies on the east side of Calathin. It is my family who has\n"
+"made Calathin, brought it to fame and greatness. We are entranced\n"
+"by your marvelous stories and tales, please come and grace our great\n"
+"estate with your presences.\n\n"
+"     \ I /   \n"
+ "   -  o  -   \n"
+"    / I \     \n"
);

}
