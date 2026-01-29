/* created by Aridor 09/14/93 */

#include <composite.h>
#include <filter_funs.h>
#include "../local.h"
#include CLOCKH

inherit CITY_ROOMBASE;

#define JAIL "/d/Krynn/solamn/palanthas/city/jailcell"

object chief;

string
query_to_jail()
{
  return "south";
}

reset_palan_room()
{
	if(!objectp(chief))
	  {
		chief = clone_object(LIV + "chief");
		chief->move(TO);
	  }

    if (E(chief) != TO)
      {
	  if (sizeof(FILTER_PLAYERS(all_inventory(E(chief)))))
	    return;
	  else
	    chief->move_living("again",TO);
      }
    if (chief)
      chief->perform_the_release(1);
}

void
create_palan_room()
{
    SHORT("City jail foyer");
    LONG("@@my_long");

    clone_object(OBJ + "jaildooro")->move(TO);

    ITEM(({"bunk","bunks"}),"All bunks look dirty and unmade. You can "
          +  "count six bunks.\n");
    ITEM(({"rack","racks","armour rack","armour racks","weapon rack",
		 "weapon racks"}),
             "Unfortunately, the racks are empty at the " +
             "moment, probably everyone has taken his things with him on " +
             "duty.\n");
    ITEM(({"jail","cell"}),"@@who_is_jailed");

    EXIT(ROOM + "plaza","north",0,0);
    EXIT(ROOM + "jailcell", "south", 0, 0);

    reset_palan_room();
}


string
who_is_jailed()
{
    object *things;
    object ja;
    string pers;
    JAIL->load_me();
    ja = find_object(JAIL);
    things = all_inventory(ja);
    pers = COMPOSITE_LIVE(things);
    if (pers == "someone")
      return "The jail to your north is completely empty at the moment.\n";
    return "You can see " + pers + " in the cell to your north.\n";
}

string
my_long()
{
    string jailed = who_is_jailed();
    return "This is the office of the City Guard. There are a few " +
      "bunks here, as well as some racks for armour and weapons. " +
      jailed;
}


help_i_need_help(mixed who, object where)
{  
    set_alarm(18.0,0.0,"help_on_the_way", who, where);
}

help_on_the_way(mixed who, object where)
{
    if (chief)
      chief->arrest_prisoner(who, where);
}
