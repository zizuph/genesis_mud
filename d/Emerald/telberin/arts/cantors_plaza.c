/*
 * /d/Emerald/telberin/arts/cantors_plaza.c
 *
 * The hub of musical activity in Telberin, this plaza is the intersection
 * between the various forces at work making music in the City. It is
 * located off of the eastern curve of Ri Circle in the Arts Quarter of
 * Telberin.
 *
 * Copyright (c) May 2000, by Cooper Sherry (Gorboth)
 */

inherit "/d/Emerald/telberin/telberin_street";
#include <macros.h>
#include <language.h>

#define PERFORM_MANAGER   ("/d/Terel/guilds/minstrels/lib/performance_manager")
#define IS_PERFORMER(x)   PERFORM_MANAGER->query_is_member(x)
#define REPUTATION(x)     PERFORM_MANAGER->query_reputation_level(x)
#define DISTINGUISHED     9


/* prototypes */
public void    create_telberin_street();
public void    init();
public int     do_drink(string str);
public int     do_enter(string arg);


/*
 *  Function name:        create_telberin_street
 *  Description  :        set up the room
 */
public void
create_telberin_street()
{
    config_street_room("Arts",
                       "Cantors Plaza");

    set_em_long(this_object()->short() +". The cobblestones of the street"
      + " expand to form a wide oval which narrows to the north and"
      + " south. Directly to the east is the entrance to a large"
      + " institution, whose otherwise solemn appearance is softened by"
      + " walls and eaves draped with many beautiful plants. One wing"
      + " of this expansive building curves around to the north, where"
      + " a small door is visible. Many people can be seen entering and"
      + " leaving the massive Music Auditorium which looms to the south."
      + " Presiding over the entire plaza, a tall fountain stands as"
      + " a dramatic centerpiece."
      + " Cantors Way extends from the plaza to the northwest and"
      + " southwest, travelling back towards the Royal Circle. A"
      + " narrow cobblestone path winds between buildings, heading"
      + " northeast.\n");

    add_item( ({ "path", "narrow path", "cobblestone path",
                 "narrow cobblestone path" }),
        "A narrow cobblestone path branches off of the plaza winding"
      + " through an archway in the campus to the Minstrel Guild.\n");
    add_item( ({ "cantors way", "way", "cantors way" }),
        "Cantors Way runs northwest and southwest of here, heading"
      + " back towards the Royal Circle. To the southwest, it appears"
      + " to have suffered great damage in the recent raids, and has"
      + " been closed to passage.\n");
    add_item( ({ "stone", "stones", "cobblestone", "cobblestones",
                "cobblestones of the street", "down" }),
        "The cobblestones of this plaza spread outward from the"
      + " majestic fountain at its midpoint in a radiating spiral"
      + " pattern.\n");
    add_item( ({ "pattern", "spiral pattern", "radiating pattern",
                 "radiating spiral pattern" }),
        "Though the pattern is spacially complex, you detect no"
      + " irregularities in the seams between individual stones.\n");
    add_item( ({ "seam", "seams" }),
        "The seams between the stones are tight and even, bearing"
      + " testimony to the great artistry and careful planning of the"
      + " hands that set them fast.\n");
    add_item( ({ "plaza", "cantors plaza", "cantors plaza", "here",
                 "wide plaza", "oval plaza", "wide oval plaza" }),
        "This plaza is the central hub for all musical activity within"
      + " the city of Telberin. People move to and fro from building"
      + " to building, often pausing before the great fountain in the"
      + " center of the cobblestones to talk with one another.\n");
    add_item( ({ "people", "musicians", "person", "musician",
                 "elf", "elves", "minstrel", "minstrels" }),
        "Most of the people here appear to be elves, stopping to"
      + " discuss things with one another in the plaza, or travelling"
      + " between buildings. Though it often difficult to tell"
      + " musicians from their appearance, many of these people are"
      + " carrying musical instruments, and most are headed"
      + " to or from the Auditorium to the south.\n");
    add_item( ({ "instrument", "instruments", "musical instrument",
                 "musical instruments", "harp", "harps", "lyre",
                 "lyres", "viol", "viols", "lute", "lutes",
                 "recorder", "recorders" }),
        "All forms of musical instruments can be seen in the hands"
      + " of the people in this plaza. Harps, lyres, viols, lutes,"
      + " and recorders are all easily recognizable.\n");
    add_item( ({ "building", "buildings", "structure", "structures" }),
        "Various structures form the perimeter of this plaza. To the"
      + " east is the entrance to an institution of some sort. South,"
      + " a vast auditorium rises above the trees. A small door leads"
      + " north into a wing of the institution.\n");
    add_item( ({ "tree", "trees" }),
        "Numerous trees have been cultivated along the perimeter of"
      + " the plaza. Their shimmering leaves rustle peacefully with"
      + " the occasional wind gust.\n");
    add_item( ({ "leaf", "leaves", "shimmering leaves" }),
        "The leaves of the trees are golden yellow and green.\n");
    add_item( ({ "perimeter", "perimeter of the plaza", "shape",
                 "oval", "oval shape" }),
        "Various buildings line the perimeter of the plaza, which"
      + " spreads out in a wide oval of cobblestones.\n");
    add_item( ({ "east", "entrance", "entrance to the east",
                 "entrance to a large institution" }),
        "The entrance is marked by a tall, ivy-hung archway through"
      + " which a lane passes from the plaza into what appears to"
      + " be a courtyard beyond.\n");
    add_item( ({ "archway", "arch", "tall archway", "ivy-hung archway",
                 "tall, ivy-hung archway" }),
        "Vines cling to the archway which marks the entrance to the"
      + " Minstrel Guild. Though made of bricks, it is a light and"
      + " graceful structure, delicately framing the lane which passes"
      + " beneath.\n");
    add_item( ({ "vine", "vines", "ivy" }),
        "Ivy vines cover a great deal of the archway, adding to the"
      + " already considerable elegance of the structure.\n");
    add_item( ({ "lane", "path", "pathway" }),
        "The pathway appears to lead into a courtyard beyond the"
      + " archway. Numerous people pass to and fro along its course.\n");
    add_item( ({ "courtyard", "yard", "court" }), 
        "Little can be seen from here.\n");
    add_item( ({ "institution", "large institution",
                 "large building", "expansive building", "guild",
                  "minstrel guild", "minstrel guild of telberin",
                  "campus", "large campus" }),
        "Directly to the east lies the Minstrel Guild of Telberin. It"
      + " is among the more reknown locations within the City, and has"
      + " been known to attract hopefuls from distant lands. The entire"
      + " campus is contained within one large building, whose many"
      + " wings can be seen extending to the north and south.\n");
    add_item( ({ "wing", "wings", "many wings", "north" }),
        "One wing of the large building to the east curves around"
      + " to the north, where a small door is visible.\n");
    add_item( ({ "apparance", "solemn appearance", "wall", "walls",
                 "eave", "eaves", "plant", "plants", "beautiful plant",
                 "beautiful plants", "many beautiful plants" }),
        "Apparently, great care has been taken to make the Minstrel"
      + " Guild a beautiful place. The eaves have been hung with"
      + " plants of many varieties, and the walls are covered with"
      + " ivy vines.\n");
    add_item( ({ "ivy vines", "ivy vine" }),
        "Vines of ivy cling to the walls of the Minstrel Guild, adding"
      + " considerably to the beauty of the institution.\n");
    add_item( ({ "auditorium", "music auditorium", "massive auditorium",
                 "massive music auditorium", "south" }),
        "To the south lies the Music Auditorium, a central location"
      + " for many of the minstrels in their daily life. Though not"
      + " as impressive as the Cathedral of Telan-Ri, is is a vast"
      + " structure, rising high above the rooftops of the city.\n");
    add_item( ({ "roof", "roofs", "rooftop", "rooftops" }),
        "The rooftops of Telberin are visible in all directions here.\n");
    add_item( ({ "fountain", "tall fountain", "centerpiece", "center",
                 "dramatic centerpiece", "dramatic fountain" }),
        "In the center of the plaza stands a tall fountain, around"
      + " which many people are gathered. Sculpted of a beautiful"
      + " white stone, Din Liel rises above the spraying waters to"
      + " watch over the Minstrel Guild.\n");
    add_item( ({ "din liel", "handmaiden", "maiden", "maid",
                 "handmaid", "handmaiden of telan-ri", "statue" }),
        "Din Liel, the Handmaiden of Telan-Ri, is beloved among"
      + " those who value music as is evidenced by the beauty and"
      + " grace of this statue.\n");
    add_item( ({ "stone", "white stone" }),
        "The stone from which Din Liel has been rendered appears"
      + " smoother and purer than marble. It is a deep white, and"
      + " glistenes with moisture.\n");
    add_item( ({ "water", "moisture", "spray", "spraying water",
                 "dancing water" }),
        "The water in the fountain pours from many spouts to fall"
      + " noisily into a large basin at the feet in Din Liel.\n");
    add_item( ({ "spout", "spouts", "many spouts" }),
        "The spouts send water into the air to land in the basin"
      + " of the fountain.\n");
    add_item( ({ "basin", "base", "basin of the fountain" }),
        "The basin stands about waist high to an elf. It is filled" 
      + " with the dancing water of the fountain.\n");

    add_exit("/d/Emerald/telberin/cantors_way05", "northwest");
    add_exit("/d/Emerald/telberin/arts/grove", "northeast");
    add_exit("/d/Emerald/telberin/arts/minstrel_guild", "east", 
        "@@enter_minstrel_guild", 1, 1);

/*
    set_no_exit_msg( ({ "east" }),
        "The gates to the Minstrel Guild stand closed. You cannot enter"
      + " the campus at this time.\n");
*/
    set_no_exit_msg( ({ "southwest" }),
        "The area to the southwest is currently blocked by repair"
      + " work which must be undertaken to undo damage done to"
      + " the city in recent raids.\n");

    add_door_exit("/d/Emerald/telberin/arts/cmasters_door",
                  "/d/Emerald/telberin/arts/cmasters_chambers",
                  "north", 0, 0, 1);
} /* create_telberin_street */


