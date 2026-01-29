#include "/d/Raumdor/defs.h"
#include <composite.h>
#include <cmdparse.h>
#include "/d/Raumdor/common/std/jewelry.h"

inherit "/std/object";

/* Global Variables */

int jewelry_value;

string jewelry_slot_name; // What is the piece set to, store here

string *ok_jslots; // Ok slots for this piece

string jewelry_gem; // Support for gem

string jewelry_metal; // Support for metal

int worn; // Worn, 1 = yes, 0 = no

// Set it as worn
void
set_worn(int i)
{
    worn = i;
}
int
query_worn()
{
    return worn;
}

void
magic_effect(object ob)
{
}

// Prototype of function to get the string of what it looks like to be worn
mixed return_the_string(object *obs,string loc,object on, object fo);


void
leave_env(object from, object to)
{
    object *obs;
    if(interactive(from))
    {
        if(sizeof(from->subinventory(ANSALON_JEWELRY_SUBLOC)) == 1)
        {
            from->remove_subloc(ANSALON_JEWELRY_SUBLOC);
            /* remove_prop(OBJ_M_NO_DROP); */
        }
    }
    ::leave_env(from,to);
}


int
move(mixed dest, mixed subloc)
{
    /* when you die, it will be able to move into your corpse even if 
       you are wearing it */
    if(calling_function() == "move_all_to")
    {
        set_worn(0);
        remove_prop(OBJ_M_NO_DROP);
    }
    return ::move(dest,subloc);
}

int
set_jewelry_slot(string str)
{
    if(jewelry_slot_name)
        remove_prop(jewelry_slot_name);
    switch(str)
    {
        case ANSALON_JEWELRY_RHAND:
            add_prop(ANSALON_JEWELRY_RHAND,({"right hand",0}));
        break;
        case ANSALON_JEWELRY_LHAND:
            add_prop(ANSALON_JEWELRY_LHAND,({"left hand",0}));
        break;
        case ANSALON_JEWELRY_RARM:
            add_prop(ANSALON_JEWELRY_RARM,({"right arm",0}));
        break;
        case ANSALON_JEWELRY_LARM:
            add_prop(ANSALON_JEWELRY_LARM,({"left arm",0}));
        break;
        case ANSALON_JEWELRY_LLEG:
            add_prop(ANSALON_JEWELRY_LLEG,({"left ankle",0}));
        break;
        case ANSALON_JEWELRY_RLEG:
            add_prop(ANSALON_JEWELRY_RLEG,({"right ankle",0}));
        break;
        case ANSALON_JEWELRY_NECK:
            add_prop(ANSALON_JEWELRY_NECK,({"neck",0}));
        break;
        case ANSALON_JEWELRY_WAIST:
            add_prop(ANSALON_JEWELRY_WAIST,({"waist",0}));
        break;
        default:
            return 0;
    }
    jewelry_slot_name = str;
    return 1;
}

string
match_str_to_slot(string str)
{
    switch(str)
    {
        case "left hand":
            return ANSALON_JEWELRY_LHAND;
        break;
        case "right hand":
            return ANSALON_JEWELRY_RHAND;
        break;
        case "left arm":
            return ANSALON_JEWELRY_LARM;
        break;
        case "right arm":
            return ANSALON_JEWELRY_RARM;
        break;
        case "left ankle":
            return ANSALON_JEWELRY_LLEG;
        break;
        case "right ankle":
            return ANSALON_JEWELRY_RLEG;
        break;
        case "neck":
            return ANSALON_JEWELRY_NECK;
        break;
        case "waist":
            return ANSALON_JEWELRY_WAIST;
        break;         
    }
    return "";
}


int
set_ok_jewelry_slots(string *arr)
{
    if(!sizeof(arr))
        return 0;
    ok_jslots = arr;
    set_jewelry_slot(arr[0]); // Default slot
    return 1;
}

string
query_jewelry_slot()
{
    return jewelry_slot_name;
}

void
set_jewelry_value(int i)
{
    jewelry_value = i;
}

int
query_jewelry_value()
{
    return jewelry_value;
}

string
query_jewelry_gem()
{
    return jewelry_gem;
}

string
query_jewelry_metal()
{
    return jewelry_metal;
}

void
set_gem_name(string str)
{
    jewelry_gem = str;
    if(str)
        add_adj(str);
}
void
set_metal_name(string str)
{
    jewelry_metal = str;
    if(str)
        add_adj(str);
}
    
mixed
jewl_drop()
{
    if(worn)
        return "You have to take it off first!\n";
    else
        return 0;
}

void
create_jewelry()
{
}

void
create_object()
{
    set_short("@@jewelry_short@@");
    set_long("@@jewelry_long@@");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_RARM,ANSALON_JEWELRY_LARM}));
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    set_jewelry_value(100);
    add_prop(OBJ_I_VALUE,"@@query_jewelry_value@@");
    add_prop(OBJ_M_NO_DROP,"@@jewl_drop@@");
    create_jewelry();
}

string
jewelry_short()
{
    if(jewelry_gem)
        return jewelry_metal+" "+jewelry_gem+" studded "+query_name();
    else
        return jewelry_metal+" "+query_name();
}

void
init()
{
    ::init();
    add_action("do_wear","wear");
    add_action("do_remove","remove");
}

