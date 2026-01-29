/*
 *  /d/Sparkle/area/tutorial/farm/crop_room.c
 *
 *  This is the standard file for the rooms in Silverdell that are
 *  part of the farm where players can pull up crops.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *  Updated July 29, 2016 by Gronkas: replacing obj->short()
 *  by LANG_THESHORT(obj)
 */
#pragma strict_types
#pragma no_clone
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit SD_ROOM;
inherit LIB_DIR + "quest_reward";

#include <language.h>      /* for LANG_PWORD    */
#include <ss_types.h>      /* for SS_AWARENESS  */
#include <macros.h>        /* for QCTNAME()     */
#include <stdproperties.h> /* for OBJ_M_NO_DROP */

/* Definitions */
#define            NEEDED_SKILL (this_player()->query_skill( \
                                 SS_AWARENESS) > 9)

/* Global Variables */
public string      Crop_Type   = "";  /* what crop is planted? */
public string      Location    = "";  /* what part of the field ? */
public int         Rabbit_Hole = 0;   /* is there a rabbit hole here? */
public string      Extraline   = " "; /* added material for room desc */

/* Prototypes */
public void        create_crop_room();
nomask void        create_silverdell();
public void        plant_crop(string type);
public void        set_field_location(string arg);
public string      describe_short();
public string      describe_long();
public string      awareness_message(object player);
public void        add_field_items();
public string      exa_crops();
public int         pick_crop(string arg);
public void        init();
public void        add_rabbit_hole();
public string      exa_rabbit_hole();
public int         throw_stuff(string arg);
public void        carrot_effect(object player, int enchanted);
public int         enter_hole(string arg);
public int         be_farmer(string arg);
public void        clone_bunny(int number, string type);
public int         check_exit();

public void        set_extraline(string s) { Extraline += s; }


/*
 * Function name:        create_crop_room
 * Description  :        dummy file for inheriting rooms
 */
public void
create_crop_room()
{
} /* create_crop_room */


/*
 * Function name:        create_silverdell
 * Description  :        set up the room with area presets
 */
nomask void
create_silverdell()
{
    //By default, these rooms are instanced.
    instance_entrance = 0;

    create_crop_room();
    add_outdoor_items();

    setuid();
    seteuid(getuid());
} /* create_silverdell */


/*
 * Function name:        plant_crop
 * Description  :        set up the room with a certain type of crop
 * Arguments    :        string type - the type of crop
 */
public void
plant_crop(string type)
{
    Crop_Type = type;

    set_short(describe_short);
    set_long(describe_long);
} /* plant_crop */


/*
 * Function name:        set_field_location
 * Description  :        set a location dependant description for the
 *                       variable Location.
 * Arguments    :        string arg - the location
 */
public void
set_field_location(string arg)
{
    string txt;

    switch(arg)
    {
        case "n":
            Location = "at the northern edge of";
            break;
        case "ne":
            Location = "at the northeastern edge of";
            break;
        case "e":
            Location = "at the eastern edge of";
            break;
        case "se":
            Location = "at the southeastern edge of";
            break;
        case "s":
            Location = "at the southern edge of";
            break;
        case "sw":
            Location = "at the southwestern edge of";
            break;
        case "w":
            Location = "at the western edge of";
            break;
        case "nw":
            Location = "at the northwestern edge of";
            break;
        case "mid":
            Location = "toward the middle of";
            break;
        default:
            Location = "somewhere in";
            break;
    }
} /* set_field_location */


