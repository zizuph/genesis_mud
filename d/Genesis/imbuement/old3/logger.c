/*
 *  Logger for imbuements
 */
#pragma strict_types
#pragma no_clone

#include "imbuement.h"
#include <time.h>

/* Global Variables */
/* Prototypes */
public void             create();
public void             log(int ID, int Num, int Text);
public void             log_stone(int Text);


/*
 * Function name:       create
 * Description  :       set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());
} /* create */


/*
 * Function name:       log
 * Description  :       log something
 * Arguments    :       int ID - ID of the imbuement
                        int Num - "slot" of the imbuement
                        string text - text to log
 */
public void
log(int ID, int Num, int Text)
{
    if (!wildmatch(IMBUE_DIR + "*", "/" + calling_program()))
        write_file(IMBUE_LOG_DIR + "imbue_log", "Strange caller " +
            file_name(calling_object()) + " " + 
            this_interactive()->query_real_name() + "\n");

    write_file(IMBUE_LOG_DIR + "imbue_log",
        sprintf("%s %s%5d %d %s\n",
            TIME2FORMAT(time(), "yyyy/mm/dd"),
            ctime(time())[11..18],
            ID,
            Num,
            Text));
} /* log */


/*
 * Function name:       log_stone
 * Description  :       log something about stones
 * Arguments    :       string text - text to log
 */
public void
log_stone(int Text)
{
    if (!wildmatch(IMBUE_DIR + "*", "/" + calling_program()))
        write_file(IMBUE_LOG_DIR + "stone_log", "Strange caller " +
            file_name(calling_object()) + " " + 
            this_interactive()->query_real_name() + "\n");

    write_file(IMBUE_LOG_DIR + "stone_log",
        sprintf("%s %s %s\n",
            TIME2FORMAT(time(), "yyyy/mm/dd"),
            ctime(time())[11..18],
            Text));
} /* log_stone */
