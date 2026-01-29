/*
 * Base file for indoor houses and farmhouses in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
//inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_house_room() {}

int room_num;
string  floor   = "",
        walls   = "",
        ceiling = "",
        windows = "";


public void
create_room()
{

    set_short("Inside a house in Green Oaks");
    set_long("Inside a house.\n");

    create_house_room();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_NO_ALLOW_STEED, 1); // sorry, no horses in here.

}

/******************************************************************************
 * Main routines for describing areas
 ******************************************************************************/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Elf house definitions
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Function name : set_elf_windows
 * Description   : adds descr of windows in elf houses
 *                 Allows extra descr to be included.
 */
void set_elf_windows(string str)
{
    add_item(({"windows", "window"}),
        "The windows are openings set into the walls. They are open and allow fresh air and light into the room. " + str + "\n");
}

/*
 * Function name : set_elf_colors
 * Description   : adds descr of basic elf colors in house
 */
void set_elf_colors()
{
    add_item(({"colors", "elf colors"}),
        "The colors are basic earth shades preferred by elves. There are browns, greens, muted yellows, soft whites, reds, blues, and other colors you don't recognize. They are used in decorating the house.\n");
}

/*
 * Function name : set_elf_ceiling
 * Description   : adds descr ceilings in elf houses.
 *                 Allows extra descr to be included.
 */
void set_elf_ceiling(string str)
{
    add_item(({"ceiling"}),
        "The ceiling is flat and plain. It is a natural color and blends " +
        "in with the other neutral colors of the room. " + str + "\n");
}

/*
 * Function name : set_elf_walls
 * Description   : adds descr of walls in elf houses
 *                 Allows extra descr to be included.
 */
void set_elf_walls(string str)
{
    add_item(({"walls"}),
        "The walls are smooth and made from gray stone. They are stacked in such a way that their seams are invisible. Windows are set into the walls and allow fresh air and light in. " + str + "\n");
//    add_elf_stones();
}

/*
 * Function name : set_elf_floor
 * Description   : adds descr of floor in elf houses
 *                 Allows extra descr to be included.
 */
void set_elf_floor(string str)
{
    add_item(({"floor", "ground"}),
        "The floor is smoth and clean. " + str + "\n");
}

/*
 * Function name : set_elf_house
 * Description   : adds descr of basic elf house parts
 */
void set_elf_house()
{
    set_elf_floor(floor);
    set_elf_walls(walls);
    set_elf_ceiling(ceiling);
    set_elf_windows(windows);
    set_elf_colors();
}

/*
 * Function name : set_elf_great_rm
 * Description   : adds descr of central room of elf house
 */
void set_elf_great_rm()
{
    add_item(({"room", "great room"}),
        "This is a large room built to resemble the outdoors. The room " +
        "is sparsely furnished with a few pieces of furniture. " +
        "One area of the room has been set aside where food is prepared.\n");
}

/*
 * Function name : set_elf_mats
 * Description   : adds descr of mats that elves sit on
 */
void set_elf_mats()
{
    add_item(({"mats", "thick mats"}),
        "They are round and thick. The mats are used in place of chairs " +
        "and beds. They look comfortable and are overstuffed.\n");
}

/*
 * Function name : set_elf_table
 * Description   : adds descr of elf dinner tables
 */
void set_elf_table()
{
    add_item(({"table"}),
        "The is rectangular shaped. It sits low to the ground and looks " +
        "large enough to sit several elves. Instead of chairs, thick " +
        "mats are set around the table.\n");
    set_elf_mats();
}

/*
 * Function name : set_elf_small_tables
 * Description   : adds descr of small tables
 */
void set_elf_small_tables()
{
    add_item(({"tables", "small tables", "end tables"}),
        "The end tables are small and set low to the ground. They are round and square and set next to a mat. They are plain looking and made from wood.\n");
}


/*
 * Function name : set_elf_kitchen
 * Description   : adds descr of elf kitchens
 */
