/*
 *  /d/Gondor/clubs/nisse/obj/cold_grog.c
 *
 *  A cold grog.
 *
 *  Deagol, September 2002
 */

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_drink()
{
    ::create_drink();

    set_name("grog");
    add_name("mug");
    set_pname("grogs");
    add_pname("mugs");
    set_short("mug of cold grog");
    set_pshort("mugs of cold grog");
    set_long("You look closer at the " + short() + ". It has " +
             "dark golden colour. It was made of the best gondorian " +
             "rum, spring boiled water, cinnamon stick and sugar. " +
             "As it is cold, you cannot warm your hands on the mug " +
             "anymore.\n");

    setuid();
    seteuid(getuid());

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);

    set_soft_amount(200);
    set_alco_amount(25);
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
    if (!strlen(str) || !parse_command(str, ({}),
        "[the] [mug] [of] [hot] [grog]"))
    {
        notify_fail("Sip what? Maybe the mug of grog?\n");
        return 0;
    }

    write("You sip your cold grog. Delicious taste of the best " +
          "gondorian rum hits your tongue.\n");
    say(QCTNAME(TP) + " sips " + POSSESSIVE(TP) + " cold grog.\n");
    return 1;
}

/*
 *  Function name: warm_hands
 *  Description  : What happens when a player warms his/her hands on the mug.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
warm_hands(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "'hands' 'on' [the] [mug] [of] [grog]"))
    {
        notify_fail("Warm what?\n");
        return 0;
    }

    write("You put your hands on the mug of cold grog to warm them.\n" +
          "It is cold! You shiver.\n");
    say(QCTNAME(TP) + " tries to warm " + POSSESSIVE(TP) +
        " hands on the mug of cold grog. " + CAP(PRONOUN(TP)) +
        " shivers.\n");
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(sip_drink, "sip");
    add_action(warm_hands, "warm");
}
