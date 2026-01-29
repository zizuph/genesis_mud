/*
 *  /d/Ansalon/taman_busuk/neraka/temple/altar.c
 *  Included functionality for the PoT to participate in the warfare
 *  system and do their guru quest.
 *  Arman - October 2018
 */

#pragma strict_types

#include "defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/new_pot/guild.h"
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

inherit TEMPLE + "std_hall.c";

#define ONE_OF(x)     ((x)[random(sizeof(x))])

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("Centre of the temple");
    set_long("You are standing at the very centre of the Great Hall of " +
        "Audience. In front of you is a high platform of rock resembling a " +
        "giant hooded snake. As you look around you notice how everything " +
        "within this large hall is focused upon this very platform.\n"); 

    add_item(({"higher platform", "snake", "giant hooded snake", "gate", 
        "altar", "platform"}),
        "As you study the forms of the rock, you see the blackness of the " +
        "stone writhing and moving as if it were alive. The entire hall is " +
        "focused upon this very point. It can be nothing short of an altar " +
        "in honour of Takhisis, the Queen of Darkness.\n");

    add_exit( TEMPLE + "hall3.c", "north" );
    add_exit( TEMPLE + "hall8.c", "south" );
    add_exit( TEMPLE + "hall6.c", "east" );
    add_exit( TEMPLE + "hall5.c", "west" );
    add_exit( TEMPLE + "hall4.c", "northeast" );
    add_exit( TEMPLE + "hall2.c", "northwest" );
    add_exit( TEMPLE + "hall9.c", "southeast" );
    add_exit( TEMPLE + "hall7.c", "southwest" );
}

string
check_army_colour(string str)
{
    string colour;

    switch(str)
    {
        case "White Dragon Army":
            colour = "white";
            break;
        case "Green Dragon Army":
            colour = "green";
            break;
        case "Black Dragon Army":
            colour = "black";
            break;
        case "Blue Dragon Army":
            colour = "blue";
            break;
        case "Red Dragon Army":
            colour = "red";
            break;
        default:
            colour = "chromatic";
            break;
    }

    return colour;
}

int
do_pray(string arg)
{
    if (arg && arg != "before altar")
    {
        notify_fail("Pray what?\n");
        return 0;
    }

    if(!MEMBER(TP) || !TP->query_priest_level())
    {
        write("You pray before the altar.\n");
        say(QCTNAME(TP)+ " prays before the altar here in the " +
            "Great Hall of Audience.\n"); 
        return 1;
    }

    if(!IS_CLUB_MEMBER(TP))
    {
        write("You pray before the altar here in the Great Hall " +
            "of Audience, and revel with your Goddess in the " +
            "tension between the five Dragonarmies as they contend " +
            "for Her attention. You realise that here you can support a " +
            "Dragonarmy of your choice in the battlefields of Krynn, " +
            "providing your dark <favour> to their cause.\n");
        say(QCTNAME(TP)+ " prays before the altar here in the " +
            "Great Hall of Audience.\n"); 
        return 1;
    }

    // Check for PoT guru quest bit
    if(!TP->test_bit("ansalon", 3, 19))
    {
        string chosen_army, chosen_area, colour;

        CLUB_MANAGER->set_pot_guru_remaining_armies(TP);
        mapping list = CLUB_MANAGER->query_pot_guru_remaining_armies(TP);

        if(!CLUB_MANAGER->query_pot_guru_army_focus(TP))
        {          
            string * armies = ({ });

            foreach (string army, string area: list)
            {
                armies += ({ army });
            }

            chosen_army = ONE_OF(armies); 
            CLUB_MANAGER->set_pot_guru_army_focus(TP, chosen_army);
        }
        else
        {
            chosen_army = CLUB_MANAGER->query_pot_guru_army_focus(TP);
        }

        colour = check_army_colour(chosen_army);
        chosen_area = list[chosen_army];

        write("You pray before the altar here in the Great Hall " +
            "of Audience, and revel with your Goddess in the " +
            "tension between the five Dragonarmies as they contend " +
            "for Her attention.\n\nThe dark shadows cast by the " +
            "low burning braziers suddenly form before you into " +
            "the dark silhouette of a five headed dragon.\n\n" +
            "One of the five heads turns to you - the " +colour+ 
            " head - its maw gaping wide! It breathes darkness " +
            "upon you, blinding you momentarily... however in " +
            "that time your mind's eye sees the " +chosen_area+
            " battlefield.\n\n'Favour me. Conquer " +chosen_area+ " in " +
            "my name.' rasps the " +colour+ " dragon head.\n\n" +
            "The dark silhouette of a five headed dragon vanishes.\n");
        say(QCTNAME(TP)+ " prays before the altar here in the " +
            "Great Hall of Audience. The burning braziers around " +
            "you seem to flicker briefly, causing the shadows " +
            "to dance eerily.\n"); 
        return 1;
    }

    if(IS_CLUB_MEMBER(TP))
    {
        write("You pray before the altar here in the Great Hall " +
            "of Audience, and revel with your Goddess in the " +
            "tension between the five Dragonarmies as they contend " +
            "for Her attention. You realise that here you can change " +
            "your support of a Dragonarmy in their attempt to conquer Krynn, " +
            "and provide your dark <favour> to another army of your choice.\n");
        say(QCTNAME(TP)+ " prays before the altar here in the " +
            "Great Hall of Audience.\n"); 
        return 1;
    }

    write("You pray before the altar.\n");
    say(QCTNAME(TP)+ " prays before the altar here in the " +
        "Great Hall of Audience.\n"); 
    return 1;
}

