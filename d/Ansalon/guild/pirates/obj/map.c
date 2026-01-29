#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
inherit "/lib/keep";

inherit "/std/object";

void
create_object()
{
    mixed *adj;
    int n;
 
    adj = ({"yellow", "brown", "ancient", "old"});
    n = random(sizeof(adj));
   
    set_name("map");
    set_adj("treasure");
    add_adj(adj[n]);
    set_short(adj[n]+" treasure map");

    if (n==0)
    {   
        set_long("This "+short()+" looks very worn and old. The map has been "+
                 "drawn on a piece of parchment, and a few words have been written "+
                 "in the lower right corner. This map shows the city of Flotsam and "+
                 "a forest surrounding the city. A big X just south of the city might "+
                 "show the location of a hidden treasure.\n");
    }
    if (n==1)
    {   
        set_long("This "+short()+" looks very worn and old. The map has been "+
                 "drawn on a piece of parchment, and a few words have been written "+
                 "in the lower left corner. This map shows the city of Kalaman and "+
                 "the plains south of the city. A big X close to a mountain might "+
                 "show the location of a hidden treasure.\n");
    }
    if (n==2)
    {   
        set_long("This "+short()+" looks very worn and old. The map has been "+
                 "drawn on a piece of parchment, and a few words have been written "+
                 "in the lower left corner. This map shows the city of Neraka and "+
                 "the dragonarmy camps surrounding the city. A big X north of "+
                 "the city might show the location of a hidden treasure.\n");
    }
    if (n==3)
    {   
        set_long("This "+short()+" looks very worn and old. The map has been "+
                 "drawn on a piece of parchment, and a few words have been written "+
                 "in the lower left corner. This map shows the isle of Mithas. A big "+
                 "X in the middle of the isle might show the location of a hidden "+
                 "treasure.\n");
    }

    add_item(({"words", "word","writting"}),"The words on the treasure map reads:\n"+
                                "'mwave'     - Wave the treasure map.\n"+
                                "'mstudy'    - Study the treasure map.\n"+
                                "'mindicate' - Show the X on the treasure map.\n");

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
emote_mstudy(string what)
{
    if (what != "map")
        write("Mstudy what?! Your map?\n");
    else
    {
        write("You unroll your "+short()+" and begin to study it carefully, before rolling it back "+
              "together.\n");
        TP->tell_watcher(QCTNAME(TP)+ " unrolls "+HIS(TP)+ " "+
                              short()+" and carefully begins to study it, before rolling it back "+
                              "up.\n");
    }
    return 1;
}

int
emote_mindicate()
{
    write("You indicate that the X on your "+short()+" marks the spot of a buried treasure.\n");
    TP->tell_watcher(QCTNAME(TP)+ " indicated that the X on "+HIS(TP)+ " "+
                          short()+" marks the spot of a buried treasure.\n");
    return 1;
}

int
emote_mwave()
{
    write("You quickly wave your "+short()+" in the air, while whispering: More "+
          "gold for us.\n");
    TP->tell_watcher(QCTNAME(TP)+ " quickly waves "+HIS(TP)+ " "+
                          short()+" in the air, while whispering: More gold for us.\n");
    return 1;
}

void
init()
{
    add_action("emote_mstudy", "mstudy");
    add_action("emote_mindicate", "mindicate");
    add_action("emote_mwave", "mwave");
    ::init();
}