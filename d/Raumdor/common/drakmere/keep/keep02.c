#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

object guard;
void reset_room();

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now inside a large square chamber. All around "+
        "you on the walls, hang tapestries and torches. In the center "+
        "of this chamber, you see a large stone altar, where you also "+
        "see priests kneeling and praying. This must be the holy temple "+
        "room.\n");
    add_item("altar","It is stone, with many ancient and golden runes "+
        "carved into it. A white cloth is placed over it with a couple of "+
        "candles burning.\n");
    add_item("priests","They are robed in white with golden runes. They "+
        "kneel before the altar humming softly.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
        "crosses, and all kinds of cool stuff.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(KEEP_DIR + "keep03","west",0);
    add_exit(KEEP_DIR + "keep01","east",0); 
    reset_room();
}

void
reset_room()
{
    if(!guard)
        {
        guard = clone_object(DRAKMERE_NPC_DIR + "eg_guard");

        guard->move_living("xxx",TO);
    }
}


void
init()
{
    ::init();
    if(TP->query_prop(LIVE_I_UNDEAD))
        set_alarm(5.0,0.0,"holy_burn",TP);
}

void
holy_burn(object ob)
{
    if(present(ob,TO))
        {
        ob->catch_msg("You feel the holy presence in here burn into your "+
            "flesh! It is horrible!\n");
        ob->command("scream");
        tell_room(TO,QCTNAME(ob)+" is burned by the holy powers in this "+
            "room.\n",ob);
        ob->heal_hp(-80);
    }
    if(present(ob,TO))
        set_alarm(30.0,0.0,"holy_burn",ob);
}
