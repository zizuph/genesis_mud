#include "/d/Genesis/login/login.h"
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

public void
create_object()
{
    set_name("fixer");
    set_adj("width");
    set_short("weight fixer");
    set_long("This is a width fixer. It was made by Khail " +
        "to reset the weight and volume of a player by " +
        "resetting his width, identically to the method " +
        "used by the now-corrected calculation in the " +
        "new 'mangler'. Use the following command to " +
        "reset a player's width:\n" +
        "width <who> <widthval>\nWhere <widthval> " +
        "consists of " + COMPOSITE_WORDS(WIDTHDESC) + ".\n");

}

public int
do_width(string str)
{
    string *arr,
           who,
           width;
    int index,
        *attr,
        val,
        oldval;
    object target;

    notify_fail("Proper syntax: width <who> <widthval>\n");

    if (!str || !strlen(str))
        return 0;

    if (!this_player()->query_wiz_level())
    {
        write("Only wizards may use this.\n");
        return 1;
    }

    arr = explode(str, " ");

    if (sizeof(arr) < 2)
        return 0;

    who = arr[0];
    width = implode(arr[1..], " ");
    index = member_array(width, WIDTHDESC);

    if (!(objectp(target = find_player(lower_case(who)))))
    {
        write(capitalize(who) + " is not in the game.\n");
        return 1;
    }

    if (index < 0 || index > sizeof(WIDTHDESC))
    {
        write(capitalize(width) + " is not a valid width.\n");
        return 1;
    }

    attr = RACEATTR[target->query_race_name()];

    val = (attr[5] * target->query_prop(CONT_I_HEIGHT) *
        (index + 7) / 10);
    if (random(2))
        val = val - random(val * attr[5] / 8000);
    else
        val = val + random(val * attr[5] / 5000);

    oldval = target->query_prop(CONT_I_WEIGHT);
    target->add_prop(CONT_I_WEIGHT, val);
    target->add_prop(CONT_I_VOLUME, val);

    this_player()->catch_msg(QCTNAME(target) + "'s width changed to " +
        width + " with a prop value of " + val +
        " from " + oldval + ".\n");
    return 1;
}
        
public void
init()
{
    ::init();
    add_action(do_width, "width");
}