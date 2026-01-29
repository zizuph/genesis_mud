inherit "/std/object";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>

static int start_time;

void create_object()
{
  set_name("_hold_object");
  set_no_show();
  remove_prop(OBJ_I_VALUE);
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VOLUME);
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GET, 1);
}

int catch_all(string str)
{
  switch (query_verb())
  {
    case "commune":
    case "quit":
    case "bug":
    case "praise":
    case "typo":
    case "help":
    case "sysbug":
    case "reply":
      return 0;
    default:
      write("You are frozen!\n");
      return 1;
  }

  return 1;
}

void remove_object()  
{
  mixed fumble;
  int i;

  environment()->catch_msg("You regain control of your body and mind.\n");
  environment()->add_fatigue(-50);
  environment()->set_skill_extra(SS_DEFENCE, 0);
  environment()->set_skill_extra(SS_PARRY, 0);

  if (pointerp(fumble = 
      (string *)environment()->query_prop(LIVE_AS_ATTACK_FUMBLE)) &&
      sizeof(fumble -= ({ "" })))      
  {
    this_player()->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble);
  }
  else 
  {
    this_player()->remove_prop(LIVE_AS_ATTACK_FUMBLE);
  }

  ::remove_object();
}

void init()
{
  mixed fumble;
  int i;

  if ((this_player() != environment()) || IS_WIZ(this_player()))
  {
    remove_object();
    return;
  }

  set_alarm(15.0, 0.0, remove_object);

  ::init();

  add_action(catch_all, "", 1);

  this_player()->cmdhooks_break_spell();

  if (!(fumble = this_player()->query_prop(LIVE_AS_ATTACK_FUMBLE)))
  {
    fumble = ({ });
  }

  this_player()->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble + ({ "" }));
  this_player()->set_skill_extra(SS_DEFENCE,
      -(this_player()->query_skill(SS_DEFENCE)) + 1);
  this_player()->set_skill_extra(SS_PARRY,
      -(this_player()->query_skill(SS_PARRY)) + 1);
}
