/*
 * parse.c    - Lib functions using parse_command.
 *
 * This file is used for different parsing of commands.
 * The following parsing routines are done:
 *
 * parse_livings            : Get livings nearby.
 * parse_one_living         : Gets one living.
 * parse_attack             : Gets livings including 'enemies' and etc.
 * parse_inventory          : Gets things in the inventory of a player.
 * parse_environment_items  : Get things in the room.
 * parse_items              : Gets things (environment first).
 * parse_items_normal       : Gets things (inventory first).
 * parse_one_item           : Gets a single item.
 * parse_place_in_room      : Gets a place in this room.
 * get_time                 : Gets a description of time.
 * parse_direction          : Gets a direction (including abbreviations).
 * parse_beetween_rooms     : Gets the two rooms from a direction.
 *
 * Sir Rogon.
 *
 */

#include "defs.h"
#include "/d/Shire/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <tasks.h>
#include <language.h>

#define NA    ({})
#define PREP    "[in] [on]"

#define DEBUG_FILE "slparse.log"
#define DEBUG(x)   /* Nothing */
#define INV(x) all_inventory(x)

inherit STRING_FILE;

//
// CMDPARSE_FILE->visible_access(arr, acsfunc|0, acsobj|0, retTP, alsoINVIS)
//  No acsfunc means : in player or environment.
//
// CMDPARSE_FILE->normal_access(arr, acsfunc|0, acsobj|0, alsoINVIS)
//  is the same as visible_access with retTP = 1.
//
//

#define VIS_ACCESS(arr, acsfunc, also_me, also_invis) \
    (object *) CMDPARSE_STD->visible_access(arr, acsfunc, TO, also_me, also_invis)

#define PRESENT_NORMAL_ACCESS(arr) \
    (object *) CMDPARSE_STD->visible_access(arr, 0, 0, 0, 0)

#define PRESENT_ACCESS(arr, also_me) \
    (object *) CMDPARSE_STD->visible_access(arr, 0, 0, also_me, 0)

#define INVIS_ACCESS(arr, acsfunc, acsobj) \
    (object *) CMDPARSE_STD->visible_access(arr, acsfunc, acsobj, 0, 1)

#define PRESENT_INVIS_ACCESS(arr, also_me) \
    (object *) CMDPARSE_STD->visible_access(arr, 0, 0, also_me, 1)


string
change_str(string instr, string from, string to)
{
    int pos;

    string *list = explode(instr, " ");

    for (pos = member_array("me", list); pos>=0; pos = member_array("me", list))
    list[pos] = to;

    return implode(list, " ");
}

string
substitute(string word)
{
    mixed hvar;

    if (word=="me" || word=="myself")
    return lower_case(TP->query_name());

    if (word=="enemy")
    {
    hvar = TP->query_attack();
    if (!hvar)
        return word;
    else
        return lower_case(hvar->query_name());
    }

    if (word=="enemies")
    {
    hvar = TP->query_enemies(-1);
    if (!sizeof(hvar))
        return word;
    if (objectp(hvar))
        hvar = ({ hvar });

    return implode(hvar, " and ");
    return 0;
    }

    return word;
}

string
parse_pre_parse(string str)
{
    string *brk = explode(str, " ");

    if(!sizeof(brk))
    return str;

    return implode(map(brk, "substitute", TO), " ");
}

/*
 * Function name:   inventory_access
 */
int
inventory_access(object ob)
{
    if (!objectp(ob))
    return 0;

    return ENV(ob) == TP;   /* Return true if in inventory. */
}

/*
 * Function name:   cmdparse_prep_livings
 * Arguments:        str - string to parse.
 *            prep - preposition match.
 */
varargs mixed
cmdparse_prep_livings(string str, string prep = "[on] [in]")
{
    object *oblist = NA;

    if (!str)
    return 0;

    str = parse_pre_parse(str);

    if (!parse_command(str, EP, prep + " %l", oblist))
    return 0;

    return oblist;
}

