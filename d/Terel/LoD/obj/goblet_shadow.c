inherit "/std/shadow";

#include <macros.h>
#include <std.h>

object goblet;

/* Don't autoload this shadow!! */

public void
autoload_shadow(mixed arg)
{
    remove_shadow();
}

public void
set_goblet(object ob)
{
    goblet = ob;
}

public void
do_die(object killer)
{
    object who = query_shadow_who();
    
    if (who->query_hp() > 0 || who->query_ghost())
    {
        return;
    }
        
    if (goblet)
    {
        goblet->solver_died(who, killer);
    }
    
    who->do_die(killer);
}
