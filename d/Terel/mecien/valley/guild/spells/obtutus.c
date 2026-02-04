/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* The mystic spell OBTUTUS. Mystic Eye, see what's behind an exit.
   Mortricia June 93
 */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <comb_mag.h>

#define TP         this_player()
#define TO         this_object()
#define BSN(xx)    break_string(xx + "\n", 72)
#define SPELL_COST 25
#define CAST_LIMIT 50
#define GUILD_NAME "The Ancient Mystic Order"

nomask mixed
obtutus(string str)
{
  int i, suc;
  object here, room;
  object *ob, *lv, *dd;
  string path, item;

  if (!str) return "Obtutus where?\n";
  if (!CAN_SEE_IN_ROOM(TP)) {
    return "It's too dark to see any exits.\n";
  }
  if (NPMAGIC(TP)) {
    return "Somehow your spell fails.\n";
  }

  here = environment(TP);
  i = member_array(str, here->query_exit_cmds());
  if (i < 0) {
    return "There is no exit leading to the "+str+" here.\n";
  }
  path = here->query_exit_rooms()[i];
  room = find_object(path);
  if (!room) {
    return "The vision is void.\n";
  }
  if (room->query_prop(OBJ_I_LIGHT) <= -TP->query_prop(LIVE_I_SEE_DARK)) {
    return "The vision is dark.\n";
  }

  if (TP->query_mana() <= SPELL_COST) {
    return "You do not have the strength.\n";
  }

  suc = TP->query_skill(SS_SPELLCRAFT)/2;
  suc += TP->query_skill(SS_FORM_DIVINATION)/2;
  if (random(suc) < CAST_LIMIT) {
    TP->add_mana(-SPELL_COST/3);
    return "Your call is not heard.\n";
  }

  TP->catch_msg("In your mind you perceive the following picture:\n" +
                room -> long());
  ob = all_inventory(room);
  if (TP->query_skill(SS_ELEMENT_DEATH) > 35) {
    dd = FILTER_DEAD(ob);
    dd = FILTER_CAN_SEE(dd, TP);
    item = (string) COMPOSITE_FILE->desc_dead(dd, 1);
    if (item) write(break_string(capitalize(item) + ".", 76) + "\n");
  }
  if (TP->query_skill(SS_ELEMENT_LIFE) > 35) {
    lv = FILTER_LIVE(ob);
    lv = FILTER_CAN_SEE(lv, TP);
    item = (string) COMPOSITE_FILE->desc_live(lv, 1);
    if (item) write(break_string(capitalize(item) + ".", 76) + "\n");
  }

  TP->add_mana(-SPELL_COST);

  return 1;
}
