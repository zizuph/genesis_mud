inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Rico */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a large room");
    set_long("You are now in the main part of the hideout of the "+
        "Shadow Walkers. The shadows around you comfort you. You "+
        "see plain straw mats and old cushions laying about. There are "+
        "a few cutthroats, thieves and whores sitting around the room, "+
        "taking refuge from the hot sun above. The room leads out "+
        "to the east, north and west.\n");
    add_item("whores","Young, dirty and hopless women. They feed "+
        "themselves by satisfying the appetites of others.\n");
    add_item("thieves","They stay in the shadows, looking around "+
        "suspiciously.\n");
    add_item("cutthroats","Emotionless brutes. They sharpen their "+
        "weapons, thinking about their next victim.\n");
    add_item("mats","Crude straw mats. You can start in this "+
        "guild if you type: start here.\n");
    add_item("cusions","Old stolen cusions. They are now filthy.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t9),"east",0,-1,1);
    add_exit(SHDIR(t11),"north",0,-1,1);
    add_exit(SHDIR(t12),"west",0,-1,1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
        {
        ob = clone_object(SHDIR(thief_seller));
        ob->move_living("xxx",TO);
    }
}

void
init()
{
    ::init();
    AA(start,start);
}

int start(string s)
{
    if(s == "here" && TP->query_guild_name_lay() == GUILD_NAME)
        {
        if(TP->set_default_start_location(SHDIR(t10)))
            {   
            write("From now on, you shall enter the game from this room.\n");
            return 1; 
       }
        else
            {
            write("For some reason, it failed.\n");
            return 1;
       }
    } 
    write("Either you can't type or you are not a member. Please try again.\n");
    return 1;
}
