/* Celeste's Lyre, by Teth, March 29, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>

public void
create_object()
{
    set_name("lyre");
    set_pname("lyres");
    set_short("ancient-looking lyre");
    set_pshort("ancient-looking lyres");
    set_adj("ancient-looking");
    set_long("This lyre is beautifully crafted. It has several strings, " +
	     "which are plucked to create soft sounds, useful for an " +
	     "an accompaniment with voice. Ancient and heirloom are words " +
	     "that come to mind when looking at it.\n");
   
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 454);
   add_prop(OBJ_I_VALUE, 138);
   add_prop(VK_NOBUY, 1);
}

init()
{
   ::init();
   ADA("pluck");
   ADA("strum");
}

int pluck(string str)
{
    if ((str=="lyre")||(str=="strings")) 
    {
      write("You pluck the strings of the lyre, creating a soft musical " +
            "sound.\n");
      say(QCTNAME(TP)+ " plucks the strings of the lyre, creating soft " +
            "musical sounds.\n");
      return 1;
    }
    NF("Pluck what?\n");
   return 0;
}

int strum(string str)
{
    if ((str=="lyre")||(str=="strings")) 
    {
      write("You strum the lyre, creating a myriad of music.\n");
      say(QCTNAME(TP)+ " strums the lyre, creating a myriad of music.\n");
      return 1;
    }
    NF("Strum what?\n");
   return 0;
}



