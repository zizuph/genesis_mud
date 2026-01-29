/* huntclub_joinrm.c - Tomas/Finwe, November 2017
*
*  Modifications:
*     added rumbald -- Tomas December 3, 2017
*     added AG guild skills -- Tomas December 6, 2017

Stolen for Allies of Rohan club
Raymundo, Summer 2021
*/


inherit "/lib/guild_support";
inherit "/d/Shire/room";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";
inherit "/d/Shire/lib/inn";
inherit "/lib/trade"; // for do_fix()

#include "/d/Gondor/defs.h"
#include "ally_rohan.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <std.h>

// for sharpen do_fix
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>



#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define NUM         sizeof(query_money_types(-1))
#define CLOSED      0    /* 1 = closed,   0 = open.  */
#define WAX_COST     5  /* Waxing costs 5% per point */
#define SHARPEN_COST 10 


/* Prototypes */
int do_join(string str);
int do_abandon(string str);
int do_signet(string str);
//int check_member();
int closed;


void
create_room()
{
    object board;

    closed = CLOSED;

    set_short("Ally Rohan Joinroom");
    set_long("The joinroom for the Allies of Rohan.\n");

   


    set_room_tell_time(900);

    // safe rooms

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");


    create_guild_support();


//    add_exit(HUNTCLUB_DIR + "huntclub_porch","south");


    reset_room();
}




string
wizinfo()
{
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed. -- Raymundo\n");
}

void
init()
{
    ::init();
    add_action("do_join", "pledge");
    add_action("do_abandon", "abandon");
    add_action("do_signet", "signet");

    

    init_guild_support();


}



string
close_guild()
{
    if (closed) {
    closed = 0;
    return "  **The club is now open**";
    }
    closed = 1;
    return "  **The club is now closed**";
}

int
query_closed()
{
    return closed;
}
/*
public int
check_member()
{
    if(!TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT))
    {
        write("You're not a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }
    return 0;
}

*/

int
do_join(string str)
{
    object signet;
    int i;
    object shadow, who = this_player();

    if(str != "loyalty")
    {
        write("Pledge what? Loyalty?\n");
        return 0;
    }

/*    if(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT))
    {
        write("You're already a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }
*/
    setuid();
    seteuid(getuid());


    write("Welcome to The Allies of Rohan!\n");
//    write_file(HUNTCLUB_LOG, TP->query_name()+ " joined on " +
//      extract(ctime(time()), 4, 15) + "\n");
/*    write_file(HUNTCLUB_LOG, extract(ctime(time()), 4,9) + " " + 
        (extract(ctime(time()), 20)) + " " + TP->query_name()+ " joined the Hunt.\n");
*/
    seteuid(getuid(TO));
//    TP->set_bit(FOURTH_GROUP,HUNTCLUB_BIT);

    shadow = clone_object(ALLY_SHADOW);
    shadow->shadow_me(who);

    signet = present("_rohan_signet_", TP);
    if (!signet)
    {
        signet = clone_object(ALLY_OBJ + "signet");
        signet->move(TP,1);
        write("You receive your signet..\n");
        say(QCTNAME(TP) +
            " pledges loyalty to Rohan!\n");
    }

    return 1;
}

int
do_abandon(string str)
{
    object signet;
    int result;

    if (str !="rohan")
    {
        write("Abandon what? Rohan??\n");
        return 1;
    }

/*    if(!(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT)))
    {
        write("You aren't a member of The Hunter's/Huntress' Club.\n");
        return 1;
    }
*/
    write("Rohan will miss such a valuable ally..\n");
    signet = present("_rohan_signet_", TP);
    if (signet)
    {
        signet->remove_object();
        write("You toss your signet onto the floor where it turns into dust.\n");
    }
    say(QCTNAME(TP) + " renounces Rohan.\n");
/*
    write_file(HUNTCLUB_LOG, TP->query_name()+" left on "+
//      extract(ctime(time()), 4, 15) + "\n");
        extract(ctime(time()), 4,9) + " " + (extract(ctime(time()), 20)) + "\n");
*/
/*
    write_file(HUNTCLUB_LOG, extract(ctime(time()), 4,9) + " " + 
        (extract(ctime(time()), 20)) + " " + TP->query_name()+ " left the Hunt.\n");

    TP->clear_bit(FOURTH_GROUP,HUNTCLUB_BIT);
*/
    TP->remove_ally_shadow();
    TP->remove_cmdsoul(ALLY_SOUL);
    TP->update_hooks();
    return 1;
}

int
do_signet(string str)
{
    object signet;

    if (str != "me")
        return 0;

/*    if (!(TP->test_bit("Shire",FOURTH_GROUP,HUNTCLUB_BIT)))
    {
        write("Only Members of the Hunt Club may tallystick themselves here.\n");
        return 1;
    }
*/
    signet = present("_rohan_signet_", TP);

    if (signet)
    {
        write("You already have a signet.\n");
        return 1;
    }
    signet = clone_object(ALLY_OBJ + "signet");
    signet -> move(TP,1);
    write("You receive a " + signet->query_short() + ".\n");
    say(QCTNAME(TP)+" receives a " + signet->query_short() +".\n");
    return 1;
}


reset_room()
{

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
        return;

    if (ob->query_wiz_level())
    write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the club.\n");
    else {
    write("The club is closed. Come back later.\n");
//    ob->move(HUNTCLUB_DIR + "huntclub_porch.c");
    }
}

