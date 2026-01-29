inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#pragma strict_types
#pragma save_binary

void
create_room()
{ 
    ::create_room();
    INSIDE;
    set_short("Red Fang Quarters");
    set_long("\n   You are within the sleeping quarters of the Red Fang. "+
    "There are many beds along the walls, where the goblins of the "+
    "Red Fang sleep. The ground is carpeted, and a fire burns in the "+
    "fireplace on the south wall, providing warmth and light. The "+
    "room is decorated with many valuable objects. There is a small "+
    "sign on the wall here.\n\n");
    add_item(({"beds","bed"}),"They look quite cozy and comfortable.\n");
    add_item(({"carpet","ground"}),"The ground is covered with a "+
    "beautiful fur carpet. Probably stolen by the Red Fang. It makes "+
    "the place feel warm and cozy.\n");
    add_item(({"fire","fireplace"}),"A warm fire burns in the stone "+
    "fireplace in the south wall. It lights up the area.\n");
    add_item("objects","You see many ceremonial weapons, tapestries, "+
    "paintings, and other baubles.\n");
    add_item("paintings","They are of beautiful women, mostly nude.\n");
    add_item(({"sign"}),"Several words have been printed on it.\n");
    add_cmd_item("sign","read","Here you may type 'start here' so that "+
      "you may begin your journeys from this place.\n");
    add_exit(FANG_DIR(rooms/hall),"west",0,-1);
}

void
init()
{
    ::init();
    add_action("start","start");


   if (!IS_MEMBER(this_player()) && !this_player()->query_wiz_level() &&
        (this_player()->query_default_start_location() == MASTER))
    {
         this_player()->set_default_start_location(0);
    }
}

int 
start(string s)
{
    if(s == "here" && (IS_MEMBER(TP)))
    {
        if(TP->set_default_start_location(
           "/d/Kalad/common/guilds/red_fang/rooms/start") )
        {
            write("From now on you shall wake up here, within the stone "+
            "halls of this hideout.\n");
            return 1; 
        }
        else
        {
            write("For some reason, it failed.\n");
            return 1;
        } 
    }
    write("Either you can't type or you are not a member.\n");
    return 1;
}
