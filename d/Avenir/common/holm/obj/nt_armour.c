/* file name:        /d/Avenir/common/holm/t_camp/nt_armour.c
*  creator(s):      (Rangorn , Feb 97)
*  revisions:
*  purpose:
*  note:
*  bug(s):
*  to-do:
*/

inherit "/std/armour";
#include "../holm.h"
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>

void
create_armour()
{
    set_short("bright chainmail");
    add_name(({"mail", "chainmail", "ringmail"}));
    add_adj(({"bright", "luminous"}));
    set_long("A very bright and almost luminous chainmail. Every "+
           "ring of the chainmail seems to have been made with "+
           "great care and effort. The steel appears to be of a "+
           "very high quality.\n"); 
  
    set_ac(35);
    set_at(A_BODY);
    /* IMPALE, SLASH, BLUDGEON */
    set_am(({1,1,-2}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) +random (200) - 100);
}

