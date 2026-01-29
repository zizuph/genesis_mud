/*
 *  /d/Emerald/common/guild/aod/rooms/council.c
 *
 *  This is the Great Hall of the Army of Darkness Guild.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";

/* prototypes */
public void        create_cave_room();
public void        init();
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_dome();
public void        leave_inv(object ob, object dest);
public void        check_dome_sitting(int dir = 0);
public string      exa_entrance();

/* definitions */
#define    CHAIR_NAME      "magma dome"


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    add_chair(CHAIR_NAME, "[down] [on] [the] [magma] 'dome'", 4);

    set_short("a huge gathering hall");
    set_em_long("This, the gathering hall for the Ogres, is actually"
      + " the base of a hollowed-out (semi) dormant volcano. From"
      + " the perimeter in all directions, the floor slopes gradually"
      + " toward the center, where a smoking magma dome acts as the"
      + " throne of the Headhunter General and his or her Black Corporal."
      + " From here, they may hold court with their kind, having"
      + " whatever sort of meeting Ogres are wont to have. A tunnel"
      + " leads south out of the area.\n");

    add_item( ({ "base" }),
        "Right here, where you stand.\n");
    add_item( ({ "gathering hall", "hall" }),
        "Gathering in a volcano that could decide to erupt at any"
      + " moment is quite typical of the ogre race.\n");
    add_item( ({ "volcano" }),
        "You glance nervously at the surrounding area. The wide basin"
      + " of the cinder cone runs almost as far as the eye can see in"
      + " all directions from the center of the chamber. At the"
      + " perimeter, blackened rock walls slope inward and up as"
      + " they rise high above to slowly taper toward an ancient"
      + " vent at the top of the volcano. Impressive!\n");
    add_item( ({ "dormant volcano" }),
        "At least one would hope it is dormant!\n");
    add_item( ({ "active volcano" }),
        "Thankfully, this volcano is dormant ... wait, did you just"
      + " feel a tremor?\n");
    add_item( ({ "tremor" }),
        "Phew ... must have been your imagination, or perhaps your"
      + " tummy. Have you eaten recently?\n");
    add_item( ({ "semi dormant volcano", "(semi) dormant volcano" }),
        "Dormant ... semi dormant ... what's the difference anyway?\n");
    add_item( ({ "surrounding area", "area" }),
        "It, um, surrounds you.\n");
    add_item( ({ "basin" }),
        "It's a basin and it is wide.\n");
    add_item( ({ "wide basin" }),
        "It is wider than an ogre's butt. Wide indeed!\n");
    add_item( ({ "cone", "cinder cone" }),
        "I suppose cinder cone is just a fancy name for the volcano"
      + " itself. Such words are meaningless to ogres of course.\n");
    add_item( ({ "perimeter" }),
        "Its the thing that determines the edge of the chamber.\n");
    add_item( ({ "edge", "edge of the chamber"  }),
        "Yeah, way way over there.\n");
    add_item( ({ "there" }),
        "Where?\n");
    add_item( ({ "over there" }),
        "Over where?\n");
    add_item( ({ "center", "center of the chamber" }),
        "A huge magma dome has formed at the center of the chamber.\n");
    add_item( ({ "wall", "walls", "blackened wall", "blackened walls",
                 "black wall", "black walls", "rock wall", "rock walls",
                 "blackened rock wall", "blackened rock walls" }),
        "The walls slope upward high from the perimeter, rising"
      + " many hundreds of feet toward the sky.\n");
    add_item( ({ "sky" }),
        "You can just glimpse it through the vent at the top of the"
      + " cinder cone.\n");
    add_item( ({ "vent", "ancient vent" }),
        "It is through that vent that the smoke rising from the"
      + " magma dome escapes to the heavens.\n");
    add_item( ({ "heaven", "heavens" }),
        "What, do you expect to hear angels singing?\n");
    add_item( ({ "angel", "angels" }),
        "Just forget it.\n");
    add_item( ({ "smoke" }),
        "Smoke rises in curling trails from the top of the magma"
      + " dome.\n");
    add_item( ({ "trail", "trails", "curling trail",
                 "curling trails" }),
        "The trails narrow from view as they travel the long length"
      + " of the cinder cone to eventually escape skyward through"
      + " the distant vent.\n");
    add_item( ({ "distant vent" }),
        "Yeah, its way up there.\n");
    add_item( ({ "magma" }),
        "Magma has pushed on the ground here to form a large dome"
      + " at the center of the chamber.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is rough and uneven, sloping gradually up toward"
      + " the center of the chamber.\n");
    add_item( ({ "rock", "rocks" }),
        "The rock of this area is black and hard.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "There is a great distance of open space between you and"
      + " the vent high above.\n");
    add_item( ({ "space", "open space" }),
        "You stare at the open space . . . its . . . abso . . . . . ."
      + " lutely . . . . . . . . . . . . . . . . . . . . . . . . ."
      + " fascinating.\n");
    add_item( ({ "tunnel" }),
        "It travels south, out of the volcano.\n");
    add_item( ({ "south" }),
        "A tunnel travels that direction.\n");
    add_item( ({ "throne", "thrones" }),
        "There is no literal throne here. Rather, the magma dome"
      + " acts as one.\n");
    add_item( ({ "dome", "magma dome", "great dome", }), look_dome);
    add_item( ({ "tube", "lava tube", "lava", "glowing chamber" }),
        exa_entrance);

    add_spike("council");

    add_exit("magma", "down", &check_dome_sitting(1), 1, 1);
    add_exit("tunnel5", "south", check_dome_sitting, 1, 0);
} /* create_cave_room */


