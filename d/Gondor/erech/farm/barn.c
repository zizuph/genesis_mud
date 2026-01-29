/*
 * barn.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "inside.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Global variables */
object ob;

/* Prototypes */
public void         create_gondor();
string              create_barn();
void                add_barn_items();

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
    set_short("A Gondorian barn.");
    set_long(&create_barn());

    add_barn_items();
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(E_FARM + "yard.c", "southwest", 0, 3, 0);

    reset_room();
}

void
reset_room()
{
    if (!present("hen"))
    {
        ob=clone_object(E_NPC + "fhen");
	ob->move(this_object());
    }
    if (!present("cow"))
    {
	ob=clone_object(E_NPC + "fcow");
	ob->move(this_object());
    }
}

void
add_barn_items()
{
    object  clock = find_object(CLOCK);
    int month = clock->query_month();
    string  time  = clock->query_time_of_day();

    add_item(({"ceiling", "roof", "pigeons"}), "The barn roof is well made " +
        "and keeps the animals from the rain. The pigeons on the roof " +
        "can't be seen, but you hear the flapping of their wings and " +
        "the scratching of their feet.\n");
    add_item(({"ground", "floor", "dirt"}), "The floor of the barn is made " +
        "of hard packed dirt. It is used for winter hay storage.\n");

    switch(month)
    {
    case 1:
        // January
        add_item(({"hay", "fine hay", "fine dry hay"}), "Hay fills the " +
            "barn, having been stored here for the winter.\n");
        break;
    case 2:
        // February
        add_item(({"hay", "fine hay", "fine dry hay"}), "Hay fills the " +
            "barn somewhat, having been stored here for the winter.\n");
        break;
    case 3:
        // March
        add_item(({"hay", "fine hay", "fine dry hay"}), "There is a little " +
            "hay left in the barn from the winter store.\n");
        break;
    case 4:
        // April
        add_item(({"corner", "barrels", "grain"}), "The barrels have " +
            "been pushed into one corner and used to store grain for " +
            "sawing.\n");
        break;
    case 5:
        // May
        add_item(({"hay", "fine hay", "fine dry hay", "floor", "ground"}), 
            "Some remains of hay lie about the floor.\n");
        add_item(({"barrels", "empty barrels"}), "There are a few grains " +
            "in the barrels.\n");
        add_item("grains", "There is only a little bit of grain leftover " +
            "from last month.\n");
        break;
    case 6:
        // June
        break;
    case 7:
        // July
        add_item(({"hay", "fine hay", "fine dry hay", "floor", "ground"}), 
            "Freshly harvested hay is stored in one corner for the " +
            "upcoming winter.\n");
        break;
    case 8:
        // August
        add_item(({"crates", "empty crates", "crate"}), "The empty " +
            "crates in the corner will be used to store the fall fruits.\n");
        break;
    case 9:
        // September
        add_item(({"crates", "corner", "crate"}), "The crates are " +
            "filled with the fall fruit harvest.\n");
        add_item(({"hay", "pile", "pile of hay"}), "The hay in the center " +
            "of the room is being stocked up for the winter.\n");
        break;
    case 10:
        // October
        add_item(({"hay", "piles", "piles of hay"}), "The hay being stored " +
            "up for the winter is plentiful now.\n");
        break;
    case 11:
        // November
        add_item(({"hay", "piles", "piles of hay"}), "The hay being stored " +
            "up for the winter is plentiful now.\n");
        break;
    default:
        // December
        add_item(({"hay", "piles", "piles of hay"}), "The hay being stored " +
            "up for the winter is plentiful now.\n");
        break;
    }
    switch (time)
    {
    case "night":
        add_item(({"stars", "gate", "sky"}), "Just through the gate, you " +
            "notice stars twinkle brightly in the night sky.\n");
        break;
    case "early morning":
        add_item(({"sky", "gate", "sun", "rays"}), "The morning sun is " +
            "rising above the horizon, it's warm rays shining through " +
            "the gate.\n");
        break;
    case "morning":
        add_item(({"columns", "sun", "rays"}), "The bright rays from the " +
            "morning sun hit the columns supporting the barn.\n");
        break;
    case "noon":
    case "afternoon":
        add_item("sun", "The brightness outside makes the barn appear " +
            "dark as your eyes attempt to adjust.\n");
        break;
    default:
        add_item(({"rays", "sun", "shadows"}), "The shadows cast in the " +
            "barn grow long as the sun sets.\n");
        break;
    } 
}

string
create_barn()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day(),
            desc;
    int     day   = clock->query_day(),
            month = clock->query_month(),
            year  = clock->query_year();



    desc = "You stand just inside a barn. ";
    switch (month)
    {
    case 1:
        // January
        desc += "The barn is used for storage as well as animals. " +
            "It is rather full of fine dry hay being stored " +
            "for the winter. ";
        break;
    case 2:
        // February
        desc += "The barn is used for storage as well as animals. " +
            "It is somewhat full of fine dry hay being stored for the " +
            "winter. ";
        break;
    case 3:
        // March
        desc += "The barn is used for storage as well as animals. " +
            "There is a little hay being stored in the barn right now for " +
            "the winter. ";
        break;
    case 4:
        // April
        desc +=  "The barn is used for storage as well as animals. " +
            "The barn is almost empty of its winter hay storage. Hopefully " +
            "the spring will bring fresh grass for the animals. In one " +
            "corner some barrels with grain for sawing have been placed. ";
        break;
    case 5:
        // May
        desc += "On the floor lies the final remains of dry hay " +
            "from the winter, and in a corner some empty barrels can be " +
            "found. ";
        break;
    case 6:
        // June
        desc += "It feels empty with all this open space. ";
        break;
    case 7:
        // July
        desc += "Some fresh hay is gathered in one corner in preparation " +
            "for the winter months. ";
        break;
    case 8:
        // August
        desc += "In one corner some empty crates can be found. ";
        break;
    case 9:
        // September
        desc += "Some crates filled with fruit have been pushed into one " + 
            "corner, waiting for delivery. A pile of hay is growing " +
            "in the center of the room in preparation for the winter months. ";
        break;
    case 10:
        // October
        desc +=  "The barn is used for storage as well as animals. " +
            "Piles of fine hay fill the barn, stored for the upcoming " +
            "winter months. ";
        break;
    case 11:
        // November
        desc +=  "The barn is used for storage as well as animals. " + 
            "Piles of fine dry hay fill the barn, stored for the barren " +
            "winter months. ";
        break;
    default:
        // December
        desc +=  "The barn is used for storage as well as animals. " +
            "The barn is very full of fine dry hay right now, a plentiful " +
            "winter store. ";
        break;
    }

    switch (time)
    {
    case "night":
        desc += "It is possible to see stars through the open gate. ";
        break;
    case "early morning":
        desc += "Through the gate you can see the sky turning red as " +
            "dawn comes. ";
        break;
    case "morning":
        desc += "The rays from the morning sun shine upon some columns " +
            "in the back of the barn. ";
        break;
    case "noon":
    case "afternoon":
        desc += "The sun shines brightly outside, in contrast to the " +
            "dimly lit barn. ";
        break;
    default:
        desc += "The rays from the setting sun make the shadows long. ";
    }

    desc += "Upon the ceiling, the sound of pigeons can be heard.\n";
    return desc;
}
