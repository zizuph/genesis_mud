/*
 * Practice Room for the Academy of Elemental Arts in Gelan
 * 
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <macros.h>
#include "defs.h"

inherit SCHOOL_ROOM_BASE;

// Global Variables
object taskmaster;

public void
create_school_room()
{
    set_short("Taskmaster's Office");
    set_long("This is the office of the Taskmaster of the Academy of "
        + "Elemental Arts. The Taskmaster is in charge of overseeing "
        + "and aiding the progress of the students who study here. You "
        + "find yourself in a cozy room with a small window in the northern "
        + "wall, a bookshelf covering the western wall, and various trinkets "
        + "adorning the southern wall. A large desk and a small chair "
        + "occupy the middle of the room.\n\n");
    
    try_item( ({ "walls" }),
        "The walls in this room are made of grey stone. The northern one has "
      + "a small window while the west one has a bookshelf fastened to it. "
      + "Along the southern wall is housed a few shelves with some "
      + "trinkets.\n");
      
    try_item( ({ "northern wall", "small window", "window", 
                 "small square window", "north wall" }),
        "A small square window with clear crystalline glass allows the "
      + "Taskmaster to glance out over the practice yard and see the "
      + "student activities there.\n" );
    
    try_item( ({ "clear glass", "glass", "crystalline", "crystalline glass",
                "clear crystalline glass" }),
        "You recognize the material as a unique crystalline glass. It is "
      + "said that only someone trained by Caliana could have wrought this.");
    
    try_item( ({ "bookshelf", "west wall", "small bookshelf", "western wall",
                 "shelf", "shelves", "bookshelves" }),
        "A small bookshelf has been placed along the western wall. There are "
      + "a few books of arcane lore that sit upon it.\n");
    
    try_item( ({ "books", "arcane lore" }),
        "You make out titles such as 'Crystalline Glass - The Art', "
      + "'Lightning Bolt - The Classic Version', and 'Gone With the Wind in 60 "
      + "Seconds - Who and Why'. Obviously whoever reads these books takes "
      + "a broad approach to the arcane arts.\n");
      
    try_item( ({ "large desk", "desk" }),
        "The desk is made of ornately carved dark wood. It is relatively clear "
      + "of clutter. Whoever uses this desk seems to be rather organized.\n");
    
    try_item( ({ "small chair", "chair" }),
        "This chair is almost too small for the large desk in front of it.\n");
    
    try_item( ({ "trinket", "trinkets", "southern wall", "south wall" }),
        "Most of the trinkets adorning the southern wall are just knickknacks "
      + "faraway places in the realms. You notice a small green ring, a "
      + "celtic cross, a statue, a small disc, and a large glass case.\n");
    
    try_item( ({ "large glass case", "glass case", "case", "large case" }),
        "The most impressive item in this room is a large glass case "
      + "housing a slender greatsword. Amazingly, the case hangs from the "
      + "wall, fastened with iron bolts to secure it in place.\n");
    
    try_item( ({ "small green ring", "green ring", "small ring", "ring" }),
        "This is a small emerald green ring with the picture of a dragon. "
      + "You can make out an engraving, 'To Amjal with love, Thera.'\n");
    
    try_item( ({ "cross", "celtic cross", "red rubies", "four points", "points" }),
        "This beautifully crafted cross is cast in black iron and comes from "
      + "the Kirk of Port Macdunn. The ring is adorned with red rubies "
      + "inlaid at each of the four points.\n");
    
    try_item( ({ "statue", "miniature dragon statue", "dragon statue",
                "miniature statue", "dragon", "krynnish dragon", "cliff" }),
        "The miniature dragon statue depicts a fierce Krynnish dragon "
      + "standing on top of a cliff, roaring to the skies.\n");
    
    try_item( ({ "disc", "small disc", "white pentacle", "pentacle" }),
        "A small disc made of deep black onyx hangs upon the wall. A "
      + "shimmering white pentacle is inlaid upon the stone. Along "
      + "the edges, golden letters read: May the Five bless your "
      + "efforts.\n");
    
    try_item( ({ "greatsword", "slender greatsword", "hilt", "glass hilt",
                 "silvery mithril", "mithril" }),
        "Set within the glass case, this is a marvelously crafted slender "
      + "greatsword. It is made from a single thin line of silvery mithril "
      + "with a crystalline glass hilt. The silvery mithril seems to "
      + "radiate, sending slow pulsating slashes of silvery light through "
      + "the blade. A black diamond is set into the bottom of the hilt.\n");
    
    add_exit(ACADEMIC_SCHOOL + "lounge", "east");
    
    set_alarm(0.0, 0.0, reset_room);
}

public void
reset_room()
{
    // Ensure that the taskmaster is always present
    if (!objectp(taskmaster))
    {
        setuid();
        seteuid(getuid());
        taskmaster = clone_object(ACADEMIC_TASKMASTER);
        taskmaster->move(this_object());
        taskmaster->arm_me();        
    }
}

public void
init()
{
    ::init();
    add_action("read_cmd", "read");
}

/*
 * function name:        read_cmd
 * description  :        sets up the read command for the sign.
 * returns      :        the room description
 */
public int
read_cmd(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    switch (lower_case(arg))
    {
    case "crystalline glass - the art":
    case "lightning bolt - the classic version":
    case "gone with the wind in 60 seconds - who and why":
    case "books":
        tell_room(environment(taskmaster), QCTNAME(this_player())
            + " tries to read the books on the bookshelf.\n", ({ this_player() }));
        write("You approach the bookshelf to try and read a book.\n");
        taskmaster->command("say Stay away from those books if you know "
            + "what's good for you.");
        taskmaster->command("emote looks really annoyed.");
        return 1;
    }
    
    return 0;
}
