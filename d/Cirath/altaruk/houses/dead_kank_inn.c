/*
 * /d/Cirath/altaruk/houses/dead_kank_inn.c
 *
 * A inn in Altaruk.
 *
 * Azazel
 */
#include "../defs.h"
inherit "/d/Cirath/std/room.c";

inherit "/lib/pub";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("korinne",ALT_NPC+"korinne.c",1,1);
}


void
create_room()
{
    set_short("the Dead Kank Inn.");
    set_long("This is the bar at the Dead Kank inn." +
        " A scarred female elf stands behind the bar, cleaning" +
        " a dirty mug. She is the owner, names Korinne. The walls " +
        " are hung with weapons and pelts of animals you don't" +
        " remember the names of. This is the main hangout of anyone" +
        " living in or passing through altaruk. A doorway leads" +
        " south into another room. A stairway leads upstairs.\n");

    add_item(({"wall", "walls", "pelts"}), "The walls are sandstone" +
        " with pelts and weapons securely hung for decorations." +
        " You guess they are stuff the owner has collected over the" +
        " years.\n");
    add_item("bar", "The bar is stabs of obsidian with a agafari" +
        " hardwood top. It looks clean. You see a menu on the wall" +
        " next to the bar. A gong is hung above it.\n");
    add_item("gong", "A dented bronze gong hangs over the bar." +
        " you have no idea what its for.\n");
    add_item(({"stair", "stairs", "stairway"}), "A stairway leads" +
        " upstairs to the rooms. Maybe you could ask the innkeeper" +
        " if there is available rooms?\n");

    add_item(({"menu","symbols"}),
     "In merchant code, symbols and in common writing" +
     " the menu lists:\n" +
     " Food                          Drinks\n"+
     "honey glob       30 cc        cactus juice        12 cc\n"+
     "small omelet     75 cc        tyrian ale          70 cc\n"+
     "inix steak      100 cc        honey mead         100 cc\n"+
     "erdlu egg       120 cc        dead kank          130 cc\n\n");

    add_cmd_item(({"menu","symbols"}),"read",
     "In merchant code, symbols and in common writing" +
     " the menu lists:\n" +
     " Food                          Drinks\n"+
     "honey glob       30 cc        cactus juice        12 cc\n"+
     "small omelet     75 cc        tyrian ale          70 cc\n"+
     "inix steak      100 cc        honey mead         100 cc\n"+
     "erdlu egg       120 cc        dead kank          130 cc\n\n"); 

    add_drink("juice","juice","cactus",50,0,12,0,0,
        "A mug of juice from a freshly crushed cactus.\n",0);
    add_drink(({"ale","ales","tyrian ale","tyrian ales"}),
        "ale","tyrian",125,25,70,0,0,
        "A stout ale brewed in tyr. A barrel or two must have"+
        " fallen of a caravan.\n",0);
    add_drink(({"mead","meads","honey mead","honey meads"}),
        "mead","honey",150,50,100,0,0,
        "A mead made from kank honey and spices. It can put"+
        " muscles back on those skinny bones of yours.\n",0);
    add_drink(({"kank","kanks","dead kank","dead kanks"}),
        "kank","dead",120,120,130,0,0,
        "This is a specialty of the Dead Kank inn. A green"+
        " goo-like drink. You don't want to know whats in it.\n",0);
     
    add_food(({"honey", "glob", "globs", "honey glob",
        "honey globs"}),"glob","honey",30,30,0,0,
        "A small glob of honey from a kank.\n",0);
    add_food(({"omelet","omelets","small omelet","small omelets"}),
        "omelet","small",50,75,0,0,
        "This a small omelet made from an erdlu egg and"+
        " spices. A good breakfast.\n",0);
    add_food(({"steak","steaks","inix steak", "inix steaks"}),
        "steak","inix",85,100,0,0,
        "A slab of inix meat, seasoned in the sun, grilled and"+
        " served with chopped mushrooms. A real feast for the" +
        " pallet.\n",0);
    add_food(({"egg","eggs","erdlu egg", "erdlu eggs"}),
        "egg","erdlu",120,120,0,0,
        "A raw erdlu egg. In the desert this can keep"+
        " you fed for a week. A breakfast of champions.\n",0);

    add_prop(ROOM_I_INSIDE,1);
    add_exit(ALT_STR+"11.c","north",0,1,0);
    add_exit("dkinn2.c","south",0,1,0);
    add_exit("dkinnup1.c","up",0,1,0);

    reset_room();

}

void
init()
{
    ::init();
    init_pub();
}

