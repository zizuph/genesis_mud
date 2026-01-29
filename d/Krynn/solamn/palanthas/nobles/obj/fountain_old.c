/* stone.c: The thing that causes the tell effect. 
   This is the ungagged stone. */

#include <options.h>
#include <macros.h>
#include <composite.h>
#include "../../local.h";

inherit "/std/object";

#define HEDGE           NOBLE + "hedge"

create_object()
{
 set_name("fountain");
 add_adj(({"tall", "marble", "tower"}));
 set_short("tall marble tower fountain");
 set_long("The fountain is a small scale replica of the Tower of "
	+ "Arms in the Merchants district.  Rising from a white, marble pool, "
	+ "it stands nearly eight feet.  Streams of water arc high into the "
	+ "air from the tops of its four corners before falling with tinkling "
	+ "bloops into the stone pool below.\n");
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
  if (!ob[i]->query_option(OPT_GAG_MISSES) 
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
  if(opt == OPT_GAG_MISSES) return 0;
}
