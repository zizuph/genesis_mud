/* 
 * /d/Kalad/common/wild/pass/w14.c
 * Purpose    : Road
 * Located    : Caravan Route out of Kabal
 * Created By : Antharanos 
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("You are travelling along the Caravan Route.\n"+
      "The way west eventually leads towards the famed city of Kabal. "+
      "All about you are the immense mountains of the Hespyre range. Almost lost "+
      "among the towering heights of the mountains are the no less "+
      "impressive redwoods, which blanket the lower slopes of the range. "+
      "The Caravan Route, which winds its way past the sheer walls of the mountains, "+
      "continues eastward, deeper into the Hespyre mountains.\n");
   add_item(({"caravan route","route","way"}),"A cobblestoned roadway that "+
      "appears worn due to heavy usage and the harsh effects of time and "+
      "weather. You notice off to the side on a hill, an old bush.\n");
   add_item(({"immense mountains","hespyre range","hespyre mountains","mountain","range","immense mountains","hespyre mountain"}),
      "Craning your neck to take in the full sight of the mountains, their "+
      "sheer size and cold beauty make you feel as insignificant as a bug "+
      "compared with a human being. The mountains of the range cast a dark "+
      "shadow over the land.\n");
   add_item(({"impressive redwoods","impressive redwood","redwoods","redwood","lower slopes","lower slope","slopes","slope"}),
      "Giant redwood trees, as large as twenty feet across at the base "+
      "cover the lower slopes of the mountains. On the higher slopes, thin "+
      "blankets of snow are visible.\n");
   add_item(({"sheer walls","sheer wall","walls","wall"}),"The "+
      "unclimbable sides of the mountains.\n");
   add_item("bush","@@bush");
   add_exit("/d/Kalad/common/wild/pass/w13", "west",0,2);
   add_exit("/d/Kalad/common/wild/pass/w15", "east",0,2);
}

string
bush()
{
    if(TP->query_guild_name_race() == "Red Fang Guild")
    {
        return
        "Its an odd bush, and you think you see a hole behind it. "+
        "Perhaps you can enter it?\n";
    }
    else
    return
    "Its an old bush, nothing more.\n";
}

void
init()
{
    ::init();
    AA(do_enter,enter);
}

int
do_enter(string str)
{
    if(TP->query_guild_name_race() == "Red Fang Guild")
    {
        NF("Enter what? The bush?\n");
        if(str != "bush")
            return 0;
        write("You distract anyone who is around you at the moment, then "+
        "quickly push the bushes aside and enter the tunnel.\n");
        switch(random(6))
        {
        case 0: 
        say(QCTNAME(TP)+" points up and says: Its a flying turtle!\n"+
        "You turn to look, and when seeing nothing, you turn back "+
        "and notice "+HE(TP)+" is gone.\n");
        break;
        case 1:
        say(QCTNAME(TP)+" points down and says: Thats a strange place "+
        "to put a maul.\n You look down, and, seeing nothing, look back "+
        "up and notice that "+HE(TP)+" is gone.\n");
        break;
        case 2:
        say(QCTNAME(TP)+" shouts: Look out bandits!\n"+
        "You turn to look, but you don't see anything. Howerver, you "+
        "notice that "+QTNAME(TP)+" is gone.\n");
        break;
        case 3:
        say(QCTNAME(TP)+" stares intently overhead for a time. You finally "+
        "look up to see what "+HE(TP)+" finds so fascinating, and find "+
        "nothing. When you look down again, you notice "+QTNAME(TP)+" is "+
        "gone.\n");
        break;
        case 4:
        say(QCTNAME(TP)+" leans back, opens "+HIS(TP)+" mouth, and "+
        "spews forth a great plume of vomit. You turn your head in "+
        "disgust. When you turn back again, you notice "+HE(TP)+" is "+
        "gone.\n");
        break;
        case 5:
        say(QCTNAME(TP)+"'s jaw drops, and "+HIS(TP)+" eyes widen in "+
        "fright as "+HE(TP)+" stares at something behind you. You turn "+
        "around to see what it is, but find nothing. When you turn back "+
        "again, you notice "+HE(TP)+" is gone.\n");
        break;
    }
        TP->move_living("M","/d/Kalad/common/guilds/red_fang/rooms/hole",1,1);
        set_alarm(5.0,0.0,"do_move");
        return 1;
    }
    NF("What ?\n");
    return 0;
}

void
do_move()
{
    write("You move further down the tunnel and eventually come "+
    "out into a cave.\n");
    set_alarm(2.0,0.0,"do_move2");
}

void
do_move2()
{
    TP->move_living("M","/d/Kalad/common/guilds/red_fang/rooms/hall3");
    tell_room(E(TP),QCTNAME(TP)+" pops out of the bushes.\n",TP);
    TP->command("fgrin");
}

