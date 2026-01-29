/*
 * Filename:        /d/Krynn/icewall/castle2/obj/armours/fael_ring.c
 * Description:     This ring was created by Fael-Thas to protect
 *                  him against assination attempts with poison.
 *                  He was extremly paranoid, thats the reason
 *                  why he had items like this.
 *                  Also, it makes it harder for mortals to slay him
 *                  easily with poison ;-)
 *                  It adds additative resist to poison of 20
 *                  Its Worn by: /d/Krynn/icewall/castle2/npc/fael-thas.c
 *
 * Credit goes to Avenir for their wonderful implementation of amulets
 * and rings, which inspired me to do one of my own.
 *
 * Coder and Copyright (c) to - Daniel W. Mathiasen, aka Boron, May 2003
 */

/* 
 * Note by Navarre, November 22th 2005:
 *
 *
 * - A great ring, the amount of resistance it provides is a little out of proportion.
 *   The ring was made so Fael-thas has more resistance to poison.
 *   So i have let the ring continue to give 40 in resistance, if its worn by a npc.
 *   if worn by a player it will offer 15 instead of 40. Which is more reasonable for
 *   one item.
 */


inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Krynn/common/defs.h"

void create_armour()
{
  set_short("clear silver ring");
  set_pshort("clear silver rings");
  set_name("ring");
  set_pname("rings");
  set_adj(({"clear","silver"}));

  set_long("Uncertain if this ring is real or not, you " +
           "examine it further. The ring might be of silver " +
           "or, you wonder if it could be ice, it is clear as " +
           "but feels like silver. Not a mark is left on the " +
           "surface.\n");


  set_ac(5);
  set_at(A_ANY_FINGER);
  set_af(TO);

  add_prop(OBJ_I_VALUE, 1500);
  add_prop(OBJ_I_WEIGHT, 50);
  add_prop(OBJ_I_VOLUME, 100);   // It is small, after all...


  add_prop(MAGIC_AM_MAGIC , ({ 60, "life" }) );
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(MAGIC_AM_ID_INFO ,
       ({"\nA shadowy elf appears before you hissing " +
         "dangerously: You filth, you are no match to me!\n\n", 25,
         "You ignore the threats and continue with the ring " +
         "This ring is a ring of protection", 35,
         " it is made of enchanted ice.\n", 50,
         "The magic is great, and would protect the " +
         "wearer from assasination through poison.\n", 65}) );
  add_prop(OBJ_S_WIZINFO, "Adds additive poison resistance of 40 to npcs and 15 to players.\n");

}

int wear(object to)
{
  TP->catch_msg("As you wear the "+ short() + " on your finger "+
            "a chill runs through your body.\n");
  say(QCTNAME(TP) + " wears " + LANG_ADDART(short()) +
        " onto " + HIS(TP) + " finger.\n", TP);

  TP->add_magic_effect(TO);

  return 1;
}

public mixed
remove(object ob)
{
    if (query_worn())
    {
        query_worn()->remove_magic_effect(TO);

	if(wearer && wearer->query_hp()>0)
	{
	  wearer->catch_msg("You remove the " + short() + " and your finger slowly "+
                            "begins to feel warm again.\n");
	  tell_room(environment(wearer), QCTNAME(wearer) + " removes "+LANG_ASHORT(TO)+".\n", wearer);
	}
        return 1;
    }
    return 0;
}



void leave_env(object to, object from)
{
   ::leave_env(to, from);

   if(!living(from))
    return;

   from->remove_magic_effect(TO);
   wearer = 0;
}

mixed
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && prop == MAGIC_I_RES_POISON)
    {
        query_worn()->catch_msg("The " + short() +
            " sends a chill through your bones, somehow this "+
            "is a pleasent feeling.\n");
	if(interactive(query_worn()))
        {
          return ({ 15, 1 });
        }
        else{
          return ({ 40, 1 });
        }
    }

    return ::query_magic_protection(prop, what);
}


int dispel_magic(int power)
{
  if(power < query_prop(MAGIC_I_RES_MAGIC))
    return 0;

  query_worn()->heal_hp(-(query_value()));
  query_worn()->catch_msg("The ring melts slowly, and isn't cold " +
            "anymore!\n");
  query_worn()->command("scream pain");
  query_worn()->command("shiver painfully");

  remove_broken(1);

  return 1;
}
