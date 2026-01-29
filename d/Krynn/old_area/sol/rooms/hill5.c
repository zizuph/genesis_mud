/* Forest coded by Lord Rastlin */
/* Modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

inherit FORINROOM;

#define TORCH    OBJ + "oiltorch"
#define METAL    SHIREOBJ + "cast_iron"

int bones_found,
    metal_found;


void
reset_solace_room()
{
    bones_found = 0;
    metal_found = 0;
}

void
create_solace_room() 
{
    set_short("A small lit cave, in bearable condition");
    set_long("This small cave is the home of goblins. It reeks " +
             "of death and decay. Bones are scattered about the floor, " +
             "as are rusty pieces of metal. The walls of the cave are " +
             "made of a greyish rock, and are both damp and very solid. " +
             "This particular cave appears to be in a bit better " +
             "condition than the others, perhaps it is where the seeker " +
             "guards come to rest when they are allowed time " +
             "off duty.\n");
    add_item("cave", "You're standing in it.\n");
    add_item("bones", "Perhaps the bones of nearby wildlife...you hope.\n");
    add_item(({"metal", "pieces of metal"}), "The pieces of metal are " +
             "rusted beyond repair. They appear to have once been old " +
             "weapons and armours.\n");
    add_item(({"rock", "walls", "wall", "greyish rock", "grey rock"}),"The " +
             "walls of the cave are made out of some worn igneous rock. " +
             "It is most likely granite or andesite.\n");
    add_exit(TDIR + "hill1", "west");
    add_search("bones",4,"find_bones",1);
    add_search("metal", 4, "find_metal", 1);

    reset_solace_room();
}

mixed
find_bones(object who, string what)
{
    if (bones_found)
    {
        return 0;
    }

    say(QCTNAME(who) + " discovers something among the scattered "
      + "bones.\n");
    clone_object(TORCH)->move(TO, 1);
    bones_found = 1;

    return "You discover an oil-dipped torch among the "
      + "scattered bones.\n";
}

mixed
find_metal(object who, string what)
{
    if (metal_found)
    {
        return 0;
    }

    say(QCTNAME(who) + " discovers something among the rusty "
      + "pieces of metal.\n");
    clone_object(METAL)->move(TO, 1);
    metal_found = 1;

    return "You discover a useful piece of cast iron among "
      + "the rusty pieces of metal.\n";
}




