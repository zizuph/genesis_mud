inherit "/std/room.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player
#define TO             this_object

void 
sword_talk(object player)
{
    tell_object(player,  BS("In the back of your mind you hear the now-familiar voice of "
            + "the ancient sword: 'Honored wielder, together we have arrived. Take "
            + "me within your hand now; strike with the power of the ancients forged "
            + "within my blade. Wield me now, for only I, Lightbringer, can vanquish "
            + "the One who is most Dark!'\n"));
}

void
enter_inv(object ob, object from)
{
    if (ob==TP())
    {
	if (!TP()->test_bit(QUEST_TH1_GROUP, QUEST_TH1_BIT))
	{
	    TP()->set_bit(QUEST_TH1_GROUP, QUEST_TH1_BIT);
	    TP()->add_exp(QUEST_TH1_EXP, 0);
	}
        if (file_name(from)==MANSION +"tapestry_room")
           call_out("sword_talk", 6,TP());
    }
}

void 
leave_inv(object ob, object to)
{
    if (ob==TP())
	if (file_name(to)==MANSION +"tapestry_room")
	{
	    if (test_bit("Terel", QUEST_TH1_GROUP, QUEST_TH1_BIT))
	    {
		write(BS("As you enter the portal, you seem to hear the sword "
		+ "one last time: 'Noble wielder, you have changed the course of "
		+ "history. Go now back to your own time; but know that you carry "
		+ "with you the eternal blessing of the ancient Sidhe. Farewell, "
		+ "traveler!\n\n"));
	    }
	    else
	    {
		write(BS("As you enter the portal, you hear within "
                + "your mind a faint echo: 'Perhaps you are not "+TP()->query_pronoun()
                + " whom I have so long sought, then. I shall return to my resting place again; "
                + "another pilgrim may someday that way come. Fare thee well, traveler!'\n"));
		write("The ancient sword bursts into flames!\n");
		present("thane_quest_sword",TP())->remove_object();
	    }
	}
}

void
create_room()
{
        set_short("Battlefield");
        set_long(BS("You find yourself standing in a charred field, alone "
        + "amidst thousands of individual melees. The fighting rages all "
        + "around you, elves and humans locked in desperate combat. Yet somehow "
        + "none come near you, whether from respect on the part of the elves "
        + "or fear on the part of the humans. Broken and mutilated bodies surround "
        + "you; a brief glance at them and you know that the battle does not go "
        + "well for your Elvish comrades. The ground "
        + "itself is red with blood and heat, the heat of battle and another heat "
        + "less wholesome. To the north you can feel the Dark One "
        + "beckoning you for the final confrontation; to the south an odd portal "
        + "seems to hover in the air, a rip in the fabric of time.\n"));
        
        add_exit(MANSION +"battlefield_2","north",0,1);
        add_exit(MANSION +"tapestry_room","south",0,1);

        add_item(({"body","bodies"}),BS("All around you are the mangled bodies "
        + "of elves and humans, their blood now mingling unmindful of race. "
        + "Sadly, you notice many more Elvish bodies than human corpses, for "
        + "the battle goes poorly for your kindred.\n"));
}
