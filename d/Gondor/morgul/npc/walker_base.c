#include <macros.h>

inherit "/d/Gondor/common/lib/pathfind";

#include "/w/petros/open/debugger_tell.h"

private string get_area_from_filename(string str)
{
    string area, *dirs;
    if(sscanf(str, "/d/Gondor/%s", area) != 1) return 0;
    dirs = explode(area, "/");
    return implode(dirs[..-2], "/");
}

public int is_valid_room(mixed str)
{
    string area = get_area_from_filename(str);

    send_debug_message("WALKER", "Validating area " + area);
    if (area == "morgul/city") return 1;
    if (area == "morgul/tower") return 1;
    if (area == "ithilien/road") return 1;
    if (area == "ithilien/osgiliath") return 1;
    if (area == "morgul/road") return 1;
    return 0;
}

