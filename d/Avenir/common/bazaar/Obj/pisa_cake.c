#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";
int amount_left = 5;

public void
create_object()
{
    set_name("piece of a cake");
    add_name("cake");
    add_name("birthday cake");
    set_long("@@desc_piece");
    set_short("piece of a princess cake");
}


void
init()
{
    ::init();
        add_action("eat", "eat");
}

string
desc_piece()
{
    string text;

    switch (amount_left)
    {
        case 1:
        {
            text = "There is only one bite left of the cake " +
                "piece. You wish you had more...\n";
            return text;
            break;
        }
        case 2:
        {
    text = "There is still some left of the cake " +
        "piece, but not much. Enjoy as you can!\n";
    return text;
    break;
    }
    case 3..4:
    {
    text = "You feel the wight of the piece of cake " +
        "in your hand. Lovely. Still quite a lot " +
        "left for you to eat.\n";
    return text;
    break;
        }
        case 5:
        {
    text = "This is a newly cut piece of birthday " +
        "cake. Still untouched and just ready for " +
        "you to take a big bite from.\n";
    return text;
    break;
    }
    }

}

int
eat(string str)
{
    if (str == "cake" | str == "piece")
    {
    if (amount_left == 1)
    {
    write("You ate the last bit of your " +
        "cake piece. The last bit was as good " +
        "as the first and you wish you had one " +
        "more to eat.\n");
    remove_object();
    }
    write("You take a big bite of the piece of cake " +
        "and it is as good as you thought.\nMmmmm.\n");
    amount_left--;
    }
}

int
query_amount()
{
    return amount_left;
}

