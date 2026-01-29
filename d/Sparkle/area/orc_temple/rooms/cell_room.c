/*
 *  /d/Sparkle/area/orc_temple/cell_room.c
 *
 *  This is the master file for cell rooms on the prison level (level 2)
 *  of the orc dungeons near Sparkle. In these rooms, players who have
 *  a bone-flute can summon up ghosts.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <filepath.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit ROOMS_DIR + "dungeon_room";

/* Definitions */
#define             GHOST_RESPAWN     1200 /* 20 minutes */

/* Global Variables */
public string       Door_Direction = "west";
public mapping      Ghost_Summonings = ([]);
public object       Ghost;
public object       Prisoner;
public int          Cell_Empty = random(4);

/* Prototypes */
public nomask void  create_dungeon_room();
public void         create_cell_room();
public int          summon_ghost(object player);
public string       search_cell();
public void         reset_room();
public void         bring_prisoner();
public int          do_escape(string arg);
public int          do_escape2(string arg);

public void         set_door_direction(string s) { Door_Direction = s; }
public void         set_summonings(string s) { Ghost_Summonings[s] = time(); }
public mapping      query_summonings() { return Ghost_Summonings; }
public string       query_door_direction() { return Door_Direction; }

/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public nomask void
create_dungeon_room()
{
    object  door;

    add_name(DUNGEON_CELL);

    set_short("in a foul-smelling prison cell");
    set_long("You stand within the confines of a truly wretched-smelling"
      + " prison cell. Filthy straw strewn with bones and refuse"
      + " litters the floor.\n\n");

    try_item( ({ "cell", "prison cell", "here", "room", "chamber",
                 "foul-smelling cell", "foul-smelling prison cell",
                 "jail cell", }),
        "This is one of the most god-forsaken places you have ever"
      + " encountered.\n");
    try_item( ({ "smell", "smells", "foul smell", "foul smells" }),
        "To describe the smells here as simply foul would be to"
      + " describe the ocean as simply wet.\n");
    try_item( ({ "god-forsaken place", "god-forsaken places",
                 "forsaken place", "god forsaken place",
                 "place", "places" }),
        "Oh, Lord, why hast thou created such smells as these?\n");
    try_item( ({ "smell" }),
        "Sleep in the hole at the bottom of an outhose, and you might"
      + " find it smells something like this cell.\n");
    try_item( ({ "confinement", "confines" }),
        "Walls ... closing ... in ... \n");
    try_item( ({ "straw", "filthy straw", "floor", "ground" }),
        "The ground is covered with straw, but it is what the straw"
      + " is covered with that is of greater concern. Oh, the filth!\n");
    try_item( ({ "filth", "refuse" }),
        "Let's just say ... it's bad. REAL bad.\n");
    try_item( ({ "bone", "bones" }),
        "Apparently, there have been a number of deaths in this"
      + " chamber, and not very many burials.\n");
    try_item( ({ "death", "deaths" }),
        "The smell alone is almost enough to kill.\n");
    try_item( ({ "burial", "burials" }),
        "Not surprising. Orcs probably just use their dead as furniture"
      + " and don't have the faintest idea about such things.\n");
    try_item( ({ "prison" }),
        "Yep. You found it.\n");
    try_item( ({ "jail" }),
        "You did not pass Go or collect 200 dollars, and yet here"
      + " you are.\n");
    try_item( ({ "stone" }),
        "There are many stones in the walls. Did you have a particular"
      + " one in mind?\n");
    try_item( ({ "loose stone" }),
        "There is a loose stone in the corner of the cell here. Moving"
      + " it aside reveals a small hole dug into the dirt.\n");
    try_item( ({ "hole", "small hole" }),
        "There is a small hole dug into the dirt behind a loose stone"
      + " here. You could probably <escape> through it if you needed"
      + " to.\n");

    add_delay_cmd_item(
        ({ "floor", "ground", "here", "cell", "area", "walls",
           "straw", "filthy straw", "bones", "refuse" }),
        "search",
        "searching around in the cell",
        10,
        "You begin searching around in the cell.\n",
        search_cell);

    add_dungeon_items();

    create_cell_room();

    if (Door_Direction == "west")
    {
        set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                            "south", "southwest", "northwest" }),
            "You boldly stroll directly into a wall. OOOF!\n");
    }
    else
    {
        set_no_exit_msg( ({ "northeast", "southeast", "west", "south",
                            "southwest", "northwest", "north" }),
            "You boldly stroll directly into a wall. OOOF!\n");
    }

    door = clone_object(DOORS_DIR + "2_cell_door");
    door->configure_cell_door(Door_Direction);
    door->set_other_room(ROOMS_DIR
      + "2_hall" + FILE_NAME(file_name(this_object()))[-1..]);
    door->move(this_object());

    remove_prop(DOOR_BLOCK_ROOM); /* don't want to create deathtraps */
    add_prop(OBJ_S_SEARCH_FUN, "search_cell");

    if (!random(4))
    {
        add_npc("/d/Genesis/start/human/obj/rat2", random(4));
    }

    bring_prisoner();

    setuid();
    seteuid(getuid());
} /* create_dungeon_room */


/*
 * Function name:        create_cell_room
 * Description  :        dummy routine to be used by inheriting
 *                       files
 */
public void
create_cell_room()
{
} /* create_cell_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_escape, "escape");
    add_action(do_escape2, "enter");
    add_action(do_escape2, "crawl");
} /* init */


