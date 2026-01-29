inherit "/std/object";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"
#define SUBLOC "wearing_pierced_subloc"

static int worn;
string metal;
string gem;
string query_ring_metal();
string query_ring_gem();
void set_ring_metal(string metal, int gem);
int set_ring_value(int i);

string
query_auto_load()
{
    return MASTER + ":|" + gem + "|" + metal + "|:";
}

void
init_arg(string arg)
{
    string foobar;

    sscanf(arg, "%s|%s|%s|%s", foobar, gem, metal, foobar);
    set_adj(metal);
    if(gem == "0")
	gem = 0;
}



void
create_object()
{
    set_name("rings");
    set_short("@@query_ring_short@@");
    set_long("@@query_ring_long@@");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,70);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_M_NO_DROP,"@@ring_drop@@");
    set_keep(1);
}



void
set_keep(int keep = 1)
{
    if (keep)
    {
	::set_keep(keep);
    }
    else
    {
	this_object()->add_prop(OBJ_M_NO_SELL,0);
    }
}

int
query_keep()
{
    return (query_prop_setting(OBJ_M_NO_SELL) != 0);
}


string
ring_drop()
{
    if(worn)
	return "You must remove it first.\n";
    else
	return 0;
}

string
query_ring_short()
{
    string qgem,qmetal;
    qgem = query_ring_gem();
    qmetal = query_ring_metal();
    if(gem && metal)
	return "pair of "+qmetal+" rings with "+qgem+" gems";
    else
	return "pair of "+qmetal+" rings";
}

string
query_ring_long()
{
    string qgem,qmetal;
    qgem = query_ring_gem();
    qmetal = query_ring_metal();
    if(gem && metal)
    {
	return
	"This is a pair of finely crafted tiny rings made from pure "+
	qmetal+". They are so tiny, they could never fit "+
	"around any finger. The tiny pins sticking out, however, "+
	"give you the idea that they must be inserted in a pair of holes. "+
	"A "+qgem+" is set in the center of each, gleaming "+
	"brightly. You can 'keep' it from being sold.\n";
    }
    if(metal)
    {
	return
	"This is a pair of finely crafted tiny rings made from pure "+
	qmetal+". They are so tiny, they could never fit "+
	"around any finger. The tiny pins sticking out, however, "+
	"give you the idea that they must be inserted in a pair of holes. "+
	"You can 'keep' it from being sold.\n";
    }
    else
	return "Undefined ring.\n";
}



int
set_ring_value(int i)
{
    add_prop(OBJ_I_VALUE,i);
    if(query_prop(OBJ_I_VALUE) == i)
	return i;
    else 
	return 0;
}

string
query_ring_metal()
{
    return metal;
}

string
query_ring_gem()
{
    return gem;
}

void
set_ring_metal(string str, int i)
{
    if(i)
    {
	gem = str;
    }
    else
    {
	set_adj(str);
	metal = str;
    }
}

int
ring_wear(string arg)
{
    string name,adname;
    name = query_name();
    adname = query_adj()+" "+query_name();
    if(arg == name+" in both ears" || arg == adname+" in both ears")
    {
	NF("You don't have both your ears pierced.\n");
	if(!TP->query_prop(KALAD_RING_EAR_BOTH))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a pair of rings in your ears.\n");
	if(TP->query_prop(KALAD_RING_EAR_BOTH) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EAR_BOTH,2);
	add_prop(KALAD_RING_LOCATION,"ears");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your ears.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " ears.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in both eyebrows" || arg == adname+" in both eyebrows")
    {
	NF("You don't have both eyebrows pierced.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_BOTH))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a pair of rings on your eyebrows.\n");
	if(TP->query_prop(KALAD_RING_EYEB_BOTH) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EYEB_BOTH,2);
	add_prop(KALAD_RING_LOCATION,"eyebrows");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your eyebrows.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " eyebrows.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in both nipples" || arg == adname+" in both nipples")
    {
	NF("You don't have both your nipples pierced.\n");
	if(!TP->query_prop(KALAD_RING_NIP_BOTH))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a pair of rings in your nipples.\n");
	if(TP->query_prop(KALAD_RING_NIP_BOTH) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_NIP_BOTH,2);
	add_prop(KALAD_RING_LOCATION,"nipples");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your nipples.\n");
	say(QCTNAME(TP)+" insert the "+short()+" in "+HIS(TP)+
	  " nipples.\n");
	worn = 1;
	return 1;
    }
    NF("Insert what in where?\n");
    return 0;
}


int
ring_remove(string arg)
{
    string loc;
    string name,adname;
    name = query_name();
    adname = query_adj()+" "+query_name();
    NF("Remove what?\n");
    if( arg == name || arg == adname)
    {
	NF("You are not wearing the "+short()+".\n");    
	if(worn == 0)
	    return 0;
	loc = query_prop(KALAD_RING_LOCATION);
	switch(loc)
	{
	case "nipples":
	    TP->add_prop(KALAD_RING_NIP_BOTH,1);
	    break;
	case "eyebrows":
	    TP->add_prop(KALAD_RING_EYEB_BOTH,1);
	    break;
	case "ears":
	    TP->add_prop(KALAD_RING_EAR_BOTH,1);
	    break;
	}
	move(TP);
	write("You remove the "+short()+" from your "+loc+".\n");
	say(QCTNAME(TP)+" removes "+HIS(TP)+" "+short()+" from "+
	  HIS(TP)+" "+loc+".\n");
	remove_prop(KALAD_RING_LOCATION);
	worn = 0;
	return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    AA(ring_wear,insert);
    AA(ring_remove,remove);
}
