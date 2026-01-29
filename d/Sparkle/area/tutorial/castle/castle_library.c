/*
 *  /d/Sparkle/area/tutorial/castle/library.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created August 2019, by Arman
 */
#pragma strict_types
#include "/d/Sparkle/area/tutorial/defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();

/* definitions */
#define  TUTORIAL_CHAPTER    20  /* the chapter for the sign */
#define  LECTERN (OBJ_DIR + "library_lectern")

object lectern;

/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("in an old library within the castle");
    set_long("You stand within the castle's library. Bookshelves "
      + "line the long walls here, with the skeletal remains of "
      + "book covers all that remain of a once impressive " 
      + "collection of tomes. Cobwebs and dust cover everything. "
      + "This room looks rarely visited and clearly has been "
      + "forsaken.\n\n");

    add_item( ({ "library", "castle's library", "room" }),
        "You stand in the middle of the castle's forsaken library. "
      + "It has clearly not been visited for many years, as the "
      + "books on the shelves have mostly decayed away.\n");
    add_item( ({ "bookshelves", "shelves", "shelf", "walls",
        "long walls", "bookshelf" }),
        "Lining the walls of the library are bookshelves, filled "
      + "with the decrepit remains of old books and tomes.\n");
    add_item( ({ "book covers", "books", "covers", "remains",
        "skeletal remains", "tomes", "tome", "book" }),
        "A once impressive collection of books and tomes have "
      + "long since suffered the fate of time, having decayed "
      + "away to little more than the skeletal remains of their "
      + "covers.\n");
    add_item( ({ "dust", "cobwebs" }),
        "Long forsaken, this library is thick with dust and "
      + "cobwebs.\n");
    add_item( ({ "hallway", "west" }),
        "The library exits into a hallway to the west, where a sense"
      + " of dread emanates.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_4", "west");


    reset_room();
} /* create_castle_room */

/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void 
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    if(!objectp(lectern))
    {
        lectern = clone_object(LECTERN);
        lectern->move(this_object(), 1);
    }
} /* reset_room */

/*    Proposed tutorial sign

                                     _____
                                    |     |`.
 ___________________________________|_____|_|_______________________________
|                                                                           `.
| Genesis Tutorial Chapter xx: Magic and Spellcasting                       | |
|                                                                           | |
| Genesis is a world of magic, where the curious adventurer may come across | |
| tomes of long-lost spells, the studious can learn magic from master       | |
| sorcerers or dark necromancers, the devout can gain the blessings from    | |
| Elemental Lords, and the damned be granted black powers from demonic      | |
| creatures from Beyond!                                                    | |
|                                                                           | |
| Upon obtaining a magical tome or learning a spell, as aspiring caster     | |
| needs a minimum level of training in the magical arts - such as           | |
| spellcraft - and may also need to gather components for their spell such  | |
| as herbs that are consumed in the casting.                                | |
|                                                                           | |
| To call upon a spell in one's 'spell' list, one must 'cast <spellname>'.  | |
|                                                                           | |
| Casting a spell drains your mana, a mental pool dependent on your         | |
| intelligence. Mana replenishes over time depending on your wisdom and     | |
| your spellcraft skill.                                                    | |
|                                                                           | |
| The path of a Magi can be challenging, and it is not for everyone,        | |
| however the benefits spells provide can be considerable!                  | |
|___________________________________________________________________________| |
`.__________________________________________________________________________`.|
                                    |     | |
                                    |     | |

*/
