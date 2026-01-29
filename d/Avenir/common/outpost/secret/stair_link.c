#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";

void
create_room()
{
    set_short("chasm wall");

    set_long("You are clinging to the chasm wall with your "+
        "fingers and toes inserted into cracks and gaps in "+
        "the hot stone. A dull, orange glow can be seen far "+
        "below, and hot, dry winds whip at you, making it "+
        "difficult to proceed up or down without losing your "+
        "nerve.\n");

    add_item(({"handholds","footholds","wall","cracks","gaps"}), 
        "There are gaps and cracks in the chasm wall which "+
        "might allow you work your way up or down--if you are "+
        "very careful.\n");

    add_item(({"abyss", "down", "lava", "lava flow"}), 
        "You stare down into the fiery abyss. The abyss looks "+
        "back into you.\n"+ VBFC_ME("see_abyss"));

    add_prop(ROOM_I_INSIDE, 1);

}

/*
 * When you look into the abyss, the abyss may look back
 * into you ;)
 */
string
see_abyss()
{
    TP->add_panic(40);
    say(QCTNAME(TP) + " stares into the abyss.\n");
    return "";
}

int
check_stair_room()
{
    return 1;
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    object *who;
    string vb = query_verb(), where;

    if(vb == "up")
       where = "above you";
    else if(vb == "down")
       where = "below you";
    else
       where = "there";

    if(!interactive(ob))
       return ::prevent_enter(ob);

    who = FILTER_PLAYERS(all_inventory(TO));

    if(sizeof(who))
    {
       /* Is the player teleporting? Is the player recovering
        * from link death? If so, don't prevent the move!
        */
       if(!ENV(ob)->check_stair_room())
           return ::prevent_enter(ob);
          
       ob->catch_msg(QCNAME(who[0]) + " is hanging from the chasm wall "+
           where + ", blocking your movement in that direction.\n");
       ob->add_panic(20);
       return 1;
    }

    return ::prevent_enter(ob);
}

