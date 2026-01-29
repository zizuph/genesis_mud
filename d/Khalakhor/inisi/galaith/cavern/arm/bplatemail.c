/**********************************************************************
 * - bplatemail.c                                                   - *
 * - Found on NPC's Galaith Isle, cavern                            - *
 * - Created by Damaris 6/15/2002                                   - *
 **********************************************************************/
#pragma strict_types

inherit "/std/armour";
#include "/d/Raumdor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("platemail");
    add_name("mail");
    set_adj(({"dingy", "black", "steel","plate"}));
    set_short("dingy black platemail");
    set_long("This "+ short() +" is a finely crafted piece of platemail. "+
      "It is made from the finest steel but is a bit dingy to look at.\n");
    add_item(({"lames", "lame"}),
      "The lames are made of black steel and there are "+
      "nine over the breast of the "+ short() +".\n");
    set_ac(36);
    set_at(A_BODY);
    set_am(({3, 3, 2}));
    set_af(this_object());
}
