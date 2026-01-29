/**********************************************************************
 * - Pool of elven nymph dragons                                    - *
 * - Created by Damaris 03/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Valen 2/2002                                        - *
 * -                Updates - Damaris@Genesis 04/2007               - *
 * -                          Added enter_pool() takes player to    - *
 * -                          /d/Khalakhor/guilds/room/ceremony.c   - *
 * -                          Takes to an open room access to all   - *
 * -                          players.                              - *
 **********************************************************************/

#pragma strict_types

#include "defs.h"
#include "/d/Khalakhor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Khalakhor/std/room";
#define HOLDING "/d/Khalakhor/guilds/eilgalaith/room/holding"
#define GROVE   "/d/Khalakhor/guilds/eilgalaith/room/ceremony"
public void
create_khalakhor_room()
{
    int i;
    
    set_short("Under a tree");

    set_long("   This is a cool darkened area under a tree. The walls " +
        "resemble a cave made with large roots of the tree. There is " +
        "a small rainbow coloured pool that shimmers with light.\n");
        
    add_item(({"pool", "rainbow pool", "small pool"}),
        "This small rainbow coloured pool looks very inviting to "+
        "drink or to enter.\n");

    add_item(({"ceiling"}),
        "The ceiling is made from intertwining limbs.\n");

    add_item(({"floor", "ground"}),
        "The ground is moist dirt with large tree roots projecting outward.\n");

    add_item(({"wall", "walls"}),
        "The walls resemble a cave that has been made out of tree roots.\n");
      
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    for (i = 0; i < 4; i++)
    {
        clone_here(NPC + "ndragon")->move(TO);
    }

    add_exit("tree", "up");
}

int
wash_it(string str)
{
    if((str == "face"))
    {
        write("You bend over and dip your hands into the pool and " +
              "wash your face with the refreshing water.\n"+
              "It feels cool on your skin.\n");
      
        /* This what others in room see. */
        say(QCTNAME(TP) + " bends over and dips " + HIS(TP) + " "+
          "hands into the pool and washes " + HIS(TP) + " face "+
          "with the refreshing water.\n");
        
        return 1;
    }
    if((str == "hands"))
    {
        write("You bend over and dip your hands into the pool and " +
              "wash them with the refreshing water.\n"+
              "It feels cool on your skin.\n");
      
        /* This what others in room see. */
        say(QCTNAME(TP) + " bends over and dips " + HIS(TP) + " "+
          "hands into the pool and washes them with the refreshing "+
          "water.\n");
       
        return 1;
    }
    if((str == "neck"))
    {
        write("You bend over and dip your hands into the pool and "+
              "wash your neck with the refreshing water.\n"+
              "It feels cool on your skin.\n");
      
        /* This what others in room see. */
        say(QCTNAME(TP) + " bends over and dips " + HIS(TP) + " hands "+
          "into the pool and washes "+ HIS(TP) +" neck "+
          "with the refreshing water.\n");
       
        return 1;
    }
    if((str == "ears"))
    {
        write("You bend over and dip your hands into the pool and "+
              "wash your ears with the refreshing water.\n"+
              "It feels cool on your skin.\n");
      
        /* This what others in room see. */
        say(QCTNAME(TP) + " bends over and dips " + HIS(TP) + " hands "+
          "into the pool and washes " + HIS(TP) + " ears with the "+
          "refreshing water.\n");
       
        return 1;
    }
    if((str == "feet"))
    {
        write("You bend over and dip your hands into the pool and "+
              "wash your feet with the refreshing water.\n"+
              "It feels cool on your skin.\n");
      
        /* This what others in room see. */
        say(QCTNAME(TP) + " bends over and dips " + HIS(TP) + " hands "+
          "into the pool and washes " + HIS(TP) + " feet with the "+
          "refreshing water.\n");
       
        return 1;
    }
    if((str == "body"))
    {
        write("There just isn't enough room for you to get in the pool.\n");
        
        /* This what others in room see. */
        say(QCTNAME(TP) + " looks like " + HE(TP) +
            " is thinking about something.\n");

        return 1;
    }
    return NF("Wash what?\n");
}

int
drink_it(string str)
{
    string what, where;
    int i;

    if (!strlen(str))
    {
        return NF("Drink what?\n");
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
        {
            /* Syntax must simply be "drink <something>" */
            what = str;
        }
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        return NF("Drink what?\n");
    }

    if (where && !parse_command(where, ({}), "[the] 'pool' "))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        return NF("Drink from where?\n");
    }

    /* Drink small amounts up to 500 soft */
    for (i = 0; i < 10; i++)
    {
        if (!TP->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!TP->drink_soft(50, 1))
    {
        write("You take a drink of the cool water. Having " +
              "drunk your fill, you feel refreshed.\n");
    }
    else
    {
        write("You take a drink of the cool water.\n");
    }

    say(QCTNAME(TP) +" drinks some water from the "+
        "pool.\n");
    return 1;
}

int
enter_pool(string str)
{
	notify_fail("Enter what?\n");
	if(str != "pool")
	return 0;
	write("You enter the pool.\n\n");
	say(QCTNAME(TP)+" enters the pool.\n");
	TP->move_living("M", HOLDING ,1,1);
	set_alarm(5.0,0.0,"do_hold");
	return 1;
}

void
do_hold()
{
	write("There is a flash of bright rainbow colours before "+
	"your eyes.\n\n");
	set_alarm(2.0,0.0,"do_move");
}

void
do_move()
{
	TP->move_living("M",GROVE);
	tell_room(environment(TP),QCTNAME(TP)+" suddenly appears "+
	"with a bright flash of rainbow light.\n",TP);
	TP->command("gasp");
}

void
init()
{
	::init();
	add_action(drink_it, "drink");
	add_action(wash_it, "wash");
	add_action(enter_pool, "enter");
}
