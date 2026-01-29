/*
 *  /d/Gondor/clubs/nisse/obj/ice_tea.c
 *
 *  An ice tea without a slice (of elf or lemon). This object is called by
 *  ice_tea_lemon.c after player eat a slice of lemon.
 *
 *  Deagol, August 2002
 */

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_drink()
{
    ::create_drink();
    
    set_name("ice tea");
    add_name(({"glass", "tea"}));
    set_pname("ice tea");
    add_pname("glasses");
    set_short("dewy glass of ice tea");
    set_pshort("dewy glasses of ice tea");
    set_long("You look closer at the dewy glass of ice tea. It has " +
             "light brown colour. It seems to be really cold. " +
             "There is a straw in the tea.\n");

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 180);

    set_soft_amount(180);
    set_alco_amount(0);
    
    setuid();
    seteuid(getuid());
}

/*
 *  Function name: sip_drink
 *  Description  : What happens when a player sips this drink?
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
sip_drink(string str)
{
    if (str != "glass" && str != "tea" && str != "ice tea"
        && str != "glass of ice tea" && str != "drink")
    {
        notify_fail("Sip what? Maybe the glass of ice tea?\n");
        return 0;
    }

    write("You sip your ice tea with a straw.\n" +
          "It is quite refreshing!\n");
    say(QCTNAME(TP) + " sips " + POSSESSIVE(TP) + " ice tea with " +
        "a straw.\n");
    return 1;
}

/*
 *  Function name: eat_slice
 *  Description  : What happens when a player tries to eat a slice of lemon?
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
eat_slice(string str)
{
    if (str != "lemon" && str != "slice" && str != "slice of lemon"
        && str != "slice of elf")
    {
        return 0;
    }

    write("Hey! You've already eaten it!\n");
    return 1;
}

/*
 *  Function name: lick_slice
 *  Description  : What happens when a player tries to lick a slice?
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
lick_slice(string str)
{
    if (str != "lemon" && str != "slice" && str != "slice of lemon"
        && str != "slice of elf")
    {
        return 0;
    }

    write("How do you want to lick it? You ate it.\n");
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(sip_drink, "sip");
    add_action(eat_slice, "eat");
    add_action(lick_slice, "lick");
}
