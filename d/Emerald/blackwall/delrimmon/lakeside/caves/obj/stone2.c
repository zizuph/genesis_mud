/* stone.c: The thing that causes the tell effect.
   This is the gagged stone. */

inherit "/std/object";
#include "defs.h"
#define RINGSIDE TYR_STADIUM+"ringside"
#include <options.h>


create_object()
{
 set_name("stone2");
 add_name("test");
 set_short("small stone");
 set_long("A small stone.\n");
 add_prop(OBJ_I_NO_GET,1);
 enable_commands();
 set_no_show(1);
 seteuid(getuid(this_object()));
}

void catch_msg(mixed str, object obj)
{
 int i;
 object *ob, *ringside;
 int size;

 if (stringp(str))
 {
  str = "ARENA: " + str;
 }
 else if (pointerp(str))
 {
  for (i = 0; i < sizeof(str); i++)
  {
   if (strlen(str[i]))
   {
    str[i] = "ARENA: " + str[i];
   }
  }
 }
 
 ob = (find_object(RINGSIDE))->return_obj_in_seats();

 size = sizeof(ob);

 for(i = 0; i < size; i++)
 {
  if (ob[i]->query_option(OPT_GAG_MISSES) 
      && !ob[i]->query_option(OPT_BLOOD)
      && CAN_SEE_IN_ROOM(ob[i]))
  {
   ob[i]->catch_msg(str);
  }
 }
}

int
query_option(int opt)
{
  if(opt == OPT_GAG_MISSES) return 1;
}

