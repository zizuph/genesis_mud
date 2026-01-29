inherit "/std/shadow";

#include  "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

int is_running;
 

string
query_m_in()
{
    if (shadow_who->query_prop(LIVE_I_SNEAK) ||
      shadow_who->query_prop(LIVE_O_STEED))
	return shadow_who->query_m_in();
    if (is_running)
    {
	is_running = 0;
	return shadow_who->query_m_in();
    }
    return "arrives limping";
}

string 
query_m_out()
{
    if (shadow_who->query_prop(LIVE_I_SNEAK) ||
        shadow_who->query_prop(LIVE_O_STEED))
	return shadow_who->query_m_out();

    if (is_running)
    {
	    return shadow_who->query_m_in();
    }
    shadow_who->add_prop(LIMP_PROP,1);
    return "leaves limping";
}

public int
query_fogey_limp_shadow()
{
    return 1;
}

public void
run_away()
{
    is_running = 1;
    shadow_who->run_away();
}

void
remove_fogey_limp_shadow()
{
    if (!shadow_who->query_wiz_level())
	shadow_who->remove_autoshadow(MASTER +":");
    remove_shadow();
}

public int
shadow_me(mixed to_shadow)
{
    int flag;

    flag = ::shadow_me(to_shadow);

    if (flag) // Shadowing was successful
    {
        shadow_who->add_prop(LIMP_PROP,1);
	    if (!shadow_who->query_wiz_level())
	        shadow_who->add_autoshadow(MASTER +":");
    }
    
    return flag;
}
