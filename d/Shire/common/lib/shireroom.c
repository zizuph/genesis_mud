inherit "/std/room";

inherit "/d/Gondor/common/lib/time.c";
#include "/d/Shire/common/include/time.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

/*
 * Global variables.
 */

mixed *room_alias;
int my_exit_desc_mode; 

/*
 * This file includes the following:
 *
 * object clock - The Middle Earth central clock object.
 *
 * string tod() - Returns a string telling which time of
 *                day it is.
 *
 * int qhour()  - Returns which hour it is today.
 */

/*
 * Function name:   set_short_dirs
 * Arguments:       set [default = 1] - set short dirs.
 * Description:     Sets the special short-direction format, as well as
 *                  the indented form of the long exit description.
 */
     
varargs void
set_short_dirs(int set = 1)
{
   my_exit_desc_mode = 1;
}
 
nomask void
create_room()
{
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
        
    set_short_dirs();
            
    TO->create_rom();
                
    if (my_exit_desc_mode)
    set_noshow_obvious(1);
}

/*
 * Function name:   reset_room
 * Description:     Calls reset_rom()
 */
   
reset_room()
{
  TO->reset_rom();
}

mapping time_desc;
qtime()
{
  return (int)find_object("/d/Gondor/common/obj/clock")->query_24_hour();
}
         
int
is_night()
{
  return qtime() >= 21 || qtime() <= 4;
}

int
is_day()
{
  return !is_night();
}

int
query_moon()
{
  return (int)find_object("/d/Gondor/common/obj/clock")->query_moon() &&
          is_night();
}

string
time_of_day()
{
  switch (qtime())
  {
    case EARLY_NIGHT   : return T_EARLY_NIGHT;
    case LATE_NIGHT    : return T_LATE_NIGHT;
    case EARLY_MORNING : return T_EARLY_MORNING;
    case MORNING       : return T_MORNING;
    case AFTERNOON     : return T_AFTERNOON;
    case EVENING       : return T_EVENING;
  }
}

varargs
set_time_desc(mixed s, ...)
{
    int i;
    mixed args;
        
    if (!sizeof(argv) || !stringp(s) || !stringp(argv[0]))
       return;                                                      
    
    args = ({ s }) + argv;
 
    if (!time_desc)
        time_desc = ([]);
             
    for (i=0; i<sizeof(args); i+=2)
        time_desc += ([ args[i] : args[i+1] ]);
}       
       
mapping
query_time_desc()
{
  return time_desc;
}

string
time_desc()
{
  string tod = time_of_day();

  if (!time_desc)
      return "It is " + tod + " in the Shire now.";
        
  if (query_moon() && time_desc[T_MOON] && random(2))
      return time_desc[T_MOON];
                    
  if (time_desc[tod])
      return time_desc[tod];
  
  if (is_night() && time_desc[T_NIGHT])
      return time_desc[T_NIGHT];
          
  if (is_day() && time_desc[T_DAY])
      return time_desc[T_DAY];
                      
  return "";
}

/*
 * Function name:   add_cmd_list
 * Description:     Common routine to add_cmd/call/neg/tell.
 * Arguments:       list    - list of elements
 *                  elem    - the element
 */

string *
add_cmd_list(string *list, mixed *elem)
{
    int i;

    if (obj_no_change)
        return list;
            
    if (!pointerp(list))
        list = ({});
                        
    if (pointerp(elem[0]))
    {
        for (i=0; i<sizeof(elem[0]); i++)
             list = add_cmd_list(list,
                 ({ elem[0][i], elem[1], elem[2], elem[3], elem[4] }));
        return list;
    }
    list = list + ({ elem });
    return list;
}

/*
 * Function name:   add_cmd
 * Arguments:       action  - action to add
 *                  form    - string to parse_command
 *                  cmd     - what command to perform
 *                  nf      - notify_fail message.
 *
 * Description:     This command adds a command which if the arguments
 *                  match with form will call TP->command(command).
 *                  If not, the errmsg will be notified.
 * Examples:
 *      add_cmd("swim", "[into] [in] [the] 'lake' / 'water'", "down", "Swim where?\n"
 *      add_cmd(({"climb", "jump"}), "[up] [the] 'tree' / 'up'", "up");
 */

varargs void
add_cmd(mixed action, string form, string cmd, string nf)
{
   room_alias = add_cmd_list(room_alias, ({ action, form, 0, cmd, nf }));
}

/*
 * Function name:   add_neg
 * Arguments:       action  - action to add
 *                  form    - string to parse_command
 *                  neg     - The negative string to output.
 *                  nf      - notify_fail message.
 * Examples:
 *      add_neg("smell", "[reek] [of] 'cookies'", "Ah, smells marvelous!\n");
 */

varargs void
add_neg(mixed action, string form, mixed neg, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, 1, neg, nf }));
}

