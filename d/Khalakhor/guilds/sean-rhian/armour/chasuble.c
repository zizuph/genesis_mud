/* Chasuble - pauncho-like vestment of a saggart (full priest)
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           8/21/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("chasuble");
    add_name("vestment");
    set_adj(({"purple","long"}));
    set_short("purple chasuble");
    set_long("It is a long purple chasuble, a priestly vestment made of a "+
             "large oval piece of fine linen. It has a hole in the "+
             "center, through which the head of the wearer goes. It "+
             "hangs down over the length of the arms and down below "+
             "the knees in the front and back. There are three "+
             "interlocked circles of gold thread embroidered on its "+
             "front.\n");
    set_ac(5);
    set_at(TS_TORSO);
}
