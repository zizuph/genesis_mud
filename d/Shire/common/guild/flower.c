inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/open/randomize.h"

string color;

create_object() {
   color = random_colour();
   set_short("beautiful " + color + " flower");
   set_pshort("beautiful " + color + " flowers");
   set_long(break_string(
     "This is a beautiful " + color + " flower. It smells wonderful and "
   + "looks like no other flower in this neighbourhood. It looks like it "
   + "has been put here by divine providence.\n",70));
   set_name("flower");
   set_pname("flowers");
   set_adj(({"beautiful",color}));

   add_prop(OBJ_I_NO_GET,1);
   add_prop(OBJ_I_NO_INS,1);
   call_out("wither",300);
}

get() {
   write("The flower is far too fragile to pick. You decide to leave it alone.\n");
   return 1;
}

wither() {
   set_short("withered " + color + " flower");
   set_pshort("withered " + color + " flowers");
   set_long("The once beautiful " + color + " flower is withering slowly.\n");
   set_adj(({"withered",color}));
   call_out("go_away",400);
}

go_away() {
   tell_room(environment(), "The withered flower crumbles to dust.\n");
   remove_object();
}

