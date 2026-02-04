/*
A readable note.
*/
inherit "/std/object";
#include <stdproperties.h>

init()
{
   add_action("read", "read");
   ::init();
}

create_object()
{
   set_name("note");
   set_short("short note");
   set_long("It's a short note. Maybe you can read it.\n");
   set_adj("short");
   add_prop(OBJ_I_VALUE, 1);
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
}

read(string str) {
   if (str != "note") {
       return 0;
   }
   write("From the cornerstone you go: s,s,s,s,e,s,w,w,n,w,s,s,e,s\n");
   return 1;
}
