/*
 * big_hole.c underground room in the Big Rock Pub
 * Coded by Shinto 101399
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <ss_types.h>

#define BASE CALATHIN_DIR + "pubs/big_base"

public string*
query_object_list()
{
    return ({CALATHIN_DIR + "npc/sliver"});
}


public void
create_room()
{
    set_short("a room below the Big Rock Pub");
    set_long("The room has been dug out of the ground. There's a bed "+
                   "against the south wall and a desk against the east. "+
                   "The room seems to be used as a hideout. A torch lights "+
                   "the room from above the desk. The hole you entered from "+
                   "above is visible.\n");
    add_item("bed","The bed is small with just a single pillow, several "+
                    "sheets, and a blanket.\n");
    add_item("torch","A single torch sits fixed to the wall, lighting the "+
                    "room.\n");
    add_item("desk","The desk is small and made of pine wood.\n");
    add_item("hole","@@hole");

    add_cmd_item(({"barrel", "on barrel"}), "knock", "@@knock");
    reset_room();

}

string
hole()
{
    if(find_object(BASE)->query_hole())
    {
        return "You can see into the basement above. The hole is not blocked.\n";
    }
    return "The hole is covered and blocked by a barrel.\n";
}

int
knock()
{
    if(find_object(BASE)->query_hole())
    {
        write("The barrel isn't blocking the hole. You can't knock on it.\n");
        return 1;
    }

    write("You knock on the barrel above.\n");
    say(QCTNAME(TP) +" knocks on the barrel above.\n");
    tell_room(BASE, "You hear a knocking coming from the barrels.\n");
    return 1;
}
