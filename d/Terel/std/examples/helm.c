/*
 * Quick steps to use this size-based armour file:
 * Inherit ~Terel/std/new_armour, define create_terel_armour,
 * call set_armour_size in it (SMALL, MEDIUM, LARGE, HUGE
 * ANY_SIZE, or a combination of these). If you want to
 * check certain conditions before allowing a player to wear
 * this armour define wear_terel_armour, otherwise the function
 * is not needed.
 *
 * NOTE: SMALL - gnome, goblin, hobbit, kender
 *       SMALL/MEDIUM - dwarf
 *       MEDIUM - elf, half-elf, human
 *       MEDIUM/LARGE - centaur
 *       LARGE - troll, ogre
 *       LARGE/HUGE - giant
 *       HUGE - dragon
 *       ANY_SIZE - shapeshifter?
 * SMALL = 1 MEDIUM = 2 LARGE = 4 HUGE = 8 ANY_SIZE = 15
 * SMALL/MEDIUM = 3 MEDIUM/LARGE = 6 LARGE/HUGE = 12
 *
 * Feel free to add new races and their corresponding
 * sizes to the race size tracker. If you possess ~Terel/open/medallion
 * simply type 'racesize <race> <size>' to add a race. For example
 * 'racesize elf 2' would mean elves are considered medium sized.
 */

#pragma strict_types


#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>
#include <ss_types.h>

void create_terel_armour()
{
    set_name("helm");
    set_adj(({"black","steel"}));
    set_short("black steel helm");
    set_long("This is a black steel helm.\n");
    set_default_armour(15, A_HEAD, ({1,0,-1}), TO);
    /* make this helm wearable by small or medium sized races */
    set_armour_size(SMALL | MEDIUM);

    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VALUE, 200);
}

/* returns  0 - wear armour normally
 *          1 - wear armour normally, print no message
 *         -1 - cant wear armour, print no message
 *          string - cant wear armour, use this message
 */

public mixed
wear_terel_armour(object obj)
{
    if (TP->query_stat(SS_STR) < 40)
        return "You are too weak to wear that.\n";

    write("You slide the helm over your head.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" slides "+
        "the "+TO->query_short()+" over his head.\n",TP);
    return 1;
}
