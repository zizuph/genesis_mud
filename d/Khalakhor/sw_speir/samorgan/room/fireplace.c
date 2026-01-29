#pragma strict_types

#include <macros.h>

#include "../defs.h"

int
stoke_fire (string str)
{
  if (str == "the fire" || str == "fire" ||
      str == "logs"     || str == "the logs")  {
    write("You take out a poker and stoke up the fire in "+
          "the fireplace.\nThe fire burns more brightly.\n"+
          "You replace the poker in its holder.\n");

    say(QCTNAME(TP)+" picks up the fireplace poker from "+
        "the holder and begins to stoke the fire.\n"+
        "The fire burns brighter now.\n");
    say(QCTNAME(TP)+" returns the fireplace poker to its holder.\n");
    return 1;
  }
  else
    NF0("Stoke what? Stoke the fire perhaps?\n");
}

int
log_fire (string str)
{
  if(str == "log on fire"  || str == "log on the fire" ||
     str == "wood on fire" || str == "wood on the fire")  {
    write("You take out a log from the firebox and place it "+
          "on the fire.\nThe fire burns more brightly.\n");
    say(QCTNAME(TP)+" takes out a log from the firebox and "+
        "places it on the fire.\nThe fire burns brighter now.\n");
    return 1;
  }
  else
    NF0("Put what? Put log on fire perhaps?\n");
}

int
warm_it (string str)
{
  switch (str) {
  case  "face":
    write("You press your face forward to warm your cheeks "+
          "from the heat of the fireplace.\n"+
          "Ahh nice and warm.\n");
    say(QCTNAME(TP)+" puts "+HIS(TP)+" face closer to the "+
        "fireplace.\n");
    break;
  case  "hands":
    write("You place your hands near the fire and rub them "+
          "together trying to warm them.\n"+
          "The warmth from the fire feels good on your skin.\n");
    say(QCTNAME(TP)+" places "+HIS(TP)+" hands very close "+
        "to the fire and begins to rub them together.\n");
    break;
  case  "legs":
    write("You step very close to the fireplace and rub "+
          "along your legs to warm them up.\n"+
          "The heat of the fire feels warm on your skin.\n");
    say(QCTNAME(TP)+" steps up to the fireplace and starts "+
        "to rub "+HIS(TP)+" legs, which appears to warm them.\n");
    break;
  case "ears":
    write("You lean your head forward. You then turn from "+
          "side to side rubbing your ears to warm them before the "+
          "hot fire.\n");
    say(QCTNAME(TP)+" learns forward to the fireplace and "+
        "turns "+HIS(TP)+" head from side to side while rubbing "+
        HIS(TP)+" ears.\n");
    break;
  case "feet":
    write("You put your feet closer to the fire rubbing "+
          "them, hoping the fire will warm them up.\n");
    say(QCTNAME(TP)+" puts "+HIS(TP)+" feet closer to "+
        "the fire and rubs them.\n");
    break;
  case "body":
    write("You step up to the fire and feel the heat soothe "+
          "your bones.\n");
    say(QCTNAME(TP)+" steps up to the fire for a long "+
        "moment.\n");
    break;
  case "bottom":
    write("You step up to the fire and stick your bottom "+
          "towards it.\n");
    say(QCTNAME(TP)+" steps up to the fire sticking "+
        ""+HIS(TP)+" bottom towards it.\n");
    break;
  default:
    NF0("Warm what? Which part of the body?\n");
  }
  return 1;
}

int
extinguish_fire (string str)
{
  if(str == "the fire" || str == "fire") {
    write("You try to extinguish the fire in the fireplace "+
          "but fail.\n");
    say(QCTNAME(TP)+" tries to extinguish the fire in the "+
        "fireplace but fails.\n");
    return 1;
  }
  else
    NF0("Extinguish what? Extinguish the fire perhaps?\n");
}

void
init_fire ()
{
  add_action(stoke_fire, "stoke");
  add_action(log_fire, "put");
  add_action(warm_it, "warm");
  add_action(extinguish_fire, "extinguish");
}
