/* The Imp of Golash, used by the Khiraa to store stuff */
/* By Sarr of Kalad, 6.5.97 */

#pragma strict_types
inherit "/std/container.c";
inherit "/cmd/std/command_driver"; /* For emotes */

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Kalad/defs.h"


public void
create_container()
{
    set_name("imp");
    set_pname("imps");
    add_adj("red-skinned");
    add_adj("black-eyed");
    set_short("red-skinned black-eyed imp");
    set_pshort("red-skinned black-eyed imps");

    set_long("This is a fiendish black-eyed imp with scaly red skin. "+
    "It holds a large black bag in its clawed hands to store your items "+
    "in. It seems to have been summoned from the depths of Hell to serve "+
    "you. You can do 'imphelp' for more information on commands.\n");
    
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 175000);
    add_prop(CONT_I_VOLUME, 9000);

    remove_prop(CONT_I_RIGID);
    
    add_prop(CONT_I_MAX_VOLUME, 175000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(CONT_I_CLOSED,1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL,1);
}


public void
enter_inv(object ob, object from)
{
    if (ob->query_prop(CONT_I_IN))
        {
        set_alarmv(1.0, 0.0, "fail_message", ({ ob, from }));
        ob->move(from);
        return;
    }
    ::enter_inv(ob, from);
}

public void
fail_message(object ob, object from)
{
    from->catch_msg("The "+short()+" takes the "+ob->short()+" out "+
    "of his black bag and gives it back, squeeking: I cannot store this.\n");
}

public void
enter_env(object to, object from)
{
    if(living(to))
        to->add_subloc("khiraa_imp", TO);
    ::enter_env(to,from);
}


public void
leave_env(object dest, object old)
{
    if(living(old))
        old->remove_subloc("khiraa_imp");
    ::leave_env(dest, old);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != "khiraa_imp")
        return "";
    if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))    
        return "";    
    if (for_obj != on)
        return capitalize(on->query_pronoun()) + " has a "+short()+
    " floating next to "+HIM(on)+".\n";
    else
        return "You have a "+short()+" floating next to you.\n";
}

/* Filter out certain objects when shifting stuff in or out of backpack */

/* This one takes non-valuable stuff */
int
b_filter(object ob)
{
    if ((ob->query_prop(OBJ_M_NO_GIVE)) ||
        (ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(CONT_I_IN)) ||
        (ob->query_worn()) || (ob->query_wielded()) ||
        (ob->query_prop(LIVE_I_IS)) ||
        (ob->query_name() == query_name()))
    return 0;
    return 1;
}
int
a_filter(object ob)
{
    if ((ob->query_prop(OBJ_M_NO_SELL)) || (ob->query_prop(OBJ_M_NO_GIVE)) ||
            (ob->query_prop(OBJ_M_NO_DROP)) || (ob->query_prop(CONT_I_IN)) ||
        (ob->query_worn()) || (ob->query_wielded()) ||
        (!ob->query_prop(OBJ_I_VALUE)) || (ob->query_prop(LIVE_I_IS)) ||
        (ob->query_name() == query_name()))
    return 0;
    return 1;
}

/* Tell player about how to use the backpack */
public int
packhelp(string arg)
{
    write("This "+short()+" can do the following:\n"+
    "impstore <items> - \n"+
    "   This will tell the imp to store those items in its bag. If you\n"+
    "   do not supply <items>, it will automatically try to store \n"+
    "   everything in your inventory that is not being worn, wielded,\n"+
    "   or a non-valuble item.\n"+
    "impget <items> - \n"+
    "   This will tell the imp to retrieve your items from its bag. If\n"+
    "   you do not supply <items>, it will automatically try to get\n"+
    "   everything it has in its bag that is not a non-valuable item\n"+
    "   and give them to you.\n"+
    "impcheck - \n"+
    "   This will tell the imp to check what it has in its bag and\n"+
    "   tell you.\n"+
    "--------------------------------Emotes---------------------------\n"+
    "impgrin <how>  -  Make the imp grin <how> \n"+
    "impwing <how>  -  Make the imp flap its wings <how> \n"+
    "impprotect     -  Make the imp protect its bag \n"+
    "impsay <what>  -  Make the imp say something \n"+
    "impeye <who>   -  Make the imp eye up someone \n");
    return 1;
}

/*
* Recovery stuff
*/

public string
query_recover()
{
    return MASTER+":#ck#";
}

public void
init_recover(string arg)
{
    string foobar;
    int tmp;
    
    sscanf(arg, "%s#ck#%d#%s", foobar, tmp, foobar);
}

