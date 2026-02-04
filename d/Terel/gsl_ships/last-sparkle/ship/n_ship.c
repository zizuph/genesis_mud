#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();

  setuid();
  seteuid(getuid());
  set_deck(DECK);
  set_cabin(CABIN);

  set_name("trawler");
  add_name("boat");
  add_name("passenger trawler");
  add_name("ship");
  set_adj("large");
  add_adj("fishing");
  add_adj("passenger");
  set_short("large fishing trawler");
  set_long("A large fishing trawler. Once this boat was " +
           "used to transport people across the continent; that is, " +
           "between the northern and southern ports of Terel. It underwent "+
           "a major refitting and sails now between Last and Sparkle.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SPARKLE_PIER, LAST_PIER, }));
}
