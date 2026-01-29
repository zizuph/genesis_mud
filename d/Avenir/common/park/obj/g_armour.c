// file name: g_armour.c
// creator(s): Ilyian
// last update: 
// purpose: Armor for the Water Amulet's Guardian
// note: 
// bug(s):
// to-do:

inherit "/std/armour";
#include "/sys/wa_types.h"  
#include "/sys/stdproperties.h"
#include <macros.h>

void
create_armour()
{
     set_name("mail");
     set_short("enclosing mail of shimmering black");
     set_adj("enclosing");
     add_adj("black");
     add_adj("shimmering");

     set_long("This strange armour seems to make of steel-like metal, "
             +"but it is very slippery to the touch. It is of an "
             +"unreflective black colour, yet shimmers with it's own "
             +"faint light. The mail is designed to cover your body "
             +"and head at the same time, having a movable neck-piece "
             +"that allows for your neck.\n");

     set_default_armour();
     set_ac(29);
     set_at(A_BODY|A_NECK|A_HEAD); /* Covers body, neck, and head. */
     set_am(({-2,-2,4}));
/*    ie. protects well against bludgeoning weapons, poorly against
          slashing/impaling weapons.    */

     add_prop(OBJ_I_VALUE, 850);
     add_prop(OBJ_I_VOLUME, 5000);
     add_prop(OBJ_I_WEIGHT, 7000);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

