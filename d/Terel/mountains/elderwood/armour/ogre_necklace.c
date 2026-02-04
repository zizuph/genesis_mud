// ogre_necklace.c
// Ogre necklace for the ogres in Elderwood
// Tomas  May 2000

inherit "/std/armour";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>


#pragma save_binary
#pragma strict_types

#define NECKLACE_SUBLOC    "_terel_ogre_necklace_subloc"


void
create_armour()
{
  set_name("Terel_Ogre_Necklace");
  add_name("necklace");
  set_short("trophy necklace");
  add_adj(({"trophy","bones","ears"}));
  add_pname(({"necklacess"}));
  set_long ("This gruesume looking necklace is comprised of " +
     "a long leather string with various humanoid ears and " +
     "bones attached to it.\n");

  add_item(({"humanoid ear","ears","ear"}),
     "The necklace contains a collection of various sized and " +
     "shaped humanoid ears. The ears appear to be mostly of dwarven " +
     "origin with some elven and human mixed in.\n");

  add_item(({"bones","bone"}),"The necklace contains several small " +
     "sized bones. The bones appear to look humanoid in origin.\n");

  set_wf (TO);
  set_ac (1);
  set_am (({ 0, 0, 0}));
  set_at (A_NECK);

  add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it disgusting and " +
     "refused to buy it.\n");

  seteuid(getuid());

}


mixed
wear(object ob)
{
   TP->add_subloc(NECKLACE_SUBLOC, TO);
   TP->update_hooks();
   return 0;

}


mixed
remove(object ob)
{
    TP->remove_subloc(NECKLACE_SUBLOC);
    TP->update_hooks();
    return 0;
}



/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - the subloc string
 *                on      - the wearer
 *                for_obj - the one looking
 * Returns:           The string that is to be seen (subloc)
 */
string
show_subloc(string subloc, object on, object for_obj)
{
   
    if (subloc != NECKLACE_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);
  
    if (for_obj == on)
        return "You proudly display your collection of humanoid bones " +
        "and ears upon your trophy necklace.\n";
    else
        return capitalize(PRONOUN(on)) +" is wearing " +HIS_HER+
        " trophy necklace, proudly displaying "+HIS_HER+ " collection " +
        "of humanoid ears and small bones.\n";
}
