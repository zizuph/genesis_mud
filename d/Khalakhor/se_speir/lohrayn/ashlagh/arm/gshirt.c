// shirt for a village guard
#pragma strict_types
#include "defs.h"
inherit  COM_ARM+"shirt_base";
 
public void create_armour()
{
    set_long("It is a loose-fitting wool shirt which looks very warm "+
             "and comfortable. It is died purple and there is a badge "+
             "sewn on its breast. It looks like part of a uniform.\n");
    create_shirt("purple", "wool");
    add_item("badge",
       "The badge sewn on the "+short()+" is a shield with a fleet of "+
       "nine sailing ships on a purple sea. A small ribbon around the "+
       "bottom of the badge bears the inscription: Freiceadanan de "+
       "Baile Ashlagh.\n");
}
