inherit "/std/room";

#include "defs.h"

#define TEST_COUNT_LOG      LOG_DIR + "test_count" 

/* prototype */
public int        do_test(string arg);



public void
create_room()
{
    set_short("a test chamber");
    set_long("This is a test chamber. Type <doit> to begin the test.\n");
}


public void
init()
{
    ::init();

    add_action(do_test, "doit");
}


public int
do_test(string arg)
{
    int     count = 0,
            one   = 0,
            two   = 0,
            three = 0;
    string  count_result;

    for (count = 0; count < 100000; count++)
    {
        if (!random(100))
        {
            if (!random(100))
            {
                if (!random(100))
                {
                    three++;
                }

                else two++;
            }

            else one++;
        }

    }

    count_result = sprintf("%-12s %-12s %-12s %-12s\n",
        "count = " + count,
        "single = " + one,
        "double = " + two,
        "triple = " + three);

    write(count_result);

    write_file(TEST_COUNT_LOG, count_result);

    write("Count tallied.\n");
    return 1;
}
