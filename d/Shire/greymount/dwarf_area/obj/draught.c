/* 
**A Mysterious Dwarven Draught
** Created By Leia
** February 20, 2005
*/

inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(120);
    set_name("draught");
    set_adj("mysterious");
    add_adj("dwarven");
    set_short("mysterious dwarven draught");
    set_pshort("mysterious dwarven draughts");
    set_long("This is a very mysterious dwarven draught. The draught is very dark, almost black, and smells vaguely like licorice. Other than the scent, there is not much to hint at what else makes up the draught, though rumor has it that more than a couple can knock even the most robust dwarves on their backs.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}