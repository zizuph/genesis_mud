#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit KENDERMORE_IN;

#define ODIR      "/d/Ansalon/private/entrance/obj/"

object door;

void
reset_kendermore_room()
{
}

void
create_kendermore_room()
{
    set_short("A damp dimly lit stone room");
    set_long("You are in what seems to be an old damp " + 
        "dungeon cell. Rough black stone surrounds you, from floor to " + 
        "walls to ceiling. A pile of dirty hay lies in the corner, " + 
        "most likely bedding for the unfortunate prisoners. "); 
    add_item(({"stone", "black stone", "rough stone", "rough black stone",
        "limestone"}),
        "Rough hewn blocks of limestone make up the walls, floors and " + 
        "ceiling of this cell. Black mold covers most of the stone.\n");
    add_item(({"mold", "black mold"}), "It looks like it has been growing " + 
        "for centuries.\n");
    add_item(({"hay", "pile of hay", "pile", "hay pile", "bedding"}), "The " + 
        "The hay looks " + 
        "dirty and smelly.\n");
    add_item(({"wall", "walls", "black wall", "black walls", "stone wall",
        "stone walls", "black stone wall", "black stone walls", "rough wall",
        "rough walls", "rough stone wall", "rough stone walls",
        "rough black stone wall", "rough black stone walls"}), "They are " + 
        "made of limestone, and covered with a thick layer of black mold.\n");
    add_item(({"layer", "mold", "mold layer", "black mold", "thick layer"}),
        "It looks like it's been growing here for centuries. Some of it " + 
        "has been scraped away near the pile of hay to reveal a surface " + 
        "of grey stone.\n");
    add_item(({"floor", "floors"}), "They are a bit slippery, covered " + 
        "with a thick layer of black mold.\n");
    add_item("ceiling", "An occasional drop of water drips down from the " + 
        "ceiling. It is covered in a thick layer of black mold.\n");
    add_item(({"water", "drop"}), "Water drips down from the ceiling " + 
        "into a shallow puddle on the floor.\n");
    add_item(({"puddle", "shallow puddle"}), "Water drips slowly into " + 
        "the puddle on the floor, making a steady and annoying sound.\n"); 
    add_search(({"hay", "pile", "hay pile", "pile of hay", "bedding"}),
        2, "search_hay", 1);
    set_tell_time(300);
    add_tell("A single drop of water separates itself from the ceiling " +
        "and falls into the puddle, leaving a slight echo in the room.\n");
    add_tell("The sound of something large moving above you can be heard.\n");
    add_tell("A chill in the air makes you shiver.\n");
    add_tell("You slip slightly on the mold on the floor.\n");
    add_tell("A rat moves around in the shadows.\n");
    add_tell("A spider scurries across the floor.\n");

    door = clone_object(ODIR + "qdoor3");
    door->move(TO);
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
search_hay()
{
    return "You search through the smelly pile of hay, and find " + 
        "nothing. You also get your hands dirty.\n";
}

