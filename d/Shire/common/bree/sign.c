inherit "/std/object.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object() {
   set_name("sign");
   set_long("@@my_long");
   set_short("sign pointing north");

   add_prop(OBJ_I_NO_GET, 1);
}

init() {
   add_action("do_read","read");
}

do_read(str) {
   if (str != "sign") return 0;

   write(my_long());
   return 1;
}

my_long() {
   return "You read:\n"
        + "You will find the Hin Warrior Guild in the mountains.\n";
}
