#include "defs.h"
inherit MAZE + "maze";

void
create_maze()
{
    string str;

    set_short("beneath the pool of mist");
  
    set_long("Overhead is a churning pool of mist "
       + "clinging to the ceiling. It flows along "
       + "like a river, or a snake, seeming to move "
	   + "with intent through the doorways. " 
	   +  ::query_long());


}
 
/* reset the words */
void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if(to->query_prop(WORD_PROP))
    {
        to->remove_prop(WORD_PROP);
        set_alarm(1.0, 0.0, &tell_object(to, "You feel you are at the beginning again.\n"));
    }
}


 
