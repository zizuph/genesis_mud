/* 
 * Ship Captain's signet ring
 *     Cirion 031696
 */

inherit "/std/armour";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/port/bury_bones.h"

void create_armour()
{
   set_name("ring");
   add_name(RING_ID);
   add_name("signet");
   set_short("golden signet ring");
   set_adj(({"gold","golden","signet"}));

   set_long("It is a thin, well-crafted signet ring made "
     +"of pure gold. The front bears the design of "
     +"a wave, within which can be seen the letter 'B'.\n");

   add_prop(OBJ_I_VOLUME,  88);
   add_prop(OBJ_I_WEIGHT,  120);
   add_prop(OBJ_I_VALUE,   395);

   set_at(A_L_FINGER);
   set_ac(2);
}
