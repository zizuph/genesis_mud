/* Scroll of congratulations. ~solace/puzzle/objects/congrat_scroll */

inherit "/std/scroll";

#include "../defs.h"
#include "/secure/std.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define MORE_OBJ       "/std/board/board_more"

#define SCROLL_FILE ({ "scroll_first_time.txt", "scroll_not_first_time.txt" })

void create_scroll()
{
    set_name("scroll");
    set_adj("tattered");
    add_adj("vellum");
    set_long("An old-looking scroll made of vellum. It glows faintly.\n"); 

    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}

int read_scroll(string str)
{
    int passed;

    if(!strlen(str))
        return 0;

    if(member_array(TO, FIND_STR_IN_OBJECT(str, TP)) != -1)
    {
        seteuid(getuid(TO));

        passed = TP->test_bit(getuid(TO), GROUP, BIT);

        if(query_verb() == "read")
            cat(MISC + SCROLL_FILE[passed]);
        else
            clone_object(MORE_OBJ)->more(MISC + SCROLL_FILE[passed], 2);

        if(!TP->query_invis())
            say(QCTNAME(TP)+" reads "+LANG_ADDART(short())+".\n");

        return 1;
    }
    else
         return 0;
}
