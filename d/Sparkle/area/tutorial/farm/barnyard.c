/*
 *  /d/Sparkle/area/tutorial/farm/barnyard.c
 *
 *  This is the barnyard belonging to Farmer Brown north of Greenhollow.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();
public int         check_exit(string exit);
public string      describe(string arg);
public int         mess_with_door(string arg);
public void        init();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in a barnyard south of some fields");
    set_long(&describe("long"));

    add_outdoor_items();

    add_item( ({ "here", "area", "yard", "barnyard", "grounds", "farm",
                 "farmer browns farm", "farmer brown's farm" }),
        &describe("long"));
    add_item( ({ "house", "home", "merry home", "farmhouse",
                 "east", "home of farmer brown", "rubble",
                 "merry house", "merry home", "little house",
                 "little home", "merry little house",
                 "merry little farmhouse", "little farmhouse",
                 "burned home", "burned house", "burned farmhouse" }),
        &describe("house"));
    add_item( ({ "barn", "large barn", "husk", "burned-out husk",
                 "burned barn", "structure", "frame", "ruined frame",
                 "timbers", "blackened timbers", "mighty structure",
                 "huge barn", "west" }), &describe("barn"));
    add_item( ({ "livestock", "animal", "animals", "dead animals",
                 "dead livestock", "chicken", "dead chicken",
                 "chickens", "dead chickens", "rooster",
                 "dead rooster", "roosters", "dead roosters",
                 "cow", "dead cow", "cows", "dead cows", "bodies",
                 "body", "fence", "noisy livestock" }),
        &describe("livestock"));
    add_item( ({ "door", "doors", "barn door", "barn doors" }),
        &describe("doors"));
    add_item( ({ "field", "fields", "ruined fields", "north" }),
        "North of the barnyard, the area opens up into wide fields"
      + " which expand for a good distance to the northwest.\n");
    add_item( ({ "path", "ground", "down", "track" }),
        "A track winds its way out of the yard travelling south toward"
      + " the crossroads.\n");
    add_item( ({ "crossroad", "crossroads" }),
        "The crossroads are too far away to see from here.\n");

    reset_room();

    add_exit("radish_patch1", "north");
    add_exit("house", "east", &check_exit("house"), 1, 0);
    add_exit("crossroad_2", "south");
    add_exit("barn", "west", &check_exit("barn"), 1, 0);
} /* create_silverdell */


/*
 * Function name:        check_exit
 * Description  :        only allow the player into the barn if they
 *                       have rescued Farmer Brown.
 * Arguments    :        string exit - which exit are we checking?
 * Returns      :        int 1 - prevent, 0 - allow
 */
