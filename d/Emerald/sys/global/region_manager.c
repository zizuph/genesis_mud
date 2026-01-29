#pragma strict_types
#pragma no_clone
#pragma no_shadow
#pragma no_inherit

#include "/d/Emerald/sys/region.h"

static private mapping regions = ([]);
private string *region_paths = ({});

mixed
get_region_name(string region_path)
{
    string name;
    if (catch(name = region_path->query_region_name()))
    {
        return 0;
    }

    return name;
}

void
save()
{
    setuid();
    seteuid(getuid());
    save_object(REGION_SAVE_FILE);
}

nomask void
create()
{
    setuid();
    seteuid(getuid());
    restore_object(REGION_SAVE_FILE);
    regions = mkmapping(map(region_paths, get_region_name), region_paths);
    regions = m_delete(regions, 0);
}

void
add_region(string path)
{
    regions += ({ path });
    save();
}

string
query_region_path(string name)
{
    return regions[name];
}
