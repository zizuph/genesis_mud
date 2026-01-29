/* stone.c: The thing that causes the tell effect.
   This is the gagged stone. */

#include <options.h>
#include <macros.h>
#include <composite.h>
#include "../../local.h";

inherit "/std/object";

#define HEDGE             NOBLE + "hedge"

create_object()
{
 set_name("bench");
 add_name("benches");
 set_short("series of curved marble benches");
 set_long("Three curved benches of translucent marble circle the pool "
 + "on all but its east side.\n");
 add_prop(OBJ_I_NO_GET,1);
 enable_commands();
 seteuid(getuid(this_object()));
}

void catch_msg(mixed str, object obj)
{
 int i;
 object *ob, *hedge;
 int size;

 if (stringp(str))
 {
  str = "PARK: " + str;
 }
 else if (pointerp(str))
 {
  for (i = 0; i < sizeof(str); i++)
  {
   if (strlen(str[i]))
   {
    str[i] = "PARK: " + str[i];
   }
  }
 }
 
 ob = (find_object(HEDGE))->return_obj_in_hedge();

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
