/* Navarre July 3rd 2006, Fixed typos */
/* Arman 19 November 2018, changed effect to standardised spell system */

inherit "/std/armour";
inherit "/d/Genesis/specials/examples/std_magic_lib";

inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 2
#define STORMSPELL   "/d/Ansalon/goodlund/bloodsea/obj/storm_amulet_spell"

object wearer;
int reset_storm = 0;

void
create_armour()
{
    setuid();
    seteuid(getuid());

    set_name("amulet");
    add_name("amulet of the storm");
    add_adj("dark");
    set_pshort("dark amulets of the storm");
    set_short("dark amulet of the storm");
    set_long("This ugly amulet consists of a string of twisted blue metal that " +
       "looks like they have been individually blasted by some powerful force. " +
       "Little bolts of blue energy appear to run up and down the chain of this " +
       "amulet.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_NECK);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This amulet has been infused with the fury of Zeboim, the Sea Queen. " +
        "When worn, this amulet offers protection from lightning, and when " +
        "grasped can summon a mighty storm to you, however with considerable " +
        "mental cost.\n",60}));
    add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50));

    add_cmd_item(({"amulet","dark amulet"}),"grasp","@@grasp_medallion@@");

   add_magic_obj_spell("[the] [dark] 'amulet'",
       ({ "grasp" }), "/d/Ansalon/goodlund/bloodsea/obj/storm_amulet_spell.c");

    set_magic_obj_effect(({"_storm_amulet_spell_object_"}));
}

int query_magic_protection(mixed prop, object for_who)
{
   if (for_who == wearer)
      if (prop == MAGIC_I_RES_ELECTRICITY)
      return 30 + random(10);
   else
      return 0;
   else
      return ::query_magic_protection(prop, for_who);
}

void
wear_message()
{
    if(E(TO) != wearer)
        return;
 
    wearer->catch_msg("A bolt of energy tickles your neck as you wear the " +
       "amulet. Surprisingly, you feel comfortable with it zapping around " +
       "your neck!\n");
}

mixed
wear(object what)
{
    wearer = TP;
    add_magic_obj_effects(wearer);
    wearer->add_magic_effect();

    set_alarm(0.5, 0.0, "wear_message");
    return 0;
}
mixed
remove(object what)
{
    remove_magic_obj_effects(wearer);
    wearer->remove_magic_effect();

    wearer = 0;
    return 0;
}

public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    if(!this_object()->query_worn())
    {
        write("You have to be wearing the amulet to activate " +
            "it.\n");
        return 0;
    }

    return 1;

}

void
init()
{
    ::init();
    
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}


/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    int result = ::cmd_parse_spell_action(arg);
    
    if (!result)
        notify_fail("Grasp what? The dark amulet?\n");
    
    return result;
} /* cmd_parse_spell_action */
