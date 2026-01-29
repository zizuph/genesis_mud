//-*-C++-*-
// robe         /d/Avenir/common/holm/obj/robe.c
// creator(s):  Lilith 06 April 1997 
// revised:     
// purpose:     Something for the priests to wear. 
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/armour";

#include "../holm.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("robe");
    add_name("cassock");
    set_adj(({"nubby", "wool"}));
    set_short("nubby wool cassock");
    set_long("This long, loose-fitting garment is woven of highest-"+
        "quality wool. It is ankle-length with slits up the sides "+
        "to knee height, providing ample leg-room.\n");
   set_ac(random(2) + 2);
   set_at(A_ROBE);

}


