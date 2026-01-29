/* 
 *  Drop box for donations to the Calian guild. 
 *
 *  Petros  Changed Drop Box so that people who are not full Calians
 *          cannot access the drop box. 5/2008
 *  Tapakah (handling some Calian bugs by request of AoD), 08/2006 -
 *    fixed the rejection of WT == 0 weapons.
 *  Bishop of Calia, sept. 2005.
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>
#include CALIAN_HEADER

inherit "/std/container";
inherit CRPALACE_SPECIALS + "calian_utility";

#define CALIAN_S_DONATION_TAG "_calian_s_donation_tag"

void
create_container()
{
    set_name("receptacle");
    set_adj("bulky");
    add_adj("crystal");
    set_short("bulky crystal receptacle");
    set_long("This receptable appears as though someone hewed a huge chunk of"+
        " crystal out from the mother lode and painstakingly hollowed it out."+
        " It is irregularly shaped and most of the surface is opaque, with" +
        " some areas tinted green or red. The crystal refracts light in an" +
        " odd and unpredictable manner, blinding you when looked at from" +
        " certain angles. There is an opening at the top of it, large enough" +
        " to fit most items within. Fastened near the opening of this huge" +
        " and bizarre looking receptacle is a small tin plaque. It reads:" +
        " 'Donations for the Calian Warrior guild'. Below that, with smaller"+
        " letters, someone has written: 'No snakes please'.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The bulky crystal receptacle can't be removed" +
        " from the floor.\n");
}

public int
prevent_enter(object ob)
{
    if (ob->query_name() == "snake")
    {
        write("As you try to put the snake into the receptacle, a chiding" +
            " female voice penetrates your mind, screaming: 'NO SNAKES!'\n");
        return 1;
    }

    if (!IS_WEAPON_OBJECT(ob)
        && !IS_ARMOUR_OBJECT(ob))
	{
      write("The receptacle will only accept weapons and armours.\n");
      return 1;
    }
      
    else
    if (ob->query_prop(OBJ_I_BROKEN))
    {
        write("You wouldn't want to put the " + ob->short() + " in there -" +
            " it's useless!\n");
        return 1;
    }

    ::prevent_enter(ob);
}

public int
prevent_leave(object ob)
{
    if (!is_calian(TP) && 
        (ob->query_prop(CALIAN_S_DONATION_TAG) != TP->query_real_name()))
    {
        write("You can only remove items from the receptable if you" +
            " put them there yourself or you are a Calian Warrior.\n");
        return 1;
    }

    if (!IS_CALIAN_WARRIOR(TP))
    {
        write("As you are not a full Calian Warrior, you are not yet able "
            + "to retrieve items donated to the Calians.\n");
        return 1;
    }
    
    ::prevent_leave(ob);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    ob->add_prop(CALIAN_S_DONATION_TAG, TP->query_real_name());
}

public void
leave_inv(object ob, object to)
{
    string s = "yourself";
    
    if (TP->query_real_name() != ob->query_prop(CALIAN_S_DONATION_TAG))
    {
        s = capitalize(ob->query_prop(CALIAN_S_DONATION_TAG));
    }
    
    ::leave_inv(ob, to);
    
    write("The " + ob->short() + " was donated by " + s + ".\n");
}
