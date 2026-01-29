/* Chapel, Vingaard Keep, coded by Percy.           */
/*                     modified by Grace, 04/07/94  */
/* modified by Teth and Morrigan Jan 97             */

/**********************************************************************
 * - Added non scry stuff                                           - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 **********************************************************************/

#include "../../guild.h"
#include <macros.h>

inherit IN_BASE;
inherit "/lib/guild_support";

#include "./std/no_scry_room.c"


void
create_vin_room()
{   
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    set_short("Chapel of Vingaard Keep");
    set_long("You are in the Chapel devoted to the patron gods of the " +
        "Knights of Solamnia. Here, you can pray to Paladine and " +
        "his twin sons Kiri-Jolith and Habbakuk. There is a modest " +
        "altar where you can kneel and meditate, allowing you to judge " +
        "your abilities, and also change the focus of your learning. A " +
        "small prayerbook hangs from a chain near the door. The room is " +
        "bathed in a soft glow. A tapestry hangs from one wall. East is a " +
        "hallway.\n");
    
    AI("prayerbook", "It is very small and bound with white leather.\n");
    AI("altar", "It is very modest in size, plain and unadorned.\n");
    AI(({"light","glow","soft glow"}),"The source of the soft glow " +
        "is not readily apparent. Instead, it seems only to fill the " +
        "room, with no real source.\n");
    AI("tapestry","The tapestry is a scene of a True Cleric of Paladine, " +
        "lifting a mace in defiance to a foul ogre, while at the same time " +
        "placing a glowing and healing hand on an injured comrade.\n");
    AI(({"cleric","cleric of paladine"}),"She has auburn curls falling " +
        "about her face. Her expression is one full of fierceness and " +
        "purity.\n");
    AI(({"ogre","foul ogre"}),"Drooling, the ogre seems to be backing " +
        "away from the cleric, obviously in fear.\n");
    AI("floor","The floor of the room is kept clean.\n");
    AI("ceiling","High above you, the ceiling is bathed in the soft glow.\n");
    AI(({"walls","wall"}),"The walls of the room are bathed in the soft " +
        "glow of the light, and are not the source.\n");
    AI("hallway","The hallway extends further east.\n");

    AE(VROOM + "west_hallway", "east", "@@remove_medi_props");

    INSIDE;
    	    
    create_guild_support();
}


int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}

void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "kneel");
    ADA("pray");
    ADA("read");
}

/*
* This function allows a knight to <pray> and <pray patron>
*/

int
pray(string str)
{
    
    NF("What?\n");
    
    if (!str)
        {
        if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 5000)
            TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 5000);
        
        write("You kneel at the altar and pray to Paladine. It gives you " +
            "a feeling of well-being.\n");
        say(QCTNAME(TP) + " does " + TP->query_possessive() + " daily " +
            "devotions at the altar.\n");
        return 1;
    }
    
    if (str == "patron" || str == "to patron")
        {
        if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 10000)
            TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 10000);
        
        if (TP->query_knight_level() == 2)
            {
            write("You kneel at the altar and pray to Paladine for " +
                "guidance.\nAs you make your devotions, a sense of " +
                "serenity envelops you.\nYou feel wonder at the " +
                "certainty that the loving, accepting presence in the " +
                "room is that of Paladine himself.\nYour resolve to " +
                " be a dedicated, courageous, and honest Squire has "+
                "firmed.\nYou rise from your daily devotions, " +
                "prepared for yet another day of fighting the forces " +
                "of evil, and confident of Paladine's blessing.\n");
            say(QCTNAME(TP) + " prays to " + TP->query_possessive() +
                " patron for guidance.\n");
            return 1;
        }
        if (TP->query_knight_level() == 3)
            {
            write("You kneel at the altar and pray to Habbakuk for " +
                "guidance.\nAs you make your devotions, a sense of " +
                "harmony envelops you.\nYou feel wonder at the " +
                "certainty that the creative, stimulating presence in " +
                "the room is that of Habbakuk, Patron of the Order of " +
                "the Crown.\nYour resolve to be a courageous, " +
                "obedient, and passionate Knight of the Crown has " +
                "firmed.\nYou rise from your daily devotions, " +
                "prepared for yet another day of fighting the forces " +
                "of evil, and confident of Habbakuk's blessing.\n");
            say(QCTNAME(TP) + " prays to " + TP->query_possessive() +
                " patron for guidance.\n");
            return 1;
        }
        if (TP->query_knight_level() == 4)
            {
            write("You kneel at the altar and pray to Kiri-Jolith for " +
                "guidance.\nAs you make your devotions, a sense of " +
                "righteousness envelops you.\nYou feel wonder at the " +
                "certainty that the magnanimous, disciplined presence " +
                "in the room is that of Kiri-Jolith, Patron of the " +
                "Order of the Sword.\nYour resolve to be a heroic, " +
                "honourable, and generous Knight has firmed.\nYou " +
                "rise from your daily devotions, prepared for yet " +
                "another day of fighting the forces of evil, and " +
                "confident of Kiri-Jolith's blessing.\n");
            say(QCTNAME(TP) + " prays to " + TP->query_possessive() +
                " patron for guidance.\n");
            return 1;
        }
        if (TP->query_knight_level() == 5)
            {
            write("You kneel at the altar and pray to Lord Paladine for " +
                "guidance.\nAs you make your devotions, a sense of " +
                "hope envelops you.\nYou feel awed by the certainty " +
                "that the wise and just presence in the room is that " +
                "of Paladine, Patron of the Order of the Rose.\nYour " +
                "resolve to be a just, honourable, and disciplined " +
                "Knight has firmed.\nYou rise from your daily " +
                "devotions, prepared for yet another day of fighting " +
                "the forces of evil, and confident of Paladine's " +
                "blessing.\n");
            say(QCTNAME(TP) + " prays to " + TP->query_possessive() +
                " patron for guidance.\n");
            return 1;
        }
    }
    return 0;
}

int
read(string str)
{
    NF("Read what?\n");
    if ((str == "book") || (str =="prayerbook"))
        {
        write("This is the Prayerbook of the Knights of Solamnia.\n"
            + " You can <pray> at the altar as part of your daily\n"
            + " devotions to Paladine. All good Knights pay homage\n"
            + " to him on a regular basis.                        \n"
            + "                                                   \n"
            + " In addition, you can <pray patron>. This allows you\n"
            + " to seek the counsel of the Patron of your Order.\n\n");
        return 1;
    }
    return 0;
}

int
check_member(object ob)
{
    NF("I don't think Paladine would let you meditate at his altar since\n" +
        "you are not a Knight.\n");
    return (MEMBER(ob) || LAYMAN(ob));
}

int
gs_meditate(string str)
{
    if (!check_member(TP))
        return 0;
    
    return ::gs_meditate(str);
}

void
gs_hook_start_meditate()
{
    write("You kneel before the altar of Paladine and close your eyes. A " +
	  "feeling of great ease and self control falls upon you. " +
	  "You block off your senses and concentrate solely upon your " +
	  "own mind. You feel your God's presence and his blessings " +
	  "imbue you with the ability to <set> the learning preferences " +
	  "at your own desire. Just <rise> when you are done meditating.\n");

    say(QCTNAME(this_player()) + " kneels before the altar and starts " +
        "to meditate.\n");
}

int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface " +
        "of your consciousness. You exhale and feel very relaxed as " +
        "you get up and leave the altar.\n");
    say(QCTNAME(TP) + " rises from the altar.\n");
}

