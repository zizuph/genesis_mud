/*
 * Rack of fish in Cair Andros
 * /d/Gondor/anorien/cairandros/obj/fishrack
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "../../defs.h"

inherit "/std/container";

int do_lift(string str);
int fish_left = 5;

public void
create_container()

{
    set_adj("rickety");
    add_adj("wooden");
    set_name("fishrack");
    add_name("rack");

    set_short("rickety wooden fishrack");
  
    set_long("This rickety wooden fishrack has been set " +
        "up to hold fish while it is curing after having " +
        "been salted.\n");

    add_item( ({"fish", "salted fish"}),
        "There are several salted fish drying on this rack, " +
        "it does not look like too many of them are ready " +
        "to be lifted off the rack yet however.\n");

    add_prop(CONT_I_VOLUME, 81000);
    add_prop(CONT_I_WEIGHT, 4535);
    add_prop(OBJ_M_NO_GET, 1);

    reset_object();
}

/*
 * Function name:        do_lift
 * Description  :        Allows someone to lift a fish out of
 *                       the rack
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote and maybe a fish
 */

public int
do_lift(string str)
{
    object fish;
    notify_fail("Lift what? A fish?\n");
    
    if((str != "fish" && str != "salted fish"))
        return 0;
        
    if (fish_left < 1)
        {
            write("There are no fish cured enough to remove yet.\n");
            return 1;
        }
            
            setuid();
            seteuid(getuid());
            fish = clone_object(AN_OBJ_DIR + "saltfish");
            fish->move(this_player(), 1);
            write("You lift a cured and salted fish out from the rack.\n");
            say(QCTNAME(TP) + " lifts a fish out from the rack.\n");
            fish_left = fish_left -1;

        return 1;
}

public void
init()
{   
    ::init();
    add_action(do_lift, "lift");
}