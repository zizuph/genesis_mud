/*
 *  /d/Emerald/telberin/magic/mage_guild2.c
 *
 *  This is the second level of the base of the tower, to which the
 *  general public is granted access. Here, the Common Enchantments
 *  and spells of the art form are accessible in a large tome.
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <stdproperties.h>
#include <macros.h>


/* prototypes */
public void        create_emerald_room();

public void        reset_room();

/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("a small library in the Mage Guild of Telberin");
    set_long("This small room is cramped and crowded with shelves and"
           + " charts which hang on the walls. A few tables provide"
           + " areas for study, and a wooden podium supports a very"
           + " large book near the eastern end of the room. An"
           + " opening to the west leads towards some stairs.\n");

    add_item( ({ "floor", "ground", "down" }),
        "The floor of this room is rather dusty, obscuring the"
      + " otherwise fine polish of the stone.\n");
    add_item( ({ "stone", "slab", "slabs", "slab of stone",
                 "slabs of stone", "smooth stone", "polished stone",
                 "smooth and polished stone",
                 "slab of smooth and polished stone",
                 "slabs of smooth and polished stone" }),
        "This room, like the other parts of the guild, is constructed"
      + " of slabs of smooth polished stone.\n");
    add_item( ({ "dust" }),
        "The floor here doesn't appear to get a lot of attention"
      + " from cleaning personnel.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling of this room is high above your head.\n");
    add_item( ({ "wall", "walls" }),
        "The walls of this room are tall, almost more so than seems"
      + " necessary. The effect is to create a spacious and peaceful"
      + " feeling in the room, filling it with light and room to"
      + " think.\n");
    add_item( ({ "room", "here", "chamber", "library", "small room",
                 "area" }),
        "The fact that this room is available to the common public"
      + " suggests that the information contained here is not of"
      + " a sensitive, or particularly dangerous nature. However,"
      + " the Mage Guild has always prided itself on its policy of"
      + " providing accurate and up-to-date information on Magic"
      + " and enchantment to any who would learn. The tables and"
      + " books here suggest that this is a library for study.\n");
    add_item( ({ "shelf", "shelves", "book shelf", "book shelves",
                 "bookshelf", "bookshelves" }),
        "There are shelves filled with books along most of the"
      + " walls in this room. They run clear up to the ceiling in"
      + " height, making it seem doubtful that one could reach"
      + " the uppermost titles without some sort of assistance.\n");
    add_item( ({ "uppermost titles" }),
        "The books at the top of the shelves seem quite out of"
      + " your reach.\n");
    add_item( ({ "chart", "charts" }),
        "Between the bookshelves, the walls are covered here and"
      + " there with charts which contain arcane symbols and"
      + " graphs.\n");
    add_item( ({ "symbol", "symbols", "graph", "graphs",
                 "arcane symbol", "arcane symbols",
                 "arcane graph", "arcane graphs",
                 "arcane symbols and graphs",
                 "symbols and graphs" }),
        "They are unfamiliar to you.\n");
    add_item( ({ "books", "title", "titles" }),
        "There must be over a thousand different titles in this"
      + " room. The subjects seem to be oriented mainly to the"
      + " magic arts, and include many references to light,"
      + " resonance, convergence, suspension, and other such"
      + " things.\n");
    add_item( ({ "table", "tables" }),
        "A few tables have been placed around the room, evidently"
      + " for those who wish to study the books contained within.\n");
    add_item( ({ "podium", "wooden podium" }),
        "The podium is positioned against the eastern wall, and"
      + " supports a very large book.\n");
    add_item( ({ "opening", "west", "west wall", "western wall",
                 "wall to the west" }),
        "The wall to the west opens on to a staircase which leads"
      + " down to the main hall in that direction.\n");
    add_item( ({ "stair", "stairs", "stairway", "staircase" }),
        "To the west, stairs descend into the main entrance to"
      + " the tower.\n");
    add_item( ({ "hall", "main hall", "entrance", "main entrance" }),
        "The main entrance lies to the west. Little can be viewed"
      + " of it from here.\n");
    add_item( ({ "tower", "guild", "mage guild",
                 "mage guild of telberin" }),
        "The greater areas of the guild lie above, in the upper"
      + " levels of the tower.\n");
    add_item( ({ "upper levels", "upper level",
                 "upper levels of the tower" }),
        "They are unreachable from here.\n");
    add_item( ({ "east", "eastern wall", "east wall",
                 "wall to the east" }),
        "A podium rests against the eastern wall, supporting a"
      + " very large book. Beside the book, a small window"
      + " overlooks the southern parts of the city.\n");
    add_item( ({ "window", "small window" }),
        "The window looks out over the souther parts of the"
      + " city of Telberin. A slight breeze comes in through its"
      + " opening to ventilate the room.\n");
    add_item( ({ "breeze", "slight breeze" }),
        "The breeze keeps this room from feeling too close and"
      + " stuffy.\n");
    add_item( ({ "view", "city", "city of telberin", "telberin" }),
        "The city looks quite lovely from this height.\n");
    add_item( ({ "outside", "sky" }),
        "The sky is bright and peaceful, peering in through the"
      + " window in the east wall.\n");
    add_item( ({ "chair", "chairs" }),
        "A few chairs have been placed around each of the tables,"
      + " and provide a place to sit and read.\n");

    add_cmd_item( ({ "chair", "chairs", "table", "tables" }),
                  ({ "sit" }),
        "You sit down briefly at one of the tables. A certain"
      + " peacefulness sets into you as you look at all the books"
      + " on the shelves. After a bit, you stand up again.\n");
    add_cmd_item( ({ "books", "title", "titles" }),
                  ({ "read", "study", "get", "take" }),
        "You browse through a few of the titles on the shelves"
      + " and take and sit with them at a nearby table. After"
      + " a short while, you realize that this knowledge is very"
      + " foreign to you, and beyond your comprehension. You"
      + " rise and return the books to their places on the"
      + " shelves.\n");


    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Emerald/telberin/magic/mage_guild1", "west" );
    add_exit("/d/Emerald/telberin/magic/mage_guild1", "down", 0, 1, 1);

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        reset_room
 * Description  :        clone the magic tome into the room
 */
public void
reset_room()
{
    object book;

    if (!present("_telberin_enchantment_tome"))
    {
        book =
            clone_object(
              "/d/Emerald/telberin/magic/obj/magic_tome")->move(
                this_object());
    }

} /* reset_room */
