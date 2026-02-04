#include "/d/Terel/include/Terel.h"

inherit  STDOBJECT;
inherit  "/lib/keep";

string gMessage, gSender;

create_object() {
   gMessage = "Nothing.\n";
   gSender = "Someone";
   set_name("letter");
   set_pname("letters");
   set_short("@@my_short");
   set_pshort("@@my_pshort");
   set_long("@@my_long");
   add_prop(OBJ_I_WEIGHT, 5);
   add_prop(OBJ_I_VOLUME, 5);
   add_prop(OBJ_I_NO_DROP, "@@do_destruct");
   set_keep();
}

init() {
   add_action("do_read", "read",0);
}

my_short() {
   return ("letter from " + query_sender());
}

my_pshort() {
   return ("letters from " + query_sender());
}

my_long() {
   return read_message();
}


do_read(str) {
   notify_fail("Read what?\n");
   if (str == "letter" || str == my_short())
   {
      write(read_message());
      return 1;
   }
   else
      return 0;
}

read_message() {
      say(QCTNAME(this_player()) + " reads over a letter.\n");
      return ("The letter from "+ gSender+ " reads:\n" +
              " _________________________________________\n" + 
                  gMessage + "\n" +
              " _________________________________________\n");
}

set_message(str) {
   gMessage = str;
}

set_sender(str) {
   gSender = CAP(str);
}

query_sender() {
   return gSender;
}

destruct_me() {
   object room;
   if(living(ENV(TO)))
         return;
   else
   if (living(room = environment()))
      room = ENV(room);
   tell_room(room, "The letter blows away with the wind.\n");
   remove_object();
}

do_destruct() {
   set_alarm(5.0, 0.0, destruct_me);
   return 0;
}

enter_env(object to, object from)
{
   ::enter_env(to, from);
   do_destruct();
}

