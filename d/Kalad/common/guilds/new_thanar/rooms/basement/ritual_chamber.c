/* 
 * The ritual chamber where players will summon Thanar and complete the 
 * Thanar summon quest for the blacksmith.
 *
 * Players will need the completed medallion to even enter this room. So
 * that should not be an issue. Once here they are not locked in. I might
 * consider locking them in if they abuse it. I just don't want it to be
 * to big of a death-trap.
 
 * Initially the summon will bring the Thanar Kitten. This is a bit of a 
 * test. See how much they pay attention. In order to complete the quest 
 * they need to kill Thanar.
 *
 * /d/Kalad/common/guilds/new_thanar/ritual_chamber
 */

#include "../local.h"

inherit THANAR_BASE_STD; 
#define I_DID_THE_SUMMON "_i_did_the_summon_"

/*Global Variable*/
int thanar_summon = 0;

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    set_short("Inside the Ritual Chamber");
    set_long("The room is mangificent and horrible all at the same time. "
        + "The walls are unnaturally smooth and bare, other than lanterns "
        + "which bring light into this otherwise desolate place. There "
        + "are no marks on any of the surfaces as though this room has "
        + "existed for eternity, but is brand new. In the centre of the "
        + "room stands an altar of black.\n");  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "Constructed from "
        + "some unknown material, the walls are bare and appear to have been"
        + "formed naturally. Lanterns have been attached to the walls as with "
        + "the rest of the area but otherwise the walls are bare. There is "
        + "a large altar in the middle of the room.\n");
    add_item(({"floor", "floors"}), "The floors are of an unknown material "
        + "and appear to have existed for eternity. They are barren and "
        + "unnaturally smooth.\n");
    add_item(({"altar", "large altar", "middle", "middle of room"}), "The "
        + "altar is ancient. Made of some unknown material it seems to "
        + "draw light into it. The black approaches the infinite. there "
        + "are some words swirling, like snakes, along the surface of the "
        + "altar. You might be able to <read> them.\n");
    add_cmd_item("words", ({"read", "examine", "exa"}), "@@read_words@@");
        
    clone_object(DOORS + "ritual_door2")->move(TO);
        
        //sets the no exit message
    set_no_exit_msg(get_all_no_exits(({"n"})),
    "The walls block your path.\n");
    reset_room();
}

/*
 * Function name: init()
 * Description  : Initializes the commands for the room.
 */
void 
init()
{
    ::init();
    add_action("do_summon",   "invoke");

}

/*
 * Function name: read_words()
 * Description  : The return for reading the sign/words in the room.
 */
string 
read_words()
{
  return "\n"+                 
  "  +-------------+ |-----------------------------------| +-------------+\n" +
  "  | +-------------+-----------------------------------+-------------+ |\n" +
  "  | |                                                               | |\n" +
  "  | |                                                               | |\n" +
  "  | |                                                               | |\n" +
  "  | |                                                               | |\n" +
  "  | |    If you have come, and come prepared you find yourself      | |\n" +
  "  | |    within His lair. Lord Thanar, the Immortal, the            | |\n" +
  "  | |    Unbreakable. the Omnipotent.                               | |\n" +
  "  | |                                                               | |\n" +
  "  | |    Long has he reigned from the realm beyond, bringing        | |\n" +
  "  | |    the human race to its place of glory with Kalad. If        | |\n" +
  "  | |    you are here, it is for one reason and one alone.          | |\n" +
  "  | |                                                               | |\n" +
  "  | |    If you wish to go through with the summoning you had best  | |\n" +
  "  | |    be prepared. Thanar is unforgiving and with smite any who  | |\n" +
  "  | |    he feels are unworth. His rage is unending. You must have  | |\n" +
  "  | |    his medallion, if you are here, and with it you can summon | |\n" +
  "  | |    him. All you must do is <invoke ranaht> and he will come.  | |\n" +
  "  | |                                                               | |\n" +
  "  | |                                                               | |\n" +
  "  | |    Do so at your own peril.                                   | |\n" +
  "  | |                                                               | |\n" +
  "  | +---------------------------------------------------------------+ |\n" +
  "  +-------------------------------------------------------------------+\n\n";
}

