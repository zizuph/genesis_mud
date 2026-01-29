/*  
/* 	Standard to inherit into Cirath rooms.
*   Sets the ROOM_M_NO_MAGIC and uses output to inform players
*   about defiling preserving magic.
*
*   Players must focus their magic on either selection before being
*   able to use magic in Cirath.
*/


inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "../defs.h"

int check_magic();
public void add_defiler_casts();
public void add_preserver_casts();

#define C_I_AM_DEFILER        "_i_am_defiler"
#define C_I_AM_PRESERVER      "_i_am_preserver"


void
create_room()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
  
    /* All detection of casting is based on ROOM_M_NO_MAGIC*/
    add_prop(ROOM_M_NO_MAGIC, VBFC_ME("check_magic"));
}

/*
*    Made this to reflect the magic nature of Cirath.
*    Magic is drawn from living(defiler magic), and is destructive,
*    unless you try to limit yourself.
*    Would like to differentiate between divine and arcane.
*    Thanks to Shanoga, Gorboth and Mirandus for explaining and polishing
*
*    Checks if player has set defiler/preserver, and blocks casting if not.
*    Does random(times player has cast spells before) to reduce spam 
*    messages about magic over time. Decreases chance each time message 
*    is triggered.
*/

int
check_magic()
{

    if (this_player()->query_prop(C_I_AM_DEFILER))
    {
        // Convert the defiler cast value to a positive number
        int defile_value = QUERY_CASTS(this_player()) * -1;

        if (!random(this_player()->query_prop(C_I_AM_DEFILER)))
        {
            add_defiler_casts();
            if (QUERY_CASTS(this_player()) > 0)
            {
                write("You draw all possible power from around you, "
                    + "still feeling the twinges from trying to "
                    + "preserve it all before.\n");
                say(QCTNAME(this_player()) + " frowns while "
                    + "gathering magical energy.\n");
            }
            else
            {
                write("You feel the power as you draw your magic "
                    +"and energy from everything around you.\n");
                say(QCTNAME(this_player()) + " frowns while gathering "
                    + "magical energy.\n");
            }
        }
        return 0;
    }

    if (this_player()->query_prop(C_I_AM_PRESERVER))
    {
        if (!random(this_player()->query_prop(C_I_AM_PRESERVER)))
        {
            add_preserver_casts();
            if (QUERY_CASTS(this_player()) < 0)
            {
                write("You focus on reducing your wasteful past, and "
                    + "keeping the balance with your magic.\n");
                say(QCTNAME(this_player()) + " concentrates while "
                    + "gathering magical energy.\n");
            }
            else
            {
                write("You concentrate to harness energy from all "
                    + "around and avoid destroying plants.\n");
                say(QCTNAME(this_player()) + " concentrates while "
                    + "gathering magical energy.\n");
            }
        }
        return 0;
    }

    if (QUERY_CASTS(this_player() != 0))
    {
        if (QUERY_CASTS(this_player()) > 0)
        {
            add_preserver_casts();
            return 0;
        }
        if (QUERY_CASTS(this_player()) < 0)
        {
            add_defiler_casts();
            return 0;
        }
    }
    write("You must focus magic on defiling or preserving.\n");
        return 1;
    

}

/*  Reduce the ADD_CAST function for defilers by 1 */
int
add_defiler_casts()
{
    int casts;

    casts = this_player()->query_prop(C_I_AM_DEFILER) + 1;
    this_player()->add_prop(C_I_AM_DEFILER, casts);
    
    ADD_CASTS(this_player(), -1);
}

/*  Increase the ADD_CAST function for preservers by 1 */
int
add_preserver_casts()
{
    int casts;

    casts = this_player()->query_prop(C_I_AM_PRESERVER) + 1;
    this_player()->add_prop(C_I_AM_PRESERVER, casts);
    
    ADD_CASTS(this_player(), 1);
}

/*  Function name: declare_defiler
*   Description: allows player to set preserver/defiler.
*   Arguments: defiler or preserver
*/
init()
{
    ::init();
    add_action("declare_defiler","focus");
}

declare_defiler(string str)
{
    string check;

    notify_fail("You must focus on either <preserving> all plant life in "
    + "this realm by conserving your magical energies, or disregard "
    + "such concerns by simply <defiling> all by drawing all magical "
    + "energies that are available.\n");
    if(!str)
        return 0;
    if(parse_command(str, this_player(), "[at] [on] [magic] [to] "
    + "'defiling' [magic] [energy] [plants] [nature] [creation]"))
    {
        if (QUERY_CASTS(this_player()) > 0)
        {
            write("You focus away from your previous disposition to "
                + "foolishly preserve the world around you, at the "
                + "expense of your own power.\n");
        }
        else
        {
            write("You focus on drawing magical energy as fast and careless as possible in this broken realm.\n");
        }
        this_player()->add_prop(C_I_AM_DEFILER, 1);
        this_player()->remove_prop(C_I_AM_PRESERVER);
        return 1;
    }
    if(parse_command(str, this_player(), "[at] [on] [magic] [to] "
    + "'preserving' [magic] [energy] [plants] [nature] [creation]"))
    {
        if (QUERY_CASTS(this_player()) < 0)
        {
            write("You repent your ways of defiling the world, and start "
                + "focusing on preserving it.\n");
        }
        else
        {
            write("You focus on drawing magical energy as careful as "
                + "possible, to avoid hurting anything in this broken "
                + "realm.\n");
        }
        this_player()->add_prop(C_I_AM_PRESERVER, 1);
        this_player()->remove_prop(C_I_AM_DEFILER);
        return 1;
    }
    return 0;
}
