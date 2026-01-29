/* /d/Faerun/guilds/fire_knives/rooms/sr.c
 *
 * Starting room 
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Resting Chambers");
    
    set_long("A quiet and spacious room with various booths divided by "
    + "velvet curtains hanging from blade-shaped poles encrusted within "
    + "the walls below each sconce. High hanging torches from each of them "
    + "would shed light upon the whole of the room were it not for the fact "
    + "that the lot of them are merely decorative, leaving the chamber in "
    + "an utter darkness to facilitate rest while also presenting the "
    + "challenge "
    + "of getting ready both to leave and sleep "
    + "without any outside source of "
    + "light. If you have found this space, you "
    + "have earned the right to take "
    + "such a challenge upon yourself. Full members may <start here> if "
    + "they so desire.\n");
    
    add_item(({"bed","bunks","beds"}),
    "The beds are single and apparently comfortable. Members "
    +"may <start here> "
    +"if they so desire.\n");
    
    add_item(({"darkness"}),
    "It's all around you.\n");
    
    add_item(({"room"}),
    "You are within it.\n");
    
    add_item(({"booths", "booth"}),
    "The booths are formed by the division of space made by the "
    +"curtains between "
    +"each one of the beds found within the room.\n");
    
    add_item(({"curtain", "curtains"}),
    "The curtains are made of a velvet fabric, soft to the touch "
    +"and emanating "
    +"nothing but a whisper when drawn to enter one of the booths.\n");
    
    add_item(({"poles"}),
    "The poles are made in the form of blades which have been "
    +"impaled upon the "
    +"walls, and from which hang the curtains.\n");
    
    add_item(({"floor"}),
    "The room is covered in a simple black carpet the muffles all sound "
    +"and provides protection against the coldness of the "
    +"stone underneath it.\n");
    
    add_item(({"stone","stones"}),
    "The stone of the floor of the old keep is covered in carpets.\n");
    
    add_item(({"sconces","sconce"}),
    "The sconces hang on the walls, holding torches.\n");
    
    add_item(({"torches","torch"}),
    "The torches hang on the sconces. They are purely decorative.\n");
    
    add_item(({"walls","wall"}),
    "The walls of the chamber are simple and bare, devoid of decorations.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "h8", "east");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


int
do_start(string str)
{
    if (str != "here")
    {

        write("<start here>, perhaps?\n");

        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()))
    {
        this_player()->set_default_start_location(file_name(this_object()));

        write("From now on, you will awake here when entering the game.\n");

        return 1;
    }
    
    write("You are not a member of the Fire Knives!\n");
    return 1;
}


void init()
{
    ::init();

    add_action(do_start, "start");
}
