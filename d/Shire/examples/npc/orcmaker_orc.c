//  include the orcmaker and local defines
#include "../local.h"
#include ORC_FILE

inherit ORCMAKER;

/*  I use the orcmaker to make a typical red eye orc type but I decided
 *  to change it's starting equipment so I have to inherit the orcmaker
 *  and change the arm_me() function to accomplish this.
 */
void
create_orc()
{
    set_power(150);  // This sets the npcs stats and skills 
    set_type(RED_EYE_ORC);  // This sets the type and equipment the orc gets
}

//   I want to change the orcs equipment
void
arm_me()
{
    object toothpick;

    FIXEUID;  //  Need this statement before we clone anything
    toothpick = clone_object(EXAMPLE_WEP + "toothpick");
    toothpick->move(TO);
    command("wield all");
}