/*
 * Function name:        init
 * Description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(do_drink, "drink");
    add_action(do_enter, "enter");
} /* init */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the fountain
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'fountain' / 'basin' [from] [the]"
      + " [basin] [of] [the] [fountain]"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You seem to have drunk your fill.\n");
    }
    else
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " fountain.\n");

    return 1;
} /* do_drink */


/* 
 * Function name:        do_enter
 * Description  :        allow players to enter the music auditorium
 *                       like they do other buildings in Telberin
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
        write("Enter what?\n");
        return 1;
    }

    if (!parse_command(arg, ({}),
        "[the] [massive] [music] 'auditorium' / 'building' /"
      + " 'structure' [to] [the] [south]"))
    {
        return 0; /* can't parse player syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'south' here"
          + " using command(). Since you are a wizard, that won't"
          + " work. Simply type 'south' yourself.\n");
        return 1;
    }

    this_player()->command("south");
    return 1;
} /* do_enter */

int
enter_minstrel_guild()
{
    if (this_player()->query_wiz_level())
    {
        write("As an immortal, the gates to the Minstrel's Guild "
            + "of Telberin open to you.\n");
        return 0;
    }

    if(IS_PERFORMER(this_player()))
    {
        if(REPUTATION(this_player()) < DISTINGUISHED)
        {
            write("The gates to the Minstrel's Guild of Telberin do "
                + "not open for you. Only distinguished performers "
                + "are granted access to their halls!\n");
            return 1;
        }
        string reputation = PERFORM_MANAGER->query_reputation_level_desc(this_player());

        write("As " +LANG_ART(reputation)+ " " +reputation+ " performer, "
            + "the gates to the Minstrel's Guild of Telberin open to "
            + "you and you enter.\n");

        if(!PERFORM_MANAGER->query_visited_telberin_guild(this_player()))
        {
            PERFORM_MANAGER->set_visited_telberin_guild(this_player(), 1);
        }

        return 0;
    }

    write("The gates to the Minstrel's Guild of Telberin do not "
        + "open for you. Only distinguished performers are granted "
        + "access to their halls!\n");
    return 1;
}

