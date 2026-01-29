/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/silver/forest";




public void
create_room()
{
    ::create_room();
    set_long_desc(0);
    set_short_desc(0);

    reset_room();
}


