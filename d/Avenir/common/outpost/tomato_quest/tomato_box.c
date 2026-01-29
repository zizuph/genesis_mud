// file name:   /d/Avenir/common/outpost/tomato_quest/tomato_box.c
// creator(s):  Kazz
// last update: March 1995
//		Denis, Jul'96: Updated it to work with new tomato_quest(SMIS).
// purpose:     loaded into fort6 to provide tomatos for the drop mini-quest.
// note:	 
// bug(s):
// to-do:        

# pragma strict_types
# include <macros.h>
# include <stdproperties.h>
# include "tomato_drop.h"

inherit "/std/container";

public int reset_placed_functions()
{
    int i = -1,
	num = 5 - sizeof(all_inventory(this_object()));
    
    // fill the box with some tomatos.
    while(++i < num)
	clone_object(TOMATOQ_TOMATO)->move(this_object());

    return 1;
}

void create_container()
{
    if(!IS_CLONE)
	return;

    set_short("wooden box");
    set_long("A wooden box smelling like tomatoes.\n");
    set_name("box");
    add_name("tomato box");
    add_name("wood box");
    add_prop (CONT_I_WEIGHT, 500);
    add_prop (CONT_I_VOLUME, 500);
    add_prop (CONT_I_MAX_WEIGHT, 5000);
    add_prop (CONT_I_MAX_VOLUME, 2000);
    add_prop (OBJ_I_VALUE,  50);
    seteuid(getuid());	

    reset_placed_functions();
}
