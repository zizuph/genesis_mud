/*
 *	/d/Gondor/minas/s2crc1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 *	12-Feb-1997, Gnadnar:	Changed check of opening/closing time
 *				to be precise; added "sign" item
 *				and "read sign" cmd_item.
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 *  Bank stays open. If shop is open, bank should be open too. 
 *  -- Finwe, November 2005
 */
#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

public int     check_open();
public void    add_door();

public void
create_street()
{
    set_streetname("Ithilien Street");
    set_circle("First");
    set_areaname("southern");
    set_streettype("street");
    set_activity(2);
    set_wealth(1);
    set_streetlight(2);

    add_exit(MINAS_DIR + "s1crc1", "northeast");
    add_exit(MINAS_DIR + "s3crc1", "west");
//    add_exit(MINAS_DIR + "rooms/mtbank", "north", check_open);
    add_exit(MINAS_DIR + "rooms/mtbank", "north");

    add_item(({"bank","gondor bank","bank of gondor"}), BSN(
        "The bank is a luxurious, white building, with a strong, iron " +
        "door leading into it. There's a sign by the door, stating:") +
	"\tThe Bank of Gondor.\n");
    add_item("sign",
	"\tThe Bank of Gondor.\n");
    add_item(({"house", "mansion", }), BSN(
        "It is one of the houses in which the citizens of Minas Tirith "
      + "live. It is rather small and is in need of a few small "
      + "repairs."));

    add_cmd_item( "sign", "read",
	"\tThe Bank of Gondor.\n");

    set_extraline("The street continues west into an alley, and northeast " +
        "to the eastern parts of the city. To the north is the Bank " +
        "of Gondor, to the south is a small house.");

    add_door();

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

public int
check_open()
{
    int hour = CLOCK->query_24_hour();

    /* ok, if you try to enter on the dot of 6pm, you are denied.
     * this matches RL bank behaviour. :-)
     */
    if ( 8 <= hour && hour < 18 )
    {
        write("You enter the Bank of Gondor.\n");
        return 0;
    }
    else
    {
        write("The door to the bank is locked, and you see a sign:\n"+
	      "\tThe Bank of Gondor is open from 8 o'clock\n"+
	      "\tin the morning to 6 o'clock in the evening.\n");
        return 1;
    }
}

void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id("MT_h3_s2crc1");
    door->set_pass_command(({"s","south"}));
    door->set_other_room(MINAS_DIR + "houses/citizens/h3r1ss2crc1");
    door->set_door_desc(BSN(
        "This door is poorly fitting. It looks as if it has been " +
        "taken from another doorway and somehow made to fit here. " +
        "On it is painted in the Numenorean alphabet:") +
        "\t\tAlgund Umarth\n");
    door->set_key("MT_h3_s2crc1");
    door->move(TO);
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


