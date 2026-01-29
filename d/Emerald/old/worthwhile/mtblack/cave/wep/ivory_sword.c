/* An ivory hilted sword - Tulix III, recoded 13/07/95 */
/* This weapon is used by /d/Emerald/cave/.c */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    add_pname("weapons");
    set_short("ivory hilted sword");
    set_pshort("ivory hilted swords");
    set_adj(({"ivory","ivory hilted"}));
    set_long("It's a very finely crafted weapon.  "
        +"The blade looks to you as if it is made of some sort of alloy, "
        +"containing silver.  The hilt is made of ivory, which "
        +"has been carved with intricate patterns.  "
        +"It looks like it was made for someone with an eye for a " 
        +"more refined type of weapon than you are used to wielding.  "
        +"A craftsman has invested a great deal of his time into producing "
        +"such a beautiful, perfectly balanced sword.\n");
    
    set_hit(30);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, 1050);
}
