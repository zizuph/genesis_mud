
/*
 *  Club Special Function Room for the Gellirs of Lars
 *    ... rising up in the Litillgap on Larsether
 *
 *  Vitwitch 2022
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit "/std/room";

/* prototypes */

int is_lgellirroom();
string otherworld();
void reset_room();
public void create_room();
void enter_inv(object ob, object from);
void transfer_to_larsether( object plyr );

/* functions */

int
is_lgellirroom()
{
    return 1;
}

string
otherworld()
{
    return LGELLIR_ETHER_INACTION_MESG;
}

void
reset_room()
{
}


public void
create_room()
{
    set_short(" ");
    set_long("\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_M_NO_ATTACK, "@@otherworld");
    add_prop(ROOM_M_NO_MAGIC, "@@otherworld");
    add_prop(ROOM_M_NO_TELEPORT_FROM, "@@otherworld");
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    reset_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        string *wgaldrar = LGELLIR_WINNERS_GALDRAR(); 

        int n = sizeof(wgaldrar);
	if ( n > 0 ) 
	{
	    int i = random(n);

            ob->catch_msg("\nChurning about you, the Larsether sings:\n\n"
                              + wgaldrar[i] + "\n\n"); 
            tell_room(this_object(),
	              "\nChurning about, the Larsether sings:\n\n"
                              + wgaldrar[i] + "\n\n",ob); 
            tell_room(LGELLIRROOM + "club_lilgap" ,
	               "\nThe motion of the Larsether seems to sing:\n\n"
                              + wgaldrar[i] + "\n\n"); 
            set_alarm(6.0,0.0,&transfer_to_larsether(ob));
        }
	else
            set_alarm(4.0,0.0,&transfer_to_larsether(ob));
    }
}


void
transfer_to_larsether( object plyr )
{
    plyr->catch_msg("\n\nThe Larsether carries you "+
           "beyond the World -- you circle over the whole of Creation.\n");

    LGELLIR_SET_BOON_INCR(plyr);

    plyr->add_prop(LGELLIR_LARSETHER_INDEX,LARSETHER_STTINGIDX);

    string movelocn = sprintf("%s%02d",LARSETHER_FILESTUB,LARSETHER_STTINGIDX);

    plyr->move_living("M",movelocn,1,0);

    return;
}