/* Store selected items in the backpack */
public int
packstore(string arg)
{
    string mt;
    object *conts, *moved;
    int x, y, temp;

    NF("First you must have it!\n");
    if(environment() != this_player())
        return 0;
    
    NF("The "+short()+" squeeks: What do you want me to store?\n");
    if (strlen(arg))
    {
        conts = FIND_STR_IN_OBJECT(arg,TP);
        conts = filter(conts,"b_filter",TO);
        if(!sizeof(conts))
            return 0;
        NF("The "+short()+" squeeks: I cannot store that in here!\n");
    }
    else
    {
        NF("The "+short()+" squeeks: You have nothing I can store!\n");

    
    
        conts = filter(all_inventory(TP), "a_filter", TO);
    }
    
    moved = ({ });
    
    add_prop(CONT_I_CLOSED,0);

    for (x = 0; x < sizeof(conts); x++)
    if (!(temp = conts[x]->move(this_object())))
        moved += ({ conts[x] });
    if(temp == 8 || temp == 1)
    {
        NF("The "+short()+" squeeks: I cannot fit anymore in my bag!\n");
        return 0;
    }

    add_prop(CONT_I_CLOSED,1);
    
    if (!sizeof(moved))
        return 0;

    if(sizeof(moved) > 1)
        mt = "them";
    else
        mt = "it";
    write("The "+short()+" happily takes "+COMPOSITE_DEAD(moved)+ 
    " from you and stuffs "+mt+" in his black bag.\n");

    tell_room(environment(TP),QCTNAME(TP)+"'s "+short()+" takes "+
    COMPOSITE_DEAD(moved)+" from "+HIM(TP)+" and stuffs "+mt+" in his "+
    "black bag.\n",TP);
    return 1;
}

/* Retrieve selected items from the backpack */
public int
packget(string arg)
{
    string mt;
    object *conts, *moved;
    int x;

    NF("First you must have it!\n");
    if(environment() != this_player())
        return 0;
    
    NF("The "+short()+" squeeks: What do you want me to get?\n");
    if (strlen(arg))
    {
        conts = FIND_STR_IN_OBJECT(arg,TO);
        conts = filter(conts,"b_filter",TO);
        if(!sizeof(conts))
            return 0;
        NF("The "+short()+" squeeks: I dont' have that in here!\n");
    }
    else
    {
        NF("The "+short()+" squeeks: You have nothing I can get!\n");

        conts = filter(all_inventory(), "a_filter", this_object());
    
    }

    add_prop(CONT_I_CLOSED,0);

    moved = ({});
        
    for (x = 0; x<sizeof(conts); x++)
    if (!conts[x]->move(this_player()))
        moved += ({ conts[x] });
    
    add_prop(CONT_I_CLOSED,1);
    
    if (!sizeof(moved))
        {
        NF("The "+short()+" squeeks: I have nothing to give you!\n");
        return 0;
    }
    if(sizeof(moved) > 1)
        mt = "them";
    else
        mt = "it";
    write("The "+short()+" pulls out "+COMPOSITE_DEAD(moved)+" from his "+
    "black bag and gives "+mt+" to you.\n");
    tell_room(environment(TP), QCTNAME(TP)+"'s "+short()+" pulls out "+
    COMPOSITE_DEAD(moved)+" from his black bag and gives "+mt+" to "+HIM(TP)+
    ".\n",TP);

    return 1;
}

int
do_impcheck()
{
    object *obs;
    obs = all_inventory(TO);
    if(!sizeof(obs))
    {
        write("The "+short()+" squeeks: I have nothing in my black bag.\n");
        return 1;
    }
    write("The "+short()+" squeeks: I have "+COMPOSITE_DEAD(obs)+" "+
    "in my black bag.\n");
    return 1;
}

int
do_impgrin(string str)
{
    string adv;
    adv = parse_adverb_with_space(str,"demonically",1)[1];
    write("The "+short()+" floating next to you grins"+adv+".\n");
    say("The "+short()+" floating next to "+QTNAME(TP)+" grins"+adv+".\n");
    return 1;
}

int
do_impwing(string str)
{
    string adv;
    adv = parse_adverb_with_space(str,"slowly",1)[1];
    write("The "+short()+" floating next to you flaps his black "+
    "leathery wings"+adv+".\n");
    say("The "+short()+" floating next to "+QTNAME(TP)+" flaps his "+
    "black leathery wings"+adv+".\n");
    return 1;
}

int
do_impprotect()
{
    write("The "+short()+" floating next to you wraps his black "+
    "leathery wings around his black bag protectivley.\n");
    say("The "+short()+" floating next to "+QTNAME(TP)+" wraps his "+
    "black leathery wings around his black bag protectivley.\n");
    return 1;
}

int
do_impsay(string str)
{
    NF("Impsay what?\n");
    if(!str)
        return 0;
    write("The "+short()+" floating next to you squeeks: "+str+"\n");
    say("The "+short()+" floating next to "+QTNAME(TP)+" squeeks: "+
    str+"\n");
    return 1;
}

int
do_impeye(string str)
{
    object *ob;
    if(!str)
        return 0;
    ob = parse_this(str,"[the] %l");
    if(!sizeof(ob))
        return 0;
    write("The "+short()+" floating next to you eyes "+
    ob[0]->query_the_name(TP)+" warily.\n");
    tell_room(E(TP),"The "+short()+" floating next to "+QTNAME(TP)+
    " eyes "+QTNAME(ob[0])+" warily.\n",({TP,ob[0]}));
    tell_object(ob[0],"The "+short()+" floating next to "+
    TP->query_the_name(ob[0])+" eyes you warily.\n");
    return 1;
}


public void
init()
{
    ::init();
    add_action("packstore", "impstore");
    add_action("packget", "impget");
    add_action("packhelp", "imphelp");
    add_action("do_impcheck","impcheck");
    add_action("do_impgrin","impgrin");
    add_action("do_impwing","impwing");
    add_action("do_impprotect","impprotect");
    add_action("do_impsay","impsay");
    add_action("do_impeye","impeye");
}

