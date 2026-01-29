/*
 * /d/Shire/annuminas/wep/dbaxel
 * Ancient double-bladed waraxe
 * Forged ages ago by the thralls of Melkor, the axe has 
 * survived. This is the lesser version that has no magical properties
 * -- Finwe, July 2002
 *
 * 2020-12-21 - Cotillion
 * - Fixed accidental non-dulling
 */

inherit "/std/weapon";
inherit "/lib/keep";


#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
 
int hit = 37;
int pen = 35;


void
create_weapon()
{
    set_name("axe");
    add_name("waraxe");
    add_name("war axe");
    set_adj("double-bladed");
    set_adj("ancient");
    set_short("ancient double-bladed waraxe");
    set_long("This is an ancient and dark axe. It was probably stolen " +
        "by the trolls and twisted to their foul ways, for the quality " +
        "is beyond their skill. The blades are sharp and deadly looking. " +
        "They are attached to a long handle made of some dark metal. " +
        "The axe appears well balanced and sharp enough to hack through " +
        "anything.\n");
    add_item(({"blades", "blade"}),
        "The blades are half circles and attached to the top of the " +
        "handle. Their edges are sharped and look to be able to slash " +
        "through anything.\n");
    add_item("handle", 
        "The handle is made of some unknown black metal. It is smooth " +
        "to the touch and durable.\n");
    set_default_weapon(hit, pen, W_AXE, W_SLASH | W_BLUDGEON, W_BOTH, TO);
    add_prop(MAGIC_AM_ID_INFO, ({
        "An evil "+short()+" with strong powers emanating from it.\n",20,
        "Though this "+short()+" appears to possess no magic, it appears " +
        "to be for evil thralls of The Dark Lord.\n",40}));

    set_wf (TO);
}
 
void
init()
{
    ::init();
}


public mixed wield (object wep)
{
    /*
     * Check to see if player is skilled enough
     */

    if(TP->query_skill(SS_WEP_AXE) < 50)
    {
        return ("You lack the skill to wield this terrible waraxe.\n");
    };
    
    // All OK, wield it ...

    write("You raise the "+short()+" above your head and yell a battlecry!\n");
    say(QCTNAME(TP) + " wields the "+short()+" above "+ HIS_HER(TP)+" head and yells a battlecry!\n");

    return (1);
}

public mixed unwield (object wep)
{
  return (0);
}


void init_wep_recover(string arg)
{
    string tf;
    int hit, pen;

    sscanf(arg, "%s#w_wh#%d#%s", tf, hit, tf);
    sscanf(arg, "%s#w_p#%d#%s", tf, pen, tf);
    set_hit(hit);
    set_pen(pen);

    ::init_wep_recover(arg);
}

string query_wep_recover()
{
    return ::query_wep_recover() + "w_wh#" + query_hit() +
        "#w_p#" + query_pen() + "#";
}
