inherit "/std/food";
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

string *adjs=({"black", "red"});

void
create_food()
{
    string *colours;
    set_name("licorice");
    set_pname("licorices");
    add_name("whip");
    add_pname("whips");
    add_name("candy");
    add_pname("candies");
    set_adj("long");
    add_adj(adjs[random(2)]);
    colours = query_adjs();
    set_short("long whip of " + colours[1] + " licorice");
    set_pshort("long whips of licorice");
    set_long("This is one of the longest whips of " + colours[1] + 
             "licorice that you've ever seen. It is so long that you may " + 
             "even be able to crack it above your head.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}

void
init()
{
    ::init();
    add_action("crack_whip", "crack");
}

/* Function name: crack
 * Description: Gives an emote to go along with the licorice.
 * Returns : Null
 */

int
crack_whip(string str)
{
    NF("Crack what?\n");
    if ((str == "licorice") || (str == "whip"))
    {
        write("You swing the long whip of licorice above your " + 
              "head with a loud crack!\n");
        say(QCTNAME(TP) + " swings a long whip of licorice above " + HIS(TP) + 
              " head with a loud and startling crack!\n");
        return 1;
    }
    return 0;
}