/*
 * Function name:        describe_short
 * Description  :        provide a crop and status-dependant short
 *                       description for the room.
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    string  txt;
    string  condition = one_of_list( ({
                            "humble ",
                            "simple ",
                            "meager ",
                            "struggling " }) );
    string  field     = " a large field";

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        condition = one_of_list( ({
            "devastated ",
            "filthy ",
            "defiled ",
            "swampy " }) );
        field     = " a ruined field";
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        condition = one_of_list( ({
            "vibrant ",
            "healthy ",
            "beautiful ",
            "rich and full ", }) );
    }

    if (Crop_Type == "garlic")
    {
        if (!CHECK_TUTORIAL_BIT(SAVIOR_BIT) &&
            !CHECK_TUTORIAL_BIT(DESTROYER_BIT) &&
            !CHECK_TUTORIAL_BIT(GARLIC_BIT))
        {
            return "an empty patch of soil " + Location + field;
        }
    }

    return "a " + condition + Crop_Type + " patch " + Location + field;
} /* describe_short */


/*
 * Function name:        describe_long
 * Description  :        provide a crop and status-dependant long
 *                       description for the room
 */
public string
describe_long()
{
    string  txt = "You are standing in " + short(this_player()) + ". ";

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        switch(random(2))
        {
            case 0:
                txt += "A cool and pleasant breeze is blowing across"
                  + " the farm, lifting the smell of the healthy earth"
                  + " to your nose. The crops here appear to be doing"
                  + " extremely well.";
                break;
            case 1:
                txt += "The lush rows of crops here are a testament to"
                  + " the health of the land which has recently returned"
                  + " in full glory.";
                break;
            default:
            case 2:
                txt += "Rich and loamy soil is mounded beneath the"
                  + " crops planted here. The smell of the earth is"
                  + " wonderful and healthy, thanks to you.";
        }
    }
    else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        switch(random(2))
        {
            case 0:
                txt += "A foul stench blows across this wasted land that"
                  + " was once a promising field. The pathetic and"
                  + " twisted remains of crops sag in the soil.";
                break;
            case 1:
                txt += "Foul-smelling crops rot where they are planted"
                  + " here. The fields have been completely destroyed"
                  + " by the powers of Baron von Krolock.";
                break;
            default:
            case 2:
                txt += "There is nothing here but rot and decay, a"
                  + " testament to your choice to work for evil rather"
                  + " than good.";
        }
    }
    else
    {
        if (Crop_Type == "garlic" && !CHECK_TUTORIAL_BIT(GARLIC_BIT))
        {
            txt += "Oddly, this area seems bare of any crops whatsoever."
              + " Perhaps something has happened to them.";
        }
        else
        {
            switch(random(2))
            {
                case 0:
                    txt += "These fields seem to be struggling somewhat."
                      + " Rows of crops have been carefully planted in"
                      + " the soil, where the farmer hopes to be able to"
                      + " harvest them when they are ready.";
                    break;
                case 1:
                    txt += "A cold breeze blows across the fields,"
                      + " sending dust against the crops which are" 
                      + " struggling to grow in the soil.";
                    break;
                default:
                case 2:
                    txt += "The soil of these fields does not appear to"
                      + " be nourishing the crops to full health."
                      + " Nonetheless, rows of " + Crop_Type + " are"
                      + " visible poking out of the dirt.";
            } /* switch(random(2)) */
        } /* else */
    } /* else */

    if (Rabbit_Hole)
    {
        if (NEEDED_SKILL)
        {
            txt += " Your keen eyes notice a large rabbit hole dug in"
              + " the ground here!";
        }
        else
        {
            set_alarm(2.0, 0.0, &awareness_message(this_player()));
        }
    }

    return txt + Extraline + "\n\n";
} /* describe_long */


/*
 * Function name:        awareness_message
 * Description  :        tell the player they need to train some in
 *                       awareness (this is a tutorial, after all!)
 * Arguments    :        object player - the player
 */
public void
awareness_message(object player)
{
    player->catch_tell("\n\nYou suddenly get the feeling you are missing"
      + " something. Perhaps if you trained your awareness skill a bit"
      + " more you might be able to notice something important"
      + " here.\n\n");
} /* awareness_message */


/*
 * Function name:        add_field_items
 * Description  :        add add_items appropriate for the fields
 */
