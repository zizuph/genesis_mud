inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

string gMessage, gSender;

create_object() {
   set_name("message");
   set_pname("messages");
   set_short("message");
   set_pshort("messages");
   set_long("@@read_message");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_NO_DROP, "@@do_destruct");
   gMessage = "Nothing.\n";
   gSender = "Someone";
}

init() {
   add_action("do_read", "read",0);
}

do_read(str) {
   if (str == "message" || str == short())
   {
      write(read_message());
      return 1;
   }
}

read_message() {
   return ("The message reads:\n" + gMessage);
}

do_destruct() {
   set_alarm(2.0,0.0,"destruct_me");
   return 0;
}

set_message(str) {
   gMessage = str;
}

set_sender(str) {
   gSender = capitalize(str);
   set_short("message from " + gSender);
   set_pshort("messages from " + gSender);
}

query_sender() {
   return gSender;
}

destruct_me() {
   object room;
   if (living(room = environment()))
      room = environment(room);
   tell_room(room, "The message blows away with the wind.\n");
   remove_object();
}
