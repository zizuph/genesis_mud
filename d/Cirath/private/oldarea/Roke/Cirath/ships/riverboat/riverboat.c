inherit "/d/Genesis/ship/ship";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

#define BOATS "/d/Roke/Cirath/ships/"

object cap;

void
create_ship()
{
  seteuid(getuid());
  set_cabin(BOATS+"riverboat/cabin");
  set_deck(BOATS+"riverboat/deck");
  cap=clone_object(BOATS+"riverboat/captain");
  set_captain(cap);
  set_places_to_go(({  S_TRADE+"r12",
                       BOATS+"riverboat/river",
                       S_TRADE+"r13",
                       BOATS+"riverboat/river"}));
  set_time_between_stops(({15,3,15,3}));
  set_ticket_id("DurniRiver"); 
  set_name("boat");
  add_adj("puny");
  set_long("A little puny river boat for transportation over Durni.\n");

  call_out("check_captain",600);

}
check_captain()
{
  if(!cap)
    {
      cap = clone_object(BOATS+"riverboat/krull");
      set_captain(cap);
      cap->move_living("X",E(TO));
    }

  call_out("check_captain",600);

}
enter_env(object dest,object from)
{
  object *obs;
  int i;

  ::enter_env(dest,from);

  if(!(dest->query_prop(ROOM_I_TYPE)==1))
    return;

  obs = all_inventory(dest);

  for(i=0;i<sizeof(obs);i++)
    {
      if(living(obs[i]))
        {
          obs[i]->catch_msg("Krull pulls you out of the river.\n");
          tell_room(SHIPS+"gontsparkle/deck","Krell rescues "+QCTNAME(obs[i])+".\n");
          obs[i]->move_living("M",BOATS+"deck");
        }
      else
        if(obs[i]!=TO)
          {
            if(member_array("ship",obs[i]->query_names())<0)
              obs[i]->remove_object(); /* remove corpses */
          }
    }
}
