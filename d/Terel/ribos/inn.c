/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * inn.c
 *
 * An inn in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public int
do_read(string str)
{
    if (str == "menu")
    {
        write("   *****R I B O S    I N N*****\n" +
              "\n" +
              "   Cornbread .......... 20 cc's\n" +
              "   Fire Beans ......... 70 cc's\n" +
              "   Satans Chili ...... 155 cc's\n" +
              "   All you can eat ...1000 cc's\n" +
              "\n" +
              "   Beer ............... 12 cc's\n" +
              "   Wine ............... 80 cc's\n" +
              "\n" +
              "   Please don't be afraid to \n" +
              "   ask for crackers with the \n" +
              "   Chili, because we KNOW its\n" +
              "   very hot!\n");
        return 1;
    }
    notify_fail("Read what?",0);
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Ribos Inn");

    set_long("You have entered the Ribos Inn.  Here, people " +
	     "once came to fill their stomachs with fine food.  " +
	     "Now that no one remains, it is no longer in business.  " +
	     "There are several tables here that have a small " +
	     "amount of dust on them.  There is an old menu here that " +
	     "you can read.\n");

    add_item(({"table", "tables"}), "These tables have " +
             "seen there best days, and are now indefinitly " +
             "on vacation.\n");

    add_item(({"menu"}), 
	     "   *****R I B O S    I N N*****\n" +
	     "\n" +
	     "   Cornbread .......... 20 cc's\n" +
	     "   Fire Beans ......... 70 cc's\n" +
	     "   Satans Chili ...... 155 cc's\n" +
	     "   All you can eat ...1000 cc's\n" +
	     "\n" +
	     "   Beer ............... 12 cc's\n" +
	     "   Wine ............... 80 cc's\n" +
	     "\n" +
	     "   Please don't be afraid to \n" +
	     "   ask for crackers with the \n" +
	     "   Chili, because we KNOW its\n" +
	     "   very hot!\n");

    add_exit(RIBOS_DIR + "road4", "west", 0);

}