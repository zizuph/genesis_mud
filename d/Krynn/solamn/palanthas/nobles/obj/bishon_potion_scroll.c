/* A scroll outlining how to make swimming potions.
 * Arman, April 2021.
 */

inherit "/std/scroll";
inherit "/lib/keep";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <cmdparse.h>

#define SCROLLFILE "/d/Krynn/solamn/palanthas/nobles/obj/recipe.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"

void
create_scroll()
{
    set_name("recipe");
    add_name("scroll");
    add_name("_bishon_potion_scroll");
    set_pname("recipes");
    add_pname("scrolls");
    set_adj("water-damaged");
    set_adj("damaged");
    set_short("furled water-damaged recipe");
    add_adj("furled");
    set_pshort("water-damaged recipes");
    set_long("This recipe is currently furled, and is a bit " +
        "water damaged.\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    add_prop(OBJ_I_VALUE, 50 + (random(50)));
    add_prop(SCROLL_I_FURLED, 1);

    set_file(SCROLLFILE);
}

init()
{
    ADA("furl");
    ADA("unfurl");
    ::init();
}

int furl(string str)
{
    if((str=="recipe")||(str=="water-damaged recipe")||
      (str=="scroll")||(str=="water-damaged scroll"))
    {
        if (TO->query_prop(SCROLL_I_FURLED))
        {
            write("The " + query_short() + " is already furled!\n");
            return 1;
        }
        write("You furl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
        TO->add_prop(SCROLL_I_FURLED, 1);
        TO->remove_adj("unfurled");
        TO->set_short("furled water-damaged recipe");
        TO->add_adj("furled");
        TO->set_long("This water-damaged recipe is currently furled.\n");
        return 1;
    }
    NF("Furl what?\n");
    return 0;
}

int unfurl(string str)
{
    if((str=="recipe")||(str=="water-damaged recipe")||
      (str=="scroll")||(str=="aged scroll"))
    {
        if (!(TO->query_prop(SCROLL_I_FURLED)))
        {
            write("The " + query_short() + " is already unfurled!\n");
            return 1;
        }
        write("You unfurl the " + query_short() + ".\n");
        say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
        TO->remove_prop(SCROLL_I_FURLED);
        TO->remove_adj("furled");
        TO->set_short("unfurled water-damaged recipe");
        TO->add_adj("unfurled");
        TO->set_long("This is a torn-out page from " +
            "an alchemist's recipe book. It is slightly " +
            "water damaged, seemingly having been exposed " +
            "to salt water.\n");
        return 1;
    }
    NF("Unfurl what?\n");
    return 0;
}

public int
read_access(object ob)
{
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        NF("You can only read unfurled scrolls!\n");
        return 0;
    }
    NF("You must be holding the scroll to read it properly!\n");
    return ((E(ob) == TP) &&
      (function_exists("create_object", ob) == SCROLL_OBJECT));
}

string
scroll_content()
{
    return ""+
        " Potion of Swimming \n" +
        "    Description: sea-green potion\n\n" +
        "    The potion of swimming is a surprisingly simple potion\n" +
        "    to make. Even an amateur alchemist would have little\n" +
        "    trouble making it... assuming they can get hold of\n" +
        "    the main potion ingredient!\n\n" +
        "    For the primary ingredient you need to make a potion\n" +
        "    of swimming is the heart of a sea lion - a creature\n" +
        "    of mythical rarity. Hard to find, and even harder to\n" +
        "    slay!\n\n" +
        "    Instructions:        1x mortar\n" +
        "                         1x empty vial\n" +
        "                         1x sea lion heart\n" +
        "                         1x water\n\n" +
        "                         Put ingredients in mortar.\n" +
        "                         <mix> potion of swimming.\n\n";

}

/*
 * Function name: read_it
 * Description  : Perform the actual read. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - the command the player executed, only 'read'
 */
void
read_it(string str)
{
    int taskcheck;
    seteuid(getuid(TO));

    if (!scroll_file)
    {
        write("There was nothing to read on the " + QSHORT(TO) + ".\n");
        return;
    }

    if ((str == "read"))
    {
        write("You read the " + query_short() + ".\n");
        say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");

        write(generate_scroll_text(scroll_content(), "Treatise on " +
            "Istarian Alchemy ... page 9 of 44"));
    }

/*
    if ((str == "read") &&
      (file_size(scroll_file) < 4000))
    {
        write("You read the " + query_short() + ".\n");
        say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");
        cat(scroll_file);
    }
    else
    {
        if (file_size(scroll_file) >= 50000)
        {
            write("The scroll is too large to be read.\n");
            return;
        }
        TP->more(read_file(scroll_file));
    }
*/
}
