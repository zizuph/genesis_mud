/*
 * Test Captain
 * 
 * Created by Petros, April 2009
 */
 
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include "../ships.h"

inherit STDCAPTAIN;

static void
create_captain()
{
    ::create_captain();

    set_name("test_captain");
    add_name("captain");
    add_name("_test_captain");
    set_race_name("human");
}
