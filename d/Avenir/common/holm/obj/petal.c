// -*-C++-*- 
// Fire Rose Petal  /d/Avenir/common/holm/obj/petal.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Beast Treasure
// last update:     
// note:            The petals burst into flames when dropped. They can
//                  be used to block exits for a short period of time.
//                  Related objects: rose.c and flames.c
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
#include "/d/Avenir/common/holm/holm.h"

/* 30 mins before no longer useful */
#define PETAL_TIME    (1800.0)
#define PETAL_EFFECT  "_petal_is_effective"

string dstr;

/* 
 * This function is called PETAL_TIME after this object is cloned.
 * It removes the magical effectiveness after 30 mins
 */
void
no_longer_effective()
{
    remove_prop(PETAL_EFFECT);
    write("The "+ short() +" seems to shrivel a bit, as though "+
        "it has lost something.\n");        
    set_long("This is a petal from a rather unique rose. The orange-"+
        "red color of the petal is less vibrant, and seems to have "+
        "ceased its flickering.\n"); 
}

/*
 * Have to use this function instead of calling remove_object
 * directly in the drop_fail func, as it will return 'drops 
 * something' instead of 'drops petal'.
 */
void
remove_it()
{
    tell_room(environment(TO), "The "+ short() +" bursts into flames.\n");
    remove_object();
}

/* 
 * This is the function called by VBFC in add_prop(OBJ_M_NO_DROP)
 */
int 
drop_fail(string str)
{
    object flames;
    string dstr = str;
    int i;

    if (!str || !strlen(str))    
    {
        add_prop(OBJ_M_NO_GET, "It has caught fire! You will burn "+
            "yourself!\n");
        flames = clone_object(HOLM_OBJ + "flames");
        flames->set_timer(60 + (random(60)));
        flames->move(environment(TP),1);
        set_alarm(1.0, 0.0, remove_it);
        return 0;
    }       
    write("That won't work. Try <toss [exit]> to block the exit "+
        "with fire from the petal.\n");
    return 1;
}

/* 
 * This is the function called by the actions 'toss' and 'throw'
 */
int
drop_check(string str)
{ 
    object flames;
    string dstr = str;
    int i;
    seteuid(getuid());

    if (!query_prop(PETAL_EFFECT))
        return 0;
        
    if (!str || !strlen(str))    
    {
        add_prop(OBJ_M_NO_GET, "It has caught fire! You will burn "+
            "yourself!\n");
        say(QCTNAME(TP) +" drops a "+ short() +".\nThe "+ short() +
            " bursts into flames.\n");
        write("You drop a "+ short() +".\nThe "+ short() +
            " bursts into flames.\n");
        flames = clone_object(HOLM_OBJ + "flames");
        flames->set_timer(60 + (random(60)));
        flames->move(environment(TP),1);
        remove_object();
        return 0;
    }

    i = member_array(str, environment(TP)->query_exit_cmds()); 
    if (i < 0) 
    {
        notify_fail("That won't work. Try <toss [exit]> to block the "+
            "exit with fire from the petal.\n");
        return 0;
    }   
    say(QCTNAME(TP) +" drops a "+ short() +".\nThe "+ short() +" lands "+
        "near the exit leading "+ str +" and bursts into flames.\n");
    write("You drop a "+ short() +".\nThe "+ short() +" lands near the "+
        "exit leading "+ str +" and bursts into flames.\n");
    add_prop(OBJ_M_NO_GET, "It has caught fire! You will burn "+
        "yourself!\n");

    flames = clone_object(HOLM_OBJ + "flames");
    flames->set_exit_blocked(dstr);
    flames->set_timer(60 + (random(60)));
    flames->move(environment(TP),1);
    remove_object();
    return 1;
}

/* Lets create the petal now */
void
create_object()
{
    set_name("Magic_Rose_Petal");
    add_name(({"petal", "rose petal"}));
    set_short("orange-red rose petal");
    add_adj(({"red", "orange", "enchanted", "fire"}));
    set_long ("This is a petal from a rather unique rose. The orange-"+
        "red color of the petal is in constant, flickering motion. "+
        "It is warm and velvet-smooth between your fingers. You "+
        "experience an urge to toss it.\n");

    add_prop(OBJ_I_VALUE,  1000);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_BUY, "It is absolutely priceless. A lifetime of "+
        "drudgery and thrift and you still wouldn't have enough plats "+
        "to buy it!");
    add_prop(OBJ_M_NO_DROP, "@@drop_fail@@");
    add_prop(PETAL_EFFECT, 1);
    add_prop(OBJ_S_WIZINFO,  "This rose is enchanted. "+
        "The petals of this rose can be plucked. "+
        "The petals will burst into flame when dropped. "+
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time. "+
        "Fools and those skilled in the art of illusion will be able "+
        "to pass through the flames, in addition to the whomever holds "+
        "this rose. The petal loses magical potency after 30 minutes.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 40, "illusion" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This petal is from an enchanted fire rose.\n", 10,
        "This petal will burst into flames when dropped.\n", 20,
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time.\n", 45,
        "Fools and those skilled in the art of illusion will be able "+
        "to pass through the flames, in addition whomever holds the "+
        "rose.\n", 55,
        "Petals lose magical potency after thirty minutes.\n", 65 }));
 
    set_alarm(PETAL_TIME, 0.0, "no_longer_effective");
    seteuid(getuid());
}

void 
init()
{
    ::init();
    add_action(drop_check,    "toss");
    add_action(drop_check,    "throw");
    add_action(drop_check,    "petaltoss");
}
