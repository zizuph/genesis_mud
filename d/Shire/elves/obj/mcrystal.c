/*
 * A glowing gem based on the Lamps of Noldor.
 * This gem emits a light level of 5 when worn, and is carried
 * by the elves that travel from Rivendell to the Gray Havens.
 * Noldor and other ME elves get the full light, othe races get a 
 * lesser light, and evil players can't wear it.
 * -- Finwe, January 2018
 * Revision History
 */

inherit "/std/armour";

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <alignment.h>

void
create_armour()
{
    set_name("crystal");
    add_adj("polished");
    add_adj("cut");
    set_short("polished cut crystal");
    set_long("This is a polished cut crystal, the size of a small fist, " +
        "and clear colored. @@check_flame@@\n");
    add_prop(OBJ_I_VALUE,2000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }) );

    set_ac(5);
    set_at(A_NECK);
    set_am( ({ 0, 0, 0 }) );
    set_af(TO);
}

string
check_flame()
{
    if(!this_object()->query_worn())
    {
        return "It sits in a fine net of silver. A fine silver " +
        "chain is woven into the net allowing you to wear the " +
        "crystal around your neck. The crystal is dim.";
    }
    else
    {
        return "It hangs from your neck inside a fine, silver net. A bright, white light shines from inside the crystal.";
    }
}

public mixed
wear(object obj)
{
    string light_type = "";

    if (ALIGN_IS_EVIL(wearer->query_alignment()) )
    {
//        write("You howl in pain as you try to wear the crystal, but the power within it is too much to bear, so you drop it.\n");
        say(QCTNAME(wearer) + " howls in pain as " + HE_SHE(wearer) + 
            " tries to wear the " + query_short() + ". " + CAP(HE_SHE(TP) + 
            " hastily removes it.\n"));
        move(ENV(wearer), 1);
        return "You howl in pain as you try to wear the crystal, but " +
            "the power within it is too much to bear. So, you drop it.\n";
    }
        
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    if(IS_NOLDOR(wearer))
    {
        light_type = "brilliant white";
        add_prop(OBJ_I_LIGHT,5);
    }
    else
    {
        light_type = "yellow"; 
        add_prop(OBJ_I_LIGHT,2 + random(2));
    }

    write("You bow your head slightly and wear the " + query_short() +
        " around your neck. The crystal comes alive and fills the area " +
        "with " + light_type + " light.\n");
    say(QCTNAME(wearer) + " bows " + HIS_HER(wearer) + " head slightly " +
        "and wears a " + query_short() + " around their neck. The crystal " +
        "comes to life and fills the room area with " + light_type + " light.\n");

//    add_prop(OBJ_I_LIGHT,5);
    return 1;
}

public mixed
remove(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    if (query_prop(OBJ_I_LIGHT))
    {
    wearer->catch_msg("You remove the " + query_short() + " from around " +
        "your neck. The crystal dims, returning the area to its natural " +
        "light.\n");
    tell_room(environment(wearer), QCTNAME(wearer) + " removes the " +
        query_short() + " from around "+ wearer->query_possessive()+
        " neck. The crystal dims, returning the area to its natural " +
        "light\n", wearer);
        remove_prop(OBJ_I_LIGHT);
    }
    return 1;
}
