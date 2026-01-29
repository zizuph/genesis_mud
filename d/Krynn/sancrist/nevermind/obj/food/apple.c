/*
 * File:          /d/Krynn/gnome/obj/food/apple.c
 * Creator:       Shadowlynx
 * Date:          June/97
 * Purpose:       This is an apple, which can be used in the
 *                inventor's module MasterBakerFritterMaker
 *                or eaten as a food. Sometimes when taking
 *                a bite from this apple, you may encounter
 *                a worm living within the apple.
 */

#pragma save_binary

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

/* prototypes */
public int    eat_apple(string str);

object   worm;

void
create_food()
{
    set_name("apple");
    add_pname("apples");
    set_adj(({"juicy","red"}));
    set_short("juicy red apple");
    set_long("It looks very tasty.\n");
    set_amount(110);
}

public int
eat_apple(string str)
{
    object   worm;


    worm = clone_object("/d/Wiz/shadowlynx/obj/worm");
    worm->move(TO);
    write("You take a bite from the juicy red apple, only to" +
      " discover a big fat ugly worm staring back at you. You" +
      " throw the apple away in disgust.\n");
    say(QCTNAME(TP)+" takes a bite from a juicy red apple, only" +
      " to discover a big fat ugly worm staring back at" +
      " "+POSSESSIVE(TP)+". You watch "+POSSESSIVE(TP)+" throw the" +
      " apple away in disgust.\n");
    TO->remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(eat_apple,"eat");
}
