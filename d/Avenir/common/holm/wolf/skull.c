// -*-C++-*-
// file name:	skull.c
// creator(s): 	sirra march 98
// last update:	
// purpose:		wolf skeleton quest item.
// note:
// bug(s):	
// to-do:

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include "wolf.h"

string my_long();
void start_destruct_timer();
void self_destruct();
void set_avenir_check_timer();
void check_near_avenir();

void
create_object()
{
    set_name("bone");
    add_name("WOLF_ID");
    add_name("SKULL_ID");
    add_name("skull");

    set_adj("skull");
    set_long(my_long);
    
    add_prop(OBJ_M_NO_SELL, "This object is too precious to sell.\n");
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 3);

    set_avenir_check_timer();

}

string
my_long()
{
    string str;

    if (this_player()->query_skill(SS_ANI_HANDL)>19)
    {
        str = "To your trained eye, this bone appears beautiful "
            + "and complex. Indentations, slight depressions, "
	    + "sharp angles, and deep open pockets form the "
	    + "nasal cavity, eyesockets, and detail of the skull "
	    + "of a large wolf.\n";
	
        return str;
    }

    else
    {
	str = "The "+ short() +" to some sort of animal. You do not "
	    + "have enough experience dealing with animals to "
            + "know for certain which kind, though.\n";
	return str;
    }
}

void
start_destruct_timer()
{
    set_alarm( 20.0, 0.0, "self_destruct" );
    
}


void
self_destruct()
{
    object *envs;
    object current_room;

    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];

    tell_room( current_room, "The skull bone glitters briefly "
	+ "and crumbles to dust.\n" );

    remove_object();

} 

void
set_avenir_check_timer()
{
    set_alarm( 300.0, 0.0, "check_near_avenir" );
} 


void
check_near_avenir()
{
    string room_filename;
    object *envs;
    object current_room;

    // Courtesy of Mercade:
    // get the filename of the current room
    //   (whether we are in a player inventory, or on a room's floor)
    envs = all_environment(this_object());
    current_room = envs[sizeof(envs) - 1];
    room_filename = file_name( current_room );

    
    // check if we are 'close enough' to Avenir.
    // (ie. in either directory path)
    if (wildmatch( AVENIR_PATH_CHECK +"*", room_filename ) ||
	room_filename == LD_PATH_CHECK)
    {
	// still in range of Avenir, no problem.
	set_avenir_check_timer();
	return;
    }
	
    // bone is too far from Avenir, crack it and set destruct timer
    tell_room( current_room,
	       "You hear a faint cracking noise.\n" );
    
    start_destruct_timer();
    
}
