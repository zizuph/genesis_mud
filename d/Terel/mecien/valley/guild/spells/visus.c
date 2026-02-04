/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <std.h>

#define SPELL_COST 60
#define CAST_LIMIT 80
#define TP         this_player()

nomask mixed
visus(string str)
{
  object receiver;
  int suc;

  if (!str)
      return "Seek vision of who?\n";

  if (TP->query_mana() < SPELL_COST)
      return "You do not have the strength.\n";

  receiver = find_living(lower_case(str));
  
  if (!receiver)
      return "Your vision is void.\n";
  
  if (SECURITY->query_wiz_rank(receiver->query_real_name()))
      return "Your vision is void.\n";
  
  if (NPMAGIC(receiver))
      return "Your vision is void.\n";

  suc  = random(TP->query_skill(SS_FORM_DIVINATION));
  suc += random(TP->query_skill(SS_ELEMENT_LIFE));
  suc -= random(receiver->query_skill(SS_FORM_ABJURATION));
  if (suc < random(CAST_LIMIT)) {
      TP->add_mana(-SPELL_COST/3);
      return "Your vision is obscure.\n";
  }

  TP->add_mana(-SPELL_COST);

  write("You seek deep within, intoning the mystic chant.\n");
  write("The spirits whisper secrets.\n");
  write("You begin to see a place within your mind.\n");
  write("The spirits whisper: It is a place called " +
        environment(receiver)->short() + ".\n");
  say(QCTNAME(TP) + " stands still and silent for a moment.\n");

  if (TP->query_stat(SS_WIS) < receiver->query_stat(SS_WIS)) {
      tell_object(receiver, "A strange and mystic feeling " +
                  "passes over you.\n");
  }
  return 1;
}
