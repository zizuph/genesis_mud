/*******************************************************************\
| TEMPLE.C                                                          |
\*******************************************************************/

/*
 * 06/02/01 Arandir     Added quest bit porting
 *
 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

#include S_DOMAIN_SYS_QUESTS

object duck;

void
create_room()
{
    set_short("An orc temple");
    set_long(
        "This is an orc temple raised in the honour of the orcish\n"
        + "god, Kalach. As far as craftsmanship goes, this is the best\n"
        + "possible, for an orc. There is a rough stone altar against\n"
        + "one of the walls, obviously well used. The room is only\n"
        + "faintly lit, shadows cast around the room dancing with\n"
        + "the agility of the winds. Many candles are lined about\n"
        + "the walls, they seem to sway and flicker synchronized,\n"
        + "perfectly. Just above the altar itself stands a large,\n"
        + "menacing statue. The doorway from which you entered has\n"
        + "some sort of words encrusted around it. There are no windows\n"
        + "or openings, besides the doorway, in this room. Yet somehow\n"
        + "there is a slight unnatural breeze.\n");
    add_item(({"altar", "stone altar"}),
             "You can see and smell body parts still dangling off the edge " +
             "of the altar. Laying near the altar is some sort of large stone.\n");
    add_item(({"candles"}), "They are lined in a figure eight just "+
    "in front of the altar.\n");
    add_item(({"doorway"}), "It has words or something around it.\n");
    add_item(({"words", "runes"}), "You cannot seem to decipher them.\n");
    add_item(({"stone"}), "It is extremely heavy, it looks like a means"+
    " of sacrificing victims.\n");
    add_item(({"statue", "statue of Kalach", "statue of kalach"}),
             "Standing malevolently above the altar, it stares "+
             "continually at you, no matter where you move. It "+
             "looks like some sort of demon. Three horns sprout from "+
             "its forehead. It most closely resembles a huge orc with "+
             "horns.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_exit("r2", "south");
}

int
do_sacrifice(string str)
{
    notify_fail("Sacrifice what?\n");
    if (str == "duck")
    {
        QUEST_PORT_TP (Q_OLD_SACRIFICE_DUCK, Q_SACRIFICE_DUCK, "ported bits for duck sacrifice.");

        if(QUEST_TEST_TP (Q_SACRIFICE_DUCK))
        {
            write("Kalach will be pleased! Wait! You are trying "+
                  "to cheat Kalach! He will kill you!\n");
            TP->heal_hp(-75);
            TP->catch_msg("You feel pain.\n");
            return 1;
        }
        if (!(duck = present("duck", TP))){
            write("You must find a living animal to please the Vile One.\n");
            return 1;
        }
        if(interactive(TP))
        {
            QUEST_PORT_TP (Q_OLD_SACRIFICE_DUCK, Q_SACRIFICE_DUCK, "ported bits for duck sacrifice.");

            if(QUEST_TEST_TP (Q_SACRIFICE_DUCK))
            {

                TP->catch_msg("You don't feel more experienced.\n");
            }
            else
            {
                write("You throw the duck onto the altar, bones crushing " +
                      "as it lands. You slowly rip its breast open. Savouring "+
                      "every moment. Blood gushes forth as you break open the "+
                      "rib cage. You begin to feel dark powers growing inside "+
                      "you. They grip you, down to your soul. Chilling, yet inviting. "+
                      "You have found it! You see the still beating heart lying "+
                      "within the duck's breast. You greedily pull it out, and squeeze "+
                      "it slightly to feel its tenderness. You slowly bring "+
                      "the heart to your mouth.\n"
                      + "You smile grimly.\n"
                      + "You place the heart inside your mouth and begin to chew. "+
                      "The feeling of blood spurting forth from all directions "+
                      "can be felt inside your mouth. Soon, "+
                      "blood begins to pour from every corner and wall in the "+
                      "room. You are bathed in blood, head to toe.\n"
                      + "From the corner of your eye you see a small object, "+
                      "gargoyle-like in it's features, it whispers to you, "+
                      "'Thank you for serving the Vile One, he will reward you.'\n");
                say(QCTNAME(TP)+" throws a duck on the sacrificial altar. You "+
                    "cannot quite tell what "+ TP->query_pronoun() +" is doing, "+
                    "but a clear sound of ripping flesh and cracking bones "+
                    "can be heard.\n"
                    + "A dark shape forms around "+ TP->query_objective() +". "+
                    "All of the sudden you are bathed in blood coming "+
                    "from everywhere!\n" +
                    "Then, as suddenly as the blood came, it disappears, "+
                    "no trace of it can "+
                    "be found.\n");
                TP->command("laugh maniac");
                TP->command("cackle demonic");
                TP->command("say The Vile One will soon be my master.");
                TP->set_alignment(TP->query_alignment() -300);


                TP->catch_msg("You feel more experienced.\n");
                TP->add_exp(1000, 0);
                QUEST_SET_TP (Q_SACRIFICE_DUCK);
                QUEST_LOG_TP ("sacrificed a duck.");
            }

            if (duck = present("duck", TP)){
                duck->remove_object();
            }
            return 1;
        }
    }
}

void
init()
{
    ::init();

    add_action("do_sacrifice", "sacrifice");
}

