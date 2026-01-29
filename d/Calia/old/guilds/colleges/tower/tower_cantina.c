/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include <math.h>
#include <composite.h>	
#include <filter_funs.h>
#include "defs.h"

#define CANTINA_I_SITTING "_cantina_i_sitting"

static string *specials1 = ({"roasted", "pan-fried", "fried", "poached", 
    "crispy","boiled", "steamed", "chargrilled", "braised", "stewed", 
    "broiled", "deep-fried", "flash-fried", "sauteed", "simmered", "smoked"});
static string *specials2 = ({"squid", "mutton", "cod", "monkfish", "bass",
    "bluecrab", "lobster", "salmon", "porkchop", "grouse", "duck",
    "shrimp", "chicken", "crayfish", "kidney", "eel", "elk", "moose",
    "boar", "tenderloin", "liver", "tuna", "quail", "hen", "lambchop"});
string *weekly_menu;
int menu_time;

void
update_menu()
{
    string timestr;
    int secs, tim, size1, size2;

    tim = time();
    timestr = ctime(tim);
    size1 = sizeof(specials1);
    size2 = sizeof(specials2);
    

    secs = atoi(timestr[17..18]) + atoi(timestr[14..15])*60
        + atoi(timestr[11..12])*60*60; //Seconds since day started.
                
    switch(timestr[0..2])
    {
        case "Mon":
            menu_time = tim - secs;
            break;
        case "Tue":
            menu_time = tim - secs - 24*60*60;
            break;
        case "Wed":
            menu_time = tim - secs - 2*24*60*60;
            break;
        case "Thu":
            menu_time = tim - secs - 3*24*60*60;
            break;
        case "Fri":
            menu_time = tim - secs - 4*24*60*60;
            break;
        case "Sat":
            menu_time = tim - secs - 5*24*60*60;
            break;
        default:
            menu_time = tim - secs - 6*24*60*60;
    }
    
    // menu_time ends up becoming the time this week started.

    if (time() - menu_time > 7*24*60*60 || !sizeof(weekly_menu))
    {
        weekly_menu = 
            ({specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)],
            specials1[random(size1)] + " " + specials2[random(size2)]});
    }    

    save_object(TOWER_OBJECTS + "cantina_log");
}

string
menu()
{
    string str, timestr;
    
    if (time() - menu_time > 7*24*60*60)
    {
        update_menu();
    }
    
    str = "This week's menu:\n" +
        "Monday:    " + weekly_menu[0] + "\n" +
        "Tuesday:   " + weekly_menu[1] + "\n" +
        "Wednesday: " + weekly_menu[2] + "\n" +
        "Thursday:  " + weekly_menu[3] + "\n" +
        "Friday:    " + weekly_menu[4] + "\n" +
        "Saturday:  " + weekly_menu[5] + "\n" +
        "Sunday:    " + weekly_menu[6];
            
    return str;
}

string
benchpeeps()
{
    object *sitters = filter(FILTER_LIVE(all_inventory(TO)), 
        &->query_prop(CANTINA_I_SITTING));
    
    if (sizeof(sitters) > 1 && !(member_array(TP, sitters) == -1))
    {
        return "You are sitting at the table, along with " + 
            COMPOSITE_ALL_LIVE(sitters - ({ TP })) + ". ";
    }
    else if (sizeof(sitters) > 1)
    {
        return "Sitting at the table are " + COMPOSITE_ALL_LIVE(sitters) +
            ". ";
    }
    else if (sizeof(sitters) && sitters[0] == TP)
    {
        return "You are sitting at the table. ";
    }
    else if (sizeof(sitters))
    {
        return "Sitting at the table is " + COMPOSITE_ALL_LIVE(sitters[0]) + 
            ". ";
    }
    else
    { 	
        return "";
    }
}


