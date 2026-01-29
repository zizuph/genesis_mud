/*
 * Navarre February 24th 2008.
 * Removed the restriction where you couldn't enter the crack if you are
 * above 175 con stat. I removed this restriction as the players are getting
 * fewer.
 */
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <ss_types.h>

inherit MITHAS_IN;

int pulled_roots = 0;
int times = 5;
int roots_hp = 8000;

void
reset_treasure()
{
    pulled_roots = 0;
    times = 5;
    roots_hp = 8000;
}

void
create_mithas_room()
{
    set_short("Dragons lair");
    set_long("@@long_descr@@"); 

    add_prop(ROOM_I_LIGHT,0);
    add_exit(MROOM + "dragons_lair","west",0);

    add_item(({"mound", "huge mound", "silver", "gold"}),
        "The mound consists of silver and gold coins. However all of them "+
        "seems to have been partly destroyed by some kind of acid.\n");

    add_item(({"root", "roots"}),
        "There are many different roots acting as support for the great "+
        "ceiling.\n");

    add_item(({"wall", "walls", "northern wall"}),
        "The walls here are almost completely hidden from the thick roots "+
        "coming down from above, eventhough these stonewalls looks quite "+
        "study, you doubt that it will be enough to keep this place together "+
        "if it wasn't for the roots.\n");

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);

    add_cmd_item(({"roots"}),"pull","@@pull_roots");

    add_cmd_item(({"mound","gold","silver","coins"}),"search","@@search_mound");

    add_cmd_item(({"crack"}),"enter","@@enter_crack");
}

string
long_descr()
{ 
    return
        "You are standing inside a large underground cave. The walls here consists of "+
        "thick stone plates with roots entangled between them. The cave looks almost "+
        "unnatural, perhaps it was created with some powerful magic centuries "+
        "ago. The only exit out of the cave is to the west.\n"+
        "A huge mound of gold and silver lies here.\n";
}

int
enter_crack()
{
    if(pulled_roots == 0)
    {
        write("What?\n");
        return 1;
    }
    
    if (TP->query_stat(SS_CON) >= 175)
    {
        write("You suck in your gut and squeeze through the small crack.\n");
    }
    TP->move_living("into a small crack in the wall", MROOM + "crack",0,0);
    
    write_file(MLOG+"MithasLog.txt", TP->query_name() + " entered the crack " + 
        extract(ctime(time()), 4, 15)+
        ", StatAvg: "+TP->query_average_stat()+
        ", Race: "+TP->query_race()+
        ", Align: "+TP->query_alignment()+"\n");
    return 1;
}

int
pull_roots()
{
    if(TP->query_fatigue() <= 40)
    {
        write("You are too exhausted to pull the roots.\n");
        return 1;
    }  


    if (TP->query_stat(SS_STR) <= 125)
    {
        write("You try to pull some of the roots from the northern wall, "+
            "but you are far to weak to move them.\n");

        say(QCTNAME(this_player()) + " attempts to pull some roots from "+
            "the northern wall, but fails.\n");
        return 1;
    }  
    write("You get a good grip around the base of a thick root and with "+
        "a quick tug you manage to pull some of the roots from the northern "+
        "wall, but there are still more roots on the wall.\n");

    say(QCTNAME(this_player()) + " grabs with both hands around a thick "+
        "root on the northern wall, and with a quick tug, some of the roots "+
        "from the wall falls to the ground.\n");
    TP->add_fatigue(-50);
    
    roots_hp -= (TP->query_stat(SS_STR) - 120) * (TP->query_stat(SS_STR) - 120);
    
    if (roots_hp <= 0)
    {
        write("You remove the last roots. Revealing a small "+
            "crack in the wall.\n");

        say(QCTNAME(this_player()) + " removes the last roots, revealing a "+
            "small crack in the wall.\n");
        pulled_roots = 1;
    }
    return 1;
}

string
search_mound()
{
    int foundAnything;
 
    foundAnything = random(3);

    if ((foundAnything == 0) && (CAN_SEE_IN_ROOM( this_player() ) ) )
    {
	if (times <= 0)
	{
	    return ("Your search reveals nothing special.\n");
	}
	else
	{
            times = times - 1;
	    write("You manage to find a few coins that hasn't been "+
                "destroyed by the acid.\n");
            MONEY_MAKE(random(20) + 5,"gold")->move(this_player(),1);
            MONEY_MAKE(random(1),"platinum")->move(this_player(),1); 
            MONEY_MAKE(random(10) + 5,"silver")->move(this_player(),1);
            say(QCTNAME(this_player()) + " finds a few useable coins in "+
                "the mound of silver and gold.\n");
	    return "";
	}
    }
    return 0;
}
