// file name        /d/Avenir/common/dead/obj/rosepetal_goddess.c copies from 
// Fire Rose Petal  /d/Avenir/common/holm/obj/petal.c       
// creator(s):      Lilith  01/20/97
// purpose:         Enchanted rose for Mascarvin Quest
// last update:     Lilith, Sept 2021: added PVP_ABILITY_DISABLED check.
//                  Lilith, Oct 2021: added 3 sec delay after block msg.
// note:            The petals burst into flames when dropped. They can
//                  be used to block exits for a short period of time (<30 seconds)
//                  Could be useful for escaping sticky situations with
//                  pursuing npcs or players.
//                  It cannot be given or dropped for others to take.
//                  Related objects: rose_fire.c and rose_flames.c
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";
#include "/d/Avenir/common/dead/dead.h"
#include "/d/Genesis/specials/defs.h"

#define TOSS_PROP     "_Avenir_Fire_Petal_Tosser"

string dstr;

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
        flames = clone_object(OBJ + "rose_flames");
        flames->set_timer(15 + (random(15)));
        flames->move(environment(TP),1);
		flames->set_tosser(TP);
        set_alarm(1.0, 0.0, remove_it);
        return 0;
    }       
    write("That won't work. Try <toss [exit]> to block the exit "+
        "with flames from the petal.\n");
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
        
    if (!str || !strlen(str))    
    {
        add_prop(OBJ_M_NO_GET, "It has caught fire! You will burn "+
            "yourself!\n");
        say(QCTNAME(TP) +" drops a "+ short() +".\nThe "+ short() +
            " bursts into flames.\n");
        write("You drop a "+ short() +".\nThe "+ short() +
            " bursts into flames.\n");
        flames = clone_object(OBJ + "rose_flames");
        flames->set_timer(15 + (random(15)));
        flames->move(environment(TP),1);
        TO->remove_object();
        return 1;
    }

    if (PVP_ABILITY_DISABLED)
	{
		write("Tossing the petal to block an exit with flames has been "+
		    "temporarily disabled by wizards.\n");
		return 1;
	}

    i = member_array(str, environment(TP)->query_exit_cmds()); 
    if (i < 0) 
    {
        notify_fail("That won't work. Try <toss [exit]> to block the "+
            "exit with fire from the petal.\n");
        return 0;
    }

    say(QCTNAME(TP) +" drops an "+ short() +".\nThe "+ short() +" lands "+
        "near the exit leading "+ str +" and bursts into flames.\n");
    write("You drop an "+ short() +".\nThe "+ short() +" lands near the "+
        "exit leading "+ str +" and bursts into flames.\n");
    add_prop(OBJ_M_NO_GET, "It has caught fire! You will burn "+
        "yourself!\n");
    TP->add_prop(TOSS_PROP, 1);
    flames = clone_object(OBJ + "rose_flames");
    flames->set_exit_blocked(dstr);
    flames->set_timer(15 + (random(15)));
    flames->move(environment(TP),1);
    TO->remove_object();
    return 1;
}

/* Lets create the petal now */
void
create_object()
{
    set_name("_Avenir_fire_rosepetal");
    add_name(({"petal", "rose petal"}));
    set_short("orange-red rose petal");
    add_adj(({"red", "orange", "enchanted", "fire"}));
    set_long ("This is a petal from a rather unique rose. The orange-"+
        "red color of the petal is in constant, flickering motion. "+
        "It is warm and velvet-smooth between your fingers. You "+
        "experience an urge to toss it toward an exit.\n");
    add_prop(OBJ_M_NO_SELL, "Mascarvin would not be pleased if you sold this.\n");
    add_prop(OBJ_I_VALUE,  1730); // 1 plats
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_M_NO_GIVE, "You do not dare to risk offending Macarvin by "
	    +"giving away even just a petal from Her rose."); 
    add_prop(OBJ_M_NO_DROP, "@@drop_fail@@");
    add_prop(OBJ_S_WIZINFO,  "This is a petal from an enchanted rose. "+
        "The petals will burst into flame when dropped. "+
        "When tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time (<30 seconds)."+
        "Players with INT<50 and with ILLUSION>40-59 will be able "+
        "to pass through the flames, in addition to the whomever holds "+
        "this rose. The petal's exit blocking functionality does not "+
		"work if PVP_ABILITY_DISABLED is true in the /d/Genesis/specials/"+
		"defs.h file.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 40, "illusion" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This petal is from an enchanted fire rose.\n", 10,
        "This petal will burst into flames when dropped.\n", 20,
		"So long as the wizards permit, "+
        "when tossed in the direction of an exit, the petal's flames "+
        "will block that exit for a short period of time.\n", 30,
        "Fools and those skilled in the art of illusion will be "+
		"able to pass through the flames,", 40,
        "as will the one who tossed the petal.", 50	}));
 
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

string
query_auto_load()
{
	 return (MASTER + ":");
}
