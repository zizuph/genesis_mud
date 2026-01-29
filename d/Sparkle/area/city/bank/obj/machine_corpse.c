/* 
 * Machine corpse for machines
 * FEB 2009, Aeg
 */
 
inherit "/std/corpse";
#include <stdproperties.h>
#include <macros.h>
 
void
create_corpse()
{
    set_name("parts");
    add_name("heap of parts");
    add_name("heap");
    set_short("heap of automaton");
    set_pshort("heaps of automaton");
    set_long("This is a heap of mechanical parts. It appears to have "
           + "come from a machine.\n");
          
}
