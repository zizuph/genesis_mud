/*
 * Letter opener
 * Knick knack from Grey Havens for domain office
 * Thanks to Abeni for the idea.
 * Finwe, March 2004
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    seteuid(getuid());

    set_name("opener");
    add_name("letter opener");
    set_pname(({"letter openers", "openers"}));
    set_short("ornate letter opener");
    set_adj("ornate");
    set_long("This is a long thin blade used to open letters. The blade is " +
        "dull and probably wouldn't hurt anything. It is silver colored " +
        "and flat, and comes to a dull point at the end. The handle is " +
        "made of mother-of-pearl and carved to resemble a tree.\n");
    add_item(({"handle", "opener handle", "letter opener handle"}),
        "The handle is made of mother-of-pearl. Etched into it arethe " +
        "details of an exquisite tree. Beneath the tree you read the words: " +
        "From Mithlond.\n");
    add_item(({"tree", "exquisite tree"}),
        "The tree is expertly carved into the handle. The detail is so " +
        "great that you can see every blade and branch. The trunk is " +
        "highly detailed, too, with every nook and cranny visible. The " +
        "rough bark can be felt in your hand when you hold it. The " +
        "branches of the tree separate the blade from the rest of the " +
        "handle.\n");
    add_item(({"mother-of-pearl", "mother of pearl"}),
        "This is a hard, smooth, piece of iridescent shell. It is set " +
        "into the handle of the letter opener, and etched with the " +
        "detail of an exquisite tree.\n");
    

    set_default_weapon(5, 5, W_KNIFE, W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5, 5) + random(41));
}
