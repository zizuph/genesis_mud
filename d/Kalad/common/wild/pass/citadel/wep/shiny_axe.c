/*
   Valen, 20011011 - new axe for Goliath, a bit better quality than
       silver lochaber battleaxe, different look and few improvements
*/

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

int marks;

string
DullTest(void)
{
    return (dull-repair_dull) ? "" : "quite sharp and ";
}

string
ShowReflection(void)
{
    string res;
    object *items;

    items = filter(all_inventory(TP), &->id("_reflection_axe_"));    

    if (!sizeof(items))
    {
        items = filter(all_inventory(environment(TP)),
                &->id("_reflection_axe_"));

        if (!sizeof(items) || !(id(OB_NAME(sort_array(items)[0])))) return "";

        return("You cannot focus properly on the reflection, " +
          "try to get the axe first?\n");
    }

    if(!(id(OB_NAME(sort_array(items)[0])))) return "";

    say(QCTNAME(TP) + " lifts the " + short() + " running " +
        TP->query_possessive() + " fingers over the hilt as " +
        TP->query_pronoun() + " intently studies the blade.\n");

    res = "You see a reflection of someone you are familiar with:\n";

    res += capitalize((string)TP->query_pronoun());
    res += " is " + LANG_ADDART(TP->query_nonmet_name()) + ".\n";
    res += TP->show_scar(TO);
    res += TP->show_sublocs(TO);
                         
    return res;
}

void
create_weapon()
{
    ::create_weapon();

    set_name("axe");
    add_name("_reflection_axe_");
    set_adj("steel");
    add_adj("shiny");
    set_short("shiny steel axe");
    set_pshort("shiny steel axes");
    set_long(
        "This is a large steel axe that was polished to a brilliant shine. " +
        "You can see a reflection of your own face as you examine " +
        "the blade closely. This axe looks @@DullTest@@very deadly " +
        "if in the hands of someone skilled with the use of axes. There " +
        "are some strange marks along the shaft of the axe.\n");

    add_item(({"mark", "marks", "strange mark", "strange marks"}),
        "As you study the marks closely, you cannot reveal their " +
        "true meaning, however they could be used to count dead foes. " +
        "Perhaps you can add your own marks as well.\n");

    add_item(({"blade", "blades", "reflection"}), ShowReflection);

    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(30);
    set_pen(35);

    KVWEP(20);
    KWWEP(30);
    KVOL(steel);

    marks = random(30) + 5;
}

int
CountMarks(string s)
{
    if( s != "marks")
    {
        NF("Count what?\n");
        return 0;
    }
    
    if(!present(TO, TP))
    {
        NF("You cannot focus properly on the marks, " +
           "try to get the axe first?\n"); 
        return 0;
    }
      
    write("You count " + LANG_WNUM(marks) +
        " marks on the shaft of your " + short() + ".\n");
    say(QCTNAME(TP) + " studies closely the shaft of " +
        TP->query_possessive() + " " + short() + ".\n");
    
    return 1;
}

int
AddMark(string s)
{
    if( s != "mark")
    {
        NF("Add what?\n");
        return 0;
    }
    
    if(!present(TO, TP))
    {
        NF("You cannot add a mark now, " +
           "try to get the axe first?\n");
        return 0;
    }

    write("You make one more mark on the shaft of your " + short() + ".\n");
    say(QCTNAME(TP) + " makes some mark on the shaft of " +
        TP->query_possessive() + " " + short() + ".\n");
    
    marks++;
    
    return 1;
}

void
init()
{
    ::init();
    add_action(CountMarks,"count");
    add_action(AddMark,"add");
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#a_m#" + marks + "#";
}

void
init_recover(string arg)
{
    string foobar;

    init_wep_recover(arg);
    sscanf(arg, "%s#a_m#%d#%s", foobar, marks, foobar);
}
