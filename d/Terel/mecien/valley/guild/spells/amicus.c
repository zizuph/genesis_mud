/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO         this_object()
#define TP         this_player()
#define ETP        environment(TP)
#define MANA_COST  10
#define EN environment

public int
are_friends(object player)
{
    if (player->query_skill(FRIEND)) return 1;
    return 0;
}

nomask mixed
amicus(string str)
{
    object *players;
     object who;

    if (TP->query_mana() < MANA_COST) return "You do not have the strength.\n";
    
  if(!str){
    write("You call upon the winds to find those named friends of the ancient world.\n");
    tell_room(ETP, QCTNAME(TP) + " holds aloft a hand in a mystic and " +
                   "peaceful sign and whispers a silent prayer.\n", TP);

    /* Filter all users() to see who is cursed and who is not. If
     * there is no-one cursed, tell the player.
     */
    players = filter(users(), are_friends);
    if (!sizeof(players))
   return "You do not sense any friends of the ancient world.\n";

    /* players->query_the_name(TP) will give an array of the names of the
     * players who are in the Shrine if we know them. COMPOSITE_WORDS puts
     * that list in a nice string of 'a, b and c'. Then, if it is singular,
     * use 'is', else 'are'.
     */
    write("You come to know through the ancient powers that " +
          COMPOSITE_WORDS(players->query_the_name(TP)) +
          ((sizeof(players) == 1) ? " is" : " are") +
    " friends with the Order.\n");
    TP->add_mana(-MANA_COST);
    return 1;
   }
   who = present(str, EN(TP));
  if(!who) return "You find no such person.\n";
  if(!living(who)) return "You find no such person.\n";
   if(who == TP) return "You find no such person.\n";
 TP->catch_msg("Raising your hand in a sign of mystical blessing, you name " +
   QTNAME(who) + " a friend of the ancient world.\n");
   who->catch_msg(QCTNAME(who) + " blesses you with a mystical sign, naming you friend of the ancient world.\n");
  tell_room(EN(TP), QCTNAME(TP) + " raises a hand and blesses " + QTNAME(who) + " with a mystical sign.\n", ({ who, TP }));
   TP->add_mana(-MANA_COST);
   who->set_skill(FRIEND, 1);
   return 1;
}