public void
add_field_items()
{
    add_item( ({ "crop", "crops", Crop_Type, Crop_Type + "s",
                 "plant", "plants", "row", "rows", "row of crops",
                 "row of " + Crop_Type, "remains", "rot", "decay",
                 "foul crops", "foul-smelling crops",
                 "rows of " + Crop_Type, "ground", "down",
                 "stem", "stems", Crop_Type + " stem",
                 Crop_Type + " stems", "field", "large field",
                 "ruined field", "patch",
                 Crop_Type + " patch" }), exa_crops);
    add_item( ({ "farm", "here", "area", }), long);
} /* add_field_items */


/*
 * Function name:        exa_crops
 * Description  :        provide a status and crop-dependant description
 *                       of the crops for the add_item
 * Returns      :        string - the description
 */
public string
exa_crops()
{
    string  txt;

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        txt = "You see many beautiful " + Crop_Type + " stems sticking"
          + " out of the fertile ground where they have been planted.";
    }
    else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        txt = "Twisted and rotting " + Crop_Type + " stems lie coiled"
          + " on the foul soil here.";
    }
    else
    {
        if (Crop_Type == "garlic" && !CHECK_TUTORIAL_BIT(GARLIC_BIT))
        {
            return "You see no crops here. It looks as if something has"
              + " eaten them all.\n";
        }

        txt = "You see a number of " + Crop_Type + " stems sticking"
          + " out of the soil.";
    }

    return txt + " You can try to <pick " + Crop_Type + "> if you"
      + " wish.\n";
} /* exa_crops */


/*
 * Function name:        pick_crop
 * Description  :        allow players to try to pick a crop
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
pick_crop(string arg)
{
    object  crop;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [a] '" + Crop_Type + "' / 'crop' / 'crops' / '"
      + LANG_PWORD(Crop_Type) + "' [stem] [from]"
      + " [the] [soil] [ground] [field] [earth]"))
    {
        return 0; /* bad syntax */
    }

    if (present("_tutorial_" + Crop_Type, deep_inventory(this_player())
      + ({ this_player() }) ))
    {
        write("You've already picked a " + Crop_Type + ". No need"
          + " to get another.\n");
        return 1; /* to avoid conflicts with thief "pick" */
    }

    if (Crop_Type == "garlic" && !CHECK_TUTORIAL_BIT(GARLIC_BIT) && 
        !CHECK_TUTORIAL_BIT(SAVIOR_BIT) && !CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        write(exa_crops());
        return 1;
    }

    crop = clone_object(OBJ_DIR + "crop_" + Crop_Type);
    crop->set_picked_by(this_player()->query_real_name());

    if (!crop->move(this_player()))
    {
        write("You dig a " + Crop_Type + " out of the field.\n");
        tell_room(this_object(), QCTNAME(this_player()) + " digs a "
          + Crop_Type + " out of the ground.\n", this_player());
        return 1;
    }

    /* move to player failed ... drop it */
    crop->remove_object();
    write("You dig a " + Crop_Type + " out of the field, but you"
      + " are carrying too much to hold it so you put it back in the"
      + " ground.\n");
    return 1;
} /* pick_crop */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(pick_crop, "harvest");
    add_action(pick_crop, "reap");
    add_action(pick_crop, "pull");
    add_action(pick_crop, "get");
    add_action(pick_crop, "pick");
    add_action(pick_crop, "dig");
    add_action(be_farmer, "farm");
    add_action(be_farmer, "plant");
    add_action(be_farmer, "sow");
    add_action(be_farmer, "plow");
    add_action(be_farmer, "till");
} /* init */


/*
 * Function name:        add_rabbit_hole
 * Description  :        create a rabbit hole in the ground here
 */
public void
add_rabbit_hole()
{
    Rabbit_Hole = 1;

    add_item( ({ "hole", "hole in the ground", "large hole",
                 "large hole in the ground", "dark hole",
                 "rabbit hole", "large rabbit hole" }), exa_rabbit_hole);
} /* add_rabbit_hole */


/*
 * Function name:        exa_rabbit_hole
 * Description  :        provide a bit-dependant description of the hole
 * Returns      :        string arg - the description
 */
