/*
 *  Filename:       armdoor_key.c
 *  Description:    This is a key for a door for a wagon.
 *
 *  Copyright (c) Sep. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 *
 */
#include "../wagon/wagon.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/key";

void
create_key()
{
   ::create_key();
   set_name(({"orb", "frail round orb"}));
   set_short("frail round orb");
   set_pshort("frail round orbs");
   set_adj("frail");
   add_adj("round");
   set_long("Its a frail round orb that are easily broken " +
            "if one is not careful, it shimmers with a " +
            "strange light, pulsing dark red at times.\n");

   set_key(ARM_KEY);


}


    /* unlocks or opens the door */

public int
do_rub()
{
    string *door_ids;
    object *doors;
    object door;
    int pos;


    /* first of all we need to find the door we're next to */

    door_ids = (string *)E(TP)->query_prop(ROOM_AS_DOORID);
    doors = (object *)E(TP)->query_prop(ROOM_AO_DOOROB);
    if (!sizeof(door_ids))
        return 0;

    pos = member_array("armdoor", door_ids);
    if (pos < 0)
        return 0;

    door = doors[pos];
    if (door->query_locked() )
    {
        /* its locked, so we unlock it */
        tell_object( TP, "As you rub the " + TO->short() +
                         " the " + door->short() + " stops humming.\n");
        tell_room(E(TP), QCTNAME(TP) + " rubs the " + TO->short() +
                             " which makes the " + door->short() +
                             " stop humming.\n", TP);

        door->query_other_door()->do_unlock_door("");
        door->do_unlock_door("");
        TP->add_mana(-random(10) - 15);
        return 1;
    }

    if (!door->query_open())
    {
        /* its closed */
        tell_object( TP, "As you rub the " + TO->short() +
                         " the " + door->short() + " magically opens.\n");
        tell_room(E(TP), QCTNAME(TP) + " rubs the " + TO->short() +
                             " which makes the " + door->short() +
                             " open silently.\n", TP);
        TP->add_mana(-random(10) - 15);
        door->query_other_door()->do_open_door("The door opens.\n");
        door->do_open_door("");
        return 1;
    }

  /* its both unlocked and open, why on earth would he
     try to open it then! */
    tell_object( TP, "You rub the " + TO->short() + ".\n");
    tell_room(E(TP), QCTNAME(TP) + " rubs the " + TO->short() + ".\n", TP);



    return 1;

}

 /* closes or locks the door */
public int
do_touch()
{
    string *door_id2;
    object *doors;
    object door;
    int pos;

    /* first of all we need to find the door we're next to */

    door_id2 = (string *)E(TP)->query_prop(ROOM_AS_DOORID);
    doors = (object *)E(TP)->query_prop(ROOM_AO_DOOROB);

    if (!sizeof(door_id2))
        return 0;

    pos = member_array("armdoor", door_id2);

    if (pos < 0)
    return 0;

    door = doors[pos];

    if (door->query_open())
    {
        /* its open */
        tell_object( TP, "As you touch the " + TO->short() +
                         " the " + door->short() + " magically closes.\n");
        tell_room(E(TP), QCTNAME(TP) + " touches the " + TO->short() +
                             " which makes the " + door->short() +
                             " close silently.\n", TP);
        TP->add_mana(-random(10) - 15);
        door->query_other_door()->do_close_door("The door closes.\n");
        door->do_close_door("");
        return 1;
    }

    if (!door->query_locked() )
    {
        /* its unlocked, so we lock it */
        tell_object( TP, "As you touch the " + TO->short() +
                         " the " + door->short() + " starts humming.\n");
        tell_room(E(TP), QCTNAME(TP) + " touches the " + TO->short() +
                             " which makes the " + door->short() +
                             " start humming.\n", TP);
        door->do_lock_door(1);
        door->query_other_door()->do_lock_door("");
        TP->add_mana(-random(10) - 15);
        return 1;
    }


  /* its both locked and closed, why on earth would he
     try to open it then! */
    tell_object( TP, "You touch the " + TO->short() + ".\n");
    tell_room(E(TP), QCTNAME(TP) + " touches the " + TO->short() + ".\n", TP);



    return 1;

}


void
init()
{
    add_cmd_item("orb","touch",do_touch);
    add_cmd_item("orb","rub",do_rub);

    ::init();
}

/*
   set_lock_command("rub2");
   set_lock_mess(({"rubs the frail thin orb onto the lock of the door, " +
                   "making the humming slightly stronger.\n","You hear a " +
            "faint humming sound from the lock of the door.\n"}));
   set_fail_lock(({"The humming continues.\n","A strange glow swiftly " +
            "passes thru the orb.\n"}));
   set_unlock_command("touch2");
   set_unlock_mess(({"touches the door with the orb and the humming "+
                    "stops.\n", "The humming dimishes, " +
                    "and finally stops.\n"}));
   set_fail_unlock("A dark red glow pulses from the lock of the door, " +
                   "and the door keeps humming.\n");
*/