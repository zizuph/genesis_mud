/*
 *	/d/Gondor/minas/tcrc7.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 29-Jan-1997, Olorin:	Changed inheritance,
 *				general revision.
 *	 14-Mar-1998, Gnadnar:	Fixed desc to not mention torches if
 *				there are none; make torch stand part of
 *				room desc; conform to domain.rules
 *  Last modified by Alto, 06 April 2001
 *      Added room tells and revised descriptions
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void	create_gondor();
public string	long_desc();
public int	daylight();

static object	Tstand;

/*
 * Function name:	create_gondor
 * Description	:	set up room here
 */
public void
create_gondor()
{
    set_short("In the tunnel through the Wall of the Citadel in Minas Tirith");
    set_long(long_desc);

    add_exit(INNER_MINAS + "/gate7", "west", 0);
    add_exit(INNER_MINAS + "/e2crc6", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, daylight);

    add_item(({"guard"}), "The men of the Tower Guard can be seen "
        + "moving through the tunnel. They are grim of face, and wear "
        + "the black robes and winged-helms of the livery of Elendil.\n");
    add_item(({"street", "stones", "passage", "tunnel", "slope"}), "The "
        + "street is cobbled with large "
        + "smooth stones. Although the streets of Minas Tirith have endured "
        + "millenia of use, they are well-maintained.\n");
    add_item(({"sky", "clouds"}), "These kinds of things are generally "
        + "very difficult to see when you are inside a tunnel.\n");
    add_item(({"wall", "walls"}), "The walls of the tunnel arch over "
        + "your head. They are smooth with the passage of many years. "
        + "Attached to the white stone walls is an iron torch stand.\n");
    add_item(({"rock", "pier", "bastion", "heart"}), "The rock "
        + "of the mountain "
        + "is all around you. It is white and worn smooth from many "
        + "years of use.\n");
    add_item(({"gate", "seventh gate"}), "The Seventh Gate "
        + "leading into the Citadel "
        + "can be seen at the west end of the tunnel.\n");
    add_item(({"lamp", "lamps"}), "The tunnel is illuminated by large "
        + "torches and lamps set at even intervals along the slope.\n");

    set_tell_time(150);

    /* These tells are for the most part unique to this tunnel */

    add_tell("Thunder rumbles in the distance.\n");
    add_tell("A Tower Guard moves quickly past on business of "
        + "the Steward.\n");
    add_tell("A sudden gale blows through the tunnel from the east.\n");
    add_tell("The tunnel suddenly grows quiet.\n");
    add_tell("Footsteps echo from the west end of the tunnel.\n");
    add_tell("Footsteps echo from the east end of the tunnel.\n");
    add_tell("Marching feet can be heard outside the tunnel.\n");
    add_tell("A rat scurries away into the shadows.\n");
    
    /* Maintain the torch */

    Tstand = clone_object(OBJ_DIR+"torchstand");
    Tstand->set_lit(1);
    Tstand->set_replace_msg(
        "A servant dressed in the livery of Gondor arrives, carrying "
      + "a bundle of new torches. He places a new torch in the iron "
      + "stand and walks away.");
    Tstand->set_no_desc(1);
    Tstand->remove_prop(CONT_I_ATTACH, 1);
    Tstand->move(TO);
} /* create_gondor */


/*
 * Function name:	long_desc
 * Description	:	VBFC for room desc -- varies w state of torchstand
 * Returns	:	string -- the description
 */
public string
long_desc()
{
    /* N.B. We assume the torch stand stays put. since it sets
     * OBJ_M_NO_GET, this seems reasonable.
     */
    if ( Tstand->query_torch_is_lit() )
    {
	 return ("This is the tunnel leading up to the Seventh Gate. It "
            + "is delved into the heart of the rock. Torches and "
            + "lamps light the passage from the walls. A long "
            + "slope runs before you toward the gate.\n");
    }
    return ("This is the tunnel leading up to the Seventh Gate. It "
        + "is delved into the heart of the rock.  A long slope runs "
        + "before you toward the gate.\n");
} /* long_desc */

/*
 * Function name:	daylight
 * Description	:	return lightlevel of room
 * Returns	:	0 if evening/night, 1 otherwise
 */
public int
daylight()
{
    string timestr = tod();
    if (timestr == "night" || timestr == "evening")
        return 0;
    return 1;
} /* daylight */


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