public string
exa_rabbit_hole()
{
    if (!NEEDED_SKILL)
    {
        return "You find no such thing here.\n";
    }

    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        return "You look down the rabbit hole. There is nothing but"
          + " silent darkness down there. You get the feeling your"
          + " carrot trick got the job done.\n";
    }

    return "This looks like a very large and disturbing version of a"
      + " rabbit hole. Long claws appear to have gouged away dirt from"
      + " the entrance and thrown it to the sides. You hear loud"
      + " breathing, and an occasional growl coming from the hole. You"
      + " wonder what might happen if you threw something down there.\n";
} /* exa_rabbit_hole */


/*
 * Function name:        throw_stuff
 * Description  :        allow players to throw stuff down the rabbit
 *                       hole.
 * Arguments    :        string arg - the argument to the verb 'throw'
 * Returns      :        1 - success, 0 - failure
 */
public int
throw_stuff(string arg)
{
    object  obj;
    mixed   fail;

    if (!NEEDED_SKILL)
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "%o 'in' / 'into' / 'down' [the] [large] [dark] [rabbit]"
      + " 'hole' [in] [the] [ground]", obj))
    {
        notify_fail("What do you want to " + query_verb() + " where?\n");
        return 0; /* give them a bit of syntax help */
    }

    if (fail = obj->query_prop(OBJ_M_NO_DROP))
    {
        if (!stringp(fail))
        {
            fail = "You cannot throw " + LANG_THESHORT(obj) + " away.\n";
        }

        notify_fail(fail);
        return 0;
    }

    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        write("The hole seems to be empty. No point in throwing things"
          + " down it anymore.\n");
        return 1;
    }

    if (present("_tutorial_bunny", this_object()))
    {
        write("As you approach the hole, the rabbit leaps in front"
          + " of you, growling ferociously! Looks like you'll"
          + " have to get rid of all the rabbits first.\n");
        return 1;
    }

    if (!obj->id("_tutorial_carrot"))
    {
        write("You throw " + LANG_THESHORT(obj) + " down the rabbit hole,"
          + " and step back as you hear all sorts of thrashing around"
          + " down there! You hear a few loud sniffs, and then a"
          + " disgusted snort as " +LANG_THESHORT(obj) + " comes sailing"
          + " back out of the hole and hits you right in the forehead."
          + " It seems the rabbit doesn't take much pleasure in"
          + " munching on " + obj->plural_short() + ".\n");
        write("You pick " + LANG_THESHORT(obj) + " up off the ground.\n");
        return 1;
    }

    write("You throw " + LANG_THESHORT(obj) + " down the rabbit hole,"
      + " and step back as all hell breaks loose in the hole. You"
      + " hear a bunch of wild thrashing, followed by some loud"
      + " sniffing. Finally, you hear the sounds of something munching"
      + " and crunching on the carrot.\n");

    set_alarm(2.0, 0.0, &carrot_effect(this_player(),
              obj->query_enchanted()));

    obj->remove_object();
    return 1;
} /* throw_stuff */


/*
 * Function name:        carrot_effect
 * Description  :        tell the player what effect the carrot
 *                       had
 * Arguments    :        object player - the player
 *                       int enchanted - true if carrot is enchanted
 */
public void
carrot_effect(object player, int enchanted)
{
    if (!enchanted)
    {
        player->catch_tell("As the munching subsides, you hear a"
          + " sudden loud belch followed by a deafening roar from the"
          + " hole. It seems the beast likes carrots!\n");
        return;
    }

    player->catch_tell("As the munching continues, something strange"
      + " occurs. Dark black mist pours slowly from the rabbit hole"
      + " and drifts across the field. Looking around, you see that"
      + " the mist is transforming every rabbit it touches, removing"
      + " their accursed state. As the mist clears, you hear a scuffling"
      + " sound, and watch as a large white mother rabbit crawls out"
      + " of the hole and scampers west into the brush.\n");

    set_this_player(player);
    SET_TUTORIAL_BIT(BUNNY_BIT);
    give_reward(player, TUTORIAL_BUNNY_GROUP, TUTORIAL_BUNNY_BIT,
                TUTORIAL_BUNNY_EXP, "Tutorial Bunny");
    return;
} /* carrot_effect */