/*
 * Function name:   parse_livings
 * Arguments:        str - string to parse.
 *            prep - preposition match.
 *            me_also - if tp should be included in the list
 *            invis_also - if invisible livings can be targets
 */
varargs mixed
parse_livings(string str, string prep = "[on] [in]",
           int me_also = 0, int invis_also = 0)
{
    return VIS_ACCESS(cmdparse_prep_livings(str, prep), 0, me_also, invis_also);
}

/*
 * Function name:   parse_one_living
 * Arguments:        str - string to parse
 *            prep - prepostion match
 *            me_also - me also?
 *            invis_also
 */
varargs mixed
parse_one_living(string str, string prep = "[on] [in]",
           int me_also = 1, int invis_also = 0)
{
    object *livs;
    livs = parse_livings(str, prep, me_also, invis_also);

    if (!sizeof(livs))
    return livs;
    else
    return ({ livs[0] });
}

/*
 * Function name:   parse_attack
 * Arguments:        str - string to parse
 *            prep -preposition match.
 *            invis_also - invisible livings can be attacked.
 * Description:     Parses inputs for attack type patterns.
 * Returns:        Who to attack.
 */
varargs mixed
parse_attack(string str, string prep = "[on]", int invis_also = 0)
{
    if ((!strlen(str) || parse_command(str, ({}), prep + " [the] [my] 'enemy'"))
    && TP->query_attack())
    return ({ TP->query_attack() });

    if (parse_command(str, ({}), prep + " [the] [my] 'enemies'")
    && sizeof(TP->query_enemy(-1)))
    return TP->query_enemy(-1);

    return parse_livings(str, prep, 0, invis_also);
}

/*
 * Function name:   cmdparse_inventory
 * Arguments:        str - string to parse
 */
varargs mixed
cmdparse_inventory(string str, string prep = PREP)
{
    object *oblist;

    if (!parse_command(str, all_inventory(TP), prep + " %i", oblist))
    return 0;

    write("Checking cmdparse_inventory:\n");
    dump_array(oblist);
    return oblist;
}

/*
 * Function name:   parse_inventory
 * Arguments:        str - string to parse
 */
varargs object *
parse_inventory(string str, string prep)
{
    object *oblist;
    string what;

    if (strlen(prep) && !parse_command(str, NA, prep + " %s", what))
    return 0;

    if (!strlen(prep))
    what = str;

    if (member_array(what,
    ({ "me", "inventory", "inv", "i", })) >= 0)
    return FILTER_CAN_SEE(INV(TP), TP);

    if (what=="worn" || what=="worn armours" || what=="worn armour")
    return TP->query_armour(-1);

    if (what=="wielded" || what=="wielded weapons" || what=="wielded weapon")
    return TP->query_weapon(-1);

    return NORMAL_ACCESS(cmdparse_inventory(what, prep), 0, 0);
}

/*
 * Function name:   cmdparse_environment_items
 * Arguments:        str - string to parse
 *            prep - preposition match
 */
varargs mixed
cmdparse_environment_items(string str, string prep = PREP)
{
    object *oblist;

    if (!parse_command(str, INV(ENV(TP)), prep + " %i", oblist))
    return 0;

    return oblist;
}

/*
 * Function name:   parse_environment_items
 * Arguments:        str - string to parse
 *            prep - preposition match
 *            invis_also - invisible objects counts
 */
varargs object *
parse_environment_items(string str, string prep = PREP, int invis_also = 0)
{
    object *all;
    if (str == "here" ||
    parse_command(str, NA, prep + " [the] [this] 'room' / 'place'"))
    {
    all = INV(ENV(TP));
    all = FILTER_DEAD(all);
    return VIS_ACCESS( ({ 0 }) + all, 0, 0, invis_also);
    }
    return VIS_ACCESS(cmdparse_environment_items(str, prep), 0, 0, invis_also);
}

