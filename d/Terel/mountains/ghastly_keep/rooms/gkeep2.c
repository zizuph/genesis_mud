/* /d/Terel/mountain/ghastly_keep/rooms/gkeep2.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  28/04-17                   Fixed typos                             Znagsnuf
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h";
#include "/d/Terel/include/herb_arrs.h"

inherit "/d/Terel/std/herbsearch.c";

inherit GKEEP_STD_ROOM;

int do_slide(string str);
string dif_smell();

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Beneath the castle ruins");

    set_long("A long narrow passage has lead between the sharp stones to "
            + "arrived here under the castle ruins. There is a dreadful smell "
            + "coming from somewhere within the immense empty hall. The "
            + "passage between the sharp rocks is still clearly visible in "
            + "the ceiling. Cobwebs hang in every corner. Cold water from the "
            + "melting snow drips in a seemingly endless rhythm to continuously "
            + "feed the mildew growing around the room. There is a sense of "
            + "foreboding that causes the air to feel more chilled than "
            + "what would seem natural.\n");

    add_item( ({"stone", "ceiling", "hole", "stones", "sharp stones"}), "You "
            + "see a small opening between the sharp stones in the "
            + "ceiling.\n"
            + "You might be able to climb out of the opening.\n");

    add_item( ({"cobwebs", "cobweb", "dust"}), "How long the burdened "
               + "cobwebs could withstand the beckoning call of gravity, "
               + "nobody knows.\n");

    add_item( ({"water", "snow", "opening"}), "A seamlessly endless stream of "
               + "cold melting water from the snow above seeps through "
               + "the small opening in the ceiling to nurse the growing "
               + "mildew of the wall.\n");

    add_item( ({"passage", "passages"}), "There are passages to the east "
               + "and the west leading deeper into the ruins of the castle. "
               + "There is a small hole on the ceiling leading out of the "
               + "ruins back the way you came.\n");

    add_item( ({"mildew", "fungus"}), "The smell of mildew and fungus "
               + "makes you cover your mouth and nose. it is unbearable.\n");

    add_item( ({"wall", "walls"}), "The wall and ceiling are completely "
               + "covered with mildew and fungus.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_exit(GKEEP + "gkeep3",   "east", "@@cobwebs@@");
    add_exit(GKEEP + "gkeep4",   "west", "@@cobwebs@@");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE,         1);

    add_npc(GKEEP_NPC + "g_spider",  1);

    // Add herbs to the fungus.
    set_up_herbs( ({ONE_OF_LIST(DARK_HERBS)} ),
                 ( { "mildew", "fungus", "here"} ), 4);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    //update_longdesc();
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();
    add_action(do_slide, "enter");
    add_action(do_slide, "climb");
    add_action(dif_smell, "smell");
}

/*
 * Function name: do_slide()
 * Description  : Transport the player to the next room.
 */
int do_slide(string str)
{
    string text;

    if (!strlen(str))
    {
        if(query_verb() == "climb")
            text = " into";
        else
            text = "";

        notify_fail(CAP(query_verb() + text + " the hole in the ceiling?\n"));
        return 0;
    }

    notify_fail("Are you trying to " + query_verb() + " the hole in the "
               + "ceiling?\n");
    if (!parse_command(str, ({ }),
        "[myself] [up] [in] / [into] [between] [out] [the] " +
        "'hole' / 'ceiling' / 'opening'"))
        return 0;    

    write("You climb out of the narrow hole in the ceiling.\n");
    say(QCTNAME(TP) + " climbs out of the narrow hole in the ceiling.\n");
    
    // Send a notification to the next room.
    tell_room(GKEEP + "gkeep1", QCTNAME(TP) + " arrives from a hole between "
             + "the stones.\n");

    TP->move_living("M", GKEEP + "gkeep1",1,0);
    
    return 1;
}

/*
 * Function name: Cobwebs()
 * Description  : Displays a simple message.
 */
cobwebs()
{
    write("\nCobwebs brush gently on your face as you pass through it.\n\n");
    return 0;
}

public string
dif_smell()
{

    switch (random(4))
    {
    case 0:
        write("The smell of fungus and mildew is unbearable, making you "
             + "cover your mouth and nose.\n");
        break;
    case 1:
        write("The stench of fungus and mildew is repellent.\n");
        break;
    case 2:
        write("The odor of fungus and mildew is brain-numbingly foul.\n");
        break;
    case 3:
        write("The moldy smell of fungus and mildew is stomach churning.\n");
        break;    
    }
    
    return "";
}