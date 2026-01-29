/*
 * Navarre January 31st 2007
 * - Added Prop OBJ_I_IS_MAGIC_ARMOUR
 *
 *
 * Borrowed and used by Nerull, 2021
 */
#pragma strict_types
inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>


void
create_armour()
{
    set_name("ring"); 
    set_pname("rings");
    set_adj(({"gold", "red-striped"}));
    set_short("gold red-striped ring");
    set_pshort("gold red-striped rings");
    set_long("This ring is made of solid gold. It is " 
        +"decorated with red painted stripes and various engravings of " 
        +"roses and crosses are clearly visible. While fairly " 
        +"large and robust, it feels remarkably light in your hand. You're " 
        +"quite sure this ring used to belong to someone important.\n"  
        +"You notice an inscription engraved on the inside\n");
    
    set_af(this_object());
    set_at(A_FINGER);
    set_ac(1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({      
        "This ring has been enchanted to aid in escapes from "
        +"danger.\n", 20,
        "Wearing this ring will increase stamina "
        +"regeneration.\n", 30 }));
        
    add_prop(OBJ_S_WIZINFO, "By wearing the ring the player " 
        +"is given a shadow that will increase the rate "
        +"fatigue heals.\n");
        
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_I_WEIGHT, 4);
    add_prop(OBJ_I_VOLUME, 4);
    add_prop(OBJ_I_VALUE, 3000);
    add_prop(OBJ_M_NO_BUY, 1);
}


mixed
wear()
{
    object sh;

    setuid();
    seteuid(getuid());
    

    /* Shadow will take care of fatigue
     */
    sh = clone_object(DRAKMERE + "/boots_sh");
    
    sh->shadow_me(this_player());
    
    write("You wear the " + short() + ".\nYou feel a continuing "
    +"magical torrent from the ring that restores your fatigue.\n");

    say(QCTNAME(this_player()) + " wears the " + short() + ".\n");
    
    return 1;
}


mixed
remove()
{
    query_worn()->remove_vigorring_shadow();
    
    return 0;
}


