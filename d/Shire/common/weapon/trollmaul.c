inherit "/std/weapon";
inherit "/d/Immortal/rogon/open/tell";
inherit "/d/Immortal/rogon/open/message";

#include "defs.h"
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <language.h>

void

create_weapon()
{

    set_name(({"maul", "club"}));
    set_short("mithril maul");
    set_pname(({"mauls","clubs"}));
    set_long("This huge axe is made for hewing heads of enemies and "
    	     +"smashing the guts. It is made of the finest Mithril "
    	     +"from Khazad-dum. It if crafted by the dwarves who lived "
    	     +"in Khazad-dum, but was most likely stolen by the trolls "
    	     +"who entered the mines there. Perhaps you want to show it "
    	     +"to your friends.\n" );

    set_adj(({"mithril","slashing"}));
	
    set_hit(30);
    set_pen(35);
    
    set_wt(W_AXE);
    set_dt(W_SLASH);
    /*set_hand(W_BOTH);*/
    set_wf(TO);
    /*set_default_weapon(35, 40, W_CLUB, W_SLASH, W_BOTH, 0);*/

    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35, 30) + random(100) + 30);

}

int
query_hands()
{
	if (!TP)
	   return W_BOTH;
	else if (STR(TP) >120)
	   return W_ANYH;
	else
	   return W_BOTH;
}

int
query_usable(object who)
{
	return STR(who) >70;
}

int
wield(object to)
{
     if(!query_usable(TP))
     {
     	write("You can feel the axe prevent you from wielding it.\n");
     	return -1;
     }
     write("With a great effort you manage to wield the mighty maul "+
          (query_hands()==W_BOTH? "in both hands.\n" : "single handed.\n")
          
     );
     return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

init()
{
    ::init();
    add_action("do_show", "show");
    add_action("do_love", "love");
}

int
do_show(string arg)
{
    if (!id(arg))
	return 0;
    action("$N $hurdle $p mighty club trough the air, showing how mighty it is!\n");
    return 1;
}

int
do_love(string arg)
{
    if (!id(arg))
	return 0;
    action("$N $kiss $p maul with great passion and $shout out: NEVER try to touch it!!\n");
    return 1;
}
