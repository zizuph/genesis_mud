/*
 *  /d/Gondor/guilds/rangers/hq/cozy.c
 *
 *  A cozy room upstairs in the Central Headquarters hideout
 *
 *  Written by Stern 29 February 2000
 *    Original theme of Druedain hideout by Elessar
 *  Modification log:
 *       10-Dec-1997, Gnadnar: general cleanup and add working fireplace
 *       Alto, 28 June 2001 (altered to fit C.H. theme, and to change
 *       storybook to Apprentice Annals)
 *       Gwyneth, 3 May 2004 - Tidied, fixed bad check
 *       Tigerlily, 19 October 2004 - Added exit to recruiter room
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/new_library.c";
inherit "/d/Gondor/open/fireplace/fireplace";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define RESET_WOOD     10
#define BENCH_NAME     "wooden bench"
#define BENCH_CAPACITY 12

public int             book_index();
public string          fire_desc(string arg);
public void            leave_inv(object ob, object to);
public string          look_at(string arg);     /* VBFC for chairs */
public int             lift_tapestry();
public string          exa_tapestry();

public void
create_gondor()
{
    set_short("a small cozy room on the second floor");
    set_long(fire_desc);
    set_parse_pattern("[the] [small] 'fireplace'");
    add_chair(BENCH_NAME,
        "[down] [on] [one] [of] [the] [wooden] 'benches' / 'bench'",
        BENCH_CAPACITY, "on");

    hideout_add_items();

    add_item(({ "small fireplace", "stone fireplace",
        "small stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item(({ "flame", "flames", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */

    add_item(({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace" }), &fire_desc("wood"));
    add_item(({ "ash", "ashes", "ash in fireplace", 
        "ashes in fireplace" }), &fire_desc("ashes"));
    add_item(({ "smokestack", "stack" }), "It's a plain smokestack. It starts "
        + "somewhat above the hearth and disappears into the ceiling.\n");
    add_item(({ "wooden bench", "wooden benches", "bench", "benches",
        "sturdy bench", "sturdy benches", "oak bench", "oak benches",
        "sturdy oak bench", "sturdy oak benches", "sturdy wooden bench", 
        "sturdy wooden benches"}), &look_at(BENCH_NAME) );
    add_item(({"book", "storybook", "oversized book", "green book", "annals"}), 
        "The large green book has decorations of gold upon it. Written upon "
        + "the front is the title: Annals of the Apprentice Rangers. You can "
        + "open it to see the index of stories, or you can even "
        + "'write story' of your own, to add in the book.\n"); 
    add_item(({"dark green rug", "green rug", "rug" }), "A dark green rug "
        + "covers the stone floor.\n");
    add_item(({"tapestry", "beautiful tapestry"}), &exa_tapestry());
    add_cmd_item(({"tapestry", "beautiful tapestry"}), "lift", lift_tapestry);
    add_cmd_item(({"book","storybook","oversized book","green book", "annals"}),
        "open", book_index);
    add_cmd_item(({"book","storybook","oversized book","green book", "annals"}),
        "read", "You should rather open it and look at the index.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(RANGERS_HQ_DIR + "office", "north", check_sitting, 1);

    set_library_name("The Cozy Room of the Apprentice Rangers");
    set_read_cmd("read");
    set_list_cmd("list");
    set_book_type("story");
    set_save_path(RANGERS_HQ_DIR + "lib/ch_annals");
    set_write_dir(RANGERS_HQ_DIR + "lib");
    set_log_file("guild");
    set_up_library();

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
        tell_room(TO, "An apprentice ranger enters.\n");
        tell_room(TO, one_of_list(({ "He", "She" })) + " puts some wood "
            + "in the fireplace.\n");
        tell_room(TO, "The apprentice ranger lights the wood in the "
            + "fireplace.\n");
        tell_room(TO, "The apprentice ranger leaves north.\n");
        set_fire_state(FIRE_BURNING);
    }
}

/*
 * Function name: lib_hook_read 
 * Description  : read a story
 *                (redefined to allow reading from a book instead of shelf)
 * Arguments    : int j: book(type) nr
 *                object p: reader
 */
void
lib_hook_read(int j, object p)   /* REDEFINED */
{
    write("You read the " + booktype + " titled \"" + CAP(descrs[j]) + "\".\n");
    say(QCTNAME(p) + " reads a " + booktype + " " + p->query_pronoun()
        + " found in the large green book.\n", p);
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
 * Description  : add verbs for library, fire and book
 */
public void
init()
{   
    ::init();
    init_room_chairs();
    init_fire();
    init_library();
}

/*
 * Function name: query_write_priv
 * Description  : Checks if a player is a Ranger or wizard of Gondor.
 * Arguments    : The player to check
 * Returns      : 1 if allowed, 0 if not
 */
int
query_write_priv(object pl)
{
    if (RANGERS_MEMBER(pl) ||
      SECURITY->query_wiz_dom(pl->query_name()) == "Gondor")
        return 1;

    return 0;
}
/*
 * Function name: query_remove_priv
 * Description  : Checks if a player is an officer or wizard of Gondor.
 * Arguments    : The player to check
 * Returns      : 1 if allowed, 0 if not
 */
int
query_remove_priv(object pl)
{
    if (SECURITY->query_wiz_dom(pl->query_name()) == "Gondor" ||
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
    NF("There are no stories in the storybook.\n");
    return 0;
}

int
lib_hook_no_remove_priv()
{
    NF("You are not allowed to remove any stories.\n");
    return 0;
}

int lib_hook_remove_fail_empty()
{
    NF("But the book is empty, there are no stories to remove?\n");
    return 0;
}

int lib_hook_remove_no_name()
{
    NF("There is no story by that name in the book!\n");
    return 0;
}

int do_list(string str)
{
    int i,j;
    string txt;

    if (strlen(str) && (str != "stories"))
    {
        NF("List what? The stories in the book, perhaps?\n");
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
 * Descripiton  : VBFC for room and items that vary with fire
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
            return "The stone fireplace in the center of the room " +
                "is not large, but holds a cheerful fire.\n";
        case FIRE_UNLIT_WOOD:
            return "The small stone fireplace in the center of the " +
                "room holds a stack of unlit wood.\n";
        default: /* FIRE_ASHES */
            return "The small stone fireplace in the center of the " +
                "room is empty.\n";
    }

    case "fire":
        if ( fire_state == FIRE_BURNING )
        {
            return ( ({ "Flames dance in the fireplace.\n",
                "The fire casts a warm glow over the room.\n",
                "The fire is burning brightly.\n", })[random(3)] );

        }

        return "You find no fire.\n";

    case "wood":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "The wood in the fireplace burns brightly, emiting " +
                "a pleasant warmth.\n";
        case FIRE_UNLIT_WOOD:
            return "Unlit wood is piled in the fireplace.\n";
        default: /* FIRE_ASHES */
            return "You find no firewood.\n";
        }

    case "ashes":
        switch ( fire_state )
        {
        case FIRE_BURNING:
            return "Beneath the brightly burning fire, " +
                "ashes cover the bottom of the fireplace.\n";
        case FIRE_UNLIT_WOOD:
            return "Beneath the wood, " +
                "ashes cover the bottom of the fireplace.\n";
        default: /* FIRE_ASHES */
            return "Ashes cover the bottom of the fireplace.\n";
        }

    default: /* room description */
        if ( fire_state == FIRE_BURNING )
            tmpstr = " A merry fire casts its glow over the room.";
        else
            tmpstr = "";

        return "This room is small and plain, but cozy. The wooden floor "
            + "creaks beneath your feet, not as a result of poor carpentry, "
            + "but rather because the hideout stands partially in the trees "
            + "and was built by clever hands to shift in the wind. A "
            + "fireplace rests in the middle of the room. One can walk "
            + "around it, and sit on one of the sturdy oak benches that are "
            + "bolted to the walls. A smokestack starts just high enough "
            + "above the hearth that, when sitting on a bench, one can still "
            + "see the opposite side of the room where a beautiful " 
            + "velvet tapestry covers the west wall." + tmpstr + "\n";
    }
    /* NOTREACHED */
}

/*
 * Function name: leave_inv
 * Description  : This masks parent to be sure that departing players
 *                are removed from chair/sofa occupants. If they leave 
 *                via a normal exit, they've already been made to stand
 *                by the exit efunc check_sitting(). However, if they
 *                leave by quitting, going netdead, teleporting, etc
 *                and we don't call leave_inv_room_chairs(), then they'll
 *                still look as if they're here.
 * Arguments    : object ob -- the departing object
 *                object dest -- its destination
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
        return "The sturdy oak benches are bolted against all walls but for "
            + "the one with the door. They are not too comfortable but can "
            + "hold quite a few people. An oversized book lies on one of the "
            + "benches. The cover simply states: 'Annals of the Apprentice "
            + "Rangers'.\n" + sitting_on_chair(BENCH_NAME, this_player(), 0);
    }
} /* look_at */

public string
exa_tapestry()
{
    object tp = this_player();

    string text;
    
    text = "The west wall is covered by a beautiful tapestry of " +
        "midnight-blue velvet embroidered with a white silver tree " +
        "crowned by seven stars. ";
    if ((tp->query_ranger_rank() >= SPECIALTY_RANK &&
        MANAGER->query_ranger_level(tp->query_real_name()) >= 3) ||
        (MANAGER->query_council(tp->query_real_name(), "ithilien") != -1) || 
        (MANAGER->query_council(tp->query_real_name(), "north") != -1) ||
        IS_GONDOR_WIZARD(tp))
    {
        text += "Your keen senses tell you that there is " +
            "something behind this tapestry. You may lift it " +
            "to find out.";
    }
    
    return text + "\n";
}

public int
lift_tapestry()
{
    object tp = this_player();
    if ((tp->query_ranger_rank() >= SPECIALTY_RANK &&
        MANAGER->query_ranger_level(tp->query_real_name()) >= 3) ||
        (MANAGER->query_council(tp->query_real_name(), "ithilien") != -1) || 
        (MANAGER->query_council(tp->query_real_name(), "north") != -1) ||
        IS_GONDOR_WIZARD(tp))
    {
        write("You lift the tapestry and enter a secret " +
            "room to the west.\n");
        say(QCTNAME(tp) + " crouches down slightly.\n");
        tp->move_living("M", RANGERS_HQ_DIR+ "recruiter_office", 1, 0);
        tell_room(environment(tp), QCTNAME(tp) + " enters " +
            "quietly from behind the tapestry to the east.\n", tp);
        return 1;
    }
    return 0;
}


