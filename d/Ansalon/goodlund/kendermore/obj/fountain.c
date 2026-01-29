/* Wishing fountain for Kendermore. Gwyneth 05/17/99 */

inherit "/std/container";
inherit "/lib/trade";

#include <cmdparse.h>
#include <files.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

int red = 0;

string
water_desc()
{
    if(!red)
    {
        return "water";
    }
    else
    {
        return "red liquid";
    }
}

string
water_cdesc()
{
    if(!red)
    {
        return "Water";
    }
    else
    {
        return "Red liquid";
    }
}

string
water_item()
{
    if(red)
    {
        return "The red liquid looks good enough to drink.\n";
    }
    else
    {
        return "The sparkling water looks good enough to drink.\n";
    }
}

void
create_container()
{
    set_name("fountain");
    set_pname("fountains");
    set_adj("water");
    set_short("water fountain");
    set_long("Sparkling clear " + "@@water_desc@@" + " bursts from a " +
        "statue in the center of " +
        "the fountain. It is made of white marble stone, and there are some " + 
        "coins tossed in the " + "@@water_desc@@" + ".\n");
    set_pshort("water fountains");
    add_item(({"water", "red liquid", "liquid"}), "@@water_item");
    add_item("statue", "It is a full size kender holding his hands out. " +
            "He has a joyful expression as he watches a stream of " +
            "@@water_desc@@" + " shoot from his hands.\n");
    add_item("expression", "You can see a look of wonder and joy radiating " + 
        "from the statue's face.\n");
    add_item(({"hands", "stream", "arch"}), "@@water_cdesc@@" +
        " shoots into a sparkling arch from the statue's hands.\n");
    add_cmd_item(({"fountain", "in fountain"}), 
        ({"enter", "wade", "swim"}), "@@enter_fount");
    add_cmd_item(({"into fountain", "in fountain"}), "dive", "@@dive_fount");

    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(OBJ_I_VALUE, 50);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_M_NO_REM, "@@get_message");
    add_prop(CONT_M_NO_INS, "@@put_message");
}

int
is_red()
{
    return red;
}

string
enter_fount()
{
    NF("Enter what?\n");
    write("People drink from here! Go bathe in a river!\n");
    return "";
}

string
dive_fount()
{
    NF("Dive into what?\n");
    write("I'm afraid the fountain isn't deep enough to dive into.\n");
    return "";
}

string
put_message()
{
    return ("Only coins should be tossed into the fountain to make a wish. " +
        "Other things should be kept out. After all, people do drink from " +
        "here!\n");
}

mixed
get_message(string str)
{
    if (str == "water")
    {
        return("You try to scoop up some " + "@@water_desc@@" + ", but " +
            "it slips through your " +
            "fingers.\n");
    }

    if ((str == "coin") || (str == "coins") || (str == "platinum coin") ||
        (str == "platinum coins") || (str == "gold coin") ||
        (str == "gold coins") || (str == "silver coin") ||
        (str == "silver coins") || (str == "copper coin") ||
        (str == "copper coins") + "from fountain") 
    {
        return("Leave the coins alone! They are other peoples' wishes!\n");
    }

    else
        return 1;
}

void
turn_clear()
{
    red = 0;
    
    tell_room(environment(TO), "The pale red liquid disappears and is " +
        "replaced by pure clear water.\n");
}

void
turn_red()
{
    red = 1;
    
    set_alarm(60.0, 0.0, &turn_clear());
}

int
pour_juice(string str)
{
    int i, juice_present = 0;
    int sz;
    mixed *oblist;
    string *names;

    if(!str)
    {
        NF("Pour what?\n");
        return 0;
    }

    if(!parse_command(str, all_inventory(TP),
        "[the] %i [in] [into] [the] [a] [water] [fountain]", oblist))
    {
        NF("Pour what?\n");
        return 0;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if(!sizeof(oblist))
    {
        NF("Pour what?\n");
        return 0;
    }

    if(sizeof(oblist) > 1)
    {
        NF("Pour one at a time, or things might get messy.\n");
        return 0;
    }

    if(!IS_DRINK_OBJECT(oblist[0]))
    {
        NF("You can't pour that into the water fountain.\n");
        return 0;
    }

    names = oblist[0]->query_names();

    sz = sizeof(names);

    for (i = 0; i < sz; i++)
    {
        if(names[i] == "_kendermore_berry_juice")
        {
            juice_present = 1;
        }
    }

    if(!juice_present)
    {
        write("You pour " + oblist[0]->short() + " into " +
            "the " + short() + ".\n");
        tell_room(environment(TO), QCTNAME(TP) + " pours " +
            oblist[0]->short() + " into the " + short() + ".\n", TP);
        oblist[0]->remove_object();
        return 1;
    }

    else
    {
        write("You pour " + oblist[0]->short() + " into the " +
            short() + ".\nThe " + short() + " turns a light shade of red.\n");
        tell_room(environment(TO), QCTNAME(TP) + " pours " +
            oblist[0]->short() + " into the " + short() + ".\nThe " +
            short() + " turns a light shade of red.\n", TP);
        oblist[0]->remove_object();
        turn_red();
        return 1;
    }
}

void
init()
{
    ::init();
    add_action("throw_coin", "throw");
    add_action("toss_coin", "toss");
    add_action("make_wish", "make");
    add_action("wish_for", "wish");
    add_action(pour_juice, "pour");
}

int
toss_coin(string str)
{
    if ((str == "coin") || (str == "coin in fountain") ||
        (str == "coin in water"))
    {
        write("Why don't you wish for something?\n");
        return 1;
    }

    NF("Toss what?\n");
    return 0;
}

int
throw_coin(string str)
{
    if ((str == "coin") || (str == "coin in fountain") ||
        (str == "coin in water"))
    {
        write("Why don't you wish for something?\n");
        return 1;
    }

    NF("Toss what?\n");
    return 0;
}

int
make_wish(string str)
{
    if ((str == "wish") || (str == "a wish"))
    {
        write("What would you like to wish for?\n");
        return 1;
    }

    NF("Make what? A wish?\n");
    return 0;
}
 
int
wish_for(string str)
{
    string type;

    remove_prop(CONT_M_NO_INS);
    if (!MONEY_MOVE_CC(1, TP, TO))
    {
        type = "copper";
    }
    else if (!MONEY_MOVE_SC(1, TP, TO))
    {
        type = "silver";
    }
    else if (!MONEY_MOVE_GC(1, TP, TO))
    {
        type = "gold";
    }
    else if (!MONEY_MOVE_PC(1, TP, TO))
    {
        type = "platinum";
    }
    else
    {
        write("You don't seem to have a coin to wish with!\n");
        add_prop(CONT_M_NO_INS, "@@put_message");
        return 1;
    }
    
    write("You close your eyes and wish " + str + ".\nYou toss a " + type +
        " coin into the fountain, hoping for your wish to come true.\n");
    say(QCTNAME(TP) + " closes " + HIS(TP) + " eyes, and tosses a " + type +
        " coin into the fountain.\n");
    add_prop(CONT_M_NO_INS, "@@put_message");
    return 1;
}

