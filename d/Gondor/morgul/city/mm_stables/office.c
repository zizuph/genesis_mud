/*
 *  /d/Gondor/morgul/city/mm_stables/office.c
 *
 *  The office of the Stable Master of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "mm_stables.h"

void 		add_items();
int		check_steeds();
object		stable_master = MM_STABLE_MASTER;

string
text_on_poster =
    "\t --------------------------------------------------------------- \n" +
    "\t| o                                                           o |\n" +
    "\t|     T H E   S T A B L E S   O F   M I N A S   M O R G U L     |\n" +
    "\t|     -----------------------------------------------------     |\n" +
    "\t|                                                               |\n" +
    "\t|     Welcome to the Stables of Minas Morgul.                   |\n" +
    "\t|                                                               |\n" +
    "\t|     A fee <pay fee> ................................. 50 pc   |\n" +
    "\t|     A steed <borrow steed/horse> ....................  2 pc   |\n" +
    "\t|     A bag of oats <buy oats> ........................ 50 cc   |\n" +
//    "\t|     A saddlebag <buy saddlebag> .....................  2 gc   |\n" +
    "\t|                                                               |\n" +
    "\t|     <stable horse/steed> ............................ free    |\n" +
    "\t|                                                               |\n" +
    "\t|     For the present only the member of the Society can pay    |\n" +
    "\t|     the fee and use the steeds.                               |\n" +
    "\t|                                                               |\n" +
    "\t|                                  Morhoon, the Stable Master   |\n" +
    "\t| o                                                           o |\n" +
    "\t --------------------------------------------------------------- \n";

void
create_room()
{
    ::create_room();
    
    set_short("Inside the office of the Stable Master of Minas Morgul");
    set_long("You are in the office of the Stable Master of Minas Morgul. " +
             "Save for a desk at which the Stable Master is currently " +
             "seated, this big, open room looks more like a barn or a " +
             "workshop than an office. You see saddles, saddlebags, riding " +
             "boots and other paraphernalia orderly stored in a huge rack, " +
             "which takes up most of the north wall. A corridor broad " +
             "enough to qualify as a bridle path opens up to the south. " +
             "A large poster has been placed on the northern wall.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit("court.c", "west", 0, 0, 0);
    add_exit("steeds.c", "south", check_steeds, 0, 0);

    add_item(({"poster", "large poster"}), text_on_poster);
    
    add_items();
}

void
add_items()
{
    object rack;
    
    clone_object(MM_STABLE_MASTER)->move(TO);
    (rack = clone_object(MM_STABLES_OBJ_DIR + "rack.c"))->move(TO);
    clone_object(MM_STABLES_OBJ_DIR + "saddle.c")->move(rack);
    clone_object(MM_STABLES_OBJ_DIR + "saddle.c")->move(rack);
    clone_object(MM_STABLES_OBJ_DIR + "boots.c")->move(rack);
    clone_object(MM_STABLES_OBJ_DIR + "saddlebag.c")->move(rack);
}

int
check_steeds()
{
    if (TP->query_wiz_level() || TP->query_name() == "Morhoon" ||
        TP->query_name() == "Horse")
    {
        return 0;
    }
    write("You do not have any business there, do you?\n");
    return 1;
}

int
read_poster(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "[a] [the] [large] 'poster' [on] [the] [northern] [wall]"))
    {
        notify_fail("Read what?\n");
        return 0;
    }
    write(text_on_poster);
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(read_poster, "read");
}
