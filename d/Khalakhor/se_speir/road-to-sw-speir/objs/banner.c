/*
 * Camp banner
 * Tapakah, 09/2021
 */

#pragma strict_types;

#include "files.h"
#include "macros.h"
#include "stdproperties.h"

#include "../defs.h"

inherit "/std/object";

#define CAMP_LIVE_I_WARNED_BANNER "_camp_live_i_warned_banner"

string
check_get ()
{
  if (! ETO || ! IS_ROOM_OBJECT(ETO)) 
    return 0;

  string caller = calling_function(-1);
  int warned = TP->query_prop(CAMP_LIVE_I_WARNED_BANNER);

  object *audience = filter(all_inventory(ETO), &->is_camp_warrior());
  foreach (object member: audience)
    if (caller == "move") {
      if (! warned) {
        TP->add_prop(CAMP_LIVE_I_WARNED_BANNER, 1);
        return member->query_The_name() + " looks at you suspiciously, " +
          "and you do not dare to touch the banner.\n";
      }
      else {
        TP->catch_msg(member->query_The_name() +
                      " notices that you ignored the warning.\n");
        member->command("$kill " + TPQN);
        TP->remove_prop(CAMP_LIVE_I_WARNED_BANNER);
      }
    }
    else {
      if (! warned) {
        if (TP->query_attack() || TP->query_prop("no_banner_for_you"))
          return "You are in a middle of a fight, and cannot get the "+
            "banner.\n";
      }
      else
        return member->query_The_name() + " looks at you suspiciously, " +
          "and you do not dare to touch the banner.\n";
    }
  if (TP->query_attack())
    return "You are in a middle of a fight, and cannot get the "+
            "banner.\n";
  return 0;
}
  
void
create_object ()
{
  set_name("banner");
  add_adj(({"tricolor", "square"}));
  set_short("tricolor square banner");
  set_long("This banner from the camp is a square canvas, about six feet "+
           "to a side, on a fifteen-feet pole. The top left corner of the "+
           "banner is black, the bottom right is green, and the diagonal "+
           "is blue, indicating the colors of the Macdunn and the " +
           "Maccrimmon clans.\n");
  add_prop(OBJ_I_WEIGHT, 2500);
  add_prop(OBJ_I_VOLUME, 10000);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_M_NO_GET, check_get);
}
