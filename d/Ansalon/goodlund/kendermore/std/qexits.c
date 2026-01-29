#include "../local.h"
#include "/d/Ansalon/common/defs.h"
inherit KENDERMORE_OUT;

string
find_exits()
{
    string *ob_exits;
    string exit1;
    string exit2;
    string exit3;
    ob_exits = TO->query_obvious_exits();
    /*
    exit1 = ob_exits[0];
    exit2 = ob_exits[1];
    exit3 = ob_exits[2];
    */

    if (sizeof(ob_exits) == 1)
    {
        exit1 = ob_exits[0];
        return exit1;
    }

    if (sizeof(ob_exits) == 2)
	{
        exit1 = ob_exits[0];
        exit2 = ob_exits[1];
        return (exit1 + " and " + exit2);
        }

    if (sizeof(ob_exits) == 3)
        {
        exit1 = ob_exits[0];
        exit2 = ob_exits[1];
        exit3 = ob_exits[2];
        return (exit1 + ", " + exit2 + " and " + exit3);
        }

    else
        return "";
}

