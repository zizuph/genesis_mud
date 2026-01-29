inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
object ob1;
object ob2;
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    set_short("Within the dwarven city of Underhome");
    set_long("You are within an old crypt of stone. The first thing "+
        "you notice is an acidious smell drifting towards you from "+
        "somewhere southwards, carrying with it a chill that penetrates through "+
        "your clothes. You shiver. It seems to come from a dark area "+
        "outside the circle of light your light source manages "+
        "to fight off the enveloping darkness in here. "+
        "Northwards this crypt acsends upwards in a broad stairway, while to the south "+
        "you think you see a shimmer of light. Must be your imagination.\n");
    add_item(({"tombstone","tombstones","stones","pillars","pillar","rubble"}),
        "Just a few hole stones can be seen but the letters on them are "+
        "unreadable. Except from them the rest are cracked and ruined "+
        "after decades of decay.\n");
    add_item(({"yard","graveyard"}),"You know the old graveyard, "+
        "dating back to the terrible wars of ancient times when the dwarves "+
        "lost so many of their men in violent combat is to the north.\n");
    add_item(({"circle","circle of light","light"}),"It is the area "+
        "your lightsource manage to fight off the everlasting darkness "+
        "down here.\n");
    add_item(({"smell","acidious smell"}),"The smell seems to come from "+
        "the southern area.\n");
    add_item(({"dark area","area"}),"The dark area is out of vision, so "+
        "all you really know about it is the chilling and acidious smell "+
        "the draft carries with it from there.\n");
    add_item("crypt","It is an old stone building, probably housing a long dead "+
        "hero or a lucky dwarf that found a gold-rich vein. The place gives you "+
        "a creepy feeling though.\n");
    add_item("stairway","You can see that the first step of it is "+
        "cut out of the mountain itself, and will take you back up "+
        "to the graveyard.\n");
    add_exit(CPASS(dwarf/crypt/c23),"up",0,-1,-1);
    add_exit(CPASS(dwarf/crypt/c26),"south","@@ghouls",-1,-1);
    
    set_noshow_obvious(1);
    set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
    if(!objectp(ob1))
        {
        ob1 = clone_object("/d/Kalad/common/wild/pass/dwarf/npc/ghoul");
        ob1 -> move_living("M", TO);
        tell_room(TO,"A creature comes walking out of the shadows.\n");
    }
    if(!objectp(ob2))
        {
        ob2 = clone_object("/d/Kalad/common/wild/pass/dwarf/npc/ghoul");
        ob2 -> move_living("M",TO);
    }
}

ghouls()
{
    if (objectp(ob1) || objectp(ob2))
        {
        if (!CAN_SEE(ob1,TP) && !CAN_SEE(ob2,TP))
            {
            TP->catch_msg("With your heart in your throat you walk past the "+
                "ghouls without being detected!\n");
            return 0;
        }
        ob1->command("say Thouu shall not pass me Aliiive!");
        ob2->command("emote slides between you and the stairway, blocking "+
            "it with its decaying flesh.");
        return 1;
    }
    TP->catch_msg("You carefully decend the stairway, feeling the "+
        "cold breeze in your face.\n");
    return 0;
}