int
do_favour(string str)
{
    object chit_obj = clone_object(WAR_OBJ);
    string army;

    NF("Favour which army with your unholy support?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "[the] %s", army);

    army = CLUB_MANAGER->query_warfare_army_string(army);

    NF("That isn't an eligible warfare army to favour.\n");
    if(!army)
        return 0;

    NF("You may only provide your favour to the Red, Blue, Green, Black " +
        "or White Dragonarmy.\n");
    if ((army != "Red Dragon Army") && (army != "Blue Dragon Army") && 
        (army != "Green Dragon Army") && (army != "Black Dragon Army") && 
        (army != "White Dragon Army"))
	return 0;

    if(IS_CLUB_MEMBER(TP))
    {
        if (army == CLUB_MANAGER->query_warfare_army(TP))
        {
            write("You already provide your dark favour to the " +
                CLUB_MANAGER->convert_warfare_army_name(army)+ "!\n");
            return 1;
        }
        else
        {
            tell_room(E(TP), QCTNAME(TP) + " favours the " +
            CLUB_MANAGER->convert_warfare_army_name(army)+ 
            " for the domination of Krynn!\n", TP);
            tell_object(TP, C(CLUB_MANAGER->query_warfare_army_name(TP))+ 
                " has fallen out of favour with you! Your dark favour now " +
                "resides with " +CLUB_MANAGER->convert_warfare_army_name(army)+ 
                " for the domination of Krynn!\n");

            // Change the army supported and reset kills and conquers
            CLUB_MANAGER->set_warfare_army(TP, army);
            CLUB_MANAGER->add_krynn_war_player_stats(TP, army, 0, 0);

            // Update the club object
             object club_object = present("_warfare_club_object_", TP);

             if (objectp(club_object))
         	club_object->update_warfare_object(TP); 

            return 1;
         } 
    }
  
    CLUB_MANAGER->add_member(TP);
    CLUB_MANAGER->set_warfare_army(TP, army);

    setuid();
    seteuid(getuid());
    chit_obj->move(TP, 1);

    tell_room(E(TP), QCTNAME(TP) + " has provided " +HIS(TP)+
        " dark favour to " +CLUB_MANAGER->query_warfare_army_name(TP)+ 
        ", supporting them in the Queen of Darkness' name for domination " +
        "of Krynn!\n", TP);
    tell_object(TP,"You have provided your dark favour to " +
        CLUB_MANAGER->query_warfare_army_name(TP)+ ", supporting them in the " +
        "Queen of Darkness' name for domination of Krynn!\n");
    return 1;

}

void
init()
{
    ::init();

    add_action(do_favour, "favour");    
    add_action(do_pray, "pray");
}
