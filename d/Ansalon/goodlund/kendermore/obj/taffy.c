/* Taffy candy from Kendermore, Gwyneth, May 1999 */

inherit "/std/food";
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

#define adjecs query_adjs()
string *adjs=({"white", "pink", "orange", "green", "yellow"});

void
create_food()
{
    set_name("taffy");
    set_pname("taffies");
    add_name("candy");
    add_pname("candies");
    set_adj("sweet");
    add_adj(adjs[random(5)]);
    set_long("Wrapped in a piece of plain wax paper, you know this " + 
             "piece of taffy will be deliciously sweet and chewy.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}

void
init()
{
    ::init();
    add_action("stretch_taffy", "pull");
}

/* Function name: stretch
 * Description: This allows a person to pull and stretch their taffy
*/

int
stretch_taffy(string str)
{
    NF("Pull what?\n");
    if ((str == "taffy") || (str == "candy"))
    {
        write("You pull and stretch on your sweet " + adjecs[1] + " taffy " + 
              "to make it nice and chewy.\n");
        say(QCTNAME(TP) + " pulls and stretches " + HIS(TP) + " sweet " + 
              adjecs[1] + " taffy\n");
        return 1;
    }
    return 0;
}
    
