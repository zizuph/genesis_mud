inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Black steel longsword(corrupted), Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("longsword");
    add_name("sword");
    set_adj("rusty");
    add_adj("black");
    set_short("rusty black longsword");
    set_long("This is a sword made of blackened steel, but it is very "+
    "dirty and rusty. It is old and used, but it looks like it can still"+
    " do some damage. On the hilt is a carving of a "+
    "skull. Set into the bottom of the hilt is a hole where a small "+
    "ruby might have been. "+
    "You see faded runes along the blade.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_RIGHT);
    set_hit(25);
    set_pen(25);
    add_prop(OBJ_I_WEIGHT,7200);
    add_prop(OBJ_I_VOLUME,4500);
    add_prop(OBJ_I_VALUE,600);
    add_item(({"runes"}),"@@runes");
    add_item(({"skull"}),"A rather grim looking skull, with two tiny "+
    "red rubies for eyes.\n");
}

string
runes()
{
   if(TP->query_skill(109) > 30)
       return "You make out the words: Khiraa.\n";
   return "You can't understand them.\n";
}