/*
* Function name: do_summon
* Description  : This is where the summoning of Thanar takes place.
* Arguments    : string str - the command line argument.
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_summon(string str)
{
    
    //Set the objects
    object thanarnpc, medallion;
    
    //You need to use the right string
    if (!strlen(str) || str != "ranaht")
    {
        notify_fail("If you wish to summon Lord Thanar you must be precise"
            +" <invoke ranaht>\n");
        return 0;
    }

    //Let's make sure Thanar or the kitten aren't in the room somehow.
    if (present("_thanar_npc_", E(TP)) || 
        present("_thanar_kitten_npc_", E(TP)))
    {
        notify_fail("Lord Thanar is present in all of his Glory. He "
            + "be summoned again!\n");
        return 0;
    }

    //Make sure he hasn't been summoned recently. Need to wait for room to reset.
    if(thanar_summon == 1)
    {
        notify_fail("The Lord Thanar has recently been summoned. His influence"+
            " over the realms is still present. You will have to return another "
            +"time\n.");
            return 0;
    }
    
    //Can't summon him right away again.
    if(TP->query_prop(I_DID_THE_SUMMON))
    {
        notify_fail("You've already managed to summon Thanar. You can't "
        +"do so again.\n");
        return 0;
    }

    if (!TP->test_bit("Kalad", 1, 16))
    {
        notify_fail("You may have the medallion, but you did not earn it. "
        +"Come back when you are worth of Thanar's notice.\n");
        return 0;

    }

    //Let's make sure they can't do it twice.
    if (TP->test_bit("Kalad", 1, 17))
    {
        notify_fail("You've released Thanar into the world. You are not able "
        +"to do so again.\n");
        return 0;
    }
    //Let's also tell the player they don't have the medallion if they
    //trying to summon Thanar. They shouldn't be able to get here without
    //it, but let's check anyways.

    if (!objectp(medallion = present("_thanar_medallion_", this_player())))
    {
        notify_fail("You are not prepared to summon the Lord Thanar.\n"
        + "Return when you have the medallion!\n");
        return 0;
    }



    //Check they used the right string and ensure the medallion is presnet
    if (str == "ranaht" && 
        objectp(medallion = present("_thanar_medallion_", this_player())))
    {
        //Do the summon ritual
        
        set_alarm(1.0, 0.0, &write("As the words leave your mouth the "
            + "medallion in your hand begins to glow brightly. It rises "
            + "up into the air above the altar.\n\n"));
        set_alarm(1.0, 0.0, &say("As "+QTNAME(TP) +" speaks the words of "
            + "summoning, "+HIS(TP)+" medallion begins to glow brightly. " 
            + "It rises into the air above the altar.\n\n"));
        
        set_alarm(4.0, 0.0, &write("The medallion begins to spin in the "
            +"air. It draws all the light from the lanterns towards it as "
            +"though they bring it power.\n\n"));
        set_alarm(4.0, 0.0, &say("The medallion begins to spin in the "
            +"air. It draws all the light from the lanterns towards it as "
            +"though they bring it power.\n\n")); 
        
        set_alarm(8.0, 0.0, &write("The wind picks up in the room and "
            + "swirls towards the altar. You strain your legs against the "
            + "force to prevent yourself from being drawn in.\n\n"));
        set_alarm(8.0, 0.0, &say("The wind picks up in the room and "
            + "swirls towards the altar. You strain your legs against the "
            + "force to prevent yourself from being drawn in.\n\n"));
            
        set_alarm(11.0, 0.0, &write("A bright stream of light shoots from "
            + "the medallion straight down into the centre of the altar "
            + "causing it to begin to glow brightly. You are forced to "
            + "turn your head from the altar.\n\n"));
         set_alarm(11.0, 0.0, &say("A bright stream of light shoots from "
            + "the medallion straight down into the centre of the altar "
            + "causing it to begin to glow brightly. You are forced to "
            + "turn your head from the altar.\n\n"));
        
        set_alarm(14.0, 0.0, &write("Just as soon as it began, the wind "
            + "subsides. The light begins to dim within the room and "
            + "returns to normal. You hear a rustling behind you and turn "
            + "your head back towards the altar. You stare in absolute "
            + "shock.\n\n"));
         set_alarm(14.0, 0.0, &say("Just as soon as it began, the wind "
            + "subsides. The light begins to dim within the room and "
            + "returns to normal. You hear a rustling behind you and turn "
            + "your head back towards the altar. You stare in absolute "
            + "shock.\n\n"));
        
        set_alarm(17.0, 0.0, &write("A small undead kitten stands in the "
            + "centre of the room. It looks up and mews "
            + "pitifully at you.\n\n"));
         set_alarm(17.0, 0.0, &say("A small undead kitten stands in the "
            + "centre of the room. It looks up and mews "
            + "pitifully at you.\n\n"));

            clone_object(LIV + "thanar_kitten")->move(E(TP));
            TP->add_prop(I_DID_THE_SUMMON, 1);
            thanar_summon = 1;
    }
    
    //Clone the kitten and move it here.
    
    return 1;
}

    
void
reset_room()
{
    thanar_summon = 0;
}
