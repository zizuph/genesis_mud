/* Statue of the Archangel Maighal; found in kapse.c
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
 
void create_object() {
    set_name("statue");
    add_name(({"angel","archangel"}));
    set_adj(({"towering","marble"}));
    set_short("towering statue of an angel");
    set_long(
       "It is a statue of a great angel, large enough to hold you in his "+
       "hand. He is slender and muscular of build, with short curly locks, "+
       "a youthful face, and eyes which gaze with power over the sanctuary. "+
       "He holds a book in one arm against his breast, and holds aloft a "+
       "torch in his other. He wears a simple robe which descends to his "+
       "feet, and a garland of leaves on his head. His wings fan out to the "+
       "sides and point straight up over his head behind him.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_VOLUME,200000);
    add_prop(OBJ_I_WEIGHT,250000);
}
