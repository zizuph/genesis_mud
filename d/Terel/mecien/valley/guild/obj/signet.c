/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/armour";

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()
#define ENV environment

public void
create_armour()
{
   set_name("ring");
   add_name("signet");
   add_name(MYSTIC_SIGNET);
   
   set_adj(({"arcane", "gold", "signet"}));
   set_at(A_ANY_FINGER);
   
   add_prop(MYSTIC_ARMOUR, 1);
   add_prop(OBJ_I_WEIGHT, 20);
   add_prop(OBJ_I_VOLUME, 5);
   
   set_long(
      "Golden and luminous, this arcane ring is a signet. Thus banded " +
      "with a mysterious seal. Upon the seal are seven stars, a serpent " +
      "and a few strange characters.\n");
}

public void
init()
{
   ::init();
   if (ENV(TO) == TP) {
      add_action("do_sense", "sense");
      add_action("do_safe", "safe");
      add_action("do_defend", "defend");
      add_action("do_return", "return");
   }
}

do_safe(){
   object who;
   write("You calm yourself, feeling that all is safe.\n");
   write("You call to the guardian, releasing him from his fury.\n");
   who = find_living("arinosticarus");
   if(!who){
      write("You do not sense the guardian.\n");
      return 1;
   }
   who->command("emote seems to grow calm and looks sleepy.\n");
   who->remove_prop("defending");
   return 1;
}

do_defend(){
   object who;
   write("You become a maddened creature of fury!\n");
   write("You call upon the guardian of the lower reaches to defend his territory.\n");
   say(QCTNAME(TP) + " turns into a maddened creature, with eyes of fire and a mantle of darkness enclosing around " + TP->query_objective() + ".\n");
   who = find_living("arinosticarus");
   if(!who){
      TP->catch_msg("The guardian was not found, so is either dead or sleeping.\n");
      return 1;
   }
   who->add_prop("defending", 1);
   who->command("emote rises up suddenly, with a blast of fire from his snout and rages violently!");
   return 1;
}

/*
* Function name: in_shrine
* Description  : This function will filter all players to see who are in
*                the Shrine.
*/
public int
in_shrine(object player)
{
   /* Player doesn't have an environment, i.e. is in the void. */
   if (!objectp(ENV(player)))
      {
      return 0;
   }
   
   /* Take the filename of the room the player is in and see whether that
   * room is in the Shrine.
   */
   return wildmatch(GUILD_DIR + "*", file_name(ENV(player)));
}

public int
do_sense(string str)
{
   object *players;
   
   if (!MEMBER(TP)) return 0;
   if (TP->query_mystic_office() != OFFICE_SEAL) return 0;
   
   if (TP != query_worn()) {
      write("The " + short() + " must be worn!\n");
      return 1;
   }
   
   write("You concentrate upon the signet.\n");
   say(QCTNAME(TP) + " holds a hand out and concentrates deeply.\n");
   
   /* Filter all users() to see who is in the Shrine and who is not. If
   * there is no-one in the Shrine, tell the player.
   */
   players = filter(users(), in_shrine);
   if (!sizeof(players))
      {
      write("You do not sense any presence.\n");
      return 1;
   }
   
   /* players->query_the_name(TP) will give an array of the names of the
   * players who are in the Shrine if we know them. COMPOSITE_WORDS puts
      * that list in a nice string of 'a, b and c'. Then, if it is singular,
      * use 'is', else 'are'.
      */
   write("You sense that " + COMPOSITE_WORDS(players->query_the_name(TP)) +
      ((sizeof(players) == 1) ? " is" : " are") +
      " within the boundaries of the Shrine.\n");
   return 1;
}

public int
do_return(string str)
{
   object dragon = find_living("arinosticarus");
   
   if (!MEMBER(TP)) return 0;
   if (TP->query_mystic_office() != OFFICE_SEAL) return 0;
   
   notify_fail("Return what?\n");
   if (!id(str)) return 0;
   
   if (TP != query_worn()) {
      write("The " + short() + " must be worn!\n");
      return 1;
   }
   
   if (!dragon) {
      write("The " + short() + " twirls on your finger, but " +
         "cannot seem to locate its keeper.\n");
   } else {
      move(dragon);
      write("The " + short() + " twirls itself off your finger " +
         "and disappears, in a whitish flash, back to its keeper!\n");
      say("The " + short() + " worn by " + QTNAME(TP) +
         " suddenly disappears in a whitish flash!\n");
      set_alarm(1.0, -1.0, remove_object);
   }
   return 1;
}