int
do_remove(string str)
{
    mixed *jewels;
    object jewl;
    mixed *jslot,*pslot;
    NF("Remove what?\n");
    jewels = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(jewels))
        return 0;
    jewl = jewels[0];
    if(!jewl)
        return 0;    
    if(jewl != TO)
        return 0;
    NF("You don't have the "+jewl->short()+".\n");
    if(!present(jewl,TP))
        return 0;
    NF("You are not wearing it!\n");
    if(!worn)
        return 0;
    jslot = jewl->query_prop(jewl->query_jewelry_slot());
    pslot = TP->query_prop(jewl->query_jewelry_slot());
    TP->add_prop(jewl->query_jewelry_slot(),({pslot[0],pslot[1]-1}));
    write("You remove the "+jewl->short()+".\n");
    say(QCTNAME(TP)+" removes the "+short()+".\n");
    worn = 0;
    jewl->move(TP);
    magic_effect(TP);
    return 1;
}


int
do_wear(string str)
{
    mixed *jewels;
    object jewl;
    mixed *jslot,*pslot;
    string *str1,str2,str3;
    NF("Wear what?\n");     
    if(!str)
        return 0;
    if(sscanf(str,"%s on %s",str3,str2) == 2)
        jewels = FIND_STR_IN_OBJECT(str3,TP);
    else
        jewels = FIND_STR_IN_OBJECT(str,TP);
    if(!sizeof(jewels))
        return 0;
    jewl = jewels[0];
    if(!jewl)
        return 0;
    if(jewl != TO)
        return 0;
    NF("You don't have the "+jewl->short()+".\n");
    if(!present(jewl,TP))
        return 0;
    NF("You already are wearing it!\n");
    if(worn)
        return 0;
    if(str3)
        str1 = explode(str," on ");
    if(sizeof(str1) > 1)
    {
        str2 = match_str_to_slot(str1[1]);
        if(member_array(str2,ok_jslots) != -1)
            set_jewelry_slot(str2);
        else
        {
            write("The "+jewl->short()+" cannot go there.\n");
            return 1;
        }
        
    }
    jslot = jewl->query_prop(jewl->query_jewelry_slot());
    pslot = TP->query_prop(jewl->query_jewelry_slot());
    if(sizeof(jslot))
    if(sizeof(pslot))
    {
        if(pslot[1] >= 5)
        {
            write("You don't have anymore room on your "+pslot[0]+".\n");
            return 1;
        }
    }
    else
        TP->add_prop(jewl->query_jewelry_slot(),({jslot[0],jslot[1]}));     
    pslot = TP->query_prop(jewl->query_jewelry_slot());
    write("You wear the "+jewl->short()+" on your "+pslot[0]+".\n");
    say(QCTNAME(TP)+" wears the "+jewl->short()+" on "+HIS(TP)+" "+
    pslot[0]+".\n");
    TP->add_prop(jewl->query_jewelry_slot(),({pslot[0],pslot[1]+1}));
    TP->add_subloc(ANSALON_JEWELRY_SUBLOC,TO);
    jewl->move(TP,ANSALON_JEWELRY_SUBLOC);
    worn = 1;
    magic_effect(TP);
    return 1;
}

string
show_subloc(string subloc, object on, object for_ob)
{
    int i;
    object *obs;
    string var1,var2,str,*locs;
    string on_lhand,on_rhand,on_larm,on_rarm,on_lleg,on_rleg,on_neck,on_waist;
    if(subloc != ANSALON_JEWELRY_SUBLOC)
        return "";
    if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if(on == for_ob)
        var1 = "You are";
    else
        var1 = CAP(HE(on))+" is";
    str = var1+" wearing ";
    locs = ({});
    obs = on->subinventory(ANSALON_JEWELRY_SUBLOC);
    if(!sizeof(obs))
        return "";
    if(on_lhand = return_the_string(obs,"on_lhand",on,for_ob))
        locs += ({on_lhand});
    if(on_rhand = return_the_string(obs,"on_rhand",on,for_ob))
        locs += ({on_rhand});
    if(on_larm = return_the_string(obs,"on_larm",on,for_ob))
        locs += ({on_larm});
    if(on_rarm = return_the_string(obs,"on_rarm",on,for_ob))
        locs += ({on_rarm});
    if(on_lleg = return_the_string(obs,"on_lleg",on,for_ob))
        locs += ({on_lleg});
    if(on_rleg = return_the_string(obs,"on_rleg",on,for_ob))
        locs += ({on_rleg});
    if(on_neck = return_the_string(obs,"on_neck",on,for_ob))
        locs += ({on_neck});
    if(on_waist = return_the_string(obs,"on_waist",on,for_ob))
        locs += ({on_waist});
    for(i=0;i<sizeof(locs)-1;i++)            
    {
        str += locs[i]+", ";
    }
    if(!sizeof(locs))
        return "";
    if(sizeof(locs) == 1)
        str += locs[0]+".\n";
    else
        str += "and "+locs[i]+".\n";
    return str;
}

mixed
return_the_string(object *obs, string loc, object on, object for_ob)
{
    int i;
    object *in_rec = ({});
    string last, str, var2;
    if(on == for_ob)
        var2 = "your";
    else
        var2 = HIS(on);
    switch(loc)
    {
        case "on_lhand":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_LHAND)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" left hand";
        break;
        case "on_rhand":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_RHAND)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" right hand";
        break;
        case "on_larm":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_LARM)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" left arm";
        break;
        case "on_rarm":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_RARM)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" right arm";
        break;
        case "on_lleg":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_LLEG)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" left ankle";
        break;
        case "on_rleg":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_RLEG)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" on "+var2+" right ankle";
        break;
        case "on_neck":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_NECK)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" around "+var2+" neck";
        break;
        case "on_waist":
            for(i=0;i<sizeof(obs);i++)
            {
                if(obs[i]->query_jewelry_slot() == ANSALON_JEWELRY_WAIST)
                    in_rec += ({obs[i]});
            }
            if(!sizeof(in_rec))
                return 0;
            return COMPOSITE_DEAD(in_rec)+" around "+var2+" waist";
        break;
    }
    return 0;
}