/*
 * Function name:        enter_hole
 * Description  :        allow players to try out "enter hole", etc
 * Arguments    :        what the player typed
 * Returns      :        1 - syntax understood, 0 - otherwise
 */
public int
enter_hole(string arg)
{
    if (!NEEDED_SKILL)
    {
        if (arg != "down")
        {
            return 0;
        }
        else
        {
            write("There is no obvious exit down.\n");
            return 1;
        }
    }

    if (arg != "down")
    {
        if (!strlen(arg))
        {
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
        }

        if (!parse_command(arg, ({}),
            "[in] [to] [into] [down] [the] [large] [dark] [rabbit]"
          + " 'hole' [in] [the] [ground]"))
        {
            return 0; /* bad syntax */
        }
    }

    write("Even though it is unusually large, this rabbit hole"
      + " is not big enough for "
      + LANG_ADDART(this_player()->query_race()) + " like you.\n");
    return 1;
} /* enter_hole */


/*
 * Function name:        be_farmer
 * Description  :        message to print for players who try to be a
 *                       farmer
 * Arguments    :        string arg - the argument following the verb
 * Returns      :        0 - it is always a fail.
 */
public int
be_farmer(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'potato' / 'carrot' / 'garlic' / 'turnip' / 'radish'"
      + " / 'crop' / 'field' / 'soil' / 'earth' / 'farm' / 'patch'"))
    {
        return 0; /* bad syntax */
    }

    notify_fail("These aren't your fields to " + query_verb()
      + ". Better to leave that sort of thing to Farmer Brown.\n");
    return 0;
} /* be_farmer */


/*
 * Function name:        clone_bunny
 * Description  :        bring the right amount of bunnies into
 *                       this room
 * Arguments    :        int number - the amount of clones we want,
 *                       string type- the type of bunny
 */
public void
clone_bunny(int number, string type)
{
    int     i, n;
    object *bunny = allocate(number + random(3));

    if (present("_tutorial_bunny", this_object()))
    {
        return;
    }

    for (i = 0, n = sizeof(bunny); i < n; i++)
    {
        if (!objectp(bunny[i]))
        {
            bunny[i] = clone_object(NPC_DIR + "bunny");
            bunny[i]->config_bunny(type);
            bunny[i]->set_restrain_path(FARM_DIR);
            bunny[i]->move_living("from the void", this_object());
        }
    }
    return;
} /* clone_bunny */


/*
 * Function name:        check_exit
 * Description  :        the bunnies will block players that have not
 *                       yet completed the bunny quest from travelling
 *                       toward the rabbit hole.
 * Returns      :        int 1 - blocked, 0 - allow
 */
public int
check_exit()
{
    string  txt = "";
    object  bunny;

    if (objectp(bunny = present("_tutorial_bunny", this_object())))
    {
        if (!CHECK_TUTORIAL_BIT(BUNNY_BIT))
        {
            if (CAN_SEE(bunny, this_player()))
            {
                txt = "Snarling savagely, a bunny dashes in front of you."
                  + " It seems these rabbits don't want you heading that"
                  + " way. Looks like you'll have to kill the little"
                  + " vermin before travelling onward.\n";
            }
            else
            {
                write("With your thief skills, you sneak past the"
                  + " vermin and make your way onward.\n");
                return 0; /* let them pass */
            }

            if (this_player()->query_wiz_level())
            {
                write(txt + "Since you are a wizard, that doesn't"
                  + " matter.\n");
                return 0; /* let wizards pass, regardless */
            }

            write(txt);
            return 1;
        }
    }

    return 0; /* they can pass */
} /* check_exit */



