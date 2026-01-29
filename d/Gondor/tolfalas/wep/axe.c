/*
 */

inherit "/std/weapon";
inherit "/lib/keep";



#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
 
int hit = 45;
int pen = 45;


void
create_weapon()
{
    set_name("axe");
    set_adj("jaggged-edged");
    set_short("jagged-edged axe");
    set_long("This "+short()+" looks quite worn, with its blade and " +
    "shaft scarred. Somehow it feels deadly none the less.\n");
    add_item("handle", 
        "The handle is made of some unknown black wood.\n");

    set_default_weapon(hit, pen, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 1000 );
    add_prop(OBJ_I_VOLUME, 1500 );
    add_prop(OBJ_I_VALUE, 1900 + random(151));
 
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "A sturdy axe that feels as if it wants to do battle, with or without you.\n",5,
        "A feeling of bloodlust takes over you.\n",40}));
    set_wf (TO);
}
 

public mixed wield (object wep)
{
    /*
     * Check to see if player is skilled enough
     */

    if(TP->query_skill(SS_WEP_AXE) < 50)
    {
        return ("You lack the skill to wield this axe.\n");
    };
    
    // All OK, wield it ...

    write("You grasp the "+short()+" and grin wickedly.\n");
    TP->tell_watcher(QCTNAME(TP) + " wields the "+short()+" and "+
    "grins wickedly.\n");

    return (1);
}

