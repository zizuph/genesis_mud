/* A pair of sailor's pantaloons
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           3/15/98  Created
**/
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("pantaloons");
    add_name(({"pants","pair of pants","pair of pantaloons",
               "pair of black pants","pair of black pantaloons"}));
    add_adj(({"black","wool"}));
    set_short("pair of black pantaloons");
    set_pshort("pairs of black pantaloons");
    set_long(
       "It is a pair of black pantaloons, commonly worn by sailors. Made of "+
       "thick soft wool, they are cut-off and cuffed just below the knees.");
    set_ac(3);
    set_at(TS_LEGS);
}
