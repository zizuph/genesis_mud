/*
 *  /d/Gondor/clubs/nisse/obj/grog.c
 *
 *  A hot grog.
 *
 *  Deagol, September 2002
 */

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

int cold_drink();

void
create_drink()
{
    ::create_drink();

    set_name("grog");
    add_name("mug");
    set_pname("grogs");
    add_pname("mugs");
    set_short("mug of hot grog");
    set_pshort("mugs of hot grog");
    set_long("You look closer at the " + short() + ". It has " +
             "dark golden colour. It was made of the best gondorian " +
             "rum, spring boiled water, cinnamon stick and sugar. " +
             "As it is warm, you can warm your hands on the mug.\n");

    add_prop(OBJ_I_VALUE, 75);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);

    set_soft_amount(200);
    set_alco_amount(25);

    setuid();
    seteuid(getuid());
    
    set_alarm(1200.0, 0.0, &cold_drink());
}

/*
 *  Function name: cold_drink
 *  Description  : It clones a cold grog into the player's inventory and
 *                 destructs itself.
 *  Returns      : always 1
 */
int
cold_drink()
{
        clone_object(NISSE_OBJ_DIR + "cold_grog")->move(ENV(TO));
        TO->remove_object();
        return 1;
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

    write("You sip your hot grog. Smooth aroma of the best gondorian " +
          "rum breezes your nose and delicious taste hits your " +
          "tongue.\n");
    say(QCTNAME(TP) + " sips " + POSSESSIVE(TP) + " hot grog.\n");
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
        notify_fail("Warm what? Maybe your hands on the mug of grog?\n");
        return 0;
    }

    write("You put your hands on the mug of hot grog to warm them.\n" +
          "Aaaah, it is fairly warm! You feel better.\n");
    say(QCTNAME(TP) + " warms " + POSSESSIVE(TP) +
        " hands on the mug of hot grog.\n");
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(sip_drink, "sip");
    add_action(warm_hands, "warm");
}
