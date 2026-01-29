inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Black steel sword, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("black");
    add_adj("steel");
    set_short("black steel sword");
    set_long("This is a sword made of blackened steel. It looks rather "+
    "well made. In the center of the hilt there is a carving of a skull, "+
    "while runes run along the handle.\n");
    set_dt(W_SLASH);
    set_wt(W_SWORD);
    set_hit(30);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
    add_item(({"runes"}),"@@runes");
    add_item(({"skull"}),"A rather grim looking skull.\n");
}

string
runes()
{
   if(TP->query_skill(109) > 30)
       return "You make out the words: Khiraa.\n";
   return "You can't understand them.\n";
}

