/* /d/Terel/mountains/ghastly_keep/ghastly_keep/rooms/gkeep8.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

#include "defs.h";

inherit GKEEP_STD_ROOM;

#include <macros.h>

int do_search(string str);
int find_key;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("End of a long hallway");
    set_long("You have reached the end of a long hallway. Huge piles of "
             + "bones are scattered around the room. Small bones covered "
             + "in dead insects are piled in the corners of the "
             + "room. There are old traps that appear to have been triggered "
             + "by unsuspecting adventurers. Skeletal remains, some turning to "
             + "dust from the passage of time, are strewn about the floor. "
             + "There is only one path out of this hall which passes by ancient "
             + "cages holding skeletal remains of various animals. Next to "
             + "the cages are some odd machines.\n"); 

    add_item( ({"bone", "bones", "pile", "piles of bones", "piles"}), 
               "The remains of those foolish enough to venture in this keep. "
               + "It might be possible to dig through the heaps of bones, in "
               + "search for lost artifacts.\n");

    add_item( ({"insects", "insect", "dead insects"}), "Smelly heaps "
               + "of dead insects can be found all around this room.\n");

    add_item( ({"remains", "remain", "skeleton", "animals"}), "Nothing "
               + "but bones are left.\n");

    add_item( ({"skeletal remains", "skeletal remain"}), "Nothing "
               + "but bones are left.\n");

    add_item( ({"corner", "corners"}), "The corner is covered in small bones, "
               + "crawling, and dead insects.\n");

    add_item( ({"cages", "cage"}), "The cages hold skeletal remains of "
               + "various animals.\n");

    add_item( ({"hall", "halls"}), "The once great hall is only a mere shadow "
               + "of its former self, ravaged by the passage of time.\n");

    add_item( ({"end", "hallway", "path"}), "You have reached the end of the "
               + "hallway. The only visible exit is where you came "
               + "from.\n");

    add_item( ({"trap", "traps"}), "All the traps seems to have sprung.\n");

    add_item( ({ "machines", "machine", "odd machine", "odd machines" }), 
               "Looking at the machines it is hard to make sense of their "
               + "purpose. They are oddly untouched by the passage of time "
               + "in comparison to the rest of the room.\n");

    add_cmd_item( ({ "machines", "machine" } ), 
                 ({"use", "try"}), "Fiddling with the machines in an attempt "
                  + "to determine their purpose, you are left even more "
                  + "confused then before.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_exit(GKEEP + "gkeep12",     "southwest");

    add_npc(GKEEP_NPC + "g_sentry",   random(3));
    add_npc(GKEEP_NPC + "g_sentinel", random(3));
    add_npc(GKEEP_NPC + "g_ghost",    random(3));

    add_prop(ROOM_I_INSIDE,  1);
    add_prop(ROOM_I_LIGHT,  -1);

    find_key = 0;

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    find_key = 0;
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() {
    ::init();
    add_action(do_search, "dig");
    add_action(do_search, "search");
}


/*
 * Function name: do_search()
 * Description  : Searching for the key
 */
int do_search(string str)
{
    if (!strlen(str))
    {
        notify_fail("Dig what?\n");
        return 0;
    }

    notify_fail("Try digging through bones instead?\n");
    if (!parse_command(str, ({ }),
        "[through] [the] [in] / [into] " +
        "'bone' / 'bones' / 'piles' / 'pile'"))
        return 0; 

    if(!find_key)
    {
        find_key = 1;

        write("You locate something among the pile of bones.\n");
        say(QCTNAME(TP) + " locates something among the pile of bones.\n");

        clone_object(GKEEP_OBJ + "g_key")->move(TP);
    
        return 1;
    }

    write("You search through the piles of bones, but find nothing.\n");
    say(QCTNAME(TP) + " searches through the piles of bones, but "
                     + "finds nothing.\n");
    return 1;
}