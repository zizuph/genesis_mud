/*

     This is the room where mortals are rewarded for Part 1 of
         the Duncan Thane quest. They have acquired the sword,
         found the right room in Avenchir mansion and have
         entered the proper tapestry, and are rewarded. To
         the north lies the Evil One, where part 2 may be
         completed.

    It's not clear to me when Cedric coded this, but it was
        certainly before 1996, and I suspect a year or two prior
        to that.

    Modified: 13 June 2003, by Bleys
        - Changed to use modern includes.
        - Now logging when part one of the quest is completed.

*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/quest_bits.h"

void
sword_talk(object player)
{
    if (player && living(player))
        player->catch_msg("In the back of your mind you hear the " +
                          "now-familiar voice of the ancient sword: " +
                          "'Honored wielder, together we have arrived. " +
                          "Take me within your hand now; strike with " +
                          "the power of the ancients forged within my " +
                          "blade. Wield me now, for only I, " +
                          "Lightbringer, can vanquish the One who is " +
                          "most Dark!'\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || !living(ob)) return;

    if (!ob->test_bit("Terel", QUEST_TH1_GROUP, QUEST_TH1_BIT))
    {
        ob->set_bit(QUEST_TH1_GROUP, QUEST_TH1_BIT);
        ob->add_exp(QUEST_TH1_EXP, 0);
        write_file(QUEST_LOG, TP->query_name() + " solved " +
            "part 1 of the Duncan Thane quest (" +
            ctime(time()) + ")\n");
    }
    if (from && file_name(from) == MANSION + "tapestry_room")
        set_alarm(6.0, -1.0, &sword_talk(ob));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (!ob || !living(ob)) return;
    if (!to || file_name(to) != MANSION + "tapestry_room") return;
    
    if (ob->test_bit("Terel", QUEST_TH1_GROUP, QUEST_TH2_BIT))
    {
        ob->catch_msg(
              "As you enter the portal, you seem to hear the sword one " +
              "last time: 'Noble wielder, you have changed the course of " +
              "history. Go now back to your own time; but know that you " +
              "carry with you the eternal blessing of the ancient Sidhe. " +
              "Farewell, traveler!\n");
    }
    else
    {
        ob->catch_msg(
              "As you enter the portal, you hear within your mind a " +
              "faint echo: 'Perhaps you are not " + ob->query_pronoun() +
              " whom I have so long sought, then. I shall return to my " +
              "resting place again; another pilgrim may someday that " +
              "way come. Fare thee well, traveler!'\n" +
              "The ancient sword bursts into flames!\n");
        present("thane_quest_sword", ob)->remove_object();
    }
}

public void
create_room()
{
    set_short("Battlefield");
    set_long("You find yourself standing in a charred field, alone " +
             "amidst thousands of individual melees. The fighting " +
             "rages all around you, elves and humans locked in " +
             "desperate combat. Yet somehow none come near you, " +
             "whether from respect on the part of the elves or " +
             "fear on the part of the humans. Broken and mutilated " +
             "bodies surround you; a brief glance at them and you " +
             "know that the battle does not go well for your Elvish " +
             "comrades. The ground itself is red with blood and " +
             "heat, the heat of battle and another heat less " +
             "wholesome. To the north you can feel the Dark One " +
             "beckoning you for the final confrontation; to the " +
             "south an odd portal seems to hover in the air, a rip " +
             "in the fabric of time.\n");

    add_exit(MANSION + "battlefield_2", "north", "@@allow_north", 1);
    add_exit(MANSION + "tapestry_room", "south", 0, 1);

    add_item(({"body", "bodies"}), "All around you are the mangled " +
             "bodies of elves and humans, their blood now mingling " +
             "unmindful of race. Sadly, you notice many more Elvish " +
             "bodies than human corpses, for the battle goes poorly " +
             "for your kindred.\n");
}

public int
allow_north()
{
    int i;
    object room, *rl;

    seteuid(getuid());
    room = find_object(MANSION + "battlefield_2");
    if (!room) return 0;
    
    rl = all_inventory(room);
    for (i=0; i<sizeof(rl); i++)
        if (interactive(rl[i]))
            return 1;
    
    return 0;
}
