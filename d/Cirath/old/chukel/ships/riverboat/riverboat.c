/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ships/riverboat/cabin.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/d/Genesis/ship/ship";
#include "defs.h"

object cap;

void
create_ship()
{
  seteuid(getuid());
  set_cabin(BOAT+"cabin");
  set_deck(BOAT+"deck");
  cap=clone_object(BOAT+"captain");
  set_captain(cap);
  set_places_to_go(({  S_TRADE+"r12",
                       BOAT+"river",
                       S_TRADE+"r13",
                       BOAT+"river"}));
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
      cap = clone_object(BOAT+"krull");
      set_captain(cap);
      cap->move_living("X",ENV(TO));
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
          tell_room(BOAT+"deck","Krell rescues "+QCTNAME(obs[i])+".\n");
          obs[i]->move_living("M",BOAT+"deck");
        }
      else
        if(obs[i]!=TO)
          {
            if(member_array("ship",obs[i]->query_names())<0)
              obs[i]->remove_object(); /* remove corpses */
          }
    }
}
