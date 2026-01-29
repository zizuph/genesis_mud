
/* 
  Ticket for the Gelan-kalad shipline that runs from Calia.
*/

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

void
create_object()
{
    set_name("ticket");
        add_name("gelan-kalad line");
        add_adj("black");
        set_long("It is a dark black ticket used for ship passage on "+
            "the shipline that runs from Gelan to Kabal. "+
                "You somehow feel that you can 'check passengers' "+
                "to discover who is on board, if the captain is around to "+
                "ask, as long as you've got this ticket.\n");
    add_prop(OBJ_I_VALUE, 70);
    add_prop(OBJ_M_NO_SELL, 1); 
}

void
init()
{
  ::init();
  add_action("check_passengers", "check");
}

int
check_passengers(string str)
{
   object *obarr;
   int i;

  notify_fail("Check what? Passengers, maybe?\n");

  if(!strlen(str) || str != "passengers")
    return 0;


  if(find_object("/d/Calia/ships/kalad/deck"))
  obarr = FILTER_LIVE(all_inventory(find_object("/d/Calia/ships/kalad/deck")));

  if(find_object("/d/Calia/ships/kalad/cabin"))
  obarr += FILTER_LIVE(all_inventory(find_object("/d/Calia/ships/kalad/cabin")));

  for(i < 0; i < sizeof(obarr); i++)
    {
    if(function_exists("create_monster", obarr[i]) == "/d/Calia/ships/kalad/captain")
      obarr -= ({obarr[i]});
    }
  if(!present("_hadrashak_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_hadrashak_", environment(this_player()))->command("say "+
      "Actually business has been slow, nobody is on board.");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_hadrashak_", environment(this_player()))->command("say "+
      "Well, I've had better days, only "+COMPOSITE_LIVE(obarr)+" is "+
      "on board.");
    return 1;
    }

  present("_hadrashak_",environment(this_player()))->command("say "+
    "At the moment, "+COMPOSITE_LIVE(obarr)+" are on the ship.");
  return 1;
}
