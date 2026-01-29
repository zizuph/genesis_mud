// -*-C++-*-
// name: chest   /d/Avenir/common/ships/sparkle/chest.c
// creator(s):    Boriska, Mar 26 1995
// last update:   Kazz June 1995  Added a piece of Source.
// purpose:       To be placed in Sparkle-Avenir ship cabin
// note:
// bug(s):
// to-do:         

#include <money.h>
#include "/d/Avenir/common/ships/ship.h"

#pragma save_binary

inherit "/std/receptacle";

void
reset_receptacle()
{
    object source;
    status was_closed;
  
    if (query_prop(CONT_I_CLOSED)) 
    {
        add_prop(CONT_I_CLOSED, 0);
        was_closed = 1;
    }
    if (!present("rum"))
        clone_object(SPAR_DIR + "rum")->move(this_object(),1);
    if (!present("coin"))
        MONEY_MAKE_CC(2)->move(this_object(),1);
    if (was_closed)
        add_prop(CONT_I_CLOSED, 1);
  
    if (!present("source")) 
    {
      // clone one of the source light pieces, setting a specific value
      // instead of accepting the random (default) one.
        source = clone_object( OUTPOST + "obj/lsource" );
        source->set_volume( 5 );
        source->move( this_object(),1 );
    }
} // reset_receptacle()


void
create_receptacle()
{
    if (!IS_CLONE)
        return;
    set_name("chest");
    set_short("mahogany chest");
    set_long("Extremely heavy chest made of mahogany, covered with\n" +
	   "ornate golden plates and jewels. It must cost a fortune!\n");
    add_adj("mahogany");
    add_prop(OBJ_M_NO_GET, "The chest is firmly nailed to the floor.\n");
    add_prop(CONT_I_WEIGHT, 7000);
    add_prop(CONT_I_MAX_WEIGHT, 90000); 
    add_prop(CONT_I_VOLUME, 7000);
    add_prop(CONT_I_MAX_VOLUME, 90000);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(CONT_I_CLOSED, 1);
    seteuid(getuid());
    enable_reset();
    reset_receptacle();
}