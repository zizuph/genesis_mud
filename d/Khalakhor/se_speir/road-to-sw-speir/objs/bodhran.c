/*
 * Bodhran - a drum that can be heard in the nearby rooms
 * Tapakah, 09/2021
 */

#pragma strict_types;

#include "macros.h"
#include "stdproperties.h"

#include "../defs.h"

inherit "/std/object";

#define EFFORT 50

void
create_object ()
{
  set_name("bodhran");
  add_name("drum");
  add_adj(({"goatskin", "wide"}));
  set_short("bodhran");
  set_long("This drum is a wooden frame bound by goatskin, tacked to one "+
           "side. It is quite large, about two feet wide. "+
           "You can try tapping or beating it.\n");
  add_prop(OBJ_I_WEIGHT, 1700);
  add_prop(OBJ_I_VOLUME, 4500);
  add_prop(OBJ_I_VALUE, 300);
  add_prop(OBJ_S_WIZINFO, "This drum can be heard in neighboring rooms " +
           "when beaten. It costs a considerable chunk of fatigue to "+
           "beat.\n");
}

int
tap_drum (string str)
{
  if (! str || str != "drum" && str != "bodhran")
    NF0("Tap what?");

  TP->catch_msg("You tap the drum lightly, producing a nicely sounding "+
                "rhythm.\n");
  tell_room(ENV(TP), QCTNAME(TP) + " taps the drum, producing a nicely sounding "+
            "light rhythm.\n", TP);

  return 1;
}

int
beat_drum (string str)
{
  if (! str || str != "drum" && str != "bodhran")
    NF0("Tap what?");

  int fatigue = TP->query_fatigue();
  if (fatigue < EFFORT) {
    TP->catch_msg("You are too tired to beat the drum.\n");
    return 1;
  }
    
  TP->catch_msg("You beat the drum hard, making sure anyone in your "+
                "vicinity and even somewhat beyond can hear it.\n");

  tell_room(ENV(TP), QCTNAME(TP) + " beats the drum hard, and the sound "+
            "is heard far and wide.\n", TP);

  object *exits = ENV(TP)->query_exit_rooms();
  foreach (string exit: exits)
    if (EXISTS(exit))
      tell_room(exit, "You hear someone beating a drum nearby.\n", 0);

  TP->add_fatigue(-EFFORT);
  return 1;
}

void
init ()
{
  ::init();
  add_action(tap_drum, "tap");
  add_action(beat_drum, "beat");
}
