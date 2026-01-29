/*
 *  /d/Gondor/clubs/nisse/obj/ice_tea_lemon.c
 *
 *  An ice tea with a slice of lemon.
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
    set_short("dewy glass of ice tea with a slice of lemon");
    set_pshort("dewy glasses of ice tea with a slice of lemon");
    set_long("You look closer at the dewy glass of ice tea. It has " +
             "light brown colour. It seems to be really cold. " +
             "There is a straw and a slice of lemon on the glass.\n");

    add_item(({"slice", "lemon"}),
             ("A slice of lemon adorns the glass.\n"));
             
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
    int num;
    
    if (str != "lemon" && str != "slice" && str != "slice of lemon")
        return 0;
    {
        write("You take the slice of lemon from your glass of ice tea " +
              "and eat it.\nAaaah, it is so refreshing!\n");
        say(QCTNAME(TP) + " takes the slice of lemon from " + POSSESSIVE(TP) +
            " glass of ice tea and eats it.\n");
        num = this_object()->num_heap();
        num = num - 1;
        this_object()->set_heap_size(num);
        clone_object(NISSE_OBJ_DIR + "ice_tea")->move(TP);
        return 1;
    }
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
    if (str != "lemon" && str != "slice" && str != "slice of lemon")
    {
        return 0;
    }

    write("You lick the slice of lemon on your glass of ice tea.\n" +
          "Aaaah, it is so refreshing!\n");
    say(QCTNAME(TP) + " licks the slice of lemon on " + POSSESSIVE(TP) +
        " glass of ice tea.\n");
    return 1;
}

void
init()
{
    ::init();
    
    add_action(sip_drink, "sip");
    add_action(eat_slice, "eat");
    add_action(lick_slice, "lick");
}
