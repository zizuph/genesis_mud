/* SaMorgan village guard courier
 * Tapakah, 04/2021
 */

#include "../defs.h"

inherit SM_WARRIOR;

public void
create_khalakhor_elf ()
{
  set_samorgan_level(SM_COURIER_LEVEL);
  ::create_khalakhor_elf();  
  set_name("courier");
  set_short("SaMorgan courier");
  set_long("This is SaMorgan guard courier. He carries messages between "+
           "different towers, and sometimes to the outposts and even "+
           "to Port Macdunn. His young face dreams of combat rather "+
           "errand running, though.\n");
}
