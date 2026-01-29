/*
 * /d/Sparkle/area/city/bank/obj/quest_hammer.c
 * Aegish weapons are lefty.
 *
 * Created FEB 4 2010, by Aeg (Matthew Morin)
 * 
 */

inherit "/std/weapon";

#include <macros.h>         /* General purpose */
#include <stdproperties.h>  /* References */
#include <wa_types.h>  
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"

public int      press_button(string button);

void
create_weapon()
{
    set_name( "_sparkle_bank_hammer" );
    add_name( "hammer" );
    set_short( "dirty well-used hammer" ); 
    set_long("This hammer appears to be the prized item of a skilled "
           + "mechanic. The hammer consists of a wooden handle and a "
           + "metallic head. "
           + "The handle appears to have two buttons protruding from "
           + "it's handle. This might hurt if swung in combat.\n");

    add_item( ({ "button", "buttons" }),
              "The handle on the hammer has a red button and a green button. "
            + "Which would you like to examine?\n");

    add_item( ({ "green button", "green buttons" }),
              "The handle on the hammer has a green button. Green usually "
            + "means go, doesn't it?\n");

    add_item( ({ "red button", "red buttons" }),
              "The handle on the hammer has a red button. Red usually means "
            + "stop, doesn't it?\n");

    add_adj("dirty");
    add_adj("well-used");

    set_hit(10);                /* To hit value        */
    set_pen(10);                /* Penetration value   */
    add_prop(OBJ_I_WEIGHT, 5000); 
    add_prop(OBJ_I_VOLUME,  500);
    set_wt(W_CLUB);             /* Club       */
    set_dt(W_BLUDGEON);         /* 'Bludgeon' */
    set_hands(W_LEFT); /* Lets make it a lefty for kicks */
}

/* Function name:       init()
 * Description  :       adds the action
 */
public void
init()
{
    ::init();
    
    add_action("press_button", "press");
    
} /* init */

/*
 * Function name:       press_button()
 * Description  :       allows the player to press the buttons
 */
public int
press_button(string button)
{
    if (button == "green button")
    {
        write("You press the green button on the " + query_short() + " and "
            + "nothing happens. It must be broken!\n");
        say(capitalize(QTNAME(this_player())) + " presses the green button on "
            + "" + this_player()->query_possessive() + " " + query_short() 
            + " and nothing seems to happen.\n");
            
        return 1;
    }
    
    if (button == "red button")
    {
        write("You press the red button on the " + query_short() + " and "
            + "nothing happens. It was already stopped...\n");
        say(capitalize(QTNAME(this_player())) + " presses the red button on " 
            + "" + this_player()->query_possessive()+ " " + query_short() 
            + " and nothing seems to happen.\n");
            
        return 1;
    }
    
    notify_fail("Press what?\n");
    return 0;
           
} /* press_button */
