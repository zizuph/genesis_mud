#include "militia.h"

void
notify_death(object killer)
{
    ::notify_death(killer);
 
    setuid();
    seteuid(getuid(this_object()));
 
    /* Militia members get one warning. */
    if (!IS_MILITIA(killer))
        MJOIN->add_not_allowed(killer->query_real_name());
}
