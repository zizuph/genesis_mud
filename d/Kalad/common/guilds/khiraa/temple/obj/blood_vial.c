inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <cmdparse.h>
#pragma strict_types
#pragma save_binary

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/blood_vial.c
 * Purpose    : Holds blood from corpses.
 * Located    : Bought from Werners, 1 copper
 * Created By : Sarr 6.Mar.97
 * Modified By: 
 */

/* Holds data on what vial contains */
mixed *bl_cont = ({});

void
set_contents(mixed bl)
{
    bl_cont[0] = bl[0];
    bl_cont[1] = bl[1];
}

mixed *
query_contents()
{
    return bl_cont;
}

void
create_object()
{
    set_name("vial");
    set_adj("blood");
    set_short("@@bl_sh@@");

    set_long("@@bl_ln@@");

    add_prop(OBJ_I_WEIGHT,30);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,0);
    bl_cont = ({0,"none"});
}

string
bl_sh()
{
    if(bl_cont[0] == 1)
        return "full blood vial";
    else
        return "empty blood vial";
}

string
bl_ln()
{
    if(bl_cont[0] == 1)
        return "This is a small vial made of glass. It is used to "+
        "contain a small amount of blood. Right now, it is full of "+
        bl_cont[1]+" blood.\n";
    else
        return "This is a small vial made of glass. It is used to "+
        "contain a small amount of blood. Right now, it is empty.\n";
}

int
do_drink(string str)
{
    string st2;
    object *obs,vl;
    NF("Drink from what?\n");
    if(!str)
        return 0;
    if(sscanf(str,"from %s",st2) != 1)
        return 0;
    obs = FIND_STR_IN_OBJECT(st2,TP);
    if(!sizeof(obs))
        return 0;
    vl = obs[0];
    if(!sizeof(vl->query_contents()))
        return 0;
    NF("The "+vl->short()+" is empty.\n");
    if(vl->query_contents()[0] == 0)
        return 0;        
    write("You drink from the "+vl->short()+".\n");
    say(QCTNAME(TP)+" drinks from the "+vl->short()+".\n");
    vl->remove_name(bl_cont[1]+" blood vial");
    vl->set_contents(({0,"empty"}));
    return 1;
}


int
do_fill(string str)
{
    string str2,str3,rname;
    object *vials,*corpses,vial,corpse;
    NF("Fill what with blood from what?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s with blood from %s",str2,str3) != 2)
        return 0;
    vials = FIND_STR_IN_OBJECT(str2,TP);
    if(!sizeof(vials))
        return 0;
    vial = vials[0];
    NF("That is not a vial.\n");
    if(!objectp(vial) || MASTER_OB(vial) !=
       "/d/Kalad/common/guilds/khiraa/temple/obj/blood_vial")
        return 0;
    NF("It is full already.\n");
    if(vial->query_contents()[0] == 1)
        return 0;
    corpses = FIND_STR_IN_OBJECT(str3,E(TP));
    if(!sizeof(corpses))
        return 0;
    corpse = corpses[0];
    NF("That is not a corpse.\n");
    if(!objectp(corpse) || living(corpse) || !corpse->id("corpse") )
        return 0;
    write("You tear open the throat of the "+corpse->short()+" and "+
    "let the fresh, gushing blood pour into your "+vial->short()+".\n");
    say(QCTNAME(TP)+" tears open the throat of the "+corpse->short()+
    "and lets the fresh, gushing blood pour into "+HIS(TP)+" "+
    vial->short()+".\n");
    rname = corpse->query_race();
    if(rname == "elf")
        rname = "elven";
    if(rname == "dwarf")
        rname = "dwarven";
    if(rname == "gnome")
        rname = "gnomish";
    vial->set_contents(({1,rname}));
    vial->add_name(rname+" blood vial");
    return 1;
}

void
init()
{
    ::init();
    AA(do_fill,fill);
    AA(do_drink,drink);
}

