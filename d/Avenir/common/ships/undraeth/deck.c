// file name: Deck   /d/Avenir/common/ships/kalad/deck.c
// creator(s):       Cirion, May 1996
// last update:
// purpose:          Deck of the Avatar
// note:
// bug(s):
// to-do:            

#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include "/d/Avenir/common/ships/ship.h"
#include "/d/Avenir/smis/sys/statserv.h"

void create_deck()
{
  set_short("on the deck of the small ship");
  set_long("The narrow prow of the ship makes standing difficult.\n");

  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, "@@check_light");
  set_bump_sound("The ship glides gently into the dock.\n");
  set_deck_sound("@@sounds");
}

int check_light()
{
  return ENV(ship)->query_prop(ROOM_I_LIGHT);
}

string sounds()
{
  string str;

  if(!strlen(str = ENV(ship)->darksea_sound()))
    return "The ship glides quietly along the still water.\n";
  else
    return str;
}

public varargs int disembark(string what)
{
    int res;

    res = ::disembark(what);
    if(res && file_name(environment(this_player()))[0..8] == "/d/Avenir")
        STATSERV_LOG_EVENT("avisits", "K_landing through ship from Kalad");
    return res;
}
