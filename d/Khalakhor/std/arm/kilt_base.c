/*
 * kilt_base.c
 *
 * Base object for kilts.
 *
 * Khail - August 12, 1997
 *
 * Modified so it's a wearable item instead, it now can be worn overtop
 * of leg armour.
 * Igneous  - October 27th 1998
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <composite.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/object";
inherit "/lib/wearable_item";

int autoloadable, drop_alarm, silent_drop;
string hunting, *colours, clan;

/*
 * Function name: create_kilt
 * Description  : Turns this object into a kilt.  
 * Arguments    : n/a
 * Returns      : n/a
 */
public void create_kilt()  {}

/* Function name:  create_unique_kilt
 * Description:    Enables you to create a non-stanard kilt
 */
public void create_unique_kilt() {}


nomask void
create_khalakhor_object()
{
  create_kilt();
  set_name("kilt");
  add_pname("clothing");
  add_pname("clothes");
  set_adj("heavy");
  add_adj("wool");    
  set_short("heavy wool kilt");
  set_long("This kilt is made from heavy wool, woven into " +
           "a pattern of " + COMPOSITE_WORDS(colours) + " checks and " +
           "lines on a " + hunting + " background, distinctive of " +
           clan + ". It's a knee-length skirt worn by men belted " +
           "around the waist.\n");

  set_slots(A_LEGS);
  set_looseness(8);
  set_layers(8);
  set_wf(TO);

  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 5000);

  create_unique_kilt();
}

/*
 * Function name: drop_kilt
 * Description  : Called at various places to make a check to
 *                see if the player is wearing a belt to keep
 *                the kilt on, and to remove the kilt if they
 *                aren't.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
drop_kilt()
{
  /* Do nothing if the kilt isn't being worn. */
  if (!query_worn())
    return;

  /* If the kilt's being worn, remove it if nothing is */
  /* being worn around the waist. */
  if (!wearer->query_clothing(A_WAIST)) {
    tell_room(environment(wearer), QCTNAME(wearer) + "'s " +
              short() + " falls off and drops to the ground.\n",
              ({wearer}));
    write("With nothing to hold it around your waist, the " +
          short() + " falls off and drops to the ground.\n");
    silent_drop = 1;
    remove_me();
    move(environment(wearer), 1);
  }
}

/*
 * Function name: wear
 * Description  : Called when the kilt is being worn.
 * Arguments    : what - Object pointer to the armour to wear.
 * Returns      : 1 - Wear successful, custom message.
 *                string - Wear failed, custom message.
 */
public mixed
wear(object what)
{
  object waist;

  say(QCTNAME(TP) + " wraps a " + short() + " around " +
      HIS_HER(TP) + " waist.\n");
  write("You wrap the " + short() + " around your waist.\n");
  return 1;
}

/*
 * Function name: remove
 * Description  : Called when removing the kilt.
 * Arguments    : what - Object pointer to the armour to remove.
 * Returns      : 1 - Remove success, custom message.
 *                string - Remove failed, custom message.
 */
public mixed
remove(object what)
{
  object waist;

  if (silent_drop) {
    silent_drop = 0;
    return 1;
  }
  
  if (this_player() == wearer)
    tell_room(environment(wearer), QCTNAME(wearer) + " unwraps " +
              HIS_HER(wearer) + " " + short() + " from " +
              HIS_HER(wearer) + " waist.\n", ({wearer}));
  wearer->catch_msg("You unwrap the " + short() + " from " +
                    "your waist.\n");
  return 1;
}

public void
leave_env(object from, object to)
{
  ::leave_env(from, to);
  wearable_item_leave_env(from, to);
}

/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
  ::appraise_object(num);

  appraise_wearable_item();
}
