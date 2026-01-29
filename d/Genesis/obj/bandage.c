/*
 *  /w/petros/bandage.c
 *
 *  A magic bandage that will accelerate healing
 *  out of combat.
 *  
 *  Created by Petros, May 2008
 */
#pragma strict_types

// Inheritance 
inherit "/std/heap";

// Includes
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#define EFFECT "/d/Genesis/obj/bandage_effect"

// Prototypes
public int          command_apply(string arg);
public void         apply_effect(object player);

/*
 * Function name: init
 * Description  : Add the apply command
 */
public void
init()
{
    ::init();

    add_action(command_apply, "apply");
}

/*
 * Function name: create_bandage
 * Description  : This function is the constructor. You should redefine
 *                it to create your own bandage object.
 */
public void
create_bandage()
{
  
}

/*
 * Function name: create_heap
 * Description  : The heap constructor. You should not redefine this
 *                function, but use create_food() instead. It makes the
 *                food object have a default size of 1 item.
 */
public nomask void
create_heap()
{
    set_name("bandage");
    set_pname("bandages");
     
    set_short("bandage");
    set_long("This is a bandage that you can <apply> to your wounds.\n");
    
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_VALUE, 0);  
    add_prop(OBJ_M_NO_SELL, "Bandages are not to be resold.\n");
    
    set_short("bandage");
    set_long("This is a bandage that you can <apply> to your wounds.\n");
    
    create_bandage();

    if (!query_prop(HEAP_S_UNIQUE_ID))
    {
        add_prop(HEAP_S_UNIQUE_ID,
            MASTER + ":" + singular_short(this_object()));
    }

    set_heap_size(1);
}


/*
 * Function name: set_short
 * Description  : When the short is set/changed, also make sure that we do set
 *                the unique identifier for the heap.
 * Arguments    : mixed new_short - the short description.
 */
void
set_short(mixed new_short)
{
    ::set_short(new_short);

    add_prop(HEAP_S_UNIQUE_ID,
        MASTER + ":" + singular_short(this_object()));
}

/*
 * Function name: remove_bandage
 * Description  : destruct this if it's empty. Otherwise reduce
 *                the heap.
 * Arguments    : string argument
 * Returns      : 0/1 - command was successful or not
 */
public void
remove_bandage()
{
    if (leave_behind > 0)
    {
        set_heap_size(leave_behind);
    }
    else
    {
        remove_object();
    }
}

/*
 * Function name: command_apply
 * Description  : apply this bandage
 * Arguments    : string argument
 * Returns      : 0/1 - command was successful or not
 */
public int
command_apply(string arg)
{
    object bandage;
    object * poisons;
    
    bandage = PARSE_COMMAND_ONE(arg, this_player(), "[the] %i");
    if (bandage != this_object())
    {
        notify_fail("Apply what?");
        return 0;
    }
    
    if (this_player()->query_attack())
    {
        write("You cannot properly apply the " + singular_short()
            + "while you are in combat.\n");
        return 1;
    }
    
    poisons = FILTER_POISON_OBJECTS(deep_inventory(this_player()));
    if (poisons && sizeof(poisons) > 0)
    {
        write("You are poisoned! Applying a bandage won't help.\n");
        return 1;
    }
    
    if (present("_bandage_effect", this_player()))
    {
        write("You can't apply more than one bandage at a time.\n");
        return 1;
    }
    
    if (this_player()->query_combat_time() >  (time() - 15))
    {
        write("You heart is racing too fast from fighting to properly "
            + "apply the bandage.\n");
        return 1;
    }
      
    // Apply the effect of the bandage    
    apply_effect(this_player());
    remove_bandage();
    return 1;
}

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover.
 */
public string
query_recover()
{
    string file = MASTER;

    return file + ":heap#" + num_heap() + "#";
}

public void
destroy_bandage()
{
    int num;
    
    num = num_heap();    
    if (IS_PLAYER_OBJECT(environment(this_object())))
    {
        environment(this_object())->catch_tell("The bandage"
                  + (num != 1 ? "s" : "") + " crumble"
                  + (num != 1 ? "" : "s") + " in your hands.\n");
    }
    remove_object();
}

/*
 * Function name: init_recover
 * Description  : This function is called when the bandage recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%s", foobar, num, foobar) == 3)
    {
        set_heap_size(num);
        set_alarm(5.0, 0.0, &destroy_bandage());
    }
}

/*      
 * Function name: apply_effect
 * Description  : This actually clones the bandage effect and moves it
 *                to the player
 * Arguments    : player - the player to move the effect to.
 */             
public void
apply_effect(object player)
{
    player->catch_tell("You apply the bandage to your wounds.\n");
    tell_room(environment(player), QCTNAME(player) + " applies a bandage "
            + "to his wounds.\n", player);

    
    setuid();
    seteuid(getuid());
    
    clone_object(EFFECT)->move(player, 1);
}
