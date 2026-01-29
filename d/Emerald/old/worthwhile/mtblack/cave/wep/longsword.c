/* An well-used longsword - Tulix III, 20/12/95 */
/* This weapon is used by /d/Emerald/common/guild/grunts/npc/trainer.c */

#include "/sys/stdproperties.h"
inherit "/std/weapon";
#include "/sys/wa_types.h"

public void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    add_name("longsword");
    add_pname("longswords");
    set_adj("well-used");
    
    set_short("well-used longsword");
    set_pshort("well-used longswords");
    set_long("This is a well-used longsword. Although it has seen a lot "  
        + "of service, it has been well maintained, and has a good sharp " 
        + "edge along the blade.\n");

    set_hit(28);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 2000);
}
