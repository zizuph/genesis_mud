/*
 * Carnyx - a horn that when played can lift the panic levels
 * slightly.
 */
 
#pragma strict_types;

#include "macros.h"
#include "stdproperties.h"

#include "../defs.h"

inherit "/std/object";

#define MAX_EFFECT -10
#define MANA_COST   25
#define SG_INSTRUMENTAL 130050

void
create_object ()
{
  set_name("carnyx");
  add_name("horn");
  add_adj("curved");
  set_short("carnyx");
  set_long("This horn, called a carnyx, is a musical instrument, "+
           "made of bronze, and ending in a boar head. You feel "+
           "that if you could play it, a powerful sound would "+
           "emit.\n");

  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 3000);
  add_prop(OBJ_I_VALUE,  1000);
  add_prop(OBJ_S_WIZINFO, "This horn, when blown, lifts spirits "+
           "of the team members of the player (but not the player "+
           "him or herself) - reducing the panic levels a little "+
           "bit. The player pays a mana price, though.\n");
}

int
play_horn (string str)
{
  if (!str || str != "horn" && str != "carnyx")
    NF0("Play what?");

  if (TP->query_skill(SG_INSTRUMENTAL) < 10) {
    TP->catch_msg("You turn the horn in your hands, but are completely "+
                  "unsure how to play it.\n");
    tell_room(ENV(TP), QCTNAME(TP) + " looks at the horn, turns it a "+
              "couple of times in his hands, and leaves it alone.\n",
              ({TP}));
    return 1;
  }

  if (TP->query_mana() < MANA_COST) {
    TP->catch_msg("You don't feel mentally strong enough to attempt this "+
                  "powerful instrument.\n");
    return 1;
  }
  TP->catch_msg("You blow the horn with confidence. A powerful sound "+
                "blows from it. You feel a bit drained from the effort, "+
                "though\n");
  tell_room(ENV(TP), QCTNAME(TP) + " lifts the carnyx to his lips and "+
            "blows it with confidence. A powerful sound comes out of it.\n",
            ({TP}));
  TP->add_mana(-MANA_COST);
  object *team_members = TP->query_team_others();
  int t = 0;
  int effect;
  foreach (object team_member: team_members) {
    if (ENV(TP) != ENV(team_member))
      continue;
    t++;
    if (! team_member->query_panic()) {
      team_member->catch_msg("You do not feel any effect, though.\n");
      continue;
    }
    effect = MAX_EFFECT * TP->query_skill(SG_INSTRUMENTAL) / 100;
    team_member->catch_msg("You feel your spirits lifted.\n");
    team_member->add_panic(effect);
  }
  
  if (! t) {
    TP->catch_msg("Unfortunately, no team members were present to feel "+
                  "the call of the horn.\n");                  
  }
  return 1;
}

void
init ()
{
  ::init();
  add_action(play_horn, "play");
}
