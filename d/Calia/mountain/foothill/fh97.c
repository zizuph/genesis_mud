
/*
  A room in the foothills of Mount Kyrus
  This room may contain a weak force of krougs, consisting mostly of
  the weakest krougs. It is also the south entrance to the lower guild
  tunnel in Mount Kyrus. 

  Coded by Maniac 16/8/95

  Modified, Maniac, 13/2/96
  Entrance to lower tunnel of mountain added, Maniac, 7/3/96

  Changed to offer protection for injured Calians, Maniac, 9/7/2000
*/

inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"
#include "/d/Calia/sys/kroug.h"
#include "kroug_reset.c"
#include "/d/Calia/mountain/special/enter_south.c"


void
create_room()
{
    make_the_room("Something unusual strikes you about the rock face " +
                  "here.\n", "south", 0, 1);

    add_exit(FOOTHILL+"fh98", "east");
    add_exit(FOOTHILL+"fh109", "southeast");
    add_exit(FOOTHILL+"fh108", "south");
    add_exit(FOOTHILL+"fh107", "southwest");
    add_exit(FOOTHILL+"fh96", "west");

    
    remove_item("rock face"); 
    add_item(({"rock face", "mountain", "mount", "mount kyrus"}), 
             "@@rock_face_desc");
    add_item("door", "@@door_desc");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SWORD);
        reset_room();
    }
    else
        enable_reset(0);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 
    enter_calian_protection_room(ob, from); 
}


void
init()
{
    ::init();
    add_action("enter_door", "knock");
}