/*
 * Function_name:        summon_ghost
 * Description  :        allow players to try to summon a ghost in this
 *                       room once per hour
 * Arguments    :        object player - the one doing the summoning
 * Returns      :        int 0 - summoning unsuccessful
 *                       int 1 - summoning successful
 */
public int
summon_ghost(object player)
{
    string  plname = player->query_real_name();
    int     gtime  = time() - Ghost_Summonings[plname];
    object  jailer;

    if (objectp(Ghost))
    {
        Ghost->command("wail");
        return 0;
    }

    /* Players must wait an hour before summoning a new ghost if
     * it has already been killed here.
     */
    if (gtime < GHOST_RESPAWN ||
        player->test_bit(ORCTEMPLE_GHOST_BIT,
                         ORCTEMPLE_GHOST_GROUP))
    {
        write("You wait as the echoes of your flute die away. Nothing"
          + " seems to happen here.\n");
        return 0;
    }

    tell_room(this_object(),
        "A spirit of the dead materializes out of the cell wall!\n");
    Ghost = clone_object(NPC_DIR + "ghost");
    Ghost->move(this_object());
    Ghost->command("wail");
    Ghost->command("kill " + plname);

    if (jailer = present("blukkmak", this_object()))
    {
        jailer->cell_arrival();
    }

#if LOG_ACTIVITY
        write_file(LOG_DIR + "ghost", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " summons a ghost in " + FILE_NAME(MASTER) + ".\n");
#endif

    return 1;
} /* summon_ghost */


/*
 * Function name:        add_dungeon_tells
 * Description  :        Provide room tells that are ubiquitous to
 *                       rooms in the dungeon
 *
 * Can be masked if these room tells are not desired for a given room.
 */
public void
add_dungeon_tells()
{
    add_tell("A loud moan sounds right behind you.\n");
    add_tell("A muffled, insane giggling seems to come from all"
      + " the walls at once.\n");
    add_tell("You hear a sudden heart-broken sobbing coming from"
      + " right next to you.\n");
    add_tell("An anguished voice mutters: Please ... please ...\n");
    add_tell("You feel a light touch on your shoulder, and when"
      + " you turn to look, what appears to be a face fades into"
      + " nothingness.\n");
    add_tell("Some of the refuse on the floor shifts suddenly, seemingly"
      + " of its own accord.\n");
    add_tell("A low, ragged breathing comes suddenly from the corner"
      + " of the cell.\n");
    add_tell("You suddenly sense the presence of someone right beside"
      + " you, but no one is there.\n");
} /* add_dungeon_tells */


/*
 * Function name:        search_cell
 * Description  :        see if the player finds something in the cell
 *                       following a search
 * Returns      :        string - the message
 */
public string
search_cell()
{
    return "After a thorough search, you find what appears to be a loose"
      + " stone in the corner of the room. Pulling it away from the"
      + " wall reveals a small hole dug into the dirt leading into"
      + " darkness. Someone could probably <escape> through that hole"
      + " if they needed to.\n";
} /* search_cell */


/*
 * Function name:        reset_room
 * Description  :        Upon reset, make sure the room has a trainer.
 */
public void
reset_room()
{
    if (sizeof(filter(all_inventory(this_object()), interactive)))
    {
        return;
    }

    bring_prisoner();
} /* reset_room */


/*
 * Function name:        bring_prisoner
 * Description  :        Bring a random prisoner to this cell
 */
public void
bring_prisoner()
{
    if (Cell_Empty ||
        objectp(Prisoner))
    {
        return;
    }

    Prisoner = clone_object(NPC_DIR + "prisoner");
    Prisoner->move_living("down", this_object());
} /* bring_prisoner */


/*
 * Function name:        do_escape
 * Description  :        allow players to escape if they get trapped
 *                       in one of the jail cells.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_escape(string arg)
{
    object  tunnel;

    if (strlen(arg) &&
        !parse_command(arg, ({}),
            "[in] [into] [the] [small] [dirt] [hole] [in] [the] [dirt]"))
    {
        notify_fail("If you want to <escape> just say so. No need to"
          + " confuse things.\n");
        return 0;
    }

    tunnel = clone_object(ROOMS_DIR + "escape_route");

    write("Getting down on your hands and knees, you remove the stone"
      + " and crawl into the hole.\n");
    this_player()->move_living("M", tunnel, 1, 1);

    tell_room(this_object(), "You hear some scuffling sounds in the"
      + " corner, and when you turn to look what it is, you notice"
      + " that " + QTNAME(this_player()) + " is gone!\n");

    return 1;
} /* do_escape */


/*
 * Function name:        do_escape2
 * Description  :        allow players to escape if they get trapped
 *                       in one of the jail cells.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_escape2(string arg)
{
    object  tunnel;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
            "[in] [into] [the] [small] [dirt] 'hole' [in] [the] [dirt]"
          + " [wall]"))
    {
        notify_fail("If you want to <escape> just say so. No need to"
          + " confuse things.\n");
        return 0;
    }

    tunnel = clone_object(ROOMS_DIR + "escape_route");

    write("Getting down on your hands and knees, you remove the stone"
      + " and crawl into the hole.\n");
    this_player()->move_living("M", tunnel, 1, 1);

    tell_room(this_object(), "You hear some scuffling sounds in the"
      + " corner, and when you turn to look what it is, you notice"
      + " that " + QTNAME(this_player()) + " is gone!\n");

    return 1;
} /* do_escape2 */