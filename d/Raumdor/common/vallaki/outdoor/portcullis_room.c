/* /d/Raumdor/common/vallaki/outdoor/road02.c
*
* Edeqium 2022
*
* This room is an in-between room between gate and portcullis.
* It is an outside room with purpose of what you can do in it
* (ride, vmeld etc), but inside with purpose of scry and sun.
* So for now it's an outside room. 
*/

#include "../defs.h"

inherit VALLAKI_ROAD_STD_ROOM;

int portcullis_lowered = 0;
string get_portcullis_description()
{
    string portcullis_desc = "The portcullis is currently ";
    if(portcullis_lowered==0)
    {
       portcullis_desc+="raised.\n";
    }
    else
    {
        portcullis_desc+="lowered.\n";
    }        
    
    
 return portcullis_desc;
}

void raise_portcullis()
{
  portcullis_lowered=0;
}

void lower_portcullis()
{
    portcullis_lowered=1;
}


void
create_vallaki_outdoor()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_LIGHT, 2);
      
    set_short("Inside the portcullis.");
    
    set_long("This area inside the portcullis is just aboout large "
        +"enough to house a traders wagon and five to ten people more. "
        +"No doubt in times of trouble this could be a death "
        +"trap to enemies of the city, effectively imprisoning "
        +"them between the portcullis and the large gate to "
        +"the southeast. There are holes in the stone ceiling "
        +"above your heads and the walls look dirty.\n"
        +"@@get_portcullis_description");
   
    add_item(({"portcullis"}), 
        "The heavy iron portcullis runs in a slit in the "
        +"northwest wall. The mechanism to lower or raise it is not "
        +"visible from here though");
    add_item(({"gate"}), 
        "The massive wooden gate to your southeast looks sturdy and "
        +"well maintained. You notice it is plate reinforced on this side, "
        +"and also lightly scorched in places.");

    add_item(({"ceiling", "holes"}),
        "The stone ceiling has holes and slits in it in regular "
        +"intervals. You can't make up what's up there, but there "
        +"are probably guards up there ready to unleash hell on anyone "
        +"foolish enough to make trouble down here.\n");
        
    add_item(({"floor", "ground"}),
        "The ground here is cobbled with stones. You see a greasy "
        +"sooty residue in the cracks between the stones.\n");
        
    add_item(({"soot", "residue", "cracks","substance"}),
        "Bending down to examine the residue, you notice it is like "
        +"some fatty substance mixed with soot.\n");
        
        
    add_exit(VALLAKI_OUTDOOR_DIR + "raumdor_gate","southeast");
    
    reset_room();
}




void reset_room()
{
}
