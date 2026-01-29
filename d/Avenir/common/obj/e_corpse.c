// /d/Avenir/common/obj/e_corpse.c  Embalmed Corpses.
// This is an object cloned by bazaar/intr/apothstore.c
// It may be used for magical (spellcasting) purposes.
// It produces nine random corpse types and adjectives.
// Lilith Feb 1997
inherit "/std/object";
#include "/d/Avenir/common/bazaar/bazaar.h"

string metl, type;
string randtype();
string randmetl();
void set_metl(string str){    metl = str;}
void set_type(string str){    type = str;}

void
init_the_corpse()
{    
    if (!metl) 
       metl = randmetl();
    if (!type) 
      type = randtype();
    set_short(""+ metl + " embalmed " + type + "");
    set_long("This is the "+ metl +" embalmed corpse of a "+
        type +".\nIt is difficult to tell for certain, but it "+
        "has probably been in this state for a long while.\n");
    add_name(type);
    set_adj(({ metl, type }));
    return;
        
}
/*************** Creation ************/
void
create_object()
{
    init_the_corpse();   
    add_name(({"_magical_ingredient", "mummy", "embalmed corpse"}));
    set_name("corpse");
    add_prop(OBJ_I_VOLUME, 100); 
    add_prop(OBJ_I_WEIGHT, 100); 
    add_prop(OBJ_I_VALUE, 100 + (random(100)));
}

string
randmetl()
{
    string str;
    switch(random(9))
    {
        case 0: str="mottled";     break;        
        case 1: str="wrinkled";    break;        
        case 2: str="shrunken";    break;
        case 3: str="darkened";    break;        
        case 4: str="smelly";      break;        
        case 5: str="shiny";       break;
        case 6: str="hairless";    break;
        case 7: str="smooth";      break;
        case 8: str="lumpy";       break;
    }
    return str;   
}

string
randtype()
{    
    string str;
    switch(random(9))    
    {       
        case 0: str="rat";      break;
        case 1: str="mouse";    break;
        case 2: str="fetus";    break;
        case 3: str="cat";      break;
        case 4: str="bat";      break;
        case 5: str="mole";     break;
        case 6: str="rabbit";   break;
        case 7: str="squirrel"; break;
        case 8: str="ferret";   break;
    }
    return str;  
}

string 
query_recover()
{
    string rec;
    rec = MASTER + ":";
    rec += "#type#" + type; 
    rec += "#metl#" + metl;  
    return rec;
}

void 
init_recover(string arg)
{
    string dummy;
    int i_check;
    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#metl#%s#%s", dummy, metl, dummy);
    init_the_corpse();
    return;
}

