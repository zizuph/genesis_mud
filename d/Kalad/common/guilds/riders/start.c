inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/riders/default.h"

void
create_room()
{ 
    ::create_room();
    INSIDE;
    set_short("Sleeping quarters of the Dark Alliance");
    set_long("You are within the sleeping quarters of the Dark Alliance. "+
    "There are many beds along the walls, where the members of the "+
    "Dark Allaince sleep. The ground is carpeted, and a fire burns in the "+
    "fireplace on the south wall, providing warmth and light. The "+
    "room is decorated with many valuable objects. There is a small "+
    "sign on the wall here. Fell free to drop any equipment on the "+
    "floor here, that you may want to share with your brothers and sisters "+
    "of the Dark Alliance.\n");
    add_item(({"beds","bed"}),"They look quite cozy and comfortable.\n");
    add_item(({"carpet","ground"}),"The ground is covered with a "+
    "beautiful fur carpet. Probably stolen by the Alliance or the trusted "+
     "Red Fang soldiers. It makes the place feel warm and cozy.\n");
    add_item(({"fire","fireplace"}),"A warm fire burns in the stone "+
    "fireplace in the south wall. It lights up the area.\n");
    add_item("objects","You see many ceremonial weapons, tapestries, "+
    "paintings, and other baubles.\n");
    add_item("paintings","They are of beautiful women, mostly nude.\n");
    add_item(({"sign"}),"Several words have been printed on it.\n");
    add_cmd_item("sign","read","Here you may type 'start here' so that "+
      "you may begin your journeys from this place.\n");
    add_prop(ROOM_M_NO_ATTACK, "The feeling of peace is too great here.\n");
    add_exit(COMMON(guilds/riders/rhall),"north",0,-1,-1);
}

init()
{
   ::init();
   
   add_action("start","start");
}

int 
start(string s)
{
    if(s == "here" && (IS_MEMBER(TP)))
    {
       if(TP->set_default_start_location("/d/Kalad/common/guilds/riders/start"))
       write("From now on you shall wake up here, within the stone halls "+
       "of this hideout.\n");
      return 1; 
    }
    else
    {
        write("For some reason, it failed.\n");
        return 1;
    } 
   return 1;
}
