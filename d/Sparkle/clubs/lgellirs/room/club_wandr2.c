#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"

inherit "/std/room";

static int gNumOldGaldrar = 0;
static string *gOldGaldrar;

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
    gOldGaldrar = LGELLIR_OLD_GALDRAR();
    gNumOldGaldrar = sizeof(gOldGaldrar);

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
        if ( wildmatch(LGELLIRROOM + "club_asklnd",file_name(from)) )
        {
            write("\n... you emerge from the struggle of the "+
                  "wood to face the mortal edge of an abyss.\n\n");
            tell_room(LGELLIRROOM+"club_lilgap", QCNAME(ob) + 
                " emerges, struggling from the wood to stand on the "+
                "edge of the abyss.\n");
            ob->move_living("M",LGELLIRROOM+"club_lilgap", 1, 0);
        }
        else
        {
           write("\n... you emerge from the struggle of the wood "+
                  "into the freedom of an open clearing.\n\n");
            tell_room( LGELLIRROOM + "club_asklnd", QCNAME(ob) +
                       " emerges, struggling out from the surrounding "+
                       "wood into the open clearing.\n",ob);
            ob->move_living("M",LGELLIRROOM + "club_asklnd", 1, 0);
        }
    }
    else
    {
        ob->remove_object();
    }
}


string
random_old_galdr()
{
    if ( !gNumOldGaldrar ) 
        return "";

    int i = random(gNumOldGaldrar);

    return gOldGaldrar[i];
}


void
walking_encounters( int icount, object ob, object from )
{
    // encounters with
    // the Woodsman (avatar of Death)
    // and the Two Ravens (avatars of Lars)         

    int ngaldr;
    string str, galdr; 

    if ( icount < 2 ) {

        switch (random(4))
        {
            case 0:
            galdr = random_old_galdr();
            str = "...restive wings beat the chill air high above";
            if ( !strlen(galdr) )
                str += " ...the Ravens call to each other high above... ";
            else
              str += " ...one Raven high above calls to the other:\n\n" + 
                      galdr + "\n";
            break;

            case 1:
            galdr = LGELLIR_LAST_GALDR(ob);
            str = "...the sound of a chopping axe echoes through the wood";
            if ( !strlen(galdr) )
                str += " ...the Woodsman chuckles in your mind...";
            else
              str += " ...the Woodsman chuckles in your mind," 
                + "'heard your squeal':\n\n" +
                      galdr + "\n";
            break;

            case 2:
            galdr = LGELLIR_HIGH_GALDR(ob);
            if ( !strlen(galdr) )
                str = "...caws of the Two Ravens rasp in your mind...";
            else
                str = "...the Two Ravens chorus in your mind," +
                    " 'Heed the galdr most favoured before Armageddon:'\n\n" +
                      galdr + "\n";
            break;

            case 3:
	    ngaldr = LGELLIR_NUM_NEW_GALDRAR();
            str = "...the Woodsman glides dark between distant trunks";
            if ( ngaldr == 0 )
              str += " ...his dejected voice sounds in your mind, " 
                + "'aint heard no squeals this Age'\n"; 
            else if ( ngaldr == 1 )
              str += " ...his voice sounds in your mind, " 
                + "'heard only one squeal this Age'\n"; 
            else
              str += " ...his voice sounds in your mind, " 
                + "'heard " + LANG_NUM2WORD(ngaldr) + " squeals this Age'\n"; 
            break;

        }
        write(str + "\n");

        icount++;

        set_alarm(5.0,0.0,&walking_encounters(icount,ob,from));
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

    set_alarm(5.0,0.0,&walking_encounters(-1,ob,from));
}