int
check_sitting()
{
    if (TP->query_prop(CANTINA_I_SITTING) == 1)
    {
        TP->catch_tell("You need to get up before you can move!\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

create_room()
{
    set_short("Tower Cantina");

    set_long("You stand in the cantina of the Marble Tower. Here you can" +
        " enjoy a quiet meal between bouts of studying. There is a counter" +
        " where you can help yourself to a plate of today's special and get" +
        " some ice water to wash it down with. There is a long table with" +
        " a bench on each side and a weekly menu is posted above the " +
        "counter. @@benchpeeps@@" + basic_desc + " To the north a corridor" +
        " stretches.\n");

    add_item(({"bench", "benches"}), "The benches are of the wooden variety," +
        " and don't look particularly comfortable.\n");
    add_item("table", "This wooden table is clean and level," +
        " as you would expect.\n");
    add_item("counter", "This solid counter separates the cantina from the" +
        " kitchen. You can <order> the special or water to drink here.\n");
    add_item("kitchen", "You can't see much of the kitchen from here, but" +
        " you can hear the cook rustling around in there.\n");
    add_item(({"menu", "weekly menu"}), "@@menu@@\n");
    
    add_cmd_item("menu", "read", "@@menu@@\n");

    add_exit(TOWER + "tower_corr_2_7.c", "north", "@@check_sitting@@", 1);

    make_college_room();
}

int
do_order(string str)
{
    string fname, fadj, *today_special;
    object obj;

    if (TP->query_prop(CANTINA_I_SITTING) == 1)
    {
        NF("You need to get up to order!\n");
        return 0;
    }

    if (str == "special" || str == "the special" || str == "today's special")
    {
        if (time() - menu_time > 7*24*60*60)
        {
            update_menu();
        }
        
        seteuid(getuid());
         
        switch(ctime(time())[0..2])
        {
            case "Mon":
                today_special = explode(weekly_menu[0], " ");
                break;
            case "Tue":
                today_special = explode(weekly_menu[1], " ");
                break;
            case "Wed":
                today_special = explode(weekly_menu[2], " ");
                break;
            case "Thu":
                today_special = explode(weekly_menu[3], " ");
                break;
            case "Fri":
                today_special = explode(weekly_menu[4], " ");
                break;
            case "Sat":
                today_special = explode(weekly_menu[5], " ");
                break;
            default:
                today_special = explode(weekly_menu[6], " ");
        }      
                
        obj = clone_object(TOWER_OBJECTS + "cantina_food");
        obj->set_name(today_special[1]);
        obj->add_adj(today_special[0]);
        obj->add_name("plate");
        obj->set_short("plate of " + today_special[0] + " " + 
            today_special[1]);
        obj->set_pshort("plates of " + today_special[0] + " " + 
            today_special[1]);
        obj->set_long("This piping hot plate of " + today_special[0] + " " + 
            today_special[1] +
            " is a feast for the eyes as well as for the palate!\n");
            
        if ((obj->move(TP)))
        {
            NF("The cook was unable to deliver the food!\n");
            return 0;
        }  
        
        TP->catch_tell("The cook arrives from the kitchen and gives you a " +
            obj->query_short() + ".\n");
        say(QCTNAME(TP) + " orders the special.\n");
        
        return 1;
    }
    else if (str == "water" || str == "glass of water" || str == "glass water")
    {
        seteuid(getuid());
        
        obj = clone_object(TOWER_OBJECTS + "cantina_water");
        
        if ((obj->move(TP)))
        {
            NF("You weren't able to pick up the glass of water!\n");
            return 0;
        }
       
        TP->catch_tell("You help yourself to a glass of water.\n");
        say(QCTNAME(TP) + " helps " + TP->query_objective() + "self" +
            " to a glass of water.\n");
       
        return 1;
    }
    else
    {
        NF("Order what?\n");
        return 0;
    }
}


/*
 * Function name: do_sit
 * Description:   let a player sit on a bench
 * Arguments:     none
 * Returns:       0/1
 */
int
do_sit()
{
    if(TP->query_prop(CANTINA_I_SITTING))
    {
        NF("You are already sitting on the bench.\n");
        return 0;
    }
    else
    {
        write("You sit down at the table.\n");
        say(QCTNAME(TP) + " sits down at the table.\n");
        TP->add_prop(CANTINA_I_SITTING, 1);
        TP->set_no_show_composite(1);
        return 1;
    }
}    
 
/*
 * Function name: do_rise
 * Description:   let a player rise from a chair
 * Arguments:     none
 * Returns:       0/1
 */
int
do_rise()
{
    if(TP->query_prop(CANTINA_I_SITTING))
    {
        write("You rise from the bench.\n");
        say(QCTNAME(TP) + " rises from the bench.\n");
        TP->remove_prop(CANTINA_I_SITTING);
        TP->set_no_show_composite(0);
        return 1;
    }
    else
    {
        NF("You're not sitting at the bench!\n");
        return 0;
    }
} 


public void
leave_inv(object ob, object to)
{
    if (TP->query_prop(CANTINA_I_SITTING))
    {
        TP->remove_prop(CANTINA_I_SITTING);
        TP->set_no_show_composite(0);
    }
    
    ::leave_inv(ob, to);
}


init()
{
    ::init();
    
    seteuid(getuid());
    restore_object(TOWER_OBJECTS + "cantina_log");
    
    if (time() - menu_time > 7*24*60*60)
    {
        update_menu();
    }
    
    add_action("do_order", "order");
    add_action("do_sit", "sit");
    add_action("do_rise", "rise");
}