#include "defs.h"

#define TXT_NO_HIGH "Not filled: Perhaps you should apply?"
#define TXT_NO_INT "Not filled: Everyone is a suspect."
#define TXT_NO_ARENA "Not filled: The arena is silent."
#define TXT_NO_REC "Not filled: The ranks are thinning."
#define DISPLAY(position, text, tmp) \
    tmp = MANAGER->query_overseer_by_position(position); \
    arr[position] = (tmp == 0 ? text : capitalize(tmp));

public int
_cmd_list_overseers(string str)
{
    if("overseers" != str)
    {
        return notify_fail("List what? The overseers perhaps?\n");
    }

    string tmp;
    string *arr = allocate(applyv(max, POS_ALL));

    DISPLAY(POS_HIGH, TXT_NO_HIGH, tmp);
    DISPLAY(POS_INT, TXT_NO_INT, tmp);
    DISPLAY(POS_REC, TXT_NO_REC, tmp);
    DISPLAY(POS_ARENA, TXT_NO_ARENA, tmp);

    write(
      "\nThe Overseers Currently Consist of\n\n"+
      "  ===========================================================\n\n"+
      "  High Overseer: "+ arr[POS_HIGH] +"\n\n"+
      "  Internal Overseer: "+ arr[POS_INT] +"\n\n"+
      "  Recruitment Overseer: "+ arr[POS_REC] +"\n\n"+
      "  Arena Overseer: "+ arr[POS_ARENA] +"\n\n"+
      "  ===========================================================\n"
    );

    int count = sizeof(MANAGER->query_revolters());

    if(count > 0)
    {
        write(
            "\nThere " + (count == 1 ? "is " : "are ") +
            LANG_NUM2WORD(count) + " gladiator" + (count == 1 ? "" : "s") +
            " revolting to overthrow the Overseers.\n"
        );

        if(MANAGER->query_revolter(this_player()->query_real_name()))
        {
            write("You are among the revolting gladiators.\n");
        }
    }

    return 1;
}
