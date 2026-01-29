/*
 * ped_sword.c
 *
 * "the sword in the stone", this sword is a longsword found embedded in
 * a pedestal (~Calia/eldoral/objects/pedestal.c) in the heart of the
 * catacombs beneath Castle Chimera (~Calia/eldoral/ruins/catacomb_hub.c).
 * While the sword itself is nothing fantastic (a good weapon, but not
 * great), it's primary role is that people carrying it can get through
 * a hidden door that lets them reach Firestorm for the final quest(s) in
 * Eldoral.
 *
 * Coded by Khail, Dec. 23/96
 *
 * Petros - September 20008 - Corrected typo to remove double "the"
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <wa_types.h>

#define HIT 20
#define PEN 20

inherit "/std/weapon";

public int do_raise(string str);

public string
exa_letters()
{
    if (TP->query_skill(SS_LANGUAGE) < 65)
        return "The letters are like nothing you've seen before, " +
            "the language must be very old indeed. Unfortunately, " +
            "you are completely unable to decipher them.\n";
    else
        return "The letters are like nothing you've seen before, " +
            "and the language ancient, lost to these lands for " +
            "hundreds of years. You have only seen it once before, " +
            "in your books on some of the more 'honoured' languages " +
            "of days long gone, as used in Calia long before what is " +
            "known as the Dim Time. That would probably explain why " +
            "the weapon beautiful, but not incredibly good as a weapon. " +
            "You translate the letters, as closely as possible, to " +
            "this:\n\tFirestorm, by the Lord be thee bound, by this blade " +
            "be thee found.\n";
}

public void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    add_name(SHIMMERING_SWORD_NAME);
    set_adj("ancient");
    add_adj("shimmering");
    set_short("ancient shimmering longsword"); 
    set_pshort("ancient shimmering longswords"); 
    set_long("This longsword is of incredibly ancient design, the " +
        "long steel blade has a high shine, an almost mirror-like " +
        "finish, with strange lettering written down it's length. " +
        "The hilt itself is very intriguing, made from bronze and " +
        "polished to a bright gleam, it has been sculpted to resemble " +
        "two small dragons intertwined. Their bodies form the handle, " +
        "their bodies face-to-face with spread wings forming " +
        "the main crosspiece. Their heads are arched backwards, with " +
        "the blade emerging from in between, forming a second, smaller " +
        "V-shaped crossguard in front of the main one.\n");
    add_item(({"lettering", "letters", "lettering on blade",
        "letters on blade", "lettering on sword", "letters on the " +
        "sword"}), "@@exa_letters");
    add_cmd_item(({"lettering", "letters", "lettering on blade",
        "letters on blade", "lettering on sword", "letters on sword"}),
        ({"read"}), "@@exa_letters");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_SWORD));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
    add_prop(OBJ_M_NO_BUY, 1);
}

public void
init()
{
    ::init();
    add_action(do_raise, "raise");
}

public int
do_raise(string str)
{
    object ob;

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "%o [above] [my] [head]", ob))
        return 0;

    if (ob != TO)
        return 0;

    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, ob))
    {
        notify_fail("Raise what?\n");
        return 0;
    }

    if (TP->query_weapon(W_RIGHT) && TP->query_weapon(W_LEFT))
    {
        notify_fail("You will need a free hand to raise the " +
            short() + ".\n");
        return 0;
    }

    if (!environment(TP)->query_dragon_door_room())
    {
        write("You raise the " + short() + " above your head, " +
            "but it does nothing.\n");
        say(QCTNAME(TP) + " raises " + LANG_ADDART(short()) + " " +
            "above " + TP->query_possessive() + " head.\n");
        return 1;
    }

    write("You raise the " + short() + " above your head, and " +
        "you begin to feel a strange, pulsing sensation from " +
        "within it.\n");
    say(QCTNAME(TP) + " raises " + LANG_ADDART(short()) + " above " +
        TP->query_possessive() + " head, and a look of awe passes " +
        "over " + TP->query_possessive() + " face.\n");
    environment(TP)->pass_door(TP);
    return 1;
}
    
