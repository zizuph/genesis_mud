/* SaMorgan village guard sergeant
 * Tapakah, 04/2021
 */


#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit SM_WARRIOR;

public void
create_khalakhor_elf ()
{
  set_samorgan_level(3);
  ::create_khalakhor_elf();  
  add_name("sergeant");
  set_short("This is SaMorgan guard sergeant.");
}
