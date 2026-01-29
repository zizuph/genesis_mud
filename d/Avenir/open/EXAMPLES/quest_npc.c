/*
 * A small example of a quest NPC. This one will
 * reward a player if he returns a certain item
 * to the NPC.
 *
 *   Cirion, April 1997
 */
inherit "/std/monster";
inherit "/d/Avenir/inherit/quest"; // defines reward_quest(), which we will
                                   // use for all Avenir quests

#include "/d/Avenir/common/common.h"  // definitions

// here we put the defines for the Quest, like the
// amount of exp the player gets, and name of the
// quest, and the group and bit the quest takes up.
// These settings *must* match the documentation
// of the quest, which needs to be at:
// Description of the quest:   ~Avenir/private/QUESTS/<quest_name>
// Group and Bit used:         ~Avenir/open/BITS
#define QUEST_NAME  "name of my example quest"
#define QUEST_GROUP  999
#define QUEST_BIT    888
#define QUEST_EXP    30

void
create_monster()
{
    set_name("troloby");

    // remove this prop so we are allowed to give
    // object to the npc
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    // put the rest of the monster settings here...

}

/*
 * enter_inv() is called every time something enters
 * my inventory.
 * we use it here to register when someone "gives" us an
 * item
 */
void
enter_inv(object what, object from_where)
{
    // when masking pre-defined functions like this, _always_
    // use the callback:
    ::enter_inv(what, from_where);

    // was it a player that gave me the object? If not, forget
    // about the rest of the function.
    if(!interactive(from_where))
       return;

    // now we need to test if the object is the object
    // we want. In not, just drop it.
    if(!(what->id("the_special_name_of_my_quest_object")))
    {
       set_alarm(1.0, 0.0, &command("drop " + what->query_name()));
       return;
    }

    // reward_quest() will fail if the player has already solved the quest.
    // if it succeeds, it will add the experience to the player, give
    // him a message like "You feel more experienced.", and log the
    // fact that the player has solved the quest.
    if(!reward_quest(QUEST_NAME, from_where, QUEST_GROUP, QUEST_BIT, QUEST_EXP))
    {
       command("say Thanks again, " + from_where->query_name() + ", but "
            + "you have already returned this item!");
    }
    else
    {
       // make the npc say thanks
       command("say Thank you for returning the item, " + from_where->query_name()
             + "!");
    }
}

     