/*
 * Function name:        init
 * Description  :        init the room chairs
 */
public void
init()
{
    ::init();

    init_room_chairs();
} /* init */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit on what?\n");
        return 0;
    }

    if (!AOD_GENERAL(this_player()) &&
        !AOD_CORPORAL(this_player()) &&
        this_player()->query_real_name() !=
        CHAMBER_MASTER->get_info("guests", NUM_OFFICER_SHORT) &&
        this_player()->query_real_name() !=
        CHAMBER_MASTER->get_info("guests", SPH_OFFICER_SHORT))
    {
        notify_fail("Only Officers of the Army are worthy to sit"
          + " on the great dome!\n");
        return 0;
    }

    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the chair msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    set_this_player(pl);

    write("You climb to the top of the magma dome and take a seat."
      + " At the top of the magma dome, you notice a lava tube"
      + " leading down here.\n");
    say(QCTNAME(pl) + " climbs to the top of the magma dome and"
      + " sits down.\n");
} /* do_sit_msgs */

/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    set_this_player(pl);

    write("You stand and walk to the floor of the chamber.\n");
    say(QCTNAME(pl) + " stands from atop the magma dome and walks"
      + " down to the floor of the chamber.\n");
} /* do_stand_msgs */


/*
 * Function name:        look_dome
 * Description  :        VBFC for the dome; include occupants
 * Returns      :        string -- the desc
 */
public string
look_dome()
{
    return    "The magma dome rises like a great stone-cracked"
            + " blister from the floor of the chamber. Officers"
            + " of the Army of Darkness are often known to <sit>"
            + " on the dome to preside over gatherings.\n"
            + sitting_on_chair(CHAIR_NAME, this_player(), 0, 1);
} /* look_dome */


/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from dome occupants
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
 * Function name:       check_dome_sitting
 * Description  :       have players stand up before leaving
 * Arguments    :       int dir - 0: (default) - leaving south
 *                                1: leaving down
 * Returns      :       0 (always)
 *
 * this routine is intended to be used as the 3rd (efunc) argument
 * to add_exit().  it will issue "you stand up"/"Foo stands up" 
 * msgs for normal exits.  
 *
 * this is separate from leave_inv() handling because by the
 * time leave_inv() is called, the "Foo leaves <dir>." message
 * has already been displayed.  at that point, it's too late to 
 * do "Foo stands up."
 * 
 * 
 */
public int
check_dome_sitting(int dir = 0)
{
    string      chairname = this_player()->query_prop(LIVE_S_SITTING);

    if (dir)
    {
        if (!AOD_GENERAL(this_player()) &&
            !AOD_CORPORAL(this_player()) &&
            this_player()->query_real_name() !=
            CHAMBER_MASTER->get_info("guests", NUM_OFFICER_SHORT) &&
            this_player()->query_real_name() !=
            CHAMBER_MASTER->get_info("guests", SPH_OFFICER_SHORT))
        {
            write("You dare not approach the great dome!\n");
            return 1;
        }
    }

    if (strlen(chairname))
    {
        if (dir)
        {
            say(QCTNAME(this_player()) + " rises from "
              + this_player()->query_objective() + " sitting position"
              + " and disappears down into the magma dome.\n");
        }
        else
        {
            stand_up(this_player(), chairname, 1);
        }
    }

    return 0;
} /* check_dome_sitting */


/*
 * Function name:        exa_entrance
 * Description  :        allow people to try to examine the entrance
 *                       to the magma chamber
 * Returns      :        string - the text for the add_item
 */
public string
exa_entrance()
{
    string      chairname = this_player()->query_prop(LIVE_S_SITTING);

    if (strlen(chairname))
    {
        return "A lava tube leads through the top of the magma"
          + " dome into a glowing chamber beneath. It is possible"
          + " to go down from here.\n";
    }

    return "You don't see anything like that from here.\n";
} /* exa_entrance */