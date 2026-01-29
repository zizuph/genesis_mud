#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit "/std/room";

int
is_lgellirroom()
{
    return 1;
}

string
short_descr()
{
    return "struggling to move forward through a dense grove";
}

public void
hook_smelled(string str)
{
    write("A faint trace of wood smoke lurks within the scent of life.\n");
}

string
long_descr()
{

    string str0;

    str0 = "Ancient ash trees stand close all about, their branches "+
    "and roots interwoven in a tangle of life -- constrained only by "+
    "each other. It is a struggle to move among them; even thought "+
    "is stifled by the enclosing growth.\n";

    return str0;

}

void
reset_room()
{
    return;
}

void
create_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_prop( ROOM_M_NO_ATTACK, "Dense growth presses in on all sides "+
                "hindering movement and action.\n" );
    add_prop( ROOM_M_NO_MAGIC, "Dense growth presses in on all sides "+
                "-- crowding the mind.\n" );
    add_prop( ROOM_I_NO_ALLOW_STEED, "Dense growth hinders all steeds "+
                "in this place.\n" );
    add_prop( ROOM_M_NO_SCRY, 1 );
    add_prop( ROOM_M_NO_TELEPORT_TO, 1 );
    add_prop( ROOM_I_INSIDE, 0 );

    reset_room();

}


void
transfer_to_dest(object ob, object from)
{
    if (living(ob))
    {
        if ( wildmatch(LGELLIR_OPENING_LOC,file_name(from)) )
        {
            write("\n... you emerge from the struggle of the wood "+
                  "into the freedom of an open clearing.\n\n");
            tell_room( LGELLIRROOM + "club_asklnd", QCNAME(ob) +
                       " emerges, struggling out from the surrounding "+
                       "wood into the open clearing.\n",ob);
            ob->move_living("M",LGELLIRROOM + "club_asklnd", 1, 0);
        }
        else
        {
            write("\n... you emerge from the ash grove "+
                  "into the wider world.\n\n");
            tell_room(LGELLIR_OPENING_LOC, QCNAME(ob) 
                + " emerges from the curious grove.\n");
            ob->move_living("M",LGELLIR_OPENING_LOC, 1, 0);
        }
    }
    else
    {
        ob->remove_object();
    }
}

void
walking_encounters( int selected, int icount, object ob, object from )
{
    // encounters with
    // the Two Ravens (avatars of Lars)
    // and the Woodsman (avatar of Death)

    string str, galdr; 
    int old_selection;

    old_selection = selected;
    selected = random(4);

    if ( (icount < 2) && (selected != old_selection) ) {

        switch (selected)
        {
            case 0:
            str = "...restive wings beat the chill air high above...";
            break;

            case 1:
            str = "...two ravens call to each other high above...";
            break;

            case 2:
            str = "...the sound of a chopping axe echoes through the wood...";
            break;

            case 3:
            str = "...a dark-robed woodsman glides between distant trunks...";
            break;
        }

        write(str + ".\n");

        icount++;

        set_alarm(5.0,0.0,&walking_encounters(selected,icount,ob,from));

    }
    else
        set_alarm(1.0,0.0,&transfer_to_dest(ob,from));

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_long("@@long_descr");

    set_alarm(5.0,0.0,&walking_encounters(-1,-1,ob,from));
}

