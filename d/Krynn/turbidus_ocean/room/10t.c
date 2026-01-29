#include "/d/Krynn/common/defs.h"
#include "/d/Calia/sys/water.h"
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit SAIL_ROOM_BASE;

#include "/d/Krynn/common/herbsearch.h"

#define ONE_OF(x)     ((x)[random(sizeof(x))])
#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

#define PIRATE_CAPTAIN TURBIDUS + "living/pirate_captain"
#define PIRATE         TURBIDUS + "living/pirate"
#define MARKSMAN       TURBIDUS + "living/pirate_marksman"
#define MINO_BOARDER   TURBIDUS + "living/minotaur_boarder"

#define ERGOTH_CAPTAIN TURBIDUS + "living/ergothian_captain"
#define ERGOTH_MAGE    TURBIDUS + "living/ergothian_wizard"
#define ERGOTH_SAILOR  TURBIDUS + "living/ergothian_sailor"

// Base pirate board time of galleon is 15 minutes 
// from room reset plus a random factor.

#define BOARD_TIME 900.0

string *herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );

object pirate_ship, ergoth_ship, captain, captain2, mage,
    sailor1, sailor2, sailor3, mb1, mb2, mb3, ship_loc,
    pirate1, pirate2, pirate3, marksman;


void
board_galleon_two()
{
    mb1->command("say Argh! To the ropes!");
    mb2->command("say Board the galleon!");
    mb1->command("board ergothian galleon");
    mb1->command("kill sailor");
    mb2->command("board ergothian galleon");
    mb2->command("kill sailor");
    mb3->command("board ergothian galleon");
    mb3->command("kill sailor");

    return;
}

public void
board_galleon(object ship_loc)
{
    mb1 = clone_object(MINO_BOARDER);
    mb2 = clone_object(MINO_BOARDER);
    mb3 = clone_object(MINO_BOARDER);

    mb1->move_living("into his pirate warship", ship_loc);
    mb2->move_living("into his pirate warship", ship_loc);
    mb3->move_living("into his pirate warship", ship_loc);

    mb1->command("say It's time!");
    mb2->command("emote roars impatiently!");
    mb3->command("say What we waiting for? Let's get the treasure!");

    set_alarm(5.0, 0.0, &board_galleon_two());

    return;
}

void
reset_sea_room()
{
    set_searched(0);

    object boat_in, boat_in2;
    int board_time;

    if (!objectp(pirate_ship)) 
    {
          pirate_ship = clone_object(TOBJ +"pirate_warship");
          pirate_ship->move(this_object());
    }
    if (!objectp(boat_in = pirate_ship->query_boat_in())) 
    {
         pirate_ship->config_boat_inside();
         boat_in = pirate_ship->query_boat_in();
    }

     if (!objectp(marksman)) 
     {
         marksman = clone_object(MARKSMAN);
         marksman->move_living("into his pirate warship", boat_in); 
     }

     if (!objectp(pirate1)) 
     {
         pirate1 = clone_object(PIRATE);
         pirate1->move_living("into his pirate warship", boat_in); 
     }

     if (!objectp(pirate2)) 
     {
         pirate2 = clone_object(PIRATE);
         pirate2->move_living("into his pirate warship", boat_in); 
     }

     if (!objectp(pirate3)) 
     {
         pirate3 = clone_object(PIRATE);
         pirate3->move_living("into his pirate warship", boat_in); 
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(PIRATE_CAPTAIN);
         captain->move_living("into his pirate warship", boat_in);
         boat_in->set_owner(captain); 
     }

     if (!objectp(ergoth_ship)) 
     {
          ergoth_ship = clone_object(TOBJ +"ergothian_warship");
          ergoth_ship->move(this_object());
     }
     if (!objectp(boat_in2 = ergoth_ship->query_boat_in())) 
     {
         ergoth_ship->config_boat_inside();
         boat_in2 = ergoth_ship->query_boat_in();
     }

     if (!objectp(mage)) 
     {
         mage = clone_object(ERGOTH_MAGE);
         mage->move_living("into his Ergothian galleon", boat_in2);
         mage->arm_me();
     }

     if (!objectp(sailor1)) 
     {
         sailor1 = clone_object(ERGOTH_SAILOR);
         sailor1->move_living("into his Ergothian galleon", boat_in2);
         sailor1->arm_me();
     }

     if (!objectp(sailor2)) 
     {
         sailor2 = clone_object(ERGOTH_SAILOR);
         sailor2->move_living("into his Ergothian galleon", boat_in2);
         sailor2->arm_me();
     }

     if (!objectp(sailor3)) 
     {
         sailor3 = clone_object(ERGOTH_SAILOR);
         sailor3->move_living("into his Ergothian galleon", boat_in2);
         sailor3->arm_me();
     }

     if (!objectp(captain2)) 
     {
         captain2 = clone_object(ERGOTH_CAPTAIN);
         captain2->move_living("into his Ergothian galleon", boat_in2);
         boat_in2->set_owner(captain); 
     }

    // clone the minotaur galleon boarders
    board_time = ftoi(BOARD_TIME) + random(ftoi(BOARD_TIME)) +
        random(ftoi(BOARD_TIME));

    set_alarm(itof(board_time), 0.0, &board_galleon(boat_in));
}

void
create_sea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");
 
    add_item(({"turbidus ocean","ocean","sea"}),
        "To your north stretches the Turbidus Ocean - a massive body of water " +
        "that extends from the Courrain Ocean in the east, across northern " +
        "Ansalon to the Sirrion Sea in the west.\n");
    add_item(({"pirates"}),
        "Pirates have grappled an Ergothian galleon, and are swinging " +
        "on ropes from the rigging to board the galleon!\n");
    add_item(({"sailors","ergothian sailors"}),
        "You can make out Ergothian sailors repelling pirates from their " +
        "decks and counter attacking and boarding the pirate frigate!\n");

    add_row_exit(ROOM + "9t", "south", "@@no_sail", 1);
    add_row_exit(ROOM + "10u", "east", "@@no_sail", 1);
    add_row_exit(ROOM + "11t", "north", "@@no_sail", 1);
    add_row_exit(ROOM + "10s", "west", "@@no_sail", 1);


    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the Turbidus Ocean are " +
        "rough, and beyond your sailing skills to navigate!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "open waters of the Turbidus Ocean!\n");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({"sea","water"}), 2);

    reset_sea_room();
}

string
short_descr()
{
    return "battle on the high seas of the Turbidus Ocean";
}
 
string
long_descr()
{
    return "Before you two great ships of the Turbidus Ocean are " +
        "locked together in battle, an embrace that only one will " +
        "emerge victorious from! Pirates and Ergothian sailors swing " +
        "on ropes from deck to deck and engage in furious combat! " +
        query_sailing_difficulty_desc()+ "\n";
}

int
no_sail()
{
    if(environment(TP)->id("_turbidus_battling_ship"))
    {
        write("This ship has been grappled and is unable to sail!\n");
        return 1;
    }
    return 0;
}
