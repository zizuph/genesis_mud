/*   larsether_dest.c
 *
 *   Destination location for the succession of rooms linking the Realms
 *   with the Centre of the Donut by way of Lars's Ether.
 *
 *   Vitwitch, 2022
 */

#include <macros.h>
#include "../defs.h"

inherit "/std/room";

int
is_lgellirroom()
{
    return 1;
}

nomask void
reset_room()
{
}


nomask void
create_room()
{
    set_short(" ");
    set_long("\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT,1); 
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    add_prop( ROOM_I_NO_ALLOW_STEED, 1 );

    reset_room();

    return;
}


void
out_of_water( object plyr, string movelocn )
{
    if (!living(plyr))
        return;

    write("\nYou crawl, dripping, up onto the pier.\n\n");
    tell_room(movelocn, QCNAME(plyr) + 
          " emerges, dripping, from water nearby.\n");
    plyr->move_living("M", movelocn, 1, 0);

    return;
}


void
transfer_to_earth( object ob, object from )
{
    int numtry = 0;
    int maxtry = 5;
    string movelocn = "";

    if ( living(ob) )
    {
        // try to splash down in Sparkle harbour
        //   ... since Litillgap is remnant of Mikillgap
        //         which widened to become all seas and
        //          oceans of the Donut...
        //
        //   ... if no viable splashdown location found
        //         drop into default end location

        while ( !objectp(find_object(movelocn)) && numtry < maxtry )
        {
            movelocn = sprintf("%s%2d",LARSETHER_ENDLOCST,
               (LARSETHER_ENDLOCMIN + random(LARSETHER_NUMENDLOC)));
            numtry++;
        }

        if ( numtry >= maxtry) numtry = 0;

        if ( !numtry )
	{
            write("You emerge from the Larsether in a "
                     + "flurry of motion.\n\n");
            tell_room(movelocn, QCNAME(ob) + 
                 " emerges from thin air in a flurry of motion.\n");
            ob->move_living("M", LARSETHER_ENDLOCDEF, 1, 0);
	}
	else
	{
            // splash down !!

            write(
           "...you SPLASH down deep right beside a pier...\n\n");

            tell_room(movelocn,"There is a huge splash in the water nearby!\n");

            set_alarm(2.0,0.0,&out_of_water(ob,movelocn));
	}
    }
    else
        ob->remove_object(); // not living

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    ob->catch_msg("\n\n...you fall from the Larsether into mortal airs..."+
           "\n\n...you glimpse a harbour from a great height...\n\n");

    LGELLIR_LOG_BOON_COMPLETION(ob);

    set_alarm(4.0,0.0,&transfer_to_earth(ob,from));
}


