/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit STDROOM;


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("log cabin.");
    set_long("Inside Dolmoors log cabin. " +
       "Mortals shouldn't be in here. Please buglog " +
       "your method of obtaining access to the cabin.\n");



    reset_room();
}


