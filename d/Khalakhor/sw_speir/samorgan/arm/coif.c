/**********************************************************************
 * - coif.c                                                         - *
 * - worn by the lieutenant                                         - *
 * - created by Tapakah, 5/2021                                     - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;
inherit "/lib/wearable_item" wi;

static mixed
check_slot (int slot)
{
  object *inv = all_inventory(TP);
  foreach (object item: inv) {
    if (item->query_name() == "coif" && item->query_worn())
      return "You are already wearing a coif\n";
  }
  wi::check_slot(slot);
}

void
create_armour()
{
  set_name("coif");
  add_name("helmet");
  set_adj(({"steel","chain"}));
  set_short("steel chain coif");
  set_long("This coif is a piece of armour that covers your head, "+
           "your neck and most of your chest. It's made from a fine "+
           "metal mesh, but still is a bit heavy.\n");
  set_ac(10);
  set_looseness(1);
  set_at(A_HEAD|A_NECK|A_CHEST);
  set_am(({1, -2, 1}));
  add_prop(OBJ_I_WEIGHT, 4500);
}
