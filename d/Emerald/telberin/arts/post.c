/*
 *  /d/Emerald/telberin/arts/post.c
 * 
 *  This is the Post Office of Telberin in Emerald.
 *
 *  Created by ??
 *
 *  Modified by Shiva and Gorboth (c) April 2003
 */
#pragma strict_types
#include "../defs.h"

inherit TELBERIN_BUILDING;
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
 
/*
 * Function name:        create_telberin_building
 * Description  :        set up the room with special
 *                       building functionality
 */
public void
create_telberin_building()
{
    set_short("Royal Post Office of Telberin");
    set_em_long("This large building has as its one purpose"
      + " to sort and deliver all of the mail that comes and"
      + " goes from the city of Telberin. Despite the large"
      + " amount of activity and bustle, the elves here go"
      + " about their business with dignity and calm reserve."
      + " The building itself is huge and beautiful, with"
      + " large columns rising to support a tall muraled"
      + " ceiling high above. " + get_std_use());

    add_item( ({ "elves", "elf" }),
        "Many elves work within this building to meet the"
      + " demands of mail delivery in such a large city."
      + " Though they work quickly, they do so with an air"
      + " of peace and serenity. You do not sense frustration"
      + " or hectic pace within these walls.\n");
    add_item( ({ "head postmaster", "postmaster" }),
        "He's supervising his employees, making sure " +
        "that all is accounted for.\n");
    add_item( ({ "here", "large building", "building",
                 "post", "post office", "room", "area" }),
        long());
    add_item( ({ "column", "columns", "large column",
                 "large columns" }),
        "The columns are of white marble, rising high above to"
      + " support the ceiling.\n");
    add_item( ({ "ceiling", "up", "above", "roof",
                 "mural", "muraled ceiling", "muraled roof" }),
        "A beautiful mural has been painted on the ceiling of"
      + " this building. It depicts a beautiful city of"
      + " dazzling light.\n");
    add_item( ({ "city", "beautiful city" }),
        "The city in the mural bears some reseblance to"
      + " modern Telberin, if only in its themes. This is"
      + " perhaps a rendering of the city in its former glory"
      + " in some age long past.\n");
    add_item( ({ "activity", "bustle", "work", "mail" }),
        "The elves here are all hard at work. There is much to"
      + " be done to get the mail delivered on time.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the post office.");

    add_exit("/d/Emerald/telberin/cantors_way06", "south", 0, 1, 1);
} /* create_telberin_building */
 
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public mixed
query_location_ids()
{
    return "[the] [well] [well-framed] [framed] [elegant]"
         + " 'building' / 'post' / 'postal' [office]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "It's a post office building.\n";
}


public string
query_entry_desc()
{
    return "into the post office";
}

