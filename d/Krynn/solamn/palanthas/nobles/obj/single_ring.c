
#include "../../local.h"
#include "/d/Kalad/common/noble/arm/ring.h"
#include <macros.h>

inherit "/lib/keep";
inherit "/std/object";

#define SUBLOC "wearing_pierced_subloc"

static int worn;
string metal, qmetal, gem, qgem;
string article;

string query_ring_metal();
string query_ring_gem();

void
create_object()
{
    set_name("ring");
    set_short("@@query_ring_short@@");
    set_long("@@query_ring_long@@");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_M_NO_DROP,"@@ring_drop@@");
    set_keep(1); /* add the protection */
}

void
set_keep(int keep)
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
	return qmetal+ " ring with "+article+" "+qgem;
    else
	return qmetal+" ring";
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
	"This is a finely crafted tiny ring made from pure "+
	qmetal+". It is so tiny, it could never fit "+
	"around any finger. The tiny pin sticking out, however, "+
	"gives you the idea that it must be inserted in a hole. "+
	capitalize(article)+" "+qgem+" is set in the center, gleaming "+
	"brightly. You can 'keep' it from being sold.\n";
    }
    if(metal)
    {
	return
	"This is a finely crafted tiny ring made from pure "+
	qmetal+". It is so tiny, it could never fit "+
	"around any finger. The tiny pin sticking out, however, "+
	"gives you the idea that it must be inserted in a hole. "+
	"You can 'keep' it from being sold.\n";
    }
    else
	return "Undefined ring.\n";
}

int
set_ring_value(int i)
{
    add_prop(OBJ_I_VALUE, i);
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
	if(gem == "amber" || gem == "emerald" || gem == "onyx"
	  || gem == "opal")
	    article = "an";
	else article = "a";
    }
    else
    {
	set_adj(str);
	metal = str;
    }
}

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
    if(gem == "amber" || gem == "emerald" || gem == "opal" ||
      gem == "onyx")
	article = "an";
    else article = "a";
}

int
ring_wear(string arg)
{
    string name,adname;
    name = query_name();
    adname = query_adj()+" "+query_name();
    if(arg == name+" in right ear" || arg == adname+" in right ear")
    {
	NF("You don't have a pierced right ear.\n");
	if(!TP->query_prop(KALAD_RING_EAR_RIGHT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your right ear.\n");
	if(TP->query_prop(KALAD_RING_EAR_RIGHT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EAR_RIGHT,2);
	add_prop(KALAD_RING_LOCATION,"right ear");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your right ear.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " right ear.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in left ear" || arg == adname+" in left ear")
    {
	NF("You don't have a pierced left ear.\n");
	if(!TP->query_prop(KALAD_RING_EAR_LEFT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your left ear.\n");
	if(TP->query_prop(KALAD_RING_EAR_LEFT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EAR_LEFT,2);
	add_prop(KALAD_RING_LOCATION,"left ear");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your left ear.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " left ear.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in nose" || arg == adname+" in nose")
    {
	NF("You don't have a pierced nose.\n");
	if(!TP->query_prop(KALAD_RING_NOSE))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring on your nose.\n");
	if(TP->query_prop(KALAD_RING_NOSE) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_NOSE,2);
	add_prop(KALAD_RING_LOCATION,"nose");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your nose.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " nose.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in left eyebrow" || arg == adname+" in left eyebrow")
    {
	NF("You don't have a pierced left eyebrow.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_LEFT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your left eyebrow.\n");
	if(TP->query_prop(KALAD_RING_EYEB_LEFT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EYEB_LEFT,2);
	add_prop(KALAD_RING_LOCATION,"left eyebrow");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your left eyebrow.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " left eyebrow.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in right eyebrow" || arg == adname+" in right eyebrow")
    {
	NF("You don't have a pierced right eyebrow.\n");
	if(!TP->query_prop(KALAD_RING_EYEB_RIGHT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your right eyebrow.\n");
	if(TP->query_prop(KALAD_RING_EYEB_RIGHT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_EYEB_RIGHT,2);
	add_prop(KALAD_RING_LOCATION,"right eyebrow");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your right eyebrow.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " right eyebrow.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in tongue" || arg == adname+" in tongue")
    {
	NF("You don't have a pierced tongue.\n");
	if(!TP->query_prop(KALAD_RING_TONGUE))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your tongue.\n");
	if(TP->query_prop(KALAD_RING_TONGUE) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_TONGUE,2);
	add_prop(KALAD_RING_LOCATION,"tongue");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your tongue.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " tongue.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in lip" || arg == adname+" in lip")
    {
	NF("You don't have a pierced lip.\n");
	if(!TP->query_prop(KALAD_RING_LIP))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your lip.\n");
	if(TP->query_prop(KALAD_RING_LIP) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_LIP,2);
	add_prop(KALAD_RING_LOCATION,"lip");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your lip.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " lip.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in left nipple" || arg == adname+" in left nipple")
    {
	NF("You don't have a pierced left nipple.\n");
	if(!TP->query_prop(KALAD_RING_NIP_LEFT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your left nipple.\n");
	if(TP->query_prop(KALAD_RING_NIP_LEFT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_NIP_LEFT,2);
	add_prop(KALAD_RING_LOCATION,"left nipple");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your left nipple.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " left nipple.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in right nipple" || arg == adname+" in right nipple")
    {
	NF("You don't have a pierced right nipple.\n");
	if(!TP->query_prop(KALAD_RING_NIP_RIGHT))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your right nipple.\n");
	if(TP->query_prop(KALAD_RING_NIP_RIGHT) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_NIP_RIGHT,2);
	add_prop(KALAD_RING_LOCATION,"right nipple");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your right nipple.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " right nipple.\n");
	worn = 1;
	return 1;
    }
    if(arg == name+" in navel" || arg == adname+" in navel")
    {
	NF("You don't have a pierced navel.\n");
	if(!TP->query_prop(KALAD_RING_NAVEL))
	    return 0;
	NF("You are already wearing the "+short()+".\n");
	if(worn == 1)
	    return 0;
	NF("You already have a ring in your navel.\n");
	if(TP->query_prop(KALAD_RING_NAVEL) == 2)
	    return 0;
	TP->add_prop(KALAD_RING_NAVEL,2);
	add_prop(KALAD_RING_LOCATION,"navel");
	move(TP,SUBLOC);
	write("You insert the "+short()+" in your navel.\n");
	say(QCTNAME(TP)+" inserts the "+short()+" in "+HIS(TP)+
	  " navel.\n");
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
	case "left ear":
	    TP->add_prop(KALAD_RING_EAR_LEFT,1);
	    break;
	case "right ear":
	    TP->add_prop(KALAD_RING_EAR_RIGHT,1);
	    break;
	case "nose":
	    TP->add_prop(KALAD_RING_NOSE,1);
	    break;
	case "left eyebrow":
	    TP->add_prop(KALAD_RING_EYEB_LEFT,1);
	    break;
	case "right eyebrow":
	    TP->add_prop(KALAD_RING_EYEB_RIGHT,1);
	    break;
	case "tongue":
	    TP->add_prop(KALAD_RING_TONGUE,1);
	    break;
	case "lip":
	    TP->add_prop(KALAD_RING_LIP,1);
	    break;
	case "left nipple":
	    TP->add_prop(KALAD_RING_NIP_LEFT,1);
	    break;
	case "right nipple":
	    TP->add_prop(KALAD_RING_NIP_RIGHT,1);
	    break;
	case "navel":
	    TP->add_prop(KALAD_RING_NAVEL,1);
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
    ADD("ring_wear", "insert");
    ADD("ring_remove", "remove");
}
