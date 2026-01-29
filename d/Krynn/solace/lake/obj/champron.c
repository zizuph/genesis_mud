/*
 * What         : A decorated iron champron.
 * Used by      : Minotaur chieftain Kadez in the Toron minotaur village
 *                near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : A head armour for minotaurs, connected to "mino_ac_obj.c".
 *                Since minotaurs ususally cant wear head armours, this is
 *                really just a wearable cloth that when weared clones an
 *                invisible object to the living, providing a small amount 
 *                of head AC.
 * Made by      : Cherek, Feb 2007
 *
 * 2010/03/19 Last change
 * 2011/03/21 Lavellan, added "armour" name. Not as good as being a proper
 *                  armour, but better than nothing.
 * 2021/10/17 Cotillion, Probably fixed an issue where items could be worn
 *                       over the champron.
 */


#pragma strict_types
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#define MINO_AC OBJ + "mino_ac_obj.c"

object ac_obj;

void
create_object()
{
    set_name("champron");
    add_name("helm");
    add_name("helmet");
    add_name("armour");
    set_adj(({"decorated","iron"}));
    set_short("decorated iron champron");
    set_long("A complex system of metal plates connected with " +
             "hinges and strappings. You recognize this as a " +
             "champron, an armour designed to protect the head " +
             "and face of a warhorse. However, this particular " +
             "headpiece is way too big for a horse and must have " +
             "been made to fit a much larger creature. By looking " +
             "at the engravings and decorations you understand it " +
             "must have belonged to someone important.\n" +
             "It looks like it is in prime condition. \n");

    set_slots(A_HEAD);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_HEAD)
             +1000+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
    
    add_prop(OBJ_S_WIZINFO,
       ("This armour is just a wearable cloth, however it acts as a " +
        "work-around to achieve a helmet for minotaurs who by default " +
        "cannot wear helmets. The AC is added by cloning an invisible magic " +
        "item to the wearer. The item is closely connected to the " +
        "champron and is removed if the champron is. \n"));    
    
    //set_keep(1);

    //Enable default item expiration
    set_item_expiration();

    set_layers(4);
    set_looseness(0);

    set_wf(TO);

    add_item("engravings", "The champron is decorated with engraved " +
             "letters in an unknown language.\n");

    add_item("decorations", "Silver bands form intricate patterns " +
             "that seem to be a part of the iron itself. This is " +
             "truly amazing work from whoever made this armour. \n");

    add_cmd_item("engravings","read","They are strange " +
                 "and beyond your comprehension..\n");

    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);

}

/*
 * Function name: wear
 * Description  : Checks if the wearer is a minotaur, other races are
 *                unable to use the armour. If the wearer is a minotaur
 *                a custom wear-message is shown and the "mino_ac_obj"
 *                is cloned to the living, giving AC.
 */
 
mixed
wear(object what)
{

    if(wearer->query_race_name() != "minotaur")
    {
        return "This armour would not fit properly on you.\n";     
    }

    tell_room(environment(wearer), QCTNAME(wearer) +
              " carefully wears a "+ query_short() +" on " + 
              HIS(wearer) + " head.\n", wearer);

    write("You carefully wear the " + query_short() + " on your head.\n");	

    seteuid(getuid(TO));
    ac_obj = clone_object(MINO_AC);
    ac_obj->move(wearer, 1);
    return 1;
    
}

/*
 * Function name: remove
 * Description  : The "mino_ac_obj" is removed from the living, 
 *                removing the AC.
 */
 
mixed
remove(object what)
{	
    ac_obj->remove_object();

    return 0;
}

/*
 * Function name: leave_env
 * Description  : Check to make sure the mino_ac_obj is removed
 *                when the armour leaves the inventory of a living.
 */
 
public void
leave_env(object from, object to)
{

    ::leave_env(from, to);

    wearable_item_leave_env(from, to);

    ac_obj->remove_object();

}

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this herb is recoverable. If you
 *                have variables you want to recover yourself, you have to
 *                redefine this function, keeping at least the filename and
 *                the herb recovery variables, like they are queried below.
 *                If, for some reason, you do not want your herb to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
string
query_recover() 
{
    return MASTER + ":" + query_item_expiration_recover();
} /* query_recover */

void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
