#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/drink";

int toast_people(string args);

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("beer");
    set_adj("small");
    set_short("small beer");
    set_pshort("small beers");
    set_long("It's a small but refreshing beer.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

public void
init()
{
        ::init();
        add_action(toast_people, "toast");
}

int
toast_people(string args)
{
  object player;

  player = environment(this_object());

  if(!interactive(player))
  {
    return 0;
  }

  if(args == "people" || 
     args == "everyone")
  {
    object* objects = all_inventory(environment(player));
    object* players = FILTER_PLAYERS(objects);

    if(sizeof(players) > 1)
    {
      player->catch_msg("You raise your "+short()+" and toast everyone.\n");
      tell_room(environment(player), QCTNAME(player)+" raises "+HIS(player)+" "+short()+" in a toast.\n", player);
    }
    else
    {
      player->catch_tell("There are no one here to toast with.\n");
    }
    return 1;
  }
  return 0;
}


