/*
 * /d/Faerun/guilds/warlocks/obj/iron_cauldron.c
 *
 * Nerull 2018
 */

inherit "/std/object.c";

#include "../guild.h"
#include "/d/Faerun/defs.h"
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

int cauldron_content;

void
refill_cauldron()
{
    cauldron_content = 30;
}


void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_short("large iron cauldron");
    set_name("cauldron");
    set_adj("large");
    add_adj("iron");
    set_long("This is a " 
    + query_short() + " made of cast iron. It's "
    +"sitting on top of a wooden fire that feeds it constant heat. "
    +"The fumes emanating from it fills the room, hinting "
    +"of infant flesh and bones boiling in its stew-like "
    +"content. If you are into cannibalism, you may "
    +"take meat from it.\n");
    
    add_prop(OBJ_M_NO_GET, "The " + query_short() 
    + " is fixed to the floor, you cannot take it.\n");
    
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  50000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    
    cauldron_content = 30;
    
    set_alarm(300.0, 300.0, &refill_cauldron());
}


/* Function name: prevent_enter
 * Description  : Checks if it is a food
 * Arguments    : object obj - the object entering
 * Returns      : 1 if not a coin, 0 if it is
 */
public int
prevent_enter(object obj)
{
    write("The " + query_name() + " is enough filled as "
    +"it is, but you may take meat from it.\n");
    
    return 1;
}


int
do_take_meat(string str)
{
     seteuid(getuid());
    
    if (str == "meat from cauldron"
    || str == "meat from iron cauldron"
    || str == "meat from large iron cauldron"
    || str == "meat from large cauldron")
    {
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            if (cauldron_content <= 0)
            {
                write("You search the muddy content in the large "
                +"iron cauldron for some meat, but finds none. Maybe "
                +"later?\n");

                tell_room(environment(this_player()), 
                this_player()->query_name()
                + " greedily searches the large iron cauldron for "
                +"infant meat, but finds none.\n", this_player());
            
                this_player()->command("swear");
            
                return 1;
            }
        
            write("You grab some stinking infant meat from the "
            +"large iron cauldron.\n");

            tell_room(environment(this_player()), this_player()->query_name()
            + " greedily grabs some stinking infant meat from the "
            +"large iron cauldron.\n", this_player());
        
            cauldron_content = cauldron_content - 1;
        
            int diceroll = random(3);
        
            if (diceroll == 0)
            {
                clone_object(WARLOCK_OBJ_DIR 
                + "infant_meat1")->move(this_player(), 1);
            }
        
            if (diceroll == 1)
            {
                clone_object(WARLOCK_OBJ_DIR 
                + "infant_meat2")->move(this_player(), 1);
            }
        
            if (diceroll == 2)
            {
                clone_object(WARLOCK_OBJ_DIR 
                + "infant_meat3")->move(this_player(), 1);
            }
           
            return 1;
        }
        
        write("Uuhm, no. You are NOT a cannibal. Infant meat is "
        +"never on your menu.\n");
            
        return 1;
    }
    
    return 0;
}


void init()
{
    ::init();

    add_action(do_take_meat, "take");
    add_action(do_take_meat, "get");
}
