#pragma strict_types

inherit "/std/room";

#define OBJ "/d/Faerun/bootcamp/silk"
#define NPC "/d/Faerun/bootcamp/court_lady"

object silk;

public void

create_room()
{
    set_short("Inside a small fortress");

    set_long("You step inside from the balcony and find yourself in an " +
        "open room. Paintings hang on the walls in the empty space " +
        "between windows. Silks hang in front of the windows and drape " +
        "from the ceiling. Pillows and large cushions lie on the floor.\n"); 

    add_item( ({ "paintings","pictures"}),
        "The paintings are Van Gogh reproductions. Starry night, Cafe " +
        "Terrace at Night, The Mulberry Tree and The Blossoming Almond " +
        "Tree are some of the ones you are able to recognize.\n");

    add_item( ({ "walls"}),
        "The walls are clean, polished white marble. Keeping the room " +
        "comfortable in appearance and the temperature cool.\n");
        
    add_item( ({ "silks","silk"}),
        "Many differently colored silks cover the windows, hanging low " +
        "from the ceiling, making the room cozy and inviting.\n");
        
    add_item( ({ "pillows","large cushions","cushions"}),
        "The silk covered pillows are all shapes and sizes. They are " +
        "scattered casually around the room. Large oversized cushions " +
        "are also placed sporadically around the room, inviting you to " +
        "sprawl out and relax.\n");
        
    add_item( ({"room"}),
        "The room you stand in is luxurious and open. Windows line " +
        "the walls allowing the daylight to naturally light the room. " +
        "The ceiling is open, allowing you to see the trusses made of dark " +
        "wood that is polished and shined to an almost black state.\n");

    add_exit("/d/Faerun/bootcamp/balcony", "balcony");
    add_exit("/d/Faerun/bootcamp/courtyard", "courtyard");
    
    silk = clone_object(OBJ);
    silk->move (this_object() );

    add_npc("/d/Faerun/bootcamp/court_lady");
    }