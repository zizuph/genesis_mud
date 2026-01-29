/*
 *  /d/Sparkle/area/tutorial/town/street_6.c
 *
 *  This road heads through a grove of trees just north
 *  of Greenhollow. It teaches about startlocations.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    30  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public string      desc(string arg);
public string      describe();
public int         check_exit(string race);
public string      which_room();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in a grove of trees just north of Greenhollow");
    set_long(describe);

    add_item( ({ "grove", "tree", "trees", "grove of trees" }),
        &desc("grove"));
    add_item( ({ "leaves", "leaf", "breeze" }), &desc("leaves"));
    add_item( ({ "town", "south", "town of greenhollow",
                 "greenhollow" }), &desc("town"));

    add_road_items();
    add_outdoor_items();

    prevent_attacks();
    reset_room();

    add_exit(which_room, "north");
    add_exit("human_start", "northeast", &check_exit("human"), 1, 1);
    add_exit("elf_start", "east", &check_exit("elf"), 1, 1);
    add_exit("hobbit_start", "southeast", &check_exit("hobbit"), 1, 1);
    add_exit("street_5", "south", &check_exit("town"), 1, 0);
    add_exit("goblin_start", "southwest", &check_exit("goblin"), 1, 1);
    add_exit("gnome_start", "west", &check_exit("gnome"), 1, 1);
    add_exit("dwarf_start", "northwest", &check_exit("dwarf"), 1, 1);
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Need a hint? Sure ... north and south are obvious exits here,"
      + " but there is another direction you can travel. Look at the"
      + " description of the room again, and you should notice that you"
      + " feel called to go a certain way. Travel that direction to"
      + " find your racial startlocation.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        desc
 * Description  :        describe various things
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - the description
 */
public string
desc(string arg)
{
    switch(arg)
    {
        case "grove":
            if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                return "The entire grove is on fire. You suspect you could"
                  + " dash through the trees to the north to make an"
                  + " escape.\n";
            }
            else
            {
                return "Trees surround you here, bordering the road on all"
                  + " sides. Leaves from the trees rustle every so often"
                  + " when the breeze comes through the grove.\n";
            }
            break;
        case "leaves":
            if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                return "The leaves of the trees are almost entirely burned"
                  + " away. The few that remain crackle and burn, growing"
                  + " black with every passing second.\n";
            }
            else
            {
                return "An occasional breeze blows through the leaves in"
                  + " the trees, creating a peaceful and relaxing"
                  + " ambiance.\n";
            }
            break;
        case "town":
            if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                return "The town of Greenhollow burns to the south! You"
                  + " cannot pass that way.\n";
            }
            else
            {
                return "The town of Greenhollow lies to the south of this"
                  + " grove.\n";
            }
            break;
    }

    return 0; /* shouldn't ever happen */
} /* desc */


/* 
 * Function name:        describe
 * Description  :        provide a direction based on race
 * Returns      :        string - the appropriate word
 */
public string
describe()
{
    string   dir;

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "The trees are ablaze! To the south, you hear the screams"
          + " and cries of the townsfolk as they burn and die in their"
          + " hopelessly ruined town. Even though this is your own"
          + " handiwork, you can't help but fear for your life here"
          + " among the flames. North is your only escape!\n\n";
    }

    switch (this_player()->query_race())
    {
        case "human":
            dir = "northeast";
            break;
        case "elf":
            dir = "east";
            break;
        case "hobbit":
            dir = "southeast";
            break;
        case "goblin":
            dir = "southwest";
            break;
        case "gnome":
            dir = "west";
            break;
        case "dwarf":
            dir = "northwest";
            break;
    }

    return("The road passes through a grove of trees here, heading"
      + " north and south. You feel a strange sense of longing here,"
      + " as if you are being called to head " + dir
      + " through the trees.\n\n");
} /* describe */


/*
 * Function name:        check_exit
 * Description  :        prevent the wrong race from entering a room
 * Arguments    :        string race - the race to allow
 * Returns      :        1 - don't allow, 0 - allow
 */
public int
check_exit(string race)
{
    string   msg;

    if (this_player()->query_race() == race)
    {
        return 0;
    }

    switch(race)
    {
        case "town":
            if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                msg = "The only escape is to the north! Run!\n";
            }
            else
            {
                return 0;
            }
            break;
        case "human":
            msg = "You smell humans in that direction, and decide it"
                + " best not to go that way.\n";
            break;
        case "elf":
            msg = "Elvish magic prevents you from going that way.\n";
            break;
        case "hobbit":
            msg = "You hear hobbit laughter in that direction, and"
                + " decide not to go that way.\n";
            break;
        case "goblin":
            msg = "You smell goblins in that direction and decide not"
                + " to go that way.\n";
            break;
        case "gnome":
            msg = "A mechanized sign swings out from behind a tree that"
                + " reads: GnOmES oNLy!!\nIt seems you cannot go that"
                + " way.\n";
            break;
        case "dwarf":
            msg = "You hear the sound of dwarves in that direction. You"
                + " decide not to go that way.\n";
            break;
    }

    this_player()->catch_msg(msg);

    if (this_player()->query_wiz_level())
    {
        write("Oh well, you're a wizard, so we'll let you through.\n");
        return 0;
    }
    
    return 1;
} /* check_exit */


/*
 * Function name:        which_room
 * Description  :        define which room the exit leads to
 * Returns      :        string - the filename
 */
public string
which_room()
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return FARM_DIR + "crossroad_1";
    }

    return TOWN_DIR + "street_7";
} /* which_room */
