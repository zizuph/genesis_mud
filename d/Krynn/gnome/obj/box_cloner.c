/*
 * A device that creates a bait box for the fishing system.
 * Purchaseable from the gnomish store.
 *
 * Arman, May 2021.
 */

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define BAIT_BOX  "/d/Krynn/solamn/palanthas/aesthetics/obj/bait_box"

void
create_object()
{
    set_name("device");
    set_adj("compact");
    add_adj("gnomish");

    set_short("compact gnomish device");
    set_long("This curious square box seems to be a compacted " +
        "collection of wooden boards, iron gears, pistons, and bells " +
        "wrapped in webbing and cords that marks it as a " +
        "typical gnomish invention of some kind. " +
        "Upon the top of the box is a big red button. Being a gnomish " +
        "invention, pressing it could do anything from causing the box " +
        "to fall to pieces or open a rift to the Abyss! A plaque has " +
        "been attached under the button, which may provide more " +
        "clarity to its purpose when read.\n");

    add_cmd_item("plaque","read","PressRedButtonOnDeckOfShipTo" +
        "ActivateArticulatedFishermanBaitStorageContainer!\n");

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 20000);
}

int
check_for_box(object ob)
{
    if (!ob)
    {
        return 0;
    }
    if (!ob->id("_gnomish_bait_box"))
    {
        return 0;
    }

    return 1;
}

int
do_press(string str)
{
    if(!str)
        return 0;

    if (str == "button" || str == "red button")
    {
        if(!E(this_player())->query_ship())
        {
            this_player()->catch_msg("You press the red button on the " +
                short()+ " and it begins to rattle alarmingly! Whistles " +
                "shriek and pistons slap erratically before stopping " +
                "with a 'clunk' as it fails to activate properly.\n");
            say(QCTNAME(this_player())+ " presses a button on the " +
                short()+ " and it begins to rattle alarmingly! Whistles " +
                "shriek and pistons slap erratically before stopping " +
                "with a 'clunk' as it fails to activate properly.\n");
            return 1;
        }

        object * ship_inv = deep_inventory(E(this_player()));
        object * boxes = filter(ship_inv, check_for_box);

        if(sizeof(boxes))
        {
            this_player()->catch_msg("You press the red button on the " +
                short()+ " and it begins to rattle alarmingly! Whistles " +
                "shriek and smoke pours from it before stopping " +
                "with a 'clunk' as it fails to activate properly.\n");
            say(QCTNAME(this_player())+ " presses a button on the " +
                short()+ " and it begins to rattle alarmingly! Whistles " +
                "shriek and smoke pours from it before stopping " +
                "with a 'clunk' as it fails to activate properly.\n");
            return 1;
        }

        this_player()->catch_msg("You press the red button on the " +
            short()+ " and it begins to rattle alarmingly! Whistles " +
            "shriek and pistons slap as it begins to transform " +
            "in to a large over-engineered hydraulic storage box!\n");
        say(QCTNAME(this_player())+ " presses a button on the " +
            short()+ " and it begins to rattle alarmingly! Whistles " +
            "shriek and pistons slap as it begins to transform " +
            "in to a large over-engineered hydraulic storage box!\n");

        seteuid(getuid(this_object()));
        object box = clone_object(BAIT_BOX);
        string name = TP->query_real_name();
        box->move(E(this_player()), 1);
        box->set_box_owner(name);

        tell_room(E(box), "\nThe gnomish bait box drills into the deck " + 
            "of the ship, attaching itself securely.\n", 0, box);

        remove_object();
        return 1;
   }

   notify_fail("Press what?\n");
   return 0;
}

void
init()
{
    ::init();
    
    add_action("do_press", "press");
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER;
}


