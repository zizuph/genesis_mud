/*
 * Lounge Room of the Elemental Worshippers - 2nd Floor
 * 
 * Created by Petros, March 2014
 * Fixed typo - Jaacar, May 2016
 */

#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit TEMPLE_ROOM_BASE;
inherit "/lib/guild_support";
inherit "/d/Sparkle/area/city/lib/random_noise";

// Defines
#define EW_LOUNGE_TAPESTRY "_player_view_ew_tapestry"
#define SITTING_ON_COUCH  "_sitting_on_couch"

// Prototypes

// Global Variables
int bBurnerLit = 0;
int bWindowOpen = 0;
int bFireplaceLit = 1;

public void
create_temple_room()
{
    setuid();
    seteuid(getuid());
    set_short("Elemental Worshipper Lounge");
    set_long("@@describe_long");

    try_item( ({ "spacious chamber", "chamber", "second floor", "temple" }),
              "This looks like a great lounge for the Worshippers of this Temple "
              + "to relax in. Whether it is the couches, the mats, the tables, "
              + "or the tapestries, everything gives a sense of peace.\n");
    try_item( ({ "couches", "couch", "pair of couches" }),
              "These couches look rather comfortable. It's hard to tell what "
              + "type of material they are made out of. Why don't you try to "
              + "<sit> in one of them and find out?\n");
    try_item( ({ "table", "small table", "tables", "small tables", "south" }),
              "These small tables are not meant to hold much. On top of one, "
              + "you see an incense burner. On top of another one, you see "
              + "a water bowl.\n");
    try_item( ({ "rack","small rack"}),"It is a small wooden rack hanging "+
        "on the wall. Hanging from the rack are several "+
        "cloaks.\n");
    try_item( ({ "window", "windows", "view" }), "@@window_desc@@");
    try_item( ({ "fireplace", "center" }), "@@fireplace_desc@@");
    try_item( ({ "burner", "incense burner", "burners", "incense burners" }),
              "@@burner_desc@@");
    try_item( ({ "bowl", "waterbowl", "water bowl" }),
              "@@waterbowl_desc@@");
    try_item( ({"tapestries", "tapestry"}),
              "Which tapestry do you want to examine? There are six of them.\n");
    try_item( ({ "first tapestry" }), "@@first_tapestry_desc@@");
    try_item( ({ "second tapestry" }), "@@second_tapestry_desc@@");
    try_item( ({ "third tapestry" }), "@@third_tapestry_desc@@");
    try_item( ({ "fourth tapestry" }), "@@fourth_tapestry_desc@@");
    try_item( ({ "fifth tapestry" }), "@@fifth_tapestry_desc@@");
    try_item( ({ "sixth tapestry" }), "@@sixth_tapestry_desc@@");

    add_exit(ELEMENTALIST_TEMPLE + "stairwell2", "southeast", "@@check_sitting", 1); 
//    add_exit(ELEMENTALIST_TEMPLE + "worshipper_councilroom", "up", "@@check_council", 1, "@@check_council");
}

/*
 * Function:    check_council
 * Description: Used in add_exit to prevent players who are not on the Council from
 *              entering the room.
 * Returns:     1 if non-council, 0 otherwise.
 */
public int
check_council()
{
    notify_fail("What?\n");
    object player = this_player();
    return !GUILD_MANAGER->query_is_ew_council(player);
}

public void
init()
{
    ::init();
    init_guild_support();
    init_random_noise();

    add_action("do_sit", "sit");
    add_action("do_stand", "stand");
    add_action("do_light", "light");
    add_action("do_extinguish", "extinguish");
    add_action("do_drink", "drink");
    add_action("do_open", "open");
    add_action("do_close", "close");
    add_action("do_unhook","unhook");
    add_action("do_hook","hook");
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);

    ::leave_inv(ob, to);    
}

public void
notify_viewed_all_tapestries(object player)
{
    player->catch_tell(
        "Having studied the ancient tales of your "
        + "predecessors, you feel a Calm and Purpose descending over "
        + "you. You are here now honoring their Work and Serving the "
        + "Elementals as your predecessors did before you.\n");
}

public void
set_tapestry_prop(int index)
{
    int prop_value = this_player()->query_prop(EW_LOUNGE_TAPESTRY);
    int new_prop_value = prop_value | (1 << index);
    if (prop_value != new_prop_value)
    {
        this_player()->add_prop(EW_LOUNGE_TAPESTRY, new_prop_value);
        if (new_prop_value == 63)
        {
            set_alarm(0.1, 0.0, &notify_viewed_all_tapestries(this_player()));
        }
    }
}

public string
first_tapestry_desc()
{
    set_tapestry_prop(0);
    string description = 
        "This first tapestry depicts a pair of kind and noble looking "
        + "individuals. A man and woman, each clad in colourful robes with "
        + "symbols of the elements. The man visits a small village and "
        + "seems to be assisting with the birth of an infant. The woman "
        + "meanwhile visits the town hall and counsels the elders there.\n";
    return description;
}

public string
second_tapestry_desc()
{
    set_tapestry_prop(1);
    string description = 
        "In the second tapestry your gaze wanders across two massive "
        + "mountain tops. Perched on top of each mountain is a walled city. "
        + "Hordes of warriors are ascending each mountain. Far away from the "
        + "hordes, a massive eerie fog moves towards the conflict. It is "
        + "a certainty that the fog will engulf both cities entirely.\n";
    return description;
}

public string
third_tapestry_desc()
{
    set_tapestry_prop(2);
    string description = 
        "As you look upon the third tapestry you see a sun rising behind "
        + "a view of two island cities. Fresh sunlight reflects from the city "
        + "walls, creating a glimmering display of radiance. You briefly "
        + "notice grim black boats setting sail from the mainland in the "
        + "background.\n";
    return description;
}

public string
fourth_tapestry_desc()
{
    set_tapestry_prop(3);
    string description = 
        "The fourth tapestry depicts a group of people working vigorously to "
        + "convert a small empty cave into a magnificent shrine. The people all "
        + "carry symbols of Elemental Worship.\n";
    return description;
}

public string
fifth_tapestry_desc()
{
    set_tapestry_prop(4);
    string description = 
        "A group of people dressed in symbols of Elemental Worship make their "
        + "way towards a Temple in this fifth tapestry. At the entrance, a "
        + "shadowy figure awaits their arrival.\n";
    return description;
}

public string
sixth_tapestry_desc()
{
    set_tapestry_prop(5);
    string description = 
        "The sixth and final tapestry reveals an individual wearing a "
        + "multi-colored cloak lifting his arms in Worship. Five crystalline "
        + "pillars spring from the earth in response to his prayers.\n";
    return description;
}

public int
do_sit(string str)
{
    if ((!strlen(str)) && (str != "down") && (str != "on couch"))
    {
        notify_fail("Sit where? On the couch? <sit on couch>\n");
        return 0;
    }

    if (this_player()->query_prop(SITTING_ON_COUCH))
    {
        notify_fail("You are already sitting on the couch.\n");
        return 0;
    }

    this_player()->add_prop(SITTING_ON_COUCH, 1);
    write("You sit down on one of the couches. It is so comfortable "+
        "that you just do not want to <stand up>. You think "
          + "it's made out of fur.\n");
    say(QCTNAME(this_player()) + " sits down on one of the couches.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," is sitting on one of the couches");
    return 1;
}

public int
do_stand(string str)
{
    if ((!strlen(str)) && (str != "up"))
    {
        notify_fail("Stand what? Up? <stand up>\n");
        return 0;
    }

    if (!this_player()->query_prop(SITTING_ON_COUCH))
    {
        notify_fail("You are already standing.\n");
        return 0;
    }

    this_player()->remove_prop(SITTING_ON_COUCH);
    write("It takes every ounce of willpower that you have to stand "+
        "up from the amazingly comfortable couch.\n");
    say(QCTNAME(this_player()) + " stands up.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

public int
check_sitting()
{
    if (!this_player()->query_prop(SITTING_ON_COUCH))
    {
        return 0;
    }
    
    write("You attempt to leave but realize that you are still "+
        "sitting on the couch. You are quickly sucked back into "+
        "the most comfortable couch you have ever sat on.\n");
    say(QCTNAME(this_player()) + " attempts to leave while still sitting on "+
        "the couch but is quickly sucked back into it!\n");
    
    return 1;
}

public int
do_light(string arg)
{
    notify_fail("Light what? The fireplace or the burner\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg == "fireplace")
    {
        if (bFireplaceLit)
        {
            write("But the fireplace is already lit!\n");
            return 1;
        }
        else
        {
            write("You prepare the logs in the fireplace and set them ablaze. "
                  + "You are surprised by the immediate warmth that springs "
                  + "forth.\n");
            say(QCTNAME(this_player()) + " prepares the logs in the fireplace and "
                + "sets them ablaze. Warmth springs forth from the fireplace.\n");
            bFireplaceLit = 1;
        }
        return 1;
    }
    else if (arg == "burner" || arg == "incense burner")
    {
        if (bBurnerLit)
        {
            write("But the incense burner is already lit!\n");
            return 1;
        }
        else
        {
            write("You pack down the incense in the burner before lighting it. "
                  + "a light grey smoke pours forth, into your nostrils, smelling "
                  + "of fragrant herbs.\n");
            say(QCTNAME(this_player()) + " packs down the incense in the burner "
                + "before lighting it. The smell of herbs drifts about the room.\n");
            bBurnerLit = 1;
        }
        return 1;
    }

    return 0;
}

public int
do_extinguish(string arg) 
{
    notify_fail("Extinguish what? The fireplace or the burner\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg == "fireplace")
    {
        if (bFireplaceLit)
        {
            write("You take the water bowl and pour the water onto the flames "
                  + "of the fireplace. Water rushes forth, and you quickly "
                  + "extinguish the flames. With a great hiss, steam fills the "
                  + "room and you place the bowl back on the table. Surprisingly, "
                  + "the bowl looks as full as when you started.\n");
            say(QCTNAME(this_player()) + " takes the water bowl from the table "
                + "pours the water onto the flames of the fireplace. A large "
                + "amount of water pours forth from the bowl and, with a great "
                + "hiss, steam fills the room as the flames are extinguished.\n");
            bFireplaceLit = 0;
        }
        else
        {
            write("But the fireplace is already extinguished!\n");
            return 1;
        }
        return 1;
    }
    else if (arg == "burner" || arg == "incense burner")
    {
        if (bBurnerLit)
        {
            write("You extinguish the incense in the burner and the smoke fades away "
                  + "quickly. You notice that the smell of herbs still hangs lightly "
                  + "in the air.\n");
            say(QCTNAME(this_player()) + " extinguishes the incense in the burner and the "
                + "smoke quickly fades away. The smell of herbs still hangs lightly in "
                + "the air.\n");
            bBurnerLit = 0;
        }
        else
        {
            write("But the incense burner is already extinguished!\n");
            return 1;
        }
        return 1;
    }

    return 0;
}

public int
do_drink(string arg)
{
    notify_fail("Drink from what? The water bowl?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    string target;
    parse_command(arg, this_object(), " [from] [the] %s ", target);
    if (target == "waterbowl" 
        || target == "water bowl"
        || target == "bowl")
    {
        int maxdrink = this_player()->drink_max();
        int soaked = this_player()->query_soaked();
        if (soaked >= maxdrink)
        {
            // Can't drink anymore!
            write("You look at the bowl with the thought to drink, but "
                  + "realize that you could not drink a single drop.\n");
            return 1;
        }
        // We can drink. We drink the max amount that we can
        int amount = min(maxdrink - soaked, maxdrink / 15);
        this_player()->drink_soft(amount, 0);
        write("You pick up the water bowl and begin to drink, finding "
              + "that your thirst is quenched before you are able "
              + "to finish the entire bowl. You place the bowl back "
              + "on the table, noting that it still looks as full "
              + "as before.\n");
        say(QCTNAME(this_player()) + " picks up the water bowl from "
            + "the table and takes a long drink, before placing it "
            + "back on the table. You notice that the water level "
            + "in the bowl remains unchanged.\n");
        return 1;
    }

    return 0;
}

public int
do_open(string arg)
{
    notify_fail("Open what? The windows?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg == "window" || arg == "windows")
    {
        if (bWindowOpen)
        {
            write("But the windows are already open!\n");
            return 1;
        }
        else
        {
            write("You grip the base of the window tightly and slide it upwards. "
                  + "You notice that a calm, salty, sea breeze immediately blows "
                  + "in and mixes with the lingering scent of incense in the "
                  + "room.\n");
            say(QCTNAME(this_player()) + " grips the base of the window and slides "
                + "it upwards. A gentle breeze of salty sea air springs into the "
                + "room, mixing with the lingering scent of incense and caressing "
                + "your cheeks.\n");
            bWindowOpen = 1;
        }
        return 1;
    }

    return 0;

}

public int
do_close(string arg)
{
    notify_fail("Close what? The windows?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg == "window" || arg == "windows")
    {
        if (bWindowOpen)
        {
            write("You grip the base of the window tightly and pull it downwards. "
                  + "You notice that, though a bit warmer, a small breeze seems "
                  + "to persist.\n");
            say(QCTNAME(this_player()) + " grips the base of the window and slides "
                + "it downwards. Though the window closes, a small breeze still "
                + "persists.\n");
            bWindowOpen = 0;
        }
        else
        {
            write("But the windows are already closed!\n");
            return 1;
        }
        return 1;
    }

    return 0;
}

/*
 * Function name:       random_noise
 * Description  :       write a random noise
 * Returns      :       int -- non-zero if noises should continue,
 *                              zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, 
        ({
            "The fire crackles, soothing your soul.\n",
            "The heat from the fire warms you nicely.\n",
            "The fire spits and sputters momentarily.\n",
            "A shadow dances around the room as the fire flares momentarily.\n",
            "Light from the window casts shadows about the room, projecting shapes and forms onto the wall.\n",
        })[random(5)] );
    return 1;
} 

int
do_unhook(string str)
{
    object item;

    if (!str)
    {
        NF("Unhook what? A cloak? <unhook cloak>\n");
        return 0;
    }

    if ((!parse_command(str, ({}),"[a] [the] 'cloak'")))
    {
        NF("Unhook what? A cloak? <unhook cloak>\n");
        return 0;
    }

	if (parse_command(str, ({}),"[a] [the] 'cloak'"))
    {
    	if (!present("_wor_cloak_",TP))
	    {
	        item = clone_object(ELEMENTALIST_OBJS+"cloak");
	        write("You unhook a cloak from the rack and take it.\n");
	        say(QCTNAME(TP)+" unhooks a cloak from the small rack and takes it.\n");
	        item->move(TP);
	        return 1;
	    }
	    NF("You already have a cloak, no use having two!\n");
	    return 0;
	}
	NF("Unhook what? A cloak? <unhook cloak>\n");
    return 0;
}

int
do_hook(string str)
{
    object item;

    if (!str)
    {
        NF("Hook what? A cloak? <hook cloak>\n");
        return 0;
    }

    if ((!parse_command(str, ({}),"[a] [the] 'cloak'")))
    {
        NF("Hook what? A cloak? <hook cloak>\n");
        return 0;
    }

	if (parse_command(str, ({}),"[a] [the] 'cloak'"))
    {
    	item = present("_wor_cloak_",TP);
    	if (!item)
	    {
	        NF("You do not have a cloak to hang back on the hook.\n");
	        return 0;
	    }
    	write("You carefully brush off any dirt from the cloak, making sure it is "+
	        "clean and ready for the next person to use. When you are sure it "+
	        "is clean, you hang the cloak back on the hook.\n");
	    say(QCTNAME(TP)+" carefully brushes any dirt from the cloak that "+
	        TP->query_pronoun()+" is holding. When "+TP->query_pronoun()+
	        " is sure it is clean, "+TP->query_pronoun()+" hangs the cloak "+
	        "back on the hook.\n");
	    item->remove_object();
	    return 1;
	}
	NF("Hook what? A cloak? <hook cloak>\n");
    return 0;
}


public string
describe_long()
{
    string description = 
        "You have entered a spacious chamber on the second floor of "
        + "the Temple. There is a pair of couches with small tables "
        + "to the south. On one of the walls you notice a small rack. "
        + "Here you could sit either to relax alone or "
        + "in the company of others. It is also possible to go to the "
        + "northern wall of the room to watch and contemplate the tapestries "
        + "hanging there. There are also windows in between the tapestries "
        + "giving you a view of the north. There are a few mats along "
        + "the western wall where you can <meditate> and pray. ";
    if (bFireplaceLit)
    {
        description += "In the center an open fireplace produces a "
            + "pleasant heat and light.\n\n";
    }
    else
    {
        description += "In the center is an unlit open fireplace.\n\n";
    }

    // Council can see additional description
//    if (GUILD_MANAGER->query_is_ew_council(this_player(), 1))
//    {
//        description += "You see a small hidden ladder that you can "
//            + "ascend. No one else seems to notice it though.\n\n";
//    }
    return description;
}

public string
window_desc()
{
    string description = "";
    if (bWindowOpen)
    {
        description = 
            "The window is open and appears to be letting in a cool breeze from the shore "
            + "that swirls about the room and tickles the skin. It might be possible to "
            + "<close> the window if the breeze is too strong. Out the window, a beautiful "
            + "view of the Calian coast can be seen.\n";
    }
    else
    {
        description = 
            "The window is currently closed, yet there still seems to be a relaxing breeze "
            + "within the room, though the source is much less obvious. It might be possible "
            + "to <open> the window and let in some fresh air. Through the window, a beautiful "
            + "view of the Calian coast can be seen.\n";
    }

    return description;
}

public string
burner_desc()
{
    string description = "";
    if (bBurnerLit)
    {
        description = 
            "The burner is lit, and a fragrant smoke seems to waft forth producing the smell "
            + "of fresh picked herbs. Smells recognizable as patchouli, sage, and tigerlily "
            + "drift freely about the room. It might be possible to <extinguish> the burner "
            + "if the fragrance becomes too strong.\n";
    }
    else
    {
        description = 
            "The burner is not currently lit, though it is loaded and may be lit at any time. "
            + "Despite this, however, a faint scent still lingers in the room, and one can "
            + "smell a gentle reminder of the herb-based fragrance. It might be possible to "
            + "<light> the burner if one wished to make the room a bit more fragrant.\n";
    }
    
    return description;
}

public string
fireplace_desc()
{
    string description = "";
    if (bFireplaceLit)
    {
        description = 
            "The embers within the fireplace glow bright, and the wood crackles and pops as "
            + "flames dance across the logs. If you get close, the heat seems to radiate "
            + "outward, encompassing the body as if it were a molded glove. It might be "
            + "possible to <extinguish> the fire if it gets too warm in the lounge.\n";
    }
    else
    {
        description = 
            "The logs in the fireplace remain unlit, yet somehow staring at it reminds one "
            + "of the warmth it provides. A warm feeling seems to encompass the surroundings. "
            + "It might be possible to <light> the fire if the louge gets cool.\n";
    }
    
    return description;
}

public string
waterbowl_desc() 
{
    string description = "";
    description = "A small water bowl, bearing an etching of a triton, sits "
        + "on a table near the couches. Though untouched, the water in the "
        + "bowl ripples from the center outward in rythmic movements, and "
        + "looks as clear and fresh as any water has ever been. It might "
        + "be possible to <drink> from the bowl and quench your thirst.\n";
    return description;
}
