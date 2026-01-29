/*
 * /d/Emerald/telberin/arts/cmasters_chambers.c
 *
 * This is the study chamber of the Choir Master of Telberin. Though the
 * Music Archives are officially located within the Minstrel Guild,
 * their contents largely reside here, scattered in unsorted piles which
 * fill the corners of this already cluttered workspace. It lies north
 * of Cantor's Plaza in the Arts Quarter of Telberin.
 *
 * Copyright (c) May 2000, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/std/room";

#include <stdproperties.h>
#include <macros.h>


/* prototypes */
public void    create_emerald_room();
public string  exa_desk();
public void    reset_room();
public int     sit_desk(string arg);
public void    init();


/* global variables */
public object    Choir_Master;


/*
 * Function name:        create_emerald_room
 * Descripiton  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("a cluttered office");
    set_em_long("A cluttered office. Tall piles of all sorts of"
        + " paper and parchment fill this small room, nearly obscuring"
        + " the view of a desk which rests near the back wall."
        + " Though a window in the west wall allows some light into"
        + " this chamber, there is so much dust hanging in the air"
        + " that the illumination only helps make the room look"
        + " slightly less dim.\n");

    add_item( ({ "office", "here", "room", "this room", "chamber",
                 "small room", "small chamber", "this chamber" }),
        this_object()->long() );
    add_item( ({ "clutter", "pile", "piles", "tall pile", "tall piles",
                 "pile of paper", "mess", "piles of paper",
                 "tall pile of paper", "tall piles of paper" }),
        "Paper and parchment have been stacked in tall piles all over"
        + " this room. It is difficult to find a place to step for"
        + " fear of overturning what appears to be a very delicate"
        + " dance with gravity in the case of most of the clutter.\n");
    add_item( ({ "paper", "parchment", "papers", "parchments" }),
          "The paper and parchment all have writing on them. In some"
        + " cases the writing is lettering, but mostly it seems to"
        + " be musical notation.\n");
    add_item( ({ "writing", "letter", "letters", "lettering" }),
          "The writing is written in such a spidery scrawl as to"
        + " make it all but illegible to anyone but the author, who"
        + " would also most likely have a very difficult time"
        + " managing an interpretation.\n");
    add_item( ({ "music", "music notation", "notation",
                 "musical notation" }),
          "Unlike the writing, the music notation is very beautiful,"
        + " and has been written with care. You are in fact gazing"
        + " at a good portion of the contents of the Music Archives"
        + " of the Minstrel's Guild.\n");
    add_item( ({ "desk" }),
          VBFC("exa_desk") );
    add_item( ({ "wall", "walls" }),
          "The chamber has four walls which surround you on all"
        + " sides.\n");
    add_item( ({ "north wall", "northern wall", "back wall" }),
          "The back wall is obscured by the tall piles of clutter,"
        + " except where a desk rests against its surface.\n");
    add_item( ({ "west wall", "western wall", "west" }),
          "The western wall contains a small window, which serves as"
        + " the only source of light in this otherwise very dim"
        + " chamber.\n");
    add_item( ({ "south wall", "southern wall", "south" }),
          "A door leads through the south wall out onto Cantor's"
        + " Plaza.\n");
    add_item( ({ "east wall", "eastern wall", "east" }),
          "The eastern wall is unadorned except for a tiny framed"
        + " diploma which hangs just to the right of the desk.\n");
    add_item( ({ "diploma", "tiny diploma", "framed diploma",
                 "tiny framed diploma" }),
          "The diploma reads as follows: 'Presented to Feni Arlal in"
        + " recognition of his meritorious service and accomplishments"
        + " in the Minstrel Guild of Telberin is this diploma, bestowing"
        + " upon him the title and office of Master of the Telberin"
        + " Choirs.'\n");
    add_item( ({ "frame", "tiny frame" }),
          "The frame is fashioned from wood which has been carved to"
        + " resemble ivy leaves.\n");
    add_item( ({ "wood", "ivy", "leaves", "leaf", "ivy leaf",
                 "ivy leaves" }),
          "It is obvious that this frame was carved by a cunning"
        + " artist, well versed in woodworking.\n");
    add_item( ({ "window", "small window", "tiny window",
                 "window in the west wall" }),
          "The window is rather small, and allows only a meager amount"
        + " of light to penetrate the gloom of this dusty chamber.\n");
    add_item( ({ "gloom", "darkness", "dust", "air" }),
          "The dust hangs so thickly in this chamber that the light"
        + " from the window seems just barely adequate.\n");
    add_item( ({ "light", "illumination", "light from the window" }),
          "Light struggles into this chamber through a window in the"
        + " west wall, barely able to provide proper illumination.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is crowded with many piles of paper. It is difficult"
      + " to find a good place to stand.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling is fairly low in this room.\n");

    add_cmd_item( ({ "window", "small window", "tiny window",
                     "window in the west wall", "the window" }),
                  ({ "open", "close" }),
          "The window is fixed in place, and does not seem to be"
        + " able to be opened or closed.\n");
    add_cmd_item( ({ "writing", "papers", "paper", "parchment",
                     "parchments", "scrawl" }),
                  ({ "read" }),
          "You strain to make out a bit of the writing on a nearby"
        + " piece of parchment. After a few moments, you give up, as"
        + " it is completely illegible.\n");
    add_cmd_item( ({ "music", "music notation", "musical notation",
                     "notation" }),
                  ({ "read" }),
          "The musical notation is elegant and carefully written. The"
        + " care which was taken in writing these notes is the"
        + " hallmark of the Minstrel Guild, which would seem to"
        + " indicate that these documents are of their craft.\n");
    add_cmd_item( ({ "music", "pile", "piles", "paper", "papers",
                     "parchment", "parchments", "pile of paper",
                     "piles of paper", "pile of parchment",
                     "piles of parchment" }),
                  ({ "get", "take", "give", "move" }),
          "You would need about twenty helpers and a wheelbarrow to"
        + " move all of this mess.\n");
    add_cmd_item( ({ "diploma" }),
                  ({ "read" }),
          "The diploma reads as follows: 'Presented to Feni Arlal in"
        + " recognition of his meritorious service and accomplishments"
        + " in the Minstrel Guild of Telberin is this diploma, bestowing"
        + " upon him the title and office of Master of the Telberin"
        + " Choirs.'\n");

    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from the north.");
    add_prop(ROOM_I_INSIDE, 1);

    add_door_exit("/d/Emerald/telberin/arts/cmasters_door",
                  "/d/Emerald/telberin/arts/cantors_plaza",
                  "south", 0, 0, 1);

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        exa_desk
 * Description  :        provides a description of the desk, showing
 *                       the player whether or not the Choir Master
 *                       is present.
 * Returns      :        string - the desk description
 */
public string
exa_desk()
{
    string   desk;

    desk = "This desk rests against the far wall, away from the door."
         + " Like every other surface in this room, it is completely"
         + " covered with piles of paper which drape"
         + " precariously over its sides. ";

    if (!present("choir_master"))
    {
        desk += "\n";
    }

    else
    {
        desk += "An old elf sits hunched over the desk, writing on some"
              + " parchment.\n";
    }

    return desk;
} /* exa_desk */


/*
 * Function name:        reset_room
 * Description  :        we want to make sure Feni is here
 */
public void
reset_room()
{
    if (!Choir_Master)
    {
        setuid();
        seteuid(getuid());

        Choir_Master = clone_object(
            "/d/Emerald/telberin/arts/npc/cmaster");

        Choir_Master->move(this_object(), 1);
        tell_room(this_object(),
            "An old elf suddenly emerges from behind a few tall"
          + " stacks of parchment and moves to sit down at the"
          + " desk.\n");
    }
} /* reset_room */


/*
 * Function name:        sit_desk
 * Description  :        let players try to sit at the desk
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
sit_desk(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Sit where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
          "[down] [at] [the] 'desk'"))
    {
        return 0;
    }

    if (!present("choir_master"))
    {
        write("Even if you could find a path through all the clutter,"
            + " there is really no room to sit at the desk.\n");
        return 1;
    }

    write("The old elf is sitting at the desk!\n");
    return 1;
} /* sit_desk */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(sit_desk, "sit");
} /* init */


