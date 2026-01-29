/*
 * This will be the start room for Pyros disciples
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER
 
int
is_fire(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

void
create_room()
{
    set_short("Firewalkers start room");
    set_long("You are standing in a large room carved out of the basalt "+
        "of this cave.  Along the walls are many tapestries and pictures "+
        "depicting Lord Pyros and his followers.  Just standing in this "+
        "room gives you an inner feeling of power as if the fires of "+
        "your blood are racing many times faster than normal.  On one wall "+
        "you notice a small sign which you could examine.  There are two "+
        "doors leading out of the chamber, one to the north and one to "+
        "the east.  Along the west wall you see many comfortable beds "+
        "for the followers of Pyros to rest on when not travelling in "+
        "the realms.\n");

    add_item(({"bed","beds","comfortable bed","comfortable beds"}),"The "+
        "beds look very comfortable and inviting.  If you wish to do so, "+
        "you may <start here> when you enter the realms.\n");

    add_item(({"tapestry","tapestries","picture","pictures"}),"Each of the "+
        "tapestries and pictures depicts a different scene.  All of them "+
        "seem to have Lord Pyros and his followers in them, most of them "+
        "depicting great battles.\n");

    add_item(({"small sign","sign"}),"The sign read:\nGreetings, Follower "+
        "of Pyros.  Here you may rest yourself when not travelling around "+
        "in the vast lands of these Realms.  If you wish to do so, merely "+
        "stating you wish to <start here> will suffice and I shall grant "+
        "you the power to do so.  If you decide you no longer wish to "+
        "serve me, you can <renounce my oath> here, but be warned:  The "+
        "results of your decision will be FATAL.\n\nLord Pyros, Elemental "+
        "of Fire, Ruler of Flames.\n");

   add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_S_WIZINFO,"This is a default start location for "+
        "the Pyros disciples (Firewalkers).\n");
 
    add_exit(CAVE+"room59","east");
    add_exit(CAVE+"room62","north",0,1);
}
 
int
start(string where)
{
    if (!is_fire(TP))
    {
        notify_fail("You are not a member of this guild!\n");
        return 0;
    }
   if (where != "here") return 0;
    TP->set_default_start_location("/d/Calia/sea/pyros/startroom");
    write("Lord Pyros welcomes you.  You shall start here now.\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("start","start");
    add_action("renounce","renounce");
}

int
renounce(string str)
{
    if (!is_fire(TP))
    {
        notify_fail("You are not a member of this guild!\n");
        return 0;
    }
    if (str !="my oath")
    {
        notify_fail("Renounce what?\n");
        return 0;
    }
    present("FW_Necklace",TP)->remove_object();
    write("Your necklace shatters into thousands of tiny pieces!\n");
    reset_euid();
    seteuid(getuid());
    TP->remove_guild_occ();
    TP->remove_cmdsoul("/d/Calia/walkers/fire/specials/firesoul");
    TP->set_skill(SS_WALKER_PUNISHMENT,3);
    TP->remove_skill(SS_PRAYER);
    TP->remove_skill(SS_WALKER_STATUS);
    TP->remove_skill(SS_WALKER_TITLE);
    TP->remove_skill(SS_WALKER_CHOSEN);
    TP->clear_guild_stat(SS_OCCUP);
    present("_fire_walker_spells_",TP)->remove_object();
    TP->update_hooks();
    write("The ground rumbles, almost as if it was angry.  "+
        "A large crack appears in the floor, Lord Pyros rising "+
        "from it.\nLord Pyros glares angrily at you.  He points his "+
        "finger at you, and a bolt of flames strikes you dead.\n"+
        "Lord Pyros smiles wickedly, and returns into the crack.  "+
        "The crack closes above him, and the ground stops shaking.  "+
        "A voice echos through your mind saying 'Death is the only "+
        "punishment suitable for betraying a God!'.\n");
    TP->heal_hp(-TP->query_max_hp());
 /* TP->do_die(THIS); */
    say(QCTNAME(TP)+" renounces his life long oath to Lord Pyros.\n"+
        "The ground rumbles, almost as if it was angry.  A large "+
        "crack appears in the floor, Lord Pyros rising from it.\n"+
        "Lord Pyros glares angrily at "+QCTNAME(TP)+".  "+
        "Lord Pyros points his finger at "+QCTNAME(TP)+" and "+
        "a bolt of flames strikes "+TP->query_objective()+
        " dead.\nLord Pyros returns into the crack.  The crack "+
        "closes above him, and the ground stop shaking.\n");
    return 1;
}
