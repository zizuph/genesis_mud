/*
 * HOBJ + cauldron_v1.c
 * This is based on Varian's version in the Genesis houses dir
 * 
 *  Lilith Feb 2022
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "../defs.h"

inherit "/std/object";

int do_scoop(string str);
int stews_left = 20;

public void
create_object()
{
    set_adj("large");
    add_adj("iron");
    set_name("cauldron");

    set_short("large iron cauldron");
  
    set_long("This large cauldron has been forged out of " +
        "black iron and has most recently been used to " +
        "cook a large batch of hearty stew. You " +
        "you could <scoop stew> out if you are hungry.\n");

    add_item( ({"stew", "vegetable stew"}),
        "The cauldron was recently used to cook a large " +
        "batch of stew, and you might be able to " +
        "scoop out a bowl if there is any left.\n");

    add_prop(CONT_I_VOLUME, 81000);
    add_prop(CONT_I_WEIGHT, 4535);
    add_prop(OBJ_M_NO_GET, 1);
	
	set_no_show_composite(1);
}

/*
 * Function name:        do_scoop
 * Description  :        Allows someone to scoop a bowl of stew out of
 *                       the cauldron - HOBJ + "stew". 
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */

public int
do_scoop(string str)
{
    object stew;

    notify_fail("Scoop what? <Scoop stew> out of the cauldron?\n");
    
    if (!parse_command(str, ({}),
	"[some] [hearty] 'stew' [out] [of] [the] [iron] [cauldron]", str))
        return 0;
        
    if (stews_left < 1)
    {
        write("The iron cauldron is empty! Hopefully " +
           "a new batch of stew will be made soon!\n");
        return 1;
    }
            
    setuid();
    seteuid(getuid());

    stew = clone_object(HOBJ + "stew");
    stew->move(this_player(), 1);
    write("You scoop out a warm bowl of the hearty stew.\n");
    say(QCTNAME(TP) + " scoops out a bowl of stew.\n");
    stews_left = stews_left -1;

    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_scoop, "scoop");
}