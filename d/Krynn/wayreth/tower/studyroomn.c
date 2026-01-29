/*
   Wayreth.

   studyroomn.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/07/26
   By ...........: Jeremiah

*/

#include <time.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;

#define PREVIOUSLY_FAILED_TEST      "_previously_failed_wohs_test"

void
reset_tower_room()
{
    return;
}

void
create_tower_room()
{
   set_short("The northern study");
   set_long("You are standing in a very quiet room. This looks most " +
            "of all like a study area. Benches lining the walls, " + 
            "a few chairs and small study tables, placed at " +
            "regular intervals across the floor, makes it possible " +
            "to sit in here undisturbed studying your spellbook. A " +
	    "thick carpet is covering the floor, silencing your "+
	    "steps. The carpet looks so clean that you feel that "+
	    "you definitely do not want to just drop things here "+
	    "cluttering a good study room. On the northern wall " +
            "hangs an honour board.\n");

   add_item("floor", "The floor is covered with a thick carpet.\n");

   add_item(({"carpet", "thick carpet"}), "A thick carpet covering " +
            "the entire floor, silencing your every step.\n");

   add_item(({"bench", "benches"}), "Comfortable cushioned benches, " +
            "standing along the walls of this room.\n");

   add_item(({"table", "tables"}), "Sturdy tables made of the finest " +
            "vallenwood.\n");

   add_item(({"chair", "chairs"}), "Sturdy looking chairs made of " +
            "the finest vallenwood. There is a chair for each table " +
            "in here.\n");

   add_item(({"honour board","northern wall","board","wall"}),
            "On the northern wall hangs a board of darkened wood, " +
            "with the names of those who have passed the Test of " +
            "High Sorcery embossed upon it in silver. If you so " +
            "desired you could read it.\n");

    set_wall_type(2);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(WTOWER + "study", "south", 0);

    reset_tower_room();
}

void
init()
{
    ADD("read_honourboard","read");
    ::init();
}

int
read_honourboard(string str)
{    
    if(!str)
    {
       notify_fail("Read what? The honour board?\n");
       return 0;
    }

    if(str != "board" && str != "honour board" && str != "the honour board")
    {
       notify_fail("Read what? The honour board?\n");
       return 0;
    }

    mapping list = WOHS_MANAGER->query_wohs_test_time_stamp();

    string  distinction = "";
    string  merit = "";
    string  passed = "";
    string * dlist = ({ });
    string * mlist = ({ });
    string * plist = ({ });
    int     dsize = 0;
    int     msize = 0;
    int     psize = 0;

    if(!m_sizeof(list))
    {
       write("There are no Wizards listed on the honour board who have " +
             "passed the Test of High Sorcery.\n");
       return 1;
    }

    foreach(string name, int * var: list)
    {
        int score = var[1];

        if(WOHS_MANAGER->query_wohs_test_prop(name, PREVIOUSLY_FAILED_TEST))
        {
            plist += ({name});
        }
        else if(score > 90)
        {
            dlist += ({name});
        }
        else if(score > 70)
        {
            mlist += ({name});
        }
        else
        {
            plist += ({name});
        }
     }

    foreach(string name, int * var: list)
    {
        int date = var[0];
        int score = var[1];
        mapping wohs_list = WOHS_MANAGER->query_wohs_members_list();
        string * wohs_names = m_indexes(wohs_list);
        string active;

        if(!IN_ARRAY(name, wohs_names))
            active = "";
        else
            active = " (@)"; 

        if(WOHS_MANAGER->query_wohs_test_prop(name, PREVIOUSLY_FAILED_TEST))
        {
            psize++;
            passed += capitalize(name) + active + 
                " - " + TIME2FORMAT(date, "d mmm yyyy");
            if (sizeof(plist) - psize == 1)
                passed += ", and ";
            else if (sizeof(plist) - psize > 1)
                passed += ", ";
        }
        else if(score > 90)
        {
            dsize++;
            distinction += capitalize(name) + active +
                " - " + TIME2FORMAT(date, "d mmm yyyy");
            if (sizeof(dlist) - dsize == 1)
                distinction += ", and ";
            else if (sizeof(dlist) - dsize > 1)
                distinction += ", ";
        }
        else if(score > 70)
        {
            msize++;
            merit += capitalize(name) + active +
                " - " + TIME2FORMAT(date, "d mmm yyyy");
            if (sizeof(mlist) - msize == 1)
                merit += ", and ";
            else if (sizeof(mlist) - msize > 1)
                merit += ", ";
        }
        else
        {
            psize++;
            passed += capitalize(name) + active +
                " - " + TIME2FORMAT(date, "d mmm yyyy");
            if (sizeof(plist) - psize == 1)
                passed += ", and ";
            else if (sizeof(plist) - psize > 1)
                passed += ", ";
        }
     }

     if(distinction == "")
         distinction = "      No one has passed with distinction";

     if(merit == "")
         merit = "      No one has meritoriously passed";

     if(passed == "")
         passed = "      No one has passed without merit";

     write("You read the honour board of those who have passed the Test of " +
           "High Sorcery.\n\n" + 
           "      ======<<@@    Passed the Test with Distinction    @@>>======\n\n" + 
           distinction + ".\n\n\n"+
           "      ======<<@@      Passed Meritoriously the Test     @@>>======\n\n" + 
           merit + ".\n\n\n"+
           "      ======<<@@             Passed the Test            @@>>======\n\n" + 
           passed + ".\n\n\n(@) denotes a current member of the Order.\n\n");

     say(QCTNAME(TP) + " examines the honour board.\n");

    return 1;
}