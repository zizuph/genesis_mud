inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* Black hat by Sarr, */
void
create_armour()
{
    ::create_armour();
    set_name("hat");
    set_adj("black");
    set_long(
     "This is a black hat that looks kind of dirty. The bring is long\n"+
     "enought that you can <pull> it down to shade your eyes.\n");
    set_ac(2);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE,100);
 }
void
init()
{
    add_action("do_pull","pull");
}
int
do_pull(string str)
{
    if(str != "brim")
    {
        notify_fail("Pull what? The brim perhaps?\n");
        return 0;
    }
    write("You pull the brim of the hat to shade your eyes.\n");
    say(QCTNAME(this_player()) + "pulls the brim of "+
    this_player()->query_possessive() + " hat down to shade "+
    this_player()->query_possessive() + " eyes.\n");
    return 1;
}

