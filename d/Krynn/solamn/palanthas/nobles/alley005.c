/* Mortis 11.2005 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit NOBLE_BASE;

void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
	add_action("action_stand", "stand");
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting by a table! How do you "
				+ "expect to sit in two places at once?\n");
                return 1;
        }
          
        if(str == "around table" | str == "around a table" | 
		   str == "at table" | str == "at a table" | str == "by table" |
		   str == "by a table" | str == "table" |
		   str == "chair around table" | str == "in chair around table" |
		   str == "in a chair around a table" | str == "chair at table" |
		   str == "in chair at table" | str == "in a chair at a table" |
		   str == "chair by table" | str == "in chair by table" |
	       str == "in a chair by a table") 
        {
                TP->catch_msg("You sit down in one of the wrought iron "
				+ "chairs near a table.\n");
                say(QCTNAME(TP) + " sits down in one of the wrought iron "
				+ "chairs at a table.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a wrought "
				+ "iron chair by a marble table");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit?  At a table?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || str != "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the table.\n");
                        say(QCTNAME(TP)+" stands up from the table.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }

        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the table before leaving.\n");
                say(QCTNAME(TP) + " stands up from the table as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }

}


nomask public string
get_time_desc()
{
    string desc = "";
	string road = "This landing is part of the marble building to "
	+ "the southwest and Averund's to the northeast.  It overlooks "
	+ "Scholar's Walk two stories below to the northwest over a railing of "
	+ "burnished, wrought iron.  A narrow flight of stairs leads down "
	+ "into a side street to the southeast.  There is enough room here "
	+ "for a pair of marble topped tables and several wrought iron chairs.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "A cool, misty breeze blows from the northwest ruffling "
	+ "the leaves of ivy growing up the railing from the road below as the "
	+ "morning rays of the sun light up the clouds overhead in pale purple "
	+ "hues.\n";
	break;

    case TOD_DAY:
	desc += road + "A warm breeze from the northwest blows strongly, "
	+ "ruffling the leaves of ivy growing up the railing from the road "
	+ "below.  The rays of the overhead sun warm the pristine marble of "
	+ "the landing and its tables.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "The translucent marble of the landing and adjacent "
	+ "buildings catches the last rays of the setting sun appearing to "
	+ "glow of its own accord.  Shadows climb slowly up from the street "
	+ "below as a cool breeze from the northwest ruffles the leaves of "
	+ "ivy growing up the railing.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the translucent "
	+ "marble of the landing and adjacent buildings amplifying the yellow "
	+ "glow of the street lamps below.  A cool, night breeze blows gently "
	+ "from the northwest ruffling the leaves of ivy growing up the "
	+ "railing.\n";
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("An alley landing over Scholar's Walk");
    LONG("@@get_time_desc@@");

	ITEM(({"stairs", "flight", "flight of stairs"}), "The flight of stairs "
	+ "descending along the building to its right is built of slabs of "
	+ "translucent marble with a burnished, wrought iron handrail.  It is "
	+ "in fact two flights of stairs with a short landing between them.  "
	+ "They lead down to the back streets behind the livery.\n");

	ITEM(({"chair", "chairs"}), "These wide chairs are constructed of "
	+ "curved bars of black, wrought iron with ample arm rests and sturdy "
	+ "leather cushions.\n");

	ITEM(({"table", "tables"}), "The pair of tables upon the landing have "
	+ "a base of wrought iron bars forming their legs upon which rest slabs "
	+ "of polished, translucent marble for a table top.\n");

	ITEM(({"rail", "railing", "handrail", "rails", "handrails"}),
	  "Burnished, wrought iron handrails line the edge of the landing over "
	+ "Scholar's Walk to the northwest and the edge of the stairs leading "
	+ "down to the southeast side streets.\n");

	ITEM("ivy", "Vines of deep green ivy climb up the wrought iron railing "
	+ "from the road below.\n");

	ITEM(({"scholar's walk", "road", "nw road", "northwest road"}), "Two "
	+ "stories down at least is Scholar's Walk, a road running from the "
	+ "Palatial plaza to the southwest to the gates in the northeast.  "
	+ "The landing provides a casual, relaxing spot to watch travellers "
	+ "coming and going along the road.\n");

	ITEM(({"averund", "averunds", "averund's"}), "The building to the "
	+ "northeast is a shop catering to new visitors and merchants.  It "
	+ "is run by the Averund family.\n");

	EXIT(NOBLE + "alley002", "southeast", 0, 0);

}