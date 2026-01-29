/*
 *   /d/Gondor/tolfalas/wep/bandedclub.c
 *
 *
 *   made by Toby 24 Sept 2006
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>

 
int iHit = 35;
int iPen = 35;


void
create_weapon()
{
    set_name("club");
    set_adj("banded");
    add_adj("iron");
    set_short("iron banded club");
    set_long("This club is about three feet long, encircled with iron bands " +
             "that sprout spikes like steel thorns. The spikes are thick " +
             "as a human fingers and rusty. The thick handle almost black " +
             "from hard use.\n");

    set_default_weapon(iHit, iPen, W_CLUB, W_BLUDGEON | F_WEAPON_DEFAULT_DT, W_ANYH, this_object());
    add_prop(OBJ_I_WEIGHT, 3000 );
    add_prop(OBJ_I_VOLUME, 3500 );
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(iHit, iPen));
}
 

public mixed wield (object wep)
{
    int fatigue = this_player()->query_max_fatigue() / 30;

    /*
     * Check to see if player has enough strength
     */

    if(this_player()->query_stat(SS_STR) < 50)
    {
        this_player()->add_fatigue(-fatigue);
        return ("You struggle to wield the " +short()+ ", but fail, only to leave you " +
                "a tad more tired from the strain in your muscles.\n");
    }
    
    // All OK, wield it ...

    write("With effort you lift the " +short()+ " and wield it.\n");
    this_player()->tell_watcher("With obvious effort " + QCTNAME(this_player()) + 
          " wields the " +short()+ ".\n");

    return (1);
}

