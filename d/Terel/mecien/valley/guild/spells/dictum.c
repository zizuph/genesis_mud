/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* This is the mystic 'voce' spell */
#include <stdproperties.h>
#include <macros.h>
#include <comb_mag.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define SPELL_COST 10
#define GUILD_NAME "The Ancient Mystic Order"
#define IS_WIZ(xx) xx->query_wiz_level()
#define TP         this_player()

nomask mixed
dictum(string str)
{
  string message, who, pron;
  object receiver;
  int mana, busy;

  if (!strlen(str) || sscanf(str, "%s %s", who, message) != 2) {
    return "Dictate whom what?\n";
  }
  if (NPMAGIC(TP)) return "Somehow your spell fails.\n";

  mana = TP->query_mana();
  if (mana < SPELL_COST) return "You do not have the strength.\n";

    if(!present(MYSTIC_AMULET, TP)) return "You will need the amulet.\n";
  receiver=find_living(lower_case(who));
  if(!receiver) return "The powers can locate no such person.\n";

  if (NPMAGIC(receiver)) {
    pron=(string)receiver->query_pronoun();
    return "Something stops your words from arriving.\n";
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
        return capitalize(pron) + " cannot hear you now.\n";
      }
    }
  }

  if(!present(MYSTIC_AMULET, TP)) return "You will need the amulet.\n";
  write("You invoke the ancient voice to make your words known.\n");
  say(QCTNAME(TP) + " raises " + TP->query_possessive() + 
    " amulet before " + TP->query_possessive() + " face, " +
  "waves a hand over it and seems to speak to it.\n");
 tell_room(environment(receiver), "A darkness seizes this place and a great wind arises!\n");
   set_alarmv(4.0, -1.0, "darker", ({receiver, message}));
   TP->add_mana(-20);
return 1;
}

darker(object receiver, string message){
  tell_room(environment(receiver), "The earth shakes.\n");
  tell_room(environment(receiver), "A tremendous voice is heard from above: " + capitalize(message) + "\n");
  set_alarm(2.0, -1.0, "still", receiver);
  return 1;
} 

still(object receiver){
  tell_room(environment(receiver), "It grows still and silent once again.\n");
}
