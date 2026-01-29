// targe (shield) of village guards
#include "defs.h"
inherit  COM_ARM+"targe";
 
void create_armour()
{
   ::create_armour();
   set_colour("purple");
   set_pattern("celtic");
   setup_targe();
}
