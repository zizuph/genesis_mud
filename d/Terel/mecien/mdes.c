#include <stdproperties.h>
#include <macros.h>
#include <comb_mag.h>

#define SPELL_COST 5
#define GUILD_NAME "The Ancient Mystic Order"
#define MEMBER(xx) xx->query_guild_member(GUILD_NAME)
#define IS_WIZ(xx) xx->query_wiz_level()
#define TP         this_player()

nomask mixed
mdes(string str)
{
  string what, who, pron;
  obj, personect obj;

  if (!strlen(str) || sscanf(str, "%s %s", who, what) != 2) {
   return "Destruct what in whom?\n";
  }
  receiver=find_living(lower_case(who));
  if (!receiver) return "The voice seeks but finds no such person.\n";

  if (NPMAGIC(receiver)) {
    pron=(string)receiver->query_pronoun();
    return capitalize(pron) + " cannot hear the voice.\n";
  }

  if (IS_WIZ(receiver)) {
    if (!MEMBER(receiver)) {
      TP->add_mana(-SPELL_COST);
      return "Wizards are busy, don't disturb them.\n";
    } else {
      busy = (int)receiver->query_prop(WIZARD_I_BUSY_LEVEL);
      if (busy & 8 || busy & 16 || busy & 128)
      {
        pron=(string)receiver->query_pronoun();
        return capitalize(pron) + " cannot hear the voice.\n";
      }
    }
  }

  write("You use the voice.\n");
  say(QCTNAME(TP) + " places " + TP->query_possessive() + 
    " hands to " + TP->query_possessive() + " forehead and " +
    "whispers in a strange trance.\n");
  receiver->catch_msg(QCTNAME(TP) + " calls with the mystic voice: " +
	      capitalize(message) + "\n");
  TP->add_mana(-SPELL_COST);
  return 1;
} 
