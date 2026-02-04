/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sword.c
 *
 * The famous darkness sword of the orcchief.  The idea with this sword
 * is that it should become dark when it it is wielded.
 *
 * The original code for this sword has been worked on by Commander,
 * Vader and Olorin.
 * Updated by Shinto 9-27-98
 * -added undead check
 * -raised hit and pen to 45
 * Updated by Tomas  -- April 2000
 * -Removed darkness enchantment 
 * Updated by Lilith 5 July 2008
 * -lowered hit/pen and removed magic identifiers
 * -This weapon is NOT mentioned in the MAGIC_WEAPON doc.
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
create_weapon()
{
    ::create_weapon();

    set_name("longsword");
    add_name("sword");
    set_pname(({"longswords","obsidian longswords","swords"}));
    set_adj(({"black","obsidian"}));
    set_short("obsidian longsword");
    set_pshort("obsidian longswords");
    set_long("It is made of pure black obsidian.  This sword reeks of  " +
      "goblins and orcs.\n");
    set_hit(35);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 7900);
    add_prop(OBJ_I_VOLUME, 1000);
}


