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

public int
are_cursed(object player)
{
    if (player->query_skill(CURSED)) return 1;
    return 0;
}

nomask mixed
inimicus(string str)
{
    object *players;

    if (TP->query_mana() < MANA_COST) return "You do not have the strength.\n";
    
    write("You call upon the winds to find those named treacherous.\n");
    tell_room(ETP, QCTNAME(TP) + " holds aloft a hand in a strange and " +
                   "forboding sign and whispers a silent prayer.\n", TP);

    /* Filter all users() to see who is cursed and who is not. If
     * there is no-one cursed, tell the player.
     */
    players = filter(users(), are_cursed);
    if (!sizeof(players))
        return "You do not sense any cursed presence.\n";

    /* players->query_the_name(TP) will give an array of the names of the
     * players who are in the Shrine if we know them. COMPOSITE_WORDS puts
     * that list in a nice string of 'a, b and c'. Then, if it is singular,
     * use 'is', else 'are'.
     */
    write("You come to know through the ancient powers that " +
          COMPOSITE_WORDS(players->query_the_name(TP)) +
          ((sizeof(players) == 1) ? " is" : " are") +
          " known as cursed before the Holy Ones.\n");
    TP->add_mana(-MANA_COST);
    return 1;
}
