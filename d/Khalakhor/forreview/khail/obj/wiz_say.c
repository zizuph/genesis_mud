#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/object";

void
create_object()
{
  set_name("wiz sayer");
  add_name("wsay");
  set_short("wiz sayer");
  set_long("Stexx's wiz sayer. Anything said with ws instead of say will be"+
    "heard by any wizard in the same room, but not mortals.\n");

  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE, 1);
}

void
init()
{
  ::init();
  add_action("w_say", "ws");
}

int
w_say(string str)
{
object *temp, *exceptions;
int i;
  if(!strlen(str))
    return 0;

  exceptions = ({this_player()});

  temp = FILTER_LIVE(all_inventory(environment(this_player())));

  for(i = 0; i < sizeof(temp); i++)
    {
    if(!find_object("/secure/master")->query_wiz_level(temp[i]->query_real_name()))
      exceptions += ({temp[i]});
    }

  this_player()->catch_msg("You wiz-say: "+str+"\n");
  tell_room(environment(this_player()),this_player()->query_name()+" wiz-says: "+str+
    "\n",exceptions);
  return 1;
}

string
query_auto_load()
{
  return MASTER;
}
