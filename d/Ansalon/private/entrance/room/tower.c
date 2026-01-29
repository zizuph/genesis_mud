#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define RDIR      "/d/Ansalon/private/entrance/room/"
#define POTION    "/d/Ansalon/private/entrance/obj/dpotion"

int vial_found = 0;

void
reset_kendermore_room()
{
    vial_found = 0;
}

void
create_kendermore_room()
{
    set_short("A room in a high tower");
    set_long("This room appears to be a study. A long table has been " + 
        "pushed against one wall, and a row of shelves is mounted on " + 
        "the opposite wall. You can glimpse the stairs to the west, " + 
        "and another doorway leads out to the balcony to the east. " + 
        "A thin layer of dust coats everything from top to bottom.\n"); 
    add_item("stairs", "It winds down beyond your view.\n");
    add_item(({"dust", "layer", "thin layer", "thin layer of dust"}),
        "Nobody has been in this room for a long time.\n");
    add_item(({"books", "vials", "bottles", "miscellaneous things"}),
        "They look like the props of a wizard or alchemist.\n");
    add_item(({"balcony", "doorway"}), "The doorway leads out to the " + 
        "balcony.\n");
    add_item(({"table", "long table"}), "It is covered with books, " + 
        "vials, bottles and other miscellaneous things.\n"); 
    add_item(({"row", "shelves", "row of shelves", "opposite wall"}),
        "It appears to be a storage space for vials, bottles and books " + 
        "that aren't in use.\n");
    add_item("stair", "It lies beyond the door to the west. It leads down " + 
        "into darkness.\n");
    add_item(({"stone", "rough stone", "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this room.\n");
    add_item(({"wall", "walls", "stone wall",
        "stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",}), "They " + 
        "are made of limestone, and look very sturdy. Torches are " + 
        "mounted on them, lighting the room with a dim " + 
        "eerie light.\n");
    add_item(({"floor", "floors"}), "They are made of roughly cut " + 
        "limestone.\n");
    add_item("ceiling", "It is made of roughly cut limestone.\n"); 
    add_item(({"torch", "torches"}), "They are large tar-drenched " + 
        "torches that light the room.\n");
    add_item(({"eerie shadows", "shadows", "eerie shadow", "shadow"}),
        "You can't quite see into the darkest part of the shadows. " + 
        "This looks like an excellent place to sneak around.\n"); 
    add_search(({"vials", "table", "long table"}),
        0, "find_vial", 1);
    set_tell_time(300);
    add_tell("The sound of something large moving below you can " + 
        "be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("The torches flicker, sending the shadows dancing.\n");
    add_tell("A breeze wafts in from the balcony, giving you a " + 
        "breath of fresh air.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    add_exit(RDIR + "stairs5", "west", "@@stair_message");
    add_exit(RDIR + "balcony", "out", "@@balcony_message");
    reset_kendermore_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

string
find_vial()
{
    if (!vial_found)
    {
        clone_object(POTION)->move(TP, 1);
        clone_object(POTION)->move(TP, 1);
        vial_found = 1;
        return "You find two frothy potions hidden among the vials.\n";
    }
    return "You find nothing but disturbed vials.\n";
}

int
stair_message()
{
    write("You look at the stairs, reluctant to go back into the " + 
        "dark gloomy castle.\n");
    return 0;
}

int
balcony_message()
{
    write("You leave the dusty room behind, and step into the fresh air.\n");
    return 0;
}
