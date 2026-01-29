inherit "/std/object.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object() {
   set_name("sign");
   set_long("@@my_long");
   set_short("rough-hewn sign on a small sign-post");

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
   return "You see a hand lettered sign, written "+
	"in big bright letters.  You read:\n"+
          "Welcome to the village of Stock!\n"+
	"The villagers of Stock.\n";
}

