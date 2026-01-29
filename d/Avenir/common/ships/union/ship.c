// name:          Ulia
// creator(s):    Cirion, April 1997
// last update:   
// purpose:       Ship that ferrys a player between the tomb of Akram and the
//                south shore of the park island.
// note:
// bug(s):
// to-do:   

#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>
#include "/d/Avenir/common/ships/ship.h"

#ifdef DEBUGGING
#define DEBUG(x)   find_living("cirion")->catch_tell("Ship debug: " + x + "\n")
#else
#define DEBUG(x)   ;
#endif

void create_ship()
{
    object cap;

    set_name("ship");
    add_name("ulia");
    add_adj("slender");
    set_short("slender ship");
    set_long("This is a long, slender ship, its wooden hull made from "
       + "thin lathes of ashwood. The hull has a deep greenish tint "
       + "to it.\n");

    set_deck(USHIP + "deck");

    seteuid(getuid());
    cap = clone_object(USHIP + "naiad");
    cap->equip_me();
    set_captain(cap);
    set_callout_fq(1);

    set_places_to_go(({
      USHIP + "void_room",
      SEA + "darkseae1",
      SEA + "darkseae2",
      SEA + "darkseae3",
      SEA + "darkseae4",
      SEA + "darkseae5",
      SEA + "darkseae6",
      SEA + "darkseae7",
      SEA + "darkseae8",
      UNION + "tomb/tomb_landing",
      SEA + "darkseae8",
      SEA + "darkseae7",
      SEA + "darkseae6",
      SEA + "darkseae5",
      SEA + "darkseae4",
      SEA + "darkseae3",
      SEA + "darkseae2",
      SEA + "darkseae1"
                   }));

    set_time_between_stops(({
      60,
      10,
      10,
      10,
      10,
      10,
      10,
      10,
      10,
      60,
      10,
      10,
      10,
      10,
      10,
      10,
      10,
      10
    }));

  }


int
board(mixed what)
{
    // free passage
    write("You board the ship.\n");
    environment(this_player())->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    DEBUG("Entering " + file_name(to));
}
