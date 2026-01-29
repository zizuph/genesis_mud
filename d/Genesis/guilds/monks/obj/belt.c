/*
 * File:     belt.c
 * Created:  Lilith, Feb 1999
 * Purpose:  Autoloading Guild token
 * Log:
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "../defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit MONKLIB;
inherit "/std/object.c";
inherit "/lib/wearable_item";

#define MONK_BELT_SUBLOC  "_monk_belt_subloc"

string    belt_long (object for_obj);
string    belt_short (object for_obj);
string    belt_desc = "\n";
string    colour;
 

void
init_belt ()
{
    object tp; 
    int i;
    string depth;

    tp = environment(this_object());
    i = (tp->query_skill(MONK_SKILL_FOCUS) + 
         tp->query_skill(SS_UNARM_COMBAT));

    switch(i)
    {
        case 0 .. 100:  
        {    
            colour = "white";    
            depth = "the first-level degree of mastery common "+
                    "to apprentices and laymen";
        }    
        break;
        case 101 .. 140:   
        { 
            colour = "yellow";   
            depth = "passed from the white belt into the second "+
                    "level of mastery expected of those who have "+
                    "begun to study the dragon-discipline in earn"+
                    "est";
        }
        break;
        case 141 .. 160:
        {
            colour = "green";    
            depth = "attained the third level, that degree of "+
                    "knowledge of the dragon-discipline which "+
                    "will swiftly propel you into the brown and "+
                    "black, if you maintain focus";
        }
        break;
        case 161 .. 175:   
        {
	  colour = "brown";    
            depth = "all but mastered the teachings of the Dragon "+
                    "Order. You are at that stage when all will soon "+
                    "become as clear to you as the sound of a gong in "+
                    "crisp mountain air";
        }
        break;
        case 176 .. 250:  
        {   
            colour = "black";    
            depth = "achieved a commendable feat. You wear the "+
                    "black belt as a sign that you have mastered "+
                    "the physical and mental rigors of the Order "+
                    "of the Dragon";
        }
        break;
        default:
        {
            colour = "white";    
            depth = "";
            break;
        }
    }

    add_adj (colour);
    belt_desc = "The "+ colour +" colour corresponds "+
       "to the depth of your mastery of the dragon-"+
       "discipline. Presently, you have "+ depth +".\n";

}

void
create_object ()
{
    init_belt();

    config_wearable_item(A_WAIST, 1, 15, this_object());

    set_name("monk_belt");
    add_name("belt");

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    add_adj(({"woven", "long", "thick", "monk"}));
    set_short(belt_short);
    set_long(belt_long);

    set_pname("belts");

    add_prop(OBJ_I_VALUE,  0);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_M_NO_DROP, "You decide not to drop your belt "+
        "after all.\n");
    add_prop(OBJ_M_NO_SELL, "This is a symbol of your mastery of "+
        "the dragon-discipline!\n");
    add_prop(OBJ_M_NO_STEAL, "The belt seems to resist your "+
        "grasp.\n");
}

string
belt_long (object for_obj)
{
    return "This flexible belt is made of densely woven flax "+
           "fiber.  It is three fingers wide and nearly as long "+
           "as you are tall.  "+ belt_desc;
}

string
belt_short (object for_obj)
{
    return "thick " + colour + " belt";
}


string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == MONK_BELT_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + 
                " is wearing " + LANG_ADDART(short()) +
                " tied around "+ on->query_possessive() +
                " waist.\n";

        else
            data = "You have " + LANG_ADDART(short()) + 
                   " tied around your waist.\n";
        return data;
    }
}

mixed
wear(object ob)
{
    object tp = environment(this_object());

    if ((tp != this_player()) || (ob != this_object()))
        return -1;

    if (member_array(MONK_BELT_SUBLOC, tp->query_sublocs()) > -1)
        return "You are already wearing your belt.\n";
         
    if (!m_query_monk(tp, -1))
        return "The belt, thick, heavy and unfamiliar, seems "+
               "to resist your attempts to tie it around your "+
               "waist.\n";

    /* Successful wear */
    tp->add_subloc(MONK_BELT_SUBLOC, this_object());
    tp->catch_msg("You loop the "+ short() +" around your "+
        "waist and draw it tight.\n");
    tell_room(environment(tp), QCTNAME(tp) + " loops the " + 
        short() +" around "+ tp->query_possessive() +" waist "+
        "and draws it tight.\n", tp);
    return 1;
}

mixed
remove(object ob)
{
    object tp = this_player();

    if ((ob != this_object()) && (tp != query_worn()))
        return -1;

    tp->remove_subloc(MONK_BELT_SUBLOC);

    return 0;
}

void
leave_env(object from, object to)
{   
    /* If I don't call this func, and people drop or put this while 
     * it is worn, it looks like it is still in the players inventory
     */
    wearable_item_leave_env(from, to);    

    ::leave_env(from, to);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    init_belt();
}

string 
query_auto_load()
{
    object tp = environment(this_object());    
    if (m_query_monk(tp, -1))
        return MASTER+":";    
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