void set_elf_kitchen()
{
    add_item(({"kitchen"}),
        "This is an area of the house where elves prepare food. The kitchen " +
        "is simple with a counter and a pantry.\n");
    add_item(({"counter"}),
        "The counter is small and made of wood. It fills one corner " +
        "of the room and used to prepare food. Next to it is a pantry.\n");
    add_item(({"pantry"}),
        "It is a small wooden closet in the kitchen area. The pantry is " +
        "tall and plain looking. It has doors that open up. Inside it " +
        "are several shelves used to store food, tableware, linens, " +
        "crockery, and other items used for meals.\n");
    add_item(({"linens"}),
        "Stacked on the shelves neatly are napkins and tablecloths. They " +
        "are freshly pressed and neatly folded.\n");
    add_item(({"crockery"}),
        "It is ceramic tableware stacked neatly in the pantry. There " +
        "are plates, bowls, mugs, serving platters, and other items. " +
        "They are made from ceramic and are earth colored.\n");
    add_item(({"platters", "serving platters"}),
        "These are large oval shaped plates. They are used to serve " +
        "food during meals.\n");
    add_item(({"plates", "dinner plates", "salad plates"}),
        "They are stacked neatly on shelves in the pantry. The plates " +
        "are round and different sizes, and used during meals.\n");
    add_item(({"bowls", "bowl"}),
        "It's a round vessel used for holding fruit or liquids or for " +
        "serving food. The bowls are different sizes and stacked neatly " +
        "in the pantry.\n");
    add_item(({"mugs", "cups"}),
        "They are stacked neatly in the pantry and are different sizes. " +
        "The mugs and cups are sturdily build and used to hold drinks.\n");
    add_item(({"tablecloth"}),
        "They are pieces of cloth that are spread over tables. The " +
        "tablecloths are large and expertly woven. Each one is neatly " +
        "folded and stacked in the pantry.\n");
    add_item(({"napkins"}),
        "These are small, square pieces of fabric used at tables. They " +
        "are folded and neatly stacked in the pantry.\n");
    add_item(({"silverware"}),
        "These are utensils used for eating and preparing food. Stacked " +
        "neatly in the pantry are knives, forks, spoons.\n");
    add_item(({"forks", "fork"}),
        "These implements with a handle on one end and long tines on " +
        "the other. They are used for both eating and serving food.\n");
    add_item(({"spoons", "spoon"}),
        "These are pieces of cutlery with a shallow bowl-shaped container " +
        "and a handle. They are used for serving food and eating.\n");
    add_item(({"knife", "knives"}),
        "These are sharp-edged instruments used for cutting, peeling, " +
        "slicing, spreading food.\n");
    add_item(({"shelves"}),
        "They are wide and set in the pantry. They are made of wood " +
        "and full of things used for meals and food preparation.\n");
    add_item(({"doors", "folding doors"}),
        "They are doors that open and close on the pantry. The doors " +
        "are open and show off what is inside the pantry.\n");
}

/*
 * Function name : set_reverie_room
 * Description   : adds descr of reverie room
 */
void set_reverie_room()
{
    add_item(({"room", "reverie room"}),
        "This is a peaceful room where a calmness seems to rest here. " +
        "This is where elves come to refresh their minds and relax " +
        "from the cares of their world.\n");
    add_item(({"candles", "small candles"}),
        "The candles are an off white color. They are lit and the flames " +
        "dance about. They fill the room with a gentle honey fragrance.\n");
}

/*
 * Function name : set_add_stairs_up
 * Description   : adds descr of stairs on lower floor
 */
void set_add_stairs_up()
{
    add_item(({"staircase", "stairs", "stairway"}),
           "They follow the wall and lead upstairs through a hole in " +
           "the ceiling.\n");
}

/*
 * Function name : set_add_stairs_dn
 * Description   : adds descr of stairs on upper floor
 */
void set_add_stairs_dn()
{
    add_item(({"stairs", "staircase", "stairway"}),
        "The staircase is set in the back of the room. They descend " +
        "through a hole in the floor to the level below.\n");
}

/*-----------------------------------------------------------------------------
 * Farm definitions
 *----------------------------------------------------------------------------*/
 /*
  * Function name : 
  * Description   : adds descr of 
  */
 void set_farmyard()
 {
    
 }
 