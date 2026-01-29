#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/std/leftover";

object lamiaheart;
void blood();

/* by Antharanos
 * Polished by Ibun may 2007
 */


void
create_leftover()
{
    set_name("heart");
    add_name("lamia heart");
    add_name("heart of the lamia");
    set_long("This is the torn and bloodied heart of the Lamia Queen!\n");
    set_decay_time(60);
    set_amount(2000);
    add_prop(HEAP_S_UNIQUE_ID, "_lamia_queen_heart");
}

void
init()
{
    ::init();
    AA(sacrifice,sacrifice);
}

int
sacrifice(string str)
{

    if(!str || str != "heart")
    {
        NF("You can't sacrifice '" + str + "'.\n");
        return 0;
    }
    write("You raise the torn and bloodied heart of the Lamia Queen "+
        "above your head and rip it asunder, showering blood all over "+
        "yourself.\n");
    say(QCTNAME(TP) + " raises the torn and bloodied heart of the Lamia "+
        "Queen above " + TP->query_possessive() + " head and rips it asunder, "+
       "showering blood all over " + TP->query_objective() + "self.\n");
    blood();
    set_alarm(2.0,0.0,"remove_heart");
    return 1;
}

void
remove_heart()
{
    TP->catch_msg("You have destroyed the heart!\n");
    remove_object();
    return;
}

void
blood()
{
    object abdell;

    write("You are now covered in blood!\n");
    say(QCTNAME(TP) + " is now covered in blood!\n");
    abdell = present("abdell", environment(TP));
    if (abdell)
        abdell->return_sacrifice();
    return;
}

