/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * store.c
 *
 * Ribos Town shop storeroom
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

reset_room()
{
/*   object anti;
   if(present("potion"))return;
   anti=clone_object("/d/Terel/vader/ribos/antidote");
   anti->move(this_object()); */
}

create_room() 
{
    ::create_room();
    set_short("The Ribos Shop's storage room");
    set_long("This is where the shopkeeper keeps his merchandise.\n");

    add_exit(RIBOS_DIR + "shop", "south");

    INSIDE;
    reset_room();
}
