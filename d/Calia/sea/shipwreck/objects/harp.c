/*   harp.c
 *
 * A small neat silver harp
 *
 * Baldacin@Genesis, July 2003
 */
inherit "/std/object";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("harp");
    set_adj("beautiful");
    add_adj("silver");
    set_short("beautiful silver harp");                    
    set_long("A large musical instrument that consists of "+
      "an upright triangular frame fitted with forty-six "+
      "strings of graduated lengths. You can 'play' it.\n");

    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VALUE, 5);
    
}

int
play(string str)
{
    notify_fail("play what? the harp?\n");
    
    if(!strlen(str))
        return 0;
   
    if (str == "harp" || str == "the harp")
    {
        write("You play the harp, creating a peaceful ringing sound.\n"+
          "Plingili-plong\n");
        say(QCTNAME(this_player()) + " plays "+ HIS(TP)+ 
          " harp creating a peaceful ringing sound.\n"+
	  "Plingili-plong\n");	  
	return 1;
    }
    return 0;
}

void
init()
{
   ::init();
   add_action(play, "play");
}