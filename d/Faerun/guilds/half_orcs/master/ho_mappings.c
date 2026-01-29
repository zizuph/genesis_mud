/*
 * HO Guild manager, mappings
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";

void create();

mapping Ho_tusks;


public int
query_ho_tusks(string real_name)
{
    return Ho_tusks[lower_case(real_name)];
}


public void
set_ho_tusks(string real_name, int ho_nr)
{
    Ho_tusks = restore_map(HO_TUSKS);
    Ho_tusks[lower_case(real_name)] = ho_nr;
    save_map(Ho_tusks, HO_TUSKS);
}


public void
clean_ho_tusks(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ho_tusks[real_name])
    {
        Ho_tusks = m_delete(Ho_tusks, real_name);
        save_map(Ho_tusks, HO_TUSKS);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    Ho_tusks = restore_map(HO_TUSKS);
}