/*
 * Function name:   cmdparse_items
 * Arguments:        str - string to parse
 *            prep - preposition match
 */
varargs mixed
cmdparse_items(string str, string prep = PREP)
{
    object *oblist;

    if (!parse_command(str, EP, prep + " %i", oblist))
    return 0;

    return oblist;
}

/*
 * Function name:   parse_items
 * Arguments:        str - string to parse
 *            prep - preposition map
 *            invis_also - invisible objects counts
 */
varargs object *
parse_items(string str, string prep = PREP, int invis_also = 0)
{
    return VIS_ACCESS(cmdparse_items(str, prep), 0, 0, invis_also);
}

/*
 * Function name:   parse_items_normal
 * Arguments:        str - string to parse
 *            prep - prepositon
 *            invis_also - invisible objects counts
 */
varargs object *
parse_items_normal(string str, string prep = PREP, int invis_also = 0)
{
    object *inv, *env;

    inv = parse_inventory(str, prep);
    env = parse_environment_items(str, prep, invis_also);

    if (!sizeof(inv))
    return env;
    if (!sizeof(env));
    return inv;
    return inv + env;
}

/*
 * Function name:   parse_one_item
 * Arguments:        str - string to parse
 *            prep - preposition map
 *            invis_also - invisible objects counts
 */
varargs object *
parse_one_item(string str, string prep = PREP, int invis_also = 0)
{
    object *items = parse_items(str, prep, invis_also);

    if (!sizeof(items))
    return ({});

    return ({ items[0] });
}

/*
 * Function name:   parse_place_in_room
 * Arguments:        str - string to parse
 *            prep - preposition to match
 */
varargs string
parse_place_in_room(string str, string prep = PREP)
{
    string *places = ({});
    string *items;
    int i;

    str=lower_case(str);

    if (str == "here" ||
    parse_command(str, NA, prep + " [the] [this] 'room' / 'place'"))
    return "room";

    if (!parse_command(str, NA, prep + " [the] %w", str))
    return "";

    items = EP->query_item();
    for(i=0;i<sizeof(items);i++)
    if(member_array(str, items[i][0])>=0)
        return "on "+str;
    return "";
}

/*
 * Function name:   get_time
 * Arguments:        str - string to parse
 * Description:     Tries to find out a specific duration in hours/mins/secs.
 * Returns:        Number of seconds. (int)
 */
int
get_time(string str)
{
    string s, s1, s2, *ex;
    int i, hours, mins, secs, time;

    if(sscanf(str, "%s hour", s)==1)
    {
    switch(s)
    {
        case "one": case "a": case "an": case "1":
        return 1*60*60;
        case "one half": case "half": case "half an": case "1/2":
        return 30*60;
        default:
        return 0;
    }
    }
    else if(sscanf(str, "%s hours", s)==1)
    {
    if(sscanf(s,"%d", i))
        return i*60*60;
    else
        return LANG_FILE->number_word(s)*60*60;
    }
    else if(sscanf(str, "%s mi%s", s, s2)==2)
    {
    if(s2=="nutes"||s2=="ns")
    {
        if(sscanf(s, "%d", i)==1)
        return i*60;
        else
        return LANG_FILE->number_word(s)*60;
    }
    else if(s2=="nute"||s2=="n")
        switch(s)
        {
        case "one": case "a": case "an": case "1":
        return 60;
        case "one half": case "half": case "half a": case "1/2":
        return 30;
        }
    }
    else if(sscanf(str, "%s se%s", s, s2)==2)
    {
    if(s2=="conds"||s2=="cs")
    {
        if(sscanf(s, "%d", i)==1)
        return i;
        else
        return LANG_FILE->number_word(s);
    }
    else if(s2=="cond"||s2=="c")
        return 1;
    }

    if(sscanf(str, "%dh%dm%ds",hours, mins, secs)==3||
       sscanf(str, "%d:%d:%d", hours, mins, secs)==3||
       sscanf(str, "%dm%ds", mins, secs)==2||
       sscanf(str, "%d:%d", mins, secs)==2||
       sscanf(str, "%ds", secs) )
    {
    return hours*60*60+mins*60+secs;
    }

    ex = explode(str, " and ");

    for(i=0;i<sizeof(ex);i++)
    time += get_time(ex[i]);

    return time;
}

