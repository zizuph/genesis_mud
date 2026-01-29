/*
This is a room file for the domain office of Ansalon
that joins up with the Tower of the Realms in Sparkle.
This room is supposed to offer info to mortals about
the domain of Ansalon.
*/

#include "/d/Ansalon/common/defs.h"
#include "/d/Genesis/start/human/town/tower.h"
#include <macros.h>

inherit TOWER_OFFICE;

create_tower_office()
{
    set_long("You stand within a dark room that makes up " +
        "the tower office of the domain of Ansalon. " +
        "In the center of the room is a large grey marble " +
        "table, with a plush cushioned chair sitting behind " +
        "it. On top of the table sits an orb of crystal, with " + 
        "a flickering candle on one side of it, and a small " +
        "sign on the other side.\n");
    
    add_item(({"grey marble table","marble table","table"}),
        "This grey marble table has been salvaged from the " +
        "ruins in the Bloodsea of Istar to serve as the desk for " +
        "the mortal representative of the Ansalon domain. On top " +
        "of the table sits an orb of crystal, with a flickering " +
        "candle on one side of it, and a small sign propped up " +
        "on the other side of the orb.\n");
    add_item(({"chair","plush cushioned chair"}),
        "A plush cushioned chair sits behind the grey marble " +
        "table.\n");
    add_item(({"orb","orb of crystal","crystal","stand",
                "golden stand"}),
        "An orb of crystal sits in a golden stand on the marble " +
        "table. Trapped inside it you see what looks like swirling mists " +
        "that change colours hypnotically as you look at it. You " +
        "feel compelled to stare into it.\n");
    add_item(({"candle","flickering candle"}),
        "This candle is the sole lightsource in this room, making " +
        "it hard to examine the rest of the room.\n");
    add_item(({"sign","small sign"}),
        "Propped up on the marble desk is a small sign. Perhaps " +
        "you should read it?\n");
    
    add_cmd_item(({"into crystal","into orb",
                "into orb of crystal"}),
        "stare","@@crystal");
    add_cmd_item(({"small sign","sign"}),"read","@@sign");
    
    
    set_project_path("/d/Ansalon/open/project/");
    add_tower_link("tower");
    reset_room();
}

string
sign()
{
    return "Upon the small sign you read:\n\n" +
    "wizards : Lists the wizards of the domain of Ansalon.\n" +
    "projects <domain/wizard> : The projects of the domain/wizard.\n\n";
}

string
crystal()
{
    write("You stare into the crystal. At first all " +
        "you see is the shifting mists trapped inside it, but " +
        "then the mists seems to part, and a scene magically " +
        "unfolds before you...\n");
    say(QCTNAME(TP) + " stares into the orb sitting on the " +
        "marble table.\n");
    
    switch(random(5))
    {
        case 0:
        return "You look down upon a wretched port city " +
        "sitting on the edge of the Bloodsea of Istar. As the " +
        "scene closes in, you notice it is heavily patrolled " +
        "by the dragonarmies of the Queen of Darkness. Before " +
        "you can take a closer look, the orb once again fills " +
        "with swirling mists... the vision has ended.\n";
        break;
        
        case 1:
        return "You look down upon an ancient forest. Here and " +
        "there you notice a few glades, where sylvan creatures " +
        "rest and play. As your vision moves over the forest, " +
        "you notice in areas it begins to look dark and twisted, " +
        "reaching menacingly towards the unwary. An irrational " +
        "aura of fear seems to rise from the center of the forest, " +
        "but before you can examine it the mists return, and the " +
        "vision is ended.\n";
        break;
        case 2:
        return "You find yourself watching an evil sacrifice " +
        "in a dark, underground temple. Unholy priests wearing " +
        "masks in the form of goat skulls pray around an altar, " +
        "while a high priest holds a dagger high over the prostrate " +
        "form of their sacrifice. Fortunately, the scene ends " +
        "with the return of the mists, thus ending the vision.\n";
        break;
        case 3:
        return "You look down upon the desert lands of Khur. " +
        "Here you notice a tribe of fierce and independent " +
        "horse barbarians, travelling from water hole to water " +
        "hole. The sun gleams off their shiny scimitars, " +
        "blinding you momentarily. When you look back, you find " +
        "the mists have returned to the orb, your vision ended.\n";
        break;
        case 4:
        
        return "You find yourself watching a mighty contest of " +
        "honour being fought out between two minotaurs in an " +
        "arena in the isle of Mithas. The crowd cheers as the " +
        "first blow is struck by a minotaur with a huge two-handed " +
        "battleaxe. Unfortunately, the fight ends for you as the " +
        "mists return, ending your vision.\n";
        break;
    }
}

void
reset_room()
{
    object quest_orb;
    seteuid(getuid(this_object()));

    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Ansalon");
        quest_orb->set_extra_line("The dark crystal orb is floating" +
                                 " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }    
}
