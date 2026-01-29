/*
 * charity.c
 *
 * Used in nyreese/cadu_guild.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* a charity box, by Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    object ob;

    if (!IS_CLONE) return;

    set_name("box");
    set_short("golden charity box");
    set_adj(({"gold", "charity"}));
  
    add_prop(CONT_I_MAX_WEIGHT, 200000); /* lots of stuff */
    add_prop(CONT_I_MAX_VOLUME, 200000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(OBJ_I_NO_GET, 1);
  
    set_long("It's a rather large box, made of gold and valuable crystals.\n"+
             "A small sign is placed on one of the sides, close to the floor.\n");

    add_item("sign", "It looks readable.\n");
    add_cmd_item("sign", "read", 
                 "Feel free to take anything placed in this box.\n" +
                 "You may donate anything you like in it, to help your " +
                 "fellow adventurers.\n");
    seteuid(getuid(TO));

    clone_object(ROKEDIR + "wep/orc_knife")->move(TO);
    //ob = clone_object("/d/Roke/gresolle/cards");
    //ob->init_cards();
    //ob->move(TO);
}
