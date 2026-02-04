
#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */

#include "../defs.h"

string * Tasted_blood=({ });

public int query_vamp_stat();

public string * query_known_scries()
{
    return query_manager()->query_known_scries(QSW);
}

public void set_known_scries(string * list)
{
    int max_size=min(10,query_vamp_stat() / 10);
    max_size=max(1,max_size);
    list=list[-max_size..];
    query_manager()->set_known_scries(QSW,list);
}

public string * query_tasted_blood()
{
    return Tasted_blood;
}

public void set_tasted_blood(string * list)
{
    Tasted_blood=list;
}

public void add_tasted_blood(string name)
{
    string * list=Tasted_blood;
    list-=({ name });
    list+=({ name });
    set_tasted_blood(list);
}


public object * query_available_scry_targets()
{
    string * available=query_tasted_blood();
    available+=query_known_scries() - query_tasted_blood();
    object * targets=({});
    foreach (string name: available)
    {
        object target=find_player(name);
        if (!interactive(target))
        {
            continue;
        }
        if (target->query_wiz_level())
        {
            continue;
        }
        targets+=({ find_player(name) });
    }
    targets-=({ 0 });
    return targets;
}
