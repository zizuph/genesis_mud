/*   chest.c
 *
 *  A small chest located in the Captain's cabin.
 *
 * Baldacin@Genesis, Aug 2003
 */
 
inherit "/std/receptacle";
#include "defs.h"
#include "/sys/stdproperties.h";
#include <macros.h>
 
void create_receptacle() 
{
    set_name("chest");
    set_adj("small");
    set_long("It is a a small wooden chest, only big enough to "+
      "hold a few personal items.\n");
 
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_VOLUME, 7000);
    add_prop(CONT_I_RIGID,  1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_NO_GET,  1);
    
    setuid();
    seteuid(getuid());
    clone_object(OBJ + "rope")->move(TO, 1);
}
