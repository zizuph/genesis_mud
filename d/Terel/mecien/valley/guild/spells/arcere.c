/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* The ARCERE mystic spell. It blocks an exit. Mortricia June 93 */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>

#define TP         this_player()
#define TO         this_object()
#define BSN(xx)    break_string(xx + "\n", 72)
#define SPELL_COST 25
#define CAST_LIMIT 45
#define GUILD_NAME "The Ancient Mystic Order"
#define BLOCK_OBJ  "/d/Terel/mecien/valley/guild/spells/blocker"

nomask mixed
arcere(string str)
{
  int time, suc;
  object here, blocker;

  if (!str) return "Arcere where?\n";
  if (!CAN_SEE_IN_ROOM(TP)) {
    return "It's too dark to see any exits.\n";
  }
  if (NPMAGIC(TP)) {
    return "Somehow your spell fails.\n";
  }

  here = environment(TP);
  if (member_array(str, here->query_exit_cmds()) < 0) {
    return "There is no exit leading to the "+str+" here.\n";
  }

  if (TP->query_mana() <= SPELL_COST) {
    return "You do not have the strength.\n";
  }

  suc = TP->query_skill(SS_SPELLCRAFT)/2;
  suc += TP->query_skill(SS_FORM_CONJURATION)/2;
  if (random(suc) < CAST_LIMIT) {
    TP->add_mana(-SPELL_COST/3);
    return "Your call is not heard.\n";
  }

  time = 2*(TP->query_stat(SS_WIS) + TP->query_stat(SS_INT));

  write("You summon the powers of the Ancients.\n");
  tell_room(here, BSN(
    "A shimmering rainbow appears. It seems to block " +
    "the exit leading to the " + str + "."));
  seteuid(getuid());
  blocker = clone_object(BLOCK_OBJ);
  blocker->set_blocked_exit(str);
  blocker->set_duration(time);
  blocker->move(here);

  TP->add_mana(-SPELL_COST);

  return 1;
}
