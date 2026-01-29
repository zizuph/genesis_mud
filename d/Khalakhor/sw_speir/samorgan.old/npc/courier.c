/* SaMorgan village guard courier
 * Tapakah, 04/2021
 */


#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit SM_WARRIOR;

public void
create_khalakhor_elf ()
{
  set_samorgan_level(1mbs);
  ::create_khalakhor_elf();  
  add_name("courier");
  set_short("This is SaMorgan guard courier.");
}
