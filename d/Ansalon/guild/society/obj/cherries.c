/* 
 * /d/Ansalon/guild/society/obj/cherries.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Ripe Kendermore cherries 
 * Gwyneth, September 1999
 */
inherit "/std/food";
#include <macros.h>
#include "/d/Ansalon/guild/society/guild.h"

void
create_food()
{
    set_name("cherries");
    add_name("fruit");
    add_name("cherry");
    set_adj("ripe");
    add_adj("red");
    set_short("handful of ripe red cherries");
    set_pshort("handfuls of ripe red cherries");
    set_long("The deep red of each cherry tells you that these fruits " + 
        "are juicy and ripe to perfection.\n");
    set_amount(40);
}

public void
special_effect(int amnt)
{
    setuid();
    seteuid(getuid(this_object()));
    write("You squeeze the pits from the juicy cherries and pop them into " + 
        "your mouth. You lick the juice from your lips as you savor " + 
        "their sweetness.\n");
    say(QCTNAME(this_player()) + " squeezes the pits from the juicy " +
        "cherries and pops them into " + this_player()->query_possessive() +
        " mouth. " + capitalize(this_player()->query_pronoun()) + " licks " +
        "the juice from " + this_player()->query_possessive() + " lips.\n");

    clone_object(KGOBJ + "pit")->move(this_player());
    clone_object(KGOBJ + "pit")->move(this_player());
    clone_object(KGOBJ + "pit")->move(this_player());
    clone_object(KGOBJ + "pit")->move(this_player());

}

