/*
 *  /d/Gondor/guilds/rangers/north/song_room.c
 *
 *  A room for stories and songs in the North Hideout
 *
 *  Coded by Elessar
 *
 **     Revision history:
 **       10-Dec-1997, Gnadnar: general cleanup and add working fireplace
 **       28-Jun-2001, Alto: move and cleanup.
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/new_library.c";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "check_exit.c"

#define RESET_WOOD     10
#define BENCH_NAME     "wooden bench"
#define BENCH_CAPACITY 12

public int             book_index();
public string          fire_desc(string arg);
public void            leave_inv(object ob, object to);
public string          look_at(string arg);
public int             check_leave(int i);


public void
create_gondor()
{
    set_short("a comfortable room for songs and tales");
    set_long(&fire_desc());
    set_parse_pattern("[the] [small] 'fireplace'");
    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [wooden] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");

    north_add_items();

    add_item(({ "small fireplace", "stone fireplace",
        "small stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item(({ "flame", "flames", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */
    add_item(({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace" }), &fire_desc("wood"));
    add_item(({ "ash", "ashes", "ash in fireplace", "ashes in fireplace" }),
        &fire_desc("ashes"));
    add_item(({ "smokestack", "stack" }), "It's a plain smokestack. It "
        + "starts above the hearth and disappears into the ceiling.\n");
    add_item(({ "wooden bench", "wooden benches", "bench", "benches",
        "sturdy bench", "sturdy benches", "oak bench", "oak benches",
        "sturdy oak bench", "sturdy oak benches", "sturdy wooden bench", 
        "sturdy wooden benches"}), &look_at(BENCH_NAME) );
    add_item(({"book", "storybook", "oversized book", "green book"}), 
        "The large green book has decorations of gold upon it. Written "
        + "upon the front is the title: Storybook of the Rangers of the "
        + "North. You can open it to see the index of stories, or you "
        + "can even 'write story' of your own, to add in the book.\n");
    add_item(({"table", "wooden table", "sturdy table"}), "On the sturdy "
        + "table lies an oversized, green and golden book.\n");
    add_item(({"pillar", "pillars"}), "Th pillars are beautifully sculpted "
        + "to resemble graceful trees. You almost need to touch them to "
        + "realize they are not real trees.\n");
    add_item(({"tree", "trees"}), "On close inspection, you realize these "
        + "are actually pillars of stone, cleverly sculpted to resemble "
        + "real trees.\n");

    add_cmd_item(({"book","storybook","oversized book","green book",
        "annals"}), "open", book_index);
    add_cmd_item(({"book","storybook","oversized book","green book",
        "annals"}), "read", "You should open it and look at the index.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGERS_NOR_DIR + "start"  , "north");
    add_exit(RANGERS_NOR_DIR + "n_corridor"  , "west");
    add_exit(RANGERS_NOR_DIR + "e_corridor"  , "south");
    add_exit(RANGERS_NOR_DIR + "meeting_room", "east");

    set_library_name("The Songroom of the Rangers of the North");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("story");
    set_save_path(RANGERS_NOR_DIR + "lib/stories");
    set_write_dir(RANGERS_NOR_DIR + "lib");
    set_log_file("guild");
    set_up_library();

    if (file_size(CHESS_GAME + ".c") > 0)
        clone_object(CHESS_GAME)->move(TO);
    else
        log_file("errors", file_name(TO) + 
            " >>>>> " + CHESS_GAME + " not found!\n");

    reset_room();
}

/* Function name: reset_room
 * Description  : replenish the fire if necessary
 */
public void
reset_room()
{
    set_wood(RESET_WOOD);
    if ( query_fire_state() != FIRE_BURNING )
    {
        /* use an imaginary ranger to light the fire ... */
        tell_room(TO, "A grey-cloaked sentinel enters.\n");
        tell_room(TO, "The grey-cloaked sentinel puts some wood "
            + "in the fireplace.\n");
        tell_room(TO, "The grey-cloaked sentinel lights the wood "
            + "in the fireplace.\n");
        tell_room(TO, "The grey-cloaked sentinel leaves north.\n");
        set_fire_state(FIRE_BURNING);
    }
}

/*
 * Function name: lib_hook_read 
 * Description  : read a story
 *                (redefined to allow reading from a book
 *                instead of shelf)
 * Arguments    : int j: book(type) nr
 *                object p: reader
 */
void
lib_hook_read(int j, object p)
{
    write("You read the " + booktype + " titled \""
        + capitalize(descrs[j]) + "\".\n");
    say(QCTNAME(p) + " reads a " + booktype + " " + p->query_pronoun()
        + " found in the large green book.\n",p);
}

int
book_index()
{
    if (!sizeof(names))
        return lib_hook_lib_empty();

    do_list("stories");
    return 1;
}

/*
 * Function name: init
 * Description  : Adds verbs for fire and book.
 */
public void
init()
{   
    ::init();
    init_room_chairs();
    init_fire();
    init_library();
}

int
query_write_priv(object pl)
{
    if (RANGERS_MEMBER(pl) ||
      SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
        return 1;

    return 0;
}

int
query_remove_priv(object pl)
{
    if (SECURITY->query_wiz_dom(pl->query_real_name()) == "Gondor" ||
      MANAGER->query_is_council(pl->query_real_name()))
        return 1;

    return 0;
}

void
lib_hook_finish_book(int sec)
{
    if (sec)
        write("You drop your story into the mailbox of the Council.\n");
    else
        write("You finish your story, and add it in the large book.\n");

    say(QCTNAME(this_player()) + " finishes writing a story.\n");
}

int
query_secure_add(object pl)
{
    return 0;
}

int
lib_hook_lib_empty()
{
    notify_fail("There are no stories in the storybook.\n");
    return 0;
}

int
lib_hook_no_remove_priv()
{
    notify_fail("You are not allowed to remove any stories.\n");
    return 0;
}

int
lib_hook_remove_fail_empty()
{
    notify_fail("But the book is empty, there are no stories to remove.\n");
    return 0;
}

int
lib_hook_remove_no_name()
{
    notify_fail("There is no story by that name in the book!\n");
    return 0;
}

int
do_list(string str)
{
    int i,j;
    string txt;

    if (strlen(str) && (str != "stories"))
    {
        notify_fail("List what? The stories in the book, perhaps?\n");
        return 0;
    }

    if (!sizeof(names))
        return lib_hook_lib_empty();

    txt = "These are the stories that you can read in the book:\n";
    for (i=0; i<sizeof(names); i++)
    txt += sprintf("%-20s %-55s\n", names[i], descrs[i]);
    write(txt);
    return 1;
}

int
do_return(string s)
{
    return 0;
}

int
do_borrow(string s)
{
    return 0;
}

/*
 * Function name: fire_desc
 * Descripiton  : VBFC for room and items that vary w fire
 * Arguments    : string arg -- what we're looking at
 * Returns      : string description
 */
public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();
    string tmpstr;

    switch ( arg )
    {
    case "fireplace":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The stone fireplace in the center of the room "
                + "is not large, but holds a cheerful fire.\n";
        case FIRE_UNLIT_WOOD:
            return "The small stone fireplace in the center of the "
                + "room holds a stack of unlit wood.\n";
        default:
            return "The small stone fireplace in the center of the " 
                + "room is empty.\n";
        }

    case "fire":
        if ( fire_state == FIRE_BURNING )
        {
            return one_of_list(({ "Flames dance in the fireplace.\n",
                "The fire casts a warm glow over the room.\n",
                "The fire is burning brightly.\n", }));

        }

        return "You find no fire.\n";

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emiting "
                + "a pleasant warmth.\n";
        case FIRE_UNLIT_WOOD:
            return "Unlit wood is piled in the fireplace.\n";
        default:
            return "You find no firewood.\n";
        }

    case "ashes":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, "
                + "ashes cover the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the wood, ashes cover the bottom of "
                + "the fireplace.\n";
        default:
            return "Ashes cover the bottom of the fireplace.\n";
        }

    default:
        if ( fire_state == FIRE_BURNING )
            tmpstr = " A merry fire casts its glow over the room.";
        else
            tmpstr = "";

        return "The room for songs and tales is dominated by four stone "
            + "pillars, standing in a single row in the center of the "
            + "room. Between the innermost pillars is a wooden table, upon "
            + "which rests a large storybook. Benches line the walls, and "
            + "the carpet is especially thick and soft." + tmpstr + "\n";
    }
}

/*
 * Function name: leave_inv
 * Description  : mask parent to be sure that departing players
 *                are removed from chair/sofa occupants
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().However, if they leave by quitting,
 * going netdead, teleporting, etc and we don't call leave_inv_room_chairs(),
 * then they'll still look as if they're here.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}

public string
look_at(string arg)
{
    if (arg == BENCH_NAME)
    {
        return "The sturdy oak benches are bolted against all of the walls "
            + "except the one with the door. They are very comfortable and "
            + "can hold quite a few people.\n" 
            + sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
}

public int
check_leave(int i)
{
    if (check_sitting() || check_ranger(i))
        return 1;
    else
        return 0;
}
