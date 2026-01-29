
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"



public void create_gondor();


public void
create_gondor()
{
    set_short("in an armoury in Ithilien");
    set_long("You're in the Proving Grounds Armoury.\n\n");

    clone_object("/d/Shire/orcmaker/wep/ghalberd")->move(this_object());

    add_exit("xroads", "up");


}

