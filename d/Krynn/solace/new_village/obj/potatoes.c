/* The potatoes served at the Inn of Last homes. */
/* Added revelation for OotS - Arman 2017 */

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/OotS/defs.h"

create_food()
{
    set_short("plate of spiced potatoes");
    set_pshort("plates of spiced potatoes");
    set_name("potatoes");
    set_pname("potatoes");
    add_name("plate");
    add_pname("plates");
    set_adj("spiced");
    set_long("These spiced potatoes give off an amazing aroma. " +
             "Just looking at them is enough to send your " +
             "salivations into overdrive.\n");
    set_amount(351);
}

public void 
special_effect(int amnt)
{
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "innfellows"))
          {
            TP->catch_msg("\n\nYour first mouthful of Otik's famous spiced potatoes " +
                "triggers a divine revelation!\n\n\n");
            OOTS_ADD_REV(TP,"innfellows","enlightenment - the innfellows");  
          }
    }
}