#define ABBREV \
    ([           \
    "n" : "north", "e" : "east", "w" : "west", "s" : "south",       \
    "ne" : "northeast", "se" : "southeast",                \
    "nw" : "northwest", "sw" : "southwest", "u" : "up", "d" : "down"   \
    ])

/*
 * Function name:    translate_dir
 * Arguments:        string arg
 * Description:     If the arg is one of ABBREV defined above, then
 *            the direction is transformed to a real direction.
 */
string
translate_dir(string dir)
{
    mapping abbrev = ABBREV;

    if (strlen(abbrev[dir]))
    return abbrev[dir];
    else
    return dir;
}

/*
 * Function name:    parse_direction
 * Arguments:        arg - argument to parse
 * Returns:        Object room in direction.
 */
object
parse_direction(string arg)
{
    string dir;
    int pos;
    mixed rooms;
    mixed exits;
    mixed funcs;
    object room;

    if (!parse_command(arg, ({}), "[to] [towards] [the] %w", dir))
    return 0;

    dir = translate_dir(dir);

    rooms = map(ENV(TP)->query_exit_rooms() , "check_call", TO);
    exits = map(ENV(TP)->query_exit_cmds(), "check_call", TO);
    funcs = map(ENV(TP)->query_exit_functions(), "check_call", TO);

    pos = member_array(dir, exits);

    if (pos == -1)
    return 0;

    if (LOAD_ERR(rooms[pos]))
    return 0;

    if (funcs[pos] != 0)
    return 0;

    return find_object(rooms[pos]);
}

/*
 * Function name:   parse_between_rooms
 * Arguments:        string arg - argument to parse
 *            string *dirs - directions to and fro
 * Description:     Parses an argument typically used to set up a
 *            a wall between two rooms.
 * Returns:        The two rooms (this_room and other_room).
 *            dirs will return the directions to and from.
 * On errors:
 *            0 : Must specify direction.
 *            1 : No exit in that direction.
 *            2 : Other room could not load.
 *            3 : Impossible to go that way for the player.
 *            4 : Can not return from other room.
 */
mixed
parse_between_rooms(string arg, string *dirs)
{
    object this_room;
    object other_room;
    string to;
    string from;
    int pos;
    mixed rooms;
    mixed exits;
    mixed funcs;
    object room;

    this_room = ENV(TP);

    if (!parse_command(arg, NA, "[to] [towards] [the] %w", to))
    return 0;

    to = translate_dir(to);

    rooms = map(this_room->query_exit_rooms() , "check_call", this_room);
    exits = map(this_room->query_exit_cmds(), "check_call", this_room);
    funcs = map(this_room->query_exit_functions(), "check_call", this_room);

    pos = member_array(to, exits);

    if (pos == -1)
    return 1;

    if (LOAD_ERR(rooms[pos]))
    return 2;

    if (funcs[pos] != 0)
    return 3;

    other_room = find_object(rooms[pos]);

    if (!objectp(other_room))
    return 2;

    rooms = map(other_room->query_exit_rooms(), "check_call", other_room);
    exits = map(other_room->query_exit_cmds(), "check_call", other_room);
    funcs = map(other_room->query_exit_functions(), "check_call", other_room);

    pos = member_array(MASTER_OB(this_room), rooms);

    if (pos == -1)
    return 4;

    if (funcs[pos] != 0)
    return 3;

    from = exits[pos];

    dirs = ({ to, from });
    return ({ this_room, other_room });
}
