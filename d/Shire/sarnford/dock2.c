/*
 * Docks at Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Gondor/common/lib/herbsearch";
inherit LIBPIER;

void
create_room()
{
    set_short("Standing on the dock");
    set_long("You are standing at the end of a small, but " +
      	"well-maintained dock that reaches out into the middle " +
      	"of the majestic Brandywine river as it rushes down " +
      	"from the north before spilling itself out into the wide " +
      	"expanse of the sea to the southwest. To the southeast, you " +
      	"can see a large, wooden building sitting right beside the " +
      	"point where this sturdy dock meets land, where a small, " +
      	"dirt path leads away northeast, up to a grassy hill in the " +
      	"far distance. A small, weathered poster here lets you know that " +
      	"occasionally, a ship will take travellers to the " +
      	"Grey Havens.\n");
    
    add_item(({"river", "brandywine", "brandywine river"}),
        "This massive river is so wide, it is difficult to see " +
        "the western bank from here! But looking upstream, you " +
        "think you can see a major tributary joining in on the " +
        "far side, helping make the river deep enough to allow " +
        "boats to navigate this far inland.\n");
    add_item(({"tributary", "major tributary"}),
      	"It is too far away to say for sure, but it looks like there " +
      	"are two rivers joining up here, making the river run deeper " +
      	"and faster.\n");
    add_item(({"building", "inn", "sleepy fisherman", "the sleepy fisherman", "sleepy fisherman inn", "the sleepy fisherman inn"}),
        "This tall building appears an inn called The Sleepy Fisherman. " +
        "Thick wooden planks cover the walls, as a few windows and a stout " +
        "oak door offer a hint of the warmth available inside. Slate tiles "+
        "cover the roof, helping to keep the inn warm and dry.\n");
    add_item(({"dock", "modest dock", "wooden dock"}),
        "This modest, wooden dock stretches out into the middle of the " +
        "mighty Brandywine river. Every now and then, a ship will " +
        "arrive in, offering passage to a distant and foreign land " +
        "known as 'Sparkle'. You see space for a second ship " +
        "out a little farther into the river.\n");
    add_item(({"ship", "ships"}),
        "There are no ships docked here right now, but the chances " +
        "are that the next one will arrive before too much longer.\n");
    add_item(({"bank", "riverbank"}),
        "Along the banks of the river, you spy a small, narrow path " +
        "which winds away to the northeast.\n");
    add_item(({"path", "dirt", "small path", "dirt path", "narrow path"}),
        "This dirt path is both small and narrow, and it follows the " +
        "riverbank while winding up near a grassy hill to the northeast.\n");
    add_item(({"hill", "grassy hill"}),
        "This is just a grassy hill, nothing more can be seen from here. " +
        "If you were to follow the path northeast from here, you would " +
        "guess it would take you fairly close to that hill.\n");
    add_item(({"sign", "wooden sign"}),
        "This wooden sign has a picture of a man sleeping beside a " +
        "river, with a fishing pole in his hands. Above the picture, " +
        "in beautifully carved letters, reads a name: 'The Sleeping " +
        "Fisherman Inn'.\n");
    add_item(({"slate", "tiles", "slate tiles", "roof"}),
        "Hundreds of flat, slate tiles cover the slanted roof in a dazzling " +
        "display of almost every colour imaginable. You would imagine " +
        "that a slate roof like this must have cost a fortune! However, " +
        "it will also do a very good job of keeping the inn very warm " +
        "and dry. A stone chimney peeks out of the slate tile at the " +
        "south end of the inn.\n");
    add_item(({"chimney", "sturdy chimney", "stone chimney"}),
        "At the south end of the roof, a study, stone chimney rises " +
        "up to happily puff out a constant stream of thick, grey smoke.\n");
    add_item(({"smoke", "grey smoke"}),
        "This smoke is coming from the chimney of the inn. The innkeeper " +
        "probably keeps a fire constantly going for the comfort of his " +
        "customers.\n");
    add_item(({"door", "thick door", "oak door"}),
        "This thick, oak door is quite sturdy, yet also strangely " +
        "welcoming. You feel a powerful urge to enter and enjoy " +
        "the comfort of the inn inside.\n");
    add_item(({"window", "windows"}),
        "Several windows are scattered around the walls of the inn, " +
        "presumably to allow the people inside to see what is happening " +
        "out here.\n");
    add_item(({"walls", "wall", "planks", "plank", "wooden wall", "wooden walls", "wooden plank", "wooden planks"}),
        "Several wide, wooden planks form the walls of this inn. They " +
        "look quite sturdy and well maintained, a good sign that the " +
        "innkeeper is probably keeping the customers happy.\n");
    add_item(({"sea", "ocean", "sparkle"}),
        "You cannot see the sea from here, but across it lies the " +
        "foreign land named Sparkle.\n");
    add_item(({"poster", "weathered poster", "small poster"}),
      	"A weathered poster here informs you that a ship will transport " +
      	"travellers from here to the Grey Havens on a regular schedule.\n");

    add_exit(SARNFORD_DIR + "dock.c", "southeast");

    add_pier_entry(MASTER_OB(this_object()), "Sarn Ford", "Dock to Grey Havens");
    initialize_pier();    
}
