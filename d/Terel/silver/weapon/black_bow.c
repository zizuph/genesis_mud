/*
  Simple bow,
            by Udana, 1/02/06

  It calls wielding npc method to wield secondary weapon if bowstring breaks
  or such.
*/


#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#define HNT query_wielded()

inherit "/std/bow";

void wield_melee();


public void
create_bow()
{
    set_adj(({"wooden", "short", "black"}));
    add_name("shortbow");
    add_name("_romme_eq_");
    set_short("black shortbow");
    set_long("This bow has been made of some uncommon black "+
              "wood. It's short enough to be used from horseback "+
              "and curved in the way that grants good stringing "+
              "despite it's length.\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(37, 41));

    set_hit(39);
    set_pen(40);
    
    seteuid(getuid(TO));
}



public varargs void
did_parry(object att, int aid, int dt)
{
    if (query_stringed() && !random(F_BOWSTRING_SNAP_CHANCE))
    {
        set_alarm(1.0, 0.0, &wield_melee());
        snap_string();
    }
}

void remove_broken()
{
    set_alarm(1.0, 0.0, &wield_melee());
    ::remove_broken();
}

void wield_melee()
{
 E(TO)->wield_melee();
}

