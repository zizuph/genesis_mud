/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This is the mystic 'voce' spell */
#include <stdproperties.h>
#include <macros.h>
#include <comb_mag.h>

#define SPELL_COST 5
#define GUILD_NAME "The Ancient Mystic Order"
#define MEMBER(xx) xx->query_guild_member(GUILD_NAME)
#define IS_WIZ(xx) xx->query_wiz_level()
#define TP         this_player()

nomask mixed
voce(string str)
{
  string message, who, pron;
  object receiver;
  int mana, busy;

  if (!strlen(str) || sscanf(str, "%s %s", who, message) != 2) {
    return "Voice whom what?\n";
  }
  if (NPMAGIC(TP)) return "Somehow your spell fails.\n";

  mana = TP->query_mana();
  if (mana < SPELL_COST) return "You do not have the strength.\n";

  receiver=find_living(lower_case(who));
  if (!receiver) return "The voice seeks but finds no such person.\n";

  if (NPMAGIC(receiver)) {
    pron=(string)receiver->query_pronoun();
    return capitalize(pron) + " cannot hear the voice.\n";
  }


     /*
      * Do we allow tells to non-members?  Seems like it's reasonable 
      * and natural for Mystics to have this ability, but for now we'll
      * disable it in deference to the admin....   also, we wouldn't
      * want to pay any outrageous 10% tax.
      */

/*  if (!MEMBER(receiver)) {
       TP->add_mana(-SPELL_COST);
       return receiver->query_name() + " is not a member of the Order!\n";
  }*/
       
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