/*
 * Function name:   add_call
 * Arguments:       action  - action to add
 *                  form    - string to parse_command
 *                  call    - the function to call
 *                  nf      - notify_fail message.
 * Examples:
 *      add_call("smell", "[reek] [of] 'cookies'", "smell_cookies");
 *      .
 *      .
 *
 * int
 * smell_cookies(string arg)
 * {
 *     write("You smell the reek of cookies in the air.\n"
 *         + "Ah!! Smells wonderful!\n");
 *     say(QCTNAME(TP) + " smells the reek of cookies in the air.\n"
 *       + QCTNAME(TP) + " smiles as " + HE_SHE(TP) + " inhales the reek.\n");
 *     return 1;
 * }
 *
 */

varargs void
add_call(mixed action, string form, string call, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, 2, call, nf }));
}

/*
 * Function name:   init
 * Description:     adds the commands in room_alias
 */

init()
{
    int i;
    ::init();
        
    add_action("check_time", "time");
    for (i=0; i<sizeof(room_alias); i++)
         add_action("do_room_alias", room_alias[i][0]);
}

/*
 * Function name:   do_room_alias
 * Arguments:       rest    - The rest after the verb.
 * Description:     Checks the room_alias variable and acts accordingly.
 */

int
do_room_alias(string rest)
{
    string verb;
    mixed *list;
    mixed *elem;
    int i;
    verb = query_verb();
    list = filter(room_alias, "match_verb", TO, verb);
    
    if (!sizeof(list))
        return 0;
                
    if (!strlen(rest))
        rest = "";
    for (i=0; i<sizeof(list); i++)
        {
            elem = list[i];
                
            if (sizeof(elem) != 5)
                continue;
                                    
            if (strlen(elem[4]))
                notify_fail(elem[4]);
            
            else
                notify_fail(CAP(verb) + " what?\n");
                        
            if (strlen(elem[1]) && !parse_command(rest, ({}), elem[1]))
                continue;
	    switch (elem[2])
	            {
	                case 0:
	                    TP->command(elem[3]);
	                    return 1;
	                case 1:
	                    write(elem[3]);
	                    return 1;
	                case 2:
			    call_other(TO, elem[3], rest);
			    return 1;
			case 3:
			    (STAND_LIB + "tell")->tellem(TP, 0, elem[3], 1);
			    return 1;
		    }
	}
    return 0;
}

int
match_verb(mixed elem, string verb)
{
    return elem[0]==verb;
}


/*
 * Function name:   set_long
 * Arguments:       str     - string for add_items.
 * Description:     Strips trailing newline and adds a space if needed.
 */

void
set_long(string str)
{
    if (str[-1..-1]=="\n")
        str = str[0..-2]+" ";
            
    else if(str[-1..-1]!=" ")
        str += " ";
                        
    ::set_long(str+"@@query_extra@@");
}

/*
 * Function name:   query_extra
 * Description:     Can be used for special outputs. Called from vbfc in long.
 */

string
query_extra()
{
    return "";
}

/*
 * Function name:   break_it
 * Description:     breaks a string into a string array on the newlines.
 * Returns:         Array of lines.
 */

string
break_it(string in, int dist)
{
    return break_string(in, dist);
}

/*
 * Function name:   my_break_string
 * Description:     Similar to break_string, but fixes newline-chars.
 */

varargs string
my_break_string(string str, int dis = 70)
{
    string *exp;
    string *brk;
        
    exp = explode(str, "\n");
            
    if (sizeof(exp) == 1)
        return break_string(str, dis);
    brk = map(exp, "break_it", TO, dis);
 
    return (str[0..0]=="\n"?"\n":"")
        + implode(brk, "\n")
        + (str[-1..-1]=="\n"?"\n":"");
}

/*
 * Function name:   MASKED long()
 * Description:     Handles the indentanation of room exits.
 */

varargs public mixed
long(string sob)
{
    if (strlen(sob))
        return ::long(sob);
            
    if (!my_exit_desc_mode)
        return ::long() + "\n";
    if (!sizeof(room_exits))
        return my_break_string(::long())
            + "\n    There are no obvious exits.\n";
    else
        return my_break_string(::long())
            + "\n    "+exits_description();
}

#define DIR  ([ "north":"n", "south":"s", "east":"e", "west":"w",\
                "northeast":"ne", "northwest":"nw",\
                "southeast":"se", "southwest":"sw",\
                "up":"u", "down":"d" ])
               
string
direction(string dir)
{
    return DIR[check_call(dir)];
}

/*
 * Function name:   MASKED short()
 * Description:     Describes the short description.
 *                  It will give a direction path on the form:
 *                  A room (n,e,s,w).
 */

string
short()
{
    string *exits = query_exit_cmds();
    
    if (!my_exit_desc_mode)
        return ::short();
    if (!sizeof(exits))
        return CAP(check_call(obj_short)) + " (No exits)";
       
    return check_call(obj_short)
        + " (" + implode(map(exits, "direction", TO), ",") + ")";
}




























