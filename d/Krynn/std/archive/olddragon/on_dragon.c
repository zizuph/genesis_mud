/* Dragon coded by Nick */
/* Completely rewritten by Aridor, 5/95 */

inherit  "/std/room";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

string dragon_room_file;

void
create_on_landed_dragon_room()
{
}

nomask void
create_room()
{
    set_short("On dragon");
    set_long("You are sitting on the back of a huge dragon. There is room for " +
	     "two people to sit here. When you want the dragon to fly, just " +
	     "give him a kick.\n");
    
    add_exit("@@room_down", "down", "@@going_down");
    
    add_prop(OBJ_S_WIZINFO,"Just kick the dragon to get it to fly with you.\n");
    
    create_on_landed_dragon_room();
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
init()
{
    add_action("check_all_cmds","",1);
    ::init();
}

int
check_all_cmds(string str)
{
    object dragon, *ob;
    int i;
    string destination;
   
    destination = (dragon_room_file)->get_destination(query_verb() + " " + str);
    NF("What?\n");
    if (!destination)
      return 0;
   
    ob = all_inventory(TO);
    for (i = 0; i < sizeof(ob); i++)
      ob[i]->move(dragon_room_file, 1);
    
    (dragon_room_file)->take_off(27, destination);
    write("You " + query_verb() + " the dragon and off you go.\n");
    say(QCTNAME(TP) + " " + query_verb() + "s the dragon and off you go.\n");
    return 1;
}

void
drop_all()
{
    object *ob;
    int i;
    
    ob = all_inventory(TO);
    for(i = 0; i < sizeof(ob); i++)
      {
	  ob[i]->move((dragon_room_file)->query_place(), 1);
	  tell_object(ob[i], "The dragon leaves suddenly and you fall to " +
		      "the ground.\n");
	  tell_room((dragon_room_file)->query_place(), "Suddenly " + QTNAME(ob[i]) +
		    " arrives falling through the air.\n", ob);
      }
}

void
going_down()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))) <= 1)
      (dragon_room_file)->set_flying(0);
}

string
room_down()
{
    return (dragon_room_file)->query_place(); 
}
     
void
set_on_flying_dragon_room_path(string path)
{
    if (!dragon_room_file)
      dragon_room_file = path;
}
