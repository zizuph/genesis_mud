inherit "/d/Terel/std/room";

#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/common/swamp/"

#define TP   this_player()
#define TO   this_object()
#define ETP  environment(TP)

public int
do_smell(string str)
{
    if (str) return 0;
    
    write("Oh dear!  It's not a very nice smell!\n");
    say(QCTNAME(TP) + " inhales deeply.\n");
    TP->command("$puke");
    return 1;
}

public int
do_sniff(string str)
{
    if (str) return 0;
    
    write("What a terrible smell!\n");
    say(QCTNAME(TP) + " sniffs with " + TP->query_possessive() +
        " nose.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_smell, "inhale");
    add_action(do_smell, "smell");
    add_action(do_sniff, "sniff");
}

public int
CheckExit(string where)
{
   object kobold = present("kobold");
   
   if (!kobold || !living(kobold) || TP->query_race_name() == "kobold" ||
       !CAN_SEE(kobold, TP)) return 0;
    
   if (!(kobold->query_attack()) || random(100) > 10) {    
       TP->catch_msg(QCTNAME(kobold) +" stops you from going " +
                     where + "!\n");
       tell_room(TO, QCTNAME(kobold) + " stops " + QTNAME(TP) +
                 " from going " + where + ".\n", ({TP, kobold}));
       kobold->command("grin at " + TP->query_real_name());
       return 1;
   } else {
       TP->catch_msg(QCTNAME(kobold) + " couldn't stop you from going " +
                     where + "!\n");
       tell_room(TO, QCTNAME(kobold) + " couldn't stop " + QTNAME(TP) +
                 " from going " + where + ".\n", ({TP, kobold}));
       return 0;
   }
}

public void
create_room()
{
   ::create_room();
}