public int
check_exit(string exit)
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(exit)
        {
            case "house":
                write("The farmer's house has been burned to the"
                  + " ground. There is nothing left to enter.\n");
                return 1;
                break;
            case "barn":
                write("The barn is nothing more than a burned-out"
                  + " shell that looks as if it could topple over at any"
                  + " moment. It is probably safest to remain outside.\n");
                return 1;
                break;
        }
    }

    if (exit == "house")
    {
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        return 0;
    }

    write("The barn doors are closed and locked.\n");
    return 1;
} /* check_exit */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(arg)
        {
            case "long":
                return "Something horrible has happened here. This once"
                  + " peaceful barnyard has been laid to waste. Both the"
                  + " barn and the farmer's house have been burned, and"
                  + " dead livestock litter the ash-soaked grounds. North,"
                  + " it looks as if the fields are in ruin.\n\n";
                break;
            case "barn":
                return "The barn is nothing more than a burned-out husk"
                  + " of its former self. Blackened timbers sag from the"
                  + " ruined frame, suggesting that the entire structure"
                  + " could collapse at any moment.\n";
                break;
            case "house":
                return "Someone has taken a torch to the home of Farmer"
                  + " and Mrs. Brown, burning it to the ground. You"
                  + " wonder with a smile if their charred and blackened"
                  + " bodies lie beneath all the rubble.\n";
                break;
            case "livestock":
                return "Someone or something has come through and killed"
                  + " all of the livestock. Their bodies litter the"
                  + " barnyard, filling the entire area with a hideous"
                  + " stench.\n";
                break;
            case "doors":
                return "The barn doors no longer exist. They have been"
                  + " destroyed by fire.\n";
                break;
        }
    }

    switch(arg)
    {
        case "long":
            return "You stand in a peaceful barnyard where a quiet wind"
              + " blows dust among noisy livestock. A large barn presides"
              + " over the yard to the west, overlooking the home of the"
              + " farmer and his wife just east of here. Fields are"
              + " visible to the north, and a path leads south back toward"
              + " the crossroads.\n\n";
            break;
        case "barn":
            return "A huge barn rises above you just west of the yard."
              + " It is a mighty structure which must have been built"
              + " many generations ago.\n";
            break;
        case "house":
            return "The home of the farmer and his wife looks on to the"
              + " barnyard from the east. It is a merry little farmhouse,"
              + " which looks lovingly cared for by able hands.\n";
            break;
        case "livestock":
            return "Many chickens and a few roosters roam the barnyard,"
              + " pecking and scratching at the earth. Beyond a fence,"
              + " numerous cows move slowly about, lowing mournfully.\n";
            break;
        case "doors":
            if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
            {
                return "The barn doors stand open.\n";
            }
            else
            {
                return "The barn doors appear to be shut and locked.\n";
            }
            break;
    }
} /* describe */


/*
 * Function name:        mess_with_door
 * Description  :        allow the player to fuss with the barn door
 * Arguments    :        string arg - the argument that followed the verb
 * Returns      :        string 1 or 0 - some fail message or text
 */
public int
mess_with_door(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (query_verb() == "enter")
    {
        notify_fail("The <enter> command does indeed work sometimes in"
          + " Genesis. However, here you can just use direction commands"
          + " to try to enter the barn or the farmhouse.\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [large] [barn] 'door' / 'doors' / 'lock' [with] [the]"
      + " [key]"))
    {
        return 0; /* can't figure out the syntax */
    }

    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        switch(query_verb())
        {
            case "knock":
            case "pound":
            case "pick":
            case "push":
            case "pull":
            case "break":
            case "unlock":
            case "open":
                write("The barn doors are wide open!\n");
                return 1;
                break;
            case "close":
            case "shut":
                write("Farmer Brown must be stronger than you. You"
                  + " can't seem to budge them!\n");
                return 1;
                break;
            case "lock":
                write("You don't have the right key to operate the"
                  + " lock.\n");
                return 1;
                break;
        }
    }

    switch(query_verb())
    {
        case "knock":
        case "pound":
        case "push":
        case "pull":
            write("You " + query_verb() + " on the barn doors with all"
              + " of your might, but to no avail.\n");
            return 1;
            break;
        case "break":
            write("You aren't nearly strong enough for that.\n");
            return 1;
            break;
        case "pick":
            write("Your thief skills aren't adept enough for that.\n");
            return 1;
            break;
        case "lock":
        case "unlock":
            write("You do not possess the proper key for that.\n");
            return 1;
            break;
        case "close":
        case "shut":
            write("The barn doors are already closed.\n");
            return 1;
            break;
        case "open":
            write("The barn doors are locked.\n");
            return 1;
            break;
    }

    return 0; /* should never happen, but just in case. */
} /* mess_with_door */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mess_with_door, "knock");
    add_action(mess_with_door, "pound");
    add_action(mess_with_door, "push");
    add_action(mess_with_door, "pull");
    add_action(mess_with_door, "pick");
    add_action(mess_with_door, "break");
    add_action(mess_with_door, "unlock");
    add_action(mess_with_door, "lock");
    add_action(mess_with_door, "open");
    add_action(mess_with_door, "close");
    add_action(mess_with_door, "shut");
    add_action(mess_with_door, "enter");
} /* init */




