/*
 *
 * One handed Pulwar for the Haradrim soldiers. Replaces the Tulwar
 * -- Finwe, Jul 2005
 *
 *    Modification log:
 *             2006.08.27: Fixed a typo. Toby
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_name(({"pulwar","sword","weapon"}));
    set_pname("pulwars");
    add_pname("swords");
    set_short("long ornate pulwar");
    set_pshort("long ornate pulwars");
    set_long("This is a " + short() + ", the preferred blade of Haradrim " +
        "soldiers. The blade is long and slightly curved and " +
        "slimmer than other swords. One edge of the blade is sharpened " +
        "to allow the wielder to slash effectively. The handle is black " +
        "and rounded with two quillions between it and the blade. " +
        "Dark engravings decorate the blade of the one-handed pulwar.\n");
    add_item(({"blade"}),
        "The blade is long and slightly curved. It was forged of steel " +
        "and sharpened on one edge, and is decorated with dark engravings " +
        "at the base near the handle.\n");
    add_item(({"handle"}),
        "The handle is round and black. It is protected by two quillions " +
        "between the blade and the handle, and protect the wielder " +
        "during battle.\n");
    add_item(({"quillions", "quillion"}),
        "The quillions are short and turned upwards towards the blade. " +
        "They protect the hand during battle.\n");
    add_item(({"engravings", "engraving"}),
        "The engravings are both ornate and dark, and extend from the " +
        "quillions to halfway down the blade. Bloody scenes are depicted " +
        "beneath an all-seeing eye.\n");
    add_item(({"eye", "all-seeing eye", "lidless eye"}),
        "The eye is etched onto the blade beneath the quillions. It is " +
        "surrounded by fire and is cat-like, and appears to follow you " +
        "whenever you move the blade.\n");
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    set_hit(39);
    set_pen(40);
    
//    set_default_weapon(39,40,W_SWORD,W_SLASH,W_NONE,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
    set_keep(0);
}
