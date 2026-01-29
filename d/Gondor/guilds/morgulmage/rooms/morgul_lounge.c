/*
 *  /d/Gondor/morgul/tower/morgul_lounge.c
 *
 *  This is a lounge for full-mages and above. Apprentices are not worthy
 *  to enter.
 *
 *  Created June 2011, by Cooper Sherry (Gorboth)
 *
 *  Many of the descriptions are based on submissions by the players.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit MORGUL_ROOM_DIR + "morgul_chairs";

/* Prototypes */
public void              create_morgul_tower_room();
public void              init();
public void              leave_inv(object ob, object dest);
public string            look_slabs();
public object            make_board();

/* Global variables */
public object            Board;

/* Definitions */
#define BLOCK_NAME       "floating obsidian slabs"

/*
 * Function name:        create_morgul_tower_room
 * Description  :        set up the room
 */
public void
create_morgul_tower_room()
{
    set_level(5);
    set_room_type("forbidden lounge");
    set_extra_long("This large chamber seems utterly bereft of hope and"
      + " joy for any other than the select High Servants who have"
      + " achieved full Mage rank within the Society. An"
      + " area in the center of the room is filled with sleek obsidian"
      + " slabs which float upon winds of flame. The slabs form"
      + " a circle around a roughly-hewn chunk of granite that serves"
      + " as a table for the countless conversations and plots"
      + " which transpire in this fell place. A pulsing ominous"
      + " glow from the single window in the east wall creates a"
      + " type of heartbeat to the room, filling the empty pit"
      + " of the undead soul with the eternal will of the Great"
      + " Eye. A blackened board hangs on the southern wall.");

    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling to the chamber is vaulted, rising high above the"
      + " table below it's central peak.\n");
    add_item( ({ "peak", "central peak" }),
        "You see a strange black gleam up there.\n");
    add_item( ({ "gleam", "black gleam", "strange gleam",
                 "strange black gleam" }),
        "It seems to glitter with a dazzling depth of blackness that"
      + " makes everything else in the chamber seem bright by"
      + " comparison.\n");
    add_item( ({ "depth", "depth of blackness",
                 "dazzling depth", "dazzling blackness",
                 "blackness",
                 "dazzling depth of blackness" }),
        "You stare into the depths of the blackness, and feel a strange"
      + " tingling upon the backs of your eye sockets.\n");
    add_item( ({ "wall", "walls", "walls of the chamber",
                 "chamber walls" }),
        "The walls of the chamber are sleek and polished, black as"
      + " midnight, and utterly bare but for the window in the east"
      + " wall, and a board hanging to the south.\n");
    add_item( ({ "east", "east wall", "east wall of the chamber", }),
        "The east wall of the chamber contains a single, round"
      + " window.\n");
    add_item( ({ "tower", "tower of black sorcery" }),
        "You are within the tower. Only from outside can you"
      + " view it properly.\n");
    add_item( ({ "ground", "floor", "down", "marble",
                 "black marble", "midnight black marble" }),
        "The floor at your feet is a canvas of midnight black marble"
      + " so seamlessly fit together that it almost appears as a vast"
      + " and perfect mirror. Each footstep upon its unblemished"
      + " surface rings through the chamber with a hollow echo.\n");
    add_item( ({ "here", "room", "area", "chamber", "lounge",
                 "forbidden lounge" }), long);
    add_item( ({ "wind", "winds", "flame", "flame wind",
                 "flame winds", "fire", "wind of flame",
                 "winds of flame", "pillar", "pillars",
                 "pillar of flame", "pillar of fire",
                 "pillars of flame", "pillars of fire", }),
        "Cool and eerily silent pillars of flame support many sleek"
      + " obsidian slabs which hover in unison motion around the"
      + " central table here.\n");
    add_item( ({ "chunk", "roughly-hewn chunk", "hewn chunk",
                 "granite", "roughly-hewn granite",
                 "roughly-hewn chunk of granite",
                 "table" }),
        "The table at the center of the lounge is scored with many"
      + " harsh-looking marks and gouges. Blood is stained into many"
      + " of these, giving the table an appealing reddish tint.\n");
    add_item( ({ "conversation", "conversation", "plot", "plots" }),
        "Perhaps you'd like to create a few of your own?\n");
    add_item( ({ "fell place" }),
        "Fell, indeed.\n");
    add_item( ({ "glow", "ominous glow", "pulsing glow",
                 "pulsing ominous glow" }),
        "The glow from the window spreads throughout the lounge,"
      + " absorbing everything in its powerful embrace.\n");
    add_item( ({ "beat", "pulse", "heartbeat" }),
        "Though your heart is long-since sacrificed to the will of"
      + " your Master, you can't help but feel a certain pulse"
      + " pounding through your undead soul in this place.\n");
    add_item( ({ "window", "single window", "eye", "great eye",
                 "round window", "single round window" }),
        &read_file(MORGUL_GUILD_DIR + "doc/eye_pic.txt", 0));
    add_item( ({ "chair", "chairs", "slab", "slabs",
                 "obsidian", "obsidian slab", "obsidian slabs",
                 "sleek slab", "sleek slabs",
                 "sleek obsidian slab", "sleek obsidian slabs",
                 "floating slab", "floating slabs",
                 "floating obsidian slab", "floating obsidian slabs" }),
        look_slabs);

    add_chair(BLOCK_NAME, "[down] [at] [in] [on] [one] [of] [the] [nearby]"
                        + " [sleek] [floating] [obsidian] "
                        + " 'slab' / 'slabs' / 'chair' / 'chairs'",
                          20, "upon one of", 1);

    add_exit(MORGUL_ROOM_DIR + "tower_5c", "west", 0, 1);

    setuid();
    seteuid(getuid());

    if (!(Board = make_board()))
    {
        add_my_desc("ERROR: Board not created. Please mail a"
          + " Gondor wizard.\n");
    }
} /* create_morgul_tower_room */


/*
 * Function name: init
 * Description:   set up the commands
 */
public void
init()
{
    ::init();

    init_room_chairs();
} /* init */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from table occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


/*
 * Function name:        look_slabs
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_slabs()
{
    return "Sleek obsidian slabs rise and fall in haunting unison"
      + " as they float upon unearthly winds of flame that surround" 
      + " the great granite table.\n"
         + sitting_on_chair(BLOCK_NAME, this_player(), 0, 1);
} /* look_block */


/*
 * Function name:        make_board
 * Description  :        set up the bulletin board
 * Returns      :        the board object - success,
 *                       0                - failure, board not created.
 */
public object
make_board()
{
    object  bboard;

    bboard = clone_object(MORGUL_OBJ_DIR + "lounge_board");

    if (bboard)
    {
        bboard->move(this_object());

        return bboard;
    }

    return 0;
} /* make_board */