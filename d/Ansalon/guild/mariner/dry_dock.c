/* 
 * Arman Kharas, October 2020
 */

#include "/d/Krynn/solamn/palanthas/local.h"
#include CLOCKH
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include <money.h>
#include "/d/Krynn/std/boats/std_boat_defs.h"

inherit SHIP_BASE;

/* Global Variables */
string sink_path;
string *row_exits_arg = ({ });
string *row_exits_path = ({ });
int *row_exits_tired = ({ });
mixed *row_exits_check = ({ });

object *boats = ({ }); 
string boat_vista; 

string * ship_options = ({ "sloop", "cutter", "schooner", "corvette",
             "frigate", "man-o-war" });

int * ship_size = ({ SLOOP, CUTTER, SCHOONER, CORVETTE, FRIGATE,
          MAN_OF_WAR });

int * ship_difficulty = ({ DIFFICULTY_NOVICE, DIFFICULTY_LAYMAN,
          DIFFICULTY_JOURNEYMAN, DIFFICULTY_PROFESSIONAL,
          DIFFICULTY_MASTER, DIFFICULTY_GURU });

int * max_passengers = ({ 3, 6, 10, 14, 20, 25 }); 

string * random_names = ({"Seas the Day", "Second Wind", "Rum Runner",
             "Knot on Call", "The Codfather", "Unsinkable II", "Seaforth",
             "The Grey Fox", "Tradewind", "The Unrivalled", "Mischief",
             "Goldfinch", "Endeavour", "The Heart of Oak", "Nighthawk",
             "Swift Return", "The Artful", "The Gravelines" });

string * figurehead_options = ({ "diving mermaid", "beautiful maiden", 
             "fierce minotaur", "noble knight", "roaring dragon",
             "eagle in flight", "undead sea captain", "rearing unicorn",
             "growling lion", "dark angel", "curious kender",
             "three-headed hydra", "victorious centurion",
             "charging bull", "leaping dolphin", "graceful swan",
             "sea goddess" });

#define PALANTHAS_MAX_BOATS_IN_ROOM 50
#define ONE_OF(x)     ((x)[random(sizeof(x))])

#define TYPE_PROP        "_mariner_ship_type"
#define SUBTYPE_PROP     "_mariner_ship_subtype"
#define SHIPADJ_PROP     "_mariner_ship_adjective"
#define SHIPNAME_PROP    "_mariner_ship_shipname"
#define FIGUREHEAD_PROP  "_mariner_ship_figurehead"

#define CUSTOM_SHIP      "/d/Krynn/std/boats/customised_boat"

string
query_to_jail()
{
  return "south";
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 0; 
}

void
boat_enter(object b)
{
    boats = filter(boats, objectp); 
    boats += ({ b }); 
}

void
boat_exit(object b)
{
    boats = filter(boats, objectp); 
    boats -= ({ b }); 
}

object 
*query_boats()
{
    boats = filter(boats, objectp); 
    return boats; 
}
 
void
set_boat_vista(string s)
{
    boat_vista = s; 
}

string
query_boat_vista()
{
    return boat_vista;
}

/* Returns the appropriate desc to be added for the row exits */
string
row_exit_desc()
{
    string desc;
    desc = "";
    if (sizeof(row_exits_arg))
        desc += ("You may sail: " + COMPOSITE_WORDS(row_exits_arg)+".\n");
    return desc;
}

/* Set the path to the room where things will sink to, if any. 
   Non living objects will automatically sink to that exit. 
   You don't have to set this if you want things to sink "down", as
   this is done by default if you add a swim exit for that direction. */
void
set_sink_path(string sp)
{
    sink_path = sp;
}

string
query_sink_path()
{
    return sink_path;
}

string
dir_alias(string str)
{
    switch (str) { 
        case "n" : return "north"; 
                   break;
        case "s" : return "south"; 
                   break;
        case "e" : return "east"; 
                   break;
        case "w" : return "west"; 
                   break;
        case "nw" : return "northwest"; 
                   break;
        case "ne" : return "northeast"; 
                   break;
        case "se" : return "southeast"; 
                   break;
        case "sw" : return "southwest"; 
                   break;
        case "u" : return "up"; 
                   break;
        case "d" : return "down"; 
                   break;
     }
     return str;
}

/*
 * This is the function which checks the rowing action and makes 
 * the call to carry out the row if it's possible. 
 * It is called from the inside of the rowing boat itself when a  
 * player does an action there. 
 */
int
try_row(string str)
{
    int i, tired, tmp;
    object tp = this_player();
    object row_to; 

    if (!str)
    {
	notify_fail("Sail where?\n");
	return 0;
    }

    str = dir_alias(str);
    i = member_array(str, row_exits_arg);
 
    if (i == -1)
    {
	notify_fail("You can't sail in that direction.\n");
	return 0;
    }

    if (this_object()->check_call(row_exits_check[i])) 
        return 1;

    tired = row_exits_tired[i]; 
    if (tp->query_fatigue() < tired) {
        notify_fail("You are too tired to sail anywhere at the moment. " +
            "You decide to drift where you are.\n"); 
        return 0;
    }

    if (sizeof(row_exits_path[i]->query_boats()) >= PALANTHAS_MAX_BOATS_IN_ROOM) 
    {   
        notify_fail("Oh dear! It seems there are too many ships " +
                    "over there and your ship won't fit!\n"); 
        return 0;
    } 

    tp->add_fatigue(-tired);
    environment(tp)->carry_out_row(str, row_exits_path[i]); 
    return 1;
}
/*
 * Function name: add_swim_exit
 * Description:   Add one swim exit to the room. 
 */
varargs void
add_swim_exit(string place, string cmd, mixed efunc, mixed tired, 
              mixed non_obvious)
{
    if ((cmd == "down") && (!stringp(query_sink_path())))
        set_sink_path(place); 
 
    add_exit(place, cmd, efunc, tired, non_obvious);  
}

/*
 * Function name: add_wade_exit
 * Description:   Add one wade exit to the room. 
 */
add_wade_exit(string place, string cmd, mixed efunc, mixed tired,
              mixed non_obvious)
{
    add_exit(place, cmd, efunc, tired, non_obvious); 
}

/*
 * Function name: add_row_exit
 * Description:   Add one ROW exit (for rowing boats) to the room. 
 * Arguments:     path: The filename of the room to move to
 *                arg:  The argument given after "row" e.g.
 *                       "north", "cave"
 *                check: A check to see if can move in that direction,
 *                       often uses vbfc. Possible values are: 
 *                       0: Direct move to destination
 *                       1: Can not move in this dir, do not try others
 *                tired: How much more tired the player should become from
 *                       rowing in that direction. Default is 1.
 */
varargs void
add_row_exit(string path, string arg, mixed check, int tired)
{
    row_exits_path += ({ path });
    row_exits_arg += ({ arg });
    row_exits_check += ({ check });
 
    if (!tired)
        tired = 1;
    row_exits_tired += ({ tired });
}

/*
 * Function name: remove_row_exit
 * Description:   Remove one row exit from the room.
 * Arguments:     arg:   The argument given after "row" for the exit to be 
 *                       removed.
 */
public int
remove_row_exit(string arg)
{
    int i;
    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;
 
    i = member_array(arg, row_exits_arg);
    if (i == -1) 
        return 0;

    row_exits_arg = exclude_array(row_exits_arg, i, i);
    row_exits_path = exclude_array(row_exits_path, i, i);
    row_exits_check = exclude_array(row_exits_check, i, i);
    row_exits_tired = exclude_array(row_exits_tired, i, i);

    return 1;
}

/* An object sinks */
void
sink(object ob)
{
    string sp, sv;
    if (!objectp(ob)) 
        return;

    if (!objectp(present(ob, this_object())))
        return;

    if (!stringp(sp = query_sink_path()))
        return;

    sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
                             " " + sv + " downwards.\n");
    ob->move(sp);
    tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
}
int
deep_water_room(object r)
{
    if ((r->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) || 
        stringp(r->query_sink_path())) 
        return 1;
    else
        return 0;
}
/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                We need to add the drown object to livings who enter.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
     ::enter_inv(ob, from);
 
}

/*
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 *                We need to remove the drown object from livings who exit.
 * Arguments:     ob: The object that just left this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    object dob;
    ::leave_inv(ob, to);

    if (!living(ob)) 
        return;

    /* quitting */
    if (!objectp(to)) 
        return;

    dob = ob->query_prop(LIVE_O_DROWN_OB);
    if (!objectp(dob)) 
        return;

    /* If they've gone linkdead, we'll not remove the drown object. */ 
    if (file_name(to) == OWN_STATUE) 
        return;

    /* Otherwise, if they're gone into a room which isn't one of 
       our standard underwater rooms, get rid of the drown object. */ 
    if (!to->query_standard_water_room()) 
        dob->remove_object();

    /* Another possibility is if you've swum to the surface, in which  
       case catch your breath but retain the drown object. */ 
    if (!(to->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
        dob->reset_oxygen_debt(); 
}

int
launch_ship()
{
    write("You launch your ship from the dry dock into Palanthas harbour!\n");
    return 0;
}

string
read_sign()
{
    return "The sign reads:\n\n" +
        "          Sailors of Genesis! The famed dry docks of Palanthas\n" +
        "          will swiftly build you the ship of your needs!\n\n" +
        "          Here you may:\n" +
        "              'select ship options', providing you with a list\n" +
        "              of ship types you can sail based on your sailing\n" +
        "              skill.\n\n" +
        "              You can 'select ship type <type>' from the following\n" +
        "              options:\n" +
        "                   sloop\n" +
        "                   cutter\n" +
        "                   schooner\n" +
        "                   corvette\n" +
        "                   frigate, and\n" +
        "                   man-o-war\n" +
        "              Ship type affects the number of passengers you can\n" +
        "              carry and the sea conditions you can navigate. The\n" +
        "              base cost is 150 gold for a sloop-type ship, going\n" +
        "              up to 1200 gold for a man-o-war-type ship.\n\n"+ 
        "              'select ship sub-type <sub-type>' to customise\n" +
        "              your ship to a specific one within its size type.\n\n" +
        "              'select ship adjective <adjective>' to expand the\n" +
        "              description of your ship.\n\n" +
        "              For an additional feel of 60 gold you may also:\n\n" +
        "              'select ship name <name>' to name your ship. Note\n" +
        "              the shipwrights won't allow inappropriate names.\n\n" +
        "              'select ship figurehead <figurehead>', to add a \n" +
        "              figurehead to your ship.\n\n" + 
        "           After customising a ship you can:\n" +
        "              'check cost' to see how much gold you will need, and\n" +
        "              'commission ship' to get it made.\n\n" +
        "           If you find you don't have the skill to sail any of the\n" +
        "           ship types, consider joining the Guild of Mariners in\n" +
        "           Palanthas just south of the dry docks.\n\n";
       
}

void
create_palan_room()
{
    SHORT("dry dock on the edge of Palanthas harbour");
    LONG("You stand at the great dry docks of Palanthas, where " +
        "industrious shipwrights build some of the finest sailing " +
        "vessels in the land. A sign has been posted here for " +
        "those interested in commissioning a customised ship.\n");

    add_item(({"sign"}), "There is a sign here you can read.\n");
    add_item(({"dry docks","docks"}),
        "The great dry docks of Palanthas, where some of the " +
        "biggest ships to sail the seas are crafted.\n");
    add_item(({"shipwrights"}), "Industrious shipwrights bustle " +
        "about as they work on their latest vessel.\n");
 
    EXIT(SHIP + "s23", "south", 0, 0);
    add_row_exit("/d/Krynn/turbidus_ocean/room/2q", "north", 
        "@@launch_ship", 1);

    add_cmd_item("sign","read","@@read_sign");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}

int
check_sail_skill(string type, int skill)
{
    switch(type)
    {
        case "sloop":
            if(skill <= DIFFICULTY_NOVICE)
                return 0;
            break;
        case "cutter":
            if(skill <= DIFFICULTY_LAYMAN)
                return 0;
            break;
        case "schooner":
            if(skill <= DIFFICULTY_JOURNEYMAN)
                return 0;
            break;
        case "corvette":
            if(skill <= DIFFICULTY_PROFESSIONAL)
                return 0;
            break;
        case "frigate":
            if(skill <= DIFFICULTY_MASTER)
                return 0;
            break;
        default:
            if(skill <= DIFFICULTY_GURU)
                return 0;
            break;
    }
    return 1;
}

int
do_select(string str)
{
    string ship_types = "";
    string arg, * all_ship_options;

    all_ship_options = ship_options;


    if (!str || str == "ship options" || str == "options")
    {
        if(TP->query_skill(SAILING_SKILL) <= DIFFICULTY_NOVICE)
        {
            write("There are no types of ships you have the skill " +
                "to sail. South of the dry docks is the Guild of " +
                "Mariners. If you wish to join them you can learn " +
                "sailing skills that will allow you to navigate " +
                "crafts commissioned here. Or, you can charter a " +
                "ship captain from the northwestern-most pier " +
                "to sail his ship to your destination for you.\n");
            return 1;
        }

        write("The following types of ships you can select, based on " +
            "your sailing skill:\n");

        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_NOVICE)
            ship_types += "    sloop\n";
        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_LAYMAN)
            ship_types += "    cutter\n";
        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_JOURNEYMAN)
            ship_types += "    schooner\n";
        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_PROFESSIONAL)
            ship_types += "    corvette\n";
        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_MASTER)
            ship_types += "    frigate\n";
        if(TP->query_skill(SAILING_SKILL) > DIFFICULTY_GURU)
            ship_types += "    man-o-war\n";

        write(ship_types + "\nTo select the type of ship you wish " +
            "to commission, 'select ship type as <type>'.\n\n" +
            "For a description of these types of ships, examine the " +
            "ship guide in the Guild of Mariners.\n");

          return 1;
    }

    if (parse_command(str, environment(TP), "'ship' 'type' [as] %s", arg))
    {
        if(member_array(lower_case(arg), all_ship_options) > -1)
        {
            if(!check_sail_skill(lower_case(arg), 
                TP->query_skill(SAILING_SKILL)))
            {
                write("You don't have the skill to sail the " +
                    arg+ " ship type.\n");
                return 1;
            }

            write("You select '" +arg+ "' as the type of ship you " +
                "want to commission. You can now select from the " +
                "following sub-types of ships - ");
            TP->add_prop(TYPE_PROP, arg);

            if(TP->query_prop(SUBTYPE_PROP))
                TP->remove_prop(SUBTYPE_PROP);
            if(TP->query_prop(SHIPADJ_PROP))
                TP->remove_prop(SHIPADJ_PROP);
            if(TP->query_prop(SHIPNAME_PROP))
                TP->remove_prop(SHIPNAME_PROP);
            if(TP->query_prop(FIGUREHEAD_PROP))
                TP->remove_prop(FIGUREHEAD_PROP);

            string * subtypes = CUSTOM_SHIP_NAME[arg];
            int csize = 0;
            string cstring = "";

            foreach(string subtype: subtypes)
            {
                csize++;
                cstring += subtype;
                if (sizeof(subtypes) - csize == 1)
                    cstring += ", and ";
                else if (sizeof(subtypes) - csize > 1)
                    cstring += ", ";
            }
            write(cstring + ".\n");

            return 1;
        }

        write("The ship type '" +arg+ "' is not an option. Check " +
            "'select ship options' for a list of available types.\n");
        return 1;
    }

    if (parse_command(str, environment(TP), "'ship' 'sub-type' [as] %s", arg))
    {
        if(!strlen(TP->query_prop(TYPE_PROP)))
        {
            write("You need to select a ship type first before you select " +
                "a sub-type.\n");
            return 1;
        }

        if(member_array(lower_case(arg), 
            CUSTOM_SHIP_NAME[TP->query_prop(TYPE_PROP)]) > -1)
        {
            if(!check_sail_skill(lower_case(TP->query_prop(TYPE_PROP)), 
                TP->query_skill(SAILING_SKILL)))
            {
                write("You don't have the skill to sail the '" +
                    arg+ "' ship sub-type.\n");
                return 1;
            }

            write("You select '" +arg+ "' as the sub-type of ship you " +
                "want to commission. You can now customise the description " +
                "of your " +arg+ " with the following adjectives - ");
            TP->add_prop(SUBTYPE_PROP, arg);

            string * subtypes = CUSTOM_SHIP_ADJ[TP->query_prop(TYPE_PROP)];
            int csize = 0;
            string cstring = "";

            foreach(string subtype: subtypes)
            {
                csize++;
                cstring += subtype;
                if (sizeof(subtypes) - csize == 1)
                    cstring += ", and ";
                else if (sizeof(subtypes) - csize > 1)
                    cstring += ", ";
            }
            write(cstring + ".\n");

            return 1;
        }

        write("The ship sub-type '" +arg+ "' is not an option.\n");
        return 1;
    }

    if (parse_command(str, environment(TP), "'ship' 'adjective' [as] %s", arg))
    {
        if(!TP->query_prop(SUBTYPE_PROP))
        {
            write("You need to select a ship sub-type first before you select " +
                "an adjective for your ship.\n");
            return 1;
        }

        if(member_array(lower_case(arg), 
            CUSTOM_SHIP_ADJ[TP->query_prop(TYPE_PROP)]) > -1)
        {
            write("You select '" +arg+ "' as the adjective for the ship you " +
                "want to commission. It will look like '" +LANG_ADDART(arg)+
                " " +TP->query_prop(SUBTYPE_PROP)+ "'.\n\n" +
                "You can optionally choose to name your ship and add a " +
                "figurehead for an additional cost of 60 gold " +
                "coins each. You can also have the shipwrights select a random name " +
                "for your ship:\n" +
                "    'select ship name <name>' or 'select ship name random', and\n" +
                "    'select ship figurehead options' and " +
                "'select ship figurehead <figurehead>'.\n\n" +
                "If you do not wish to name your ship or give it a figurehead " +
                "you can 'check cost' and, if you have the gold, 'commission ship'.\n");
            TP->add_prop(SHIPADJ_PROP, arg);

            return 1;
        }

        write("The ship adjective '" +arg+ "' is not an option.\n");
        return 1;
    }

    if (parse_command(str, environment(TP), "'ship' 'figurehead' [as] %s", arg))
    {
        if(!TP->query_prop(SUBTYPE_PROP))
        {
            write("You need to select a ship sub-type first before you select " +
                "a figurehead for your ship.\n");
            return 1;
        }

        if(member_array(arg, figurehead_options) > -1)
        {
            write("You select '" +arg+ "' as the figurehead for the ship you " +
                "want to commission.\n\n" +
                "If you have finished customising your ship " +
                "you can now 'check cost' and 'commission ship'.\n");
            TP->add_prop(FIGUREHEAD_PROP, arg);

            return 1;
        }

        write("The figurehead options you have are: ");

            int csize = 0;
            string cstring = "";

            foreach(string figurehead: figurehead_options)
            {
                csize++;
                cstring += figurehead;
                if (sizeof(figurehead_options) - csize == 1)
                    cstring += ", and ";
                else if (sizeof(figurehead_options) - csize > 1)
                    cstring += ", ";
            }
            write(cstring + ".\n");

        return 1;
    }

    if (parse_command(str, environment(TP), "'ship' 'name' %s", arg))
    {
        if(!TP->query_prop(SUBTYPE_PROP))
        {
            write("You need to select a ship sub-type first before you select " +
                "a name for your ship.\n");
            return 1;
        }

        if(arg == "random")
            arg = ONE_OF(random_names);

        if(strlen(arg) > 21)
        {
            write("The name is too long! Choose a shorter one of 20 characters " +
                "or less.\n");
            return 1;
        }

        if(LANG_IS_OFFENSIVE(arg))
        {
            write("The name uses inappropriate language. Choose a different " +
                "ship name, with the understanding that misuse of the naming " +
                "of your ship can result in the wroth of the administration.\n");
            return 1;
        }

        write("You select '" +arg+ "' as the name for your ship.\n\n" +
            "BE WARNED. Inappropriate and offensive ship names will " +
            "draw immortal ire and punishment. Do not continue with " +
            "the commissioning of your ship if in any doubt of the " +
            "appropriateness of the name you have chosen.\n\n" +
            "If you have finished customising your ship " +
            "you can now 'check cost' and 'commission ship'.\n");
        TP->add_prop(SHIPNAME_PROP, arg);

        return 1;
    }

    write("The order of selection is:\n" +
          "    'select ship options'\n" +
          "    'select ship type <type>'\n"+ 
          "    'select ship sub-type <sub-type>'\n" +
          "    'select ship adjective <adjective>'\n\n" +
          "For an additional feel you may also:\n" +
          "    'select ship name <name>', and\n" +
          "    'select ship figurehead <figurehead>'\n\n" + 
          "When you are finished you can:\n" +
          "    'check cost' and\n" +
          "    'commission ship'.\n\n");
    return 1;
}

int
do_check(string str)
{
    if(!str || str != "cost")
    {
        notify_fail("Check what? Cost?\n");
        return 0;
    }

    string ship_type = TP->query_prop(TYPE_PROP);
    string ship_subtype = TP->query_prop(SUBTYPE_PROP);

    if(!strlen(ship_type))
    {
        notify_fail("You haven't completed selecting your customised " +
            "ship options to check its cost yet!\n");
        return 0;
    }

    if(!strlen(ship_subtype))
    {
        notify_fail("You haven't completed selecting your customised " +
            "ship options to check its cost yet!\n");
        return 0;
    }

    int ship_no = member_array(ship_type, ship_options);
    int size = ship_size[ship_no];
    int difficulty = ship_difficulty[ship_no];
    int passengers = max_passengers[ship_no];

    int subtype_no = member_array(ship_subtype, CUSTOM_SHIP_NAME[ship_type]);
    string long = CUSTOM_SHIP_LONG_OUT[ship_type][subtype_no];

    string figurehead;

    string * split_subtype = explode(ship_subtype, " ");
    string * ship_adj = ({ TP->query_prop(SHIPADJ_PROP) });

    if(sizeof(split_subtype) > 1)
    {
        ship_subtype = split_subtype[1];
        ship_adj = ({ TP->query_prop(SHIPADJ_PROP), split_subtype[0] });
    }

    if(!TP->query_prop(FIGUREHEAD_PROP))
        figurehead = "";
    else
        figurehead = TP->query_prop(FIGUREHEAD_PROP);

    // base cost is 150 gold, multiplied by ship size.
    // So cost ranges from between 150 gold and 1200 gold.
    int cost = 21600;
    cost = cost * size;

    // Figureheads cost an extra 60 gold coins
    if(strlen(figurehead))
        cost += 8640;

    // Ship names cost an extra 60 gold coins
    if(TP->query_prop(SHIPNAME_PROP))
        cost += 8640;

    int gold_cost = cost / 144;

    write("It will cost you approximately " +gold_cost+ " gold coins to commission " +
        "your customised ship.\n");
    say(QCTNAME(TP) + " checks the price for a customised ship.\n");

    return 1;
}

int
do_commission(string str)
{
    if(!str || str != "ship")
    {
        notify_fail("Commission what? Ship?\n");
        return 0;
    }

    string ship_type = TP->query_prop(TYPE_PROP);
    string ship_subtype = TP->query_prop(SUBTYPE_PROP);

    if(!strlen(ship_type))
    {
        notify_fail("You haven't selected a ship type to commission!\n");
        return 0;
    }

    if(!strlen(ship_subtype))
    {
        notify_fail("You haven't selected a ship subtype to commission!\n");
        return 0;
    }

    if(!TP->query_prop(SHIPADJ_PROP))
    {
        notify_fail("You haven't selected an adjective for the ship you " +
            "want to commission!\n");
        return 0;
    }

    int ship_no = member_array(ship_type, ship_options);
    int size = ship_size[ship_no];
    int difficulty = ship_difficulty[ship_no];
    int passengers = max_passengers[ship_no];

    int subtype_no = member_array(ship_subtype, CUSTOM_SHIP_NAME[ship_type]);
    string long = CUSTOM_SHIP_LONG_OUT[ship_type][subtype_no];
    string long_in = CUSTOM_SHIP_LONG_IN[ship_type][subtype_no];

    string figurehead;

    string * split_subtype = explode(ship_subtype, " ");
    string * ship_adj = ({ TP->query_prop(SHIPADJ_PROP) });

    if(sizeof(split_subtype) > 1)
    {
        ship_subtype = split_subtype[1];
        ship_adj = ({ TP->query_prop(SHIPADJ_PROP), split_subtype[0] });
    }

    if(!TP->query_prop(FIGUREHEAD_PROP))
        figurehead = "";
    else
        figurehead = TP->query_prop(FIGUREHEAD_PROP);

    // base cost is 150 gold, multiplied by ship size.
    // So cost ranges from between 150 gold and 1200 gold.
    int cost = 21600;
    cost = cost * size;

    // Figureheads cost an extra 60 gold coins
    if(strlen(figurehead))
        cost += 8640;

    // Ship names cost an extra 60 gold coins
    if(TP->query_prop(SHIPNAME_PROP))
        cost += 8640;

    if(!MONEY_ADD(TP, -cost))
    {
        int gold_cost = cost / 144;

        notify_fail("You don't have " +gold_cost+ " gold coins " +
            "to commission the building of your ship.\n");
        return 0; 
    }

    setuid();
    seteuid(getuid());

    write("You pay the head shipwright. The crew of the dry docks swiftly crafts " +
        "you up your customised ship!\n");
    say(QCTNAME(TP) + " pays the head shipwright, who swiftly works with his crew to " +
        "craft up a customised ship!\n");

    object ship = clone_object(CUSTOM_SHIP);
    object boat_in;

    ship->set_ship_name(ship_subtype);
    ship->set_ship_adj(ship_adj);
    ship->set_custom_ship_size(size);
    ship->set_custom_sailing_difficulty(difficulty);
    ship->set_max_ship_passengers(passengers);
    if(TP->query_prop(SHIPNAME_PROP))
        ship->set_ship_naming(TP->query_prop(SHIPNAME_PROP));
    ship->set_ship_long(long);
    ship->set_ship_long_in(long_in);
    ship->set_ship_figurehead(figurehead);
    ship->create_the_boat();
    ship->move(TO);
    ship->config_boat_inside();
    boat_in = ship->query_boat_in();
    boat_in->set_owner(TP);

    if(TP->query_prop(SUBTYPE_PROP))
        TP->remove_prop(SUBTYPE_PROP);
    if(TP->query_prop(SHIPADJ_PROP))
        TP->remove_prop(SHIPADJ_PROP);
    if(TP->query_prop(SHIPNAME_PROP))
        TP->remove_prop(SHIPNAME_PROP);
    if(TP->query_prop(FIGUREHEAD_PROP))
        TP->remove_prop(FIGUREHEAD_PROP);

    return 1;
}


void
init()
{
    ::init();
    add_action(do_select, "design");
    add_action(do_select, "select");
    add_action(do_check, "check");
    add_action(do_commission, "commission");

}
