//
// Changed the do_sacrifice function slightly to parse items from
// the inventory and giving a hint that Kalach got a soft spot for
// ducks :) (In other words)
// --Baldacin, Dec 2015.

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>

#include "local.h"

object duck;


void
create_room()
{
    set_short("An orc temple");
    set_long(
        "This is an orc temple raised in the honour of the orcish"
        + " god, Kalach. As far as craftsmanship goes, this is the best"
        + " possible, for an orc. There is a rough stone altar against"
        + " one of the walls, obviously well used. The room is only"
        + " faintly lit, shadows cast around the room dancing with"
        + " the agility of the winds. Many candles are lined about"
        + " the walls, they seem to sway and flicker synchronized,"
        + " perfectly. Just above the altar itself stands a large,"
        + " menacing statue. The doorway to the south has"
        + " some sort of words encrusted around it. There are no windows"
        + " in this chamber, and other than the doorway to the south, the"
        + " only access is a cramped passage leading north, from which"
        + " there is a slight unnatural breeze.\n");
    add_item(({"altar", "stone altar"}),
             "You can see and smell bloody feathers as well as other "+
             "bits and pieces of what seems to be duck remains scattered "+
             "all around the altar. By the looks of it this altar is "+
             "used when you want to <sacrifice> something to the orc "+
             "god, Kalach.\n");
    add_item( ({ "passage", "cramped passage",
                 "north passage", "north", "northern passage",
                 "passage leading north",
                 "cramped passage leading north" }),
        "It almost seems to stare back at you.\n");
    add_item(({"candles"}), "They are lined in a figure eight just "+
    "in front of the altar.\n");
    add_item(({"doorway"}), "It has words or something around it.\n");
    add_item(({"words", "runes"}), "You cannot seem to decipher them.\n");
    add_item(({"statue", "statue of Kalach", "statue of kalach"}),
             "Standing malevolently above the altar, it stares "+
             "continually at you, no matter where you move. It "+
             "looks like some sort of demon. Three horns sprout from "+
             "its forehead. It most closely resembles a huge orc with "+
             "horns.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");
    add_exit(ORC+"r2", "south");
    add_exit(ORC + "stair", "north");
}

int
do_sacrifice(string str)
{
    object *items;
    int i;

    notify_fail("Sacrifice what?\n");

    items = FIND_STR_IN_OBJECT(str, TP);

    if (sizeof(items))
    {   
      if (sizeof(items)>1)
      {
        notify_fail("You can only try to sacrifice one thing at a time.\n");
        return 0;
      }

      //the quest duck got donald as name, everything else should just
      //give a hint.
      if (!items[0]->id("duck") && !items[0]->id("donald")) 
      {
        notify_fail("By looking at the remains and leftovers on the altar "+
          "you don't think Kalach will pleased with "+
          LANG_THESHORT(items[0])+". You must find a living sacrifice and "+
          "by the looks of it, ducks seem to be a common sacrifice...\n");
        return 0;
      } 
     
        if(TP->test_bit("Genesis", 0, 1)){
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

            if(TP->test_bit("Genesis",0,1))
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
//              TP->set_alignment(TP->query_alignment() -300);


                TP->catch_msg("You feel more experienced.\n");
                TP->add_exp(1000, 0);
                TP->set_bit(0,1);
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
