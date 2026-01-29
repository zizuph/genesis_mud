/*
 * This file is the hobbit's bathing area.
 * Dunstable, 3-21-95
 *
 */

#pragma save_binary

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "hobbit.h"
 
static object hob, rack, hamper;


int do_bathe(string str);
int do_enter(string str);
int do_stand(string str);
int do_splash(string str);
void reset_room();

void
create_room()
{
    set_short("Bath hall");
    set_long("The floor here is littered with large metal tubs arrayed "+
    "in rows side by side.  At the far south wall a very large fire burns. "+
    "The west and east walls are lined with plush towels, and to the north "+
    "there is a mirror on the wall, a sink and a rack of soaps.\n");
 
    add_item("walls","Examine a particular wall, please.\n");
    add_item("north wall","This wall has a large mirror mounted to "+
    "it and underneath the mirror is a sink and a soap-rack.\n");
    add_item("south wall","The south wall has a fireplace built into it.\n");
    add_item("east wall","Plush towels hang on hooks here.\n");
    add_item("west wall","Plush towels hang on hooks here.\n");

    add_item(({"large fire","very large fire","fireplace"}),
    "The very large fire burning in the fireplace on the south wall must "+
    "create a lot of heat.  Probably enough to make very hot bathing water.\n");

    add_item(({"sink","soaps","rack","soap"}),
    "The sink underneath the mirror has water in it and soaps in the "+
    "rack above make washing up only a little, simpler than the tubs.\n");
    add_item("mirror","It is a large silvery mirror, made of a polished "+
    "metal you do not recognize, and it seems to have a rather familiar "+
    "reflection to it.\n");

    add_item(({"row","rows"}),
    "The metal bathtubs are arranged in rows so that bathers are side by side "+
    "in addition to being in front and behind one another.\n");

    add_item(({"tub","tubs","bathtubs","bathtub","metal tub","metal tubs"}),
    "The bathtubs are made of cast iron, and probably very heavy, but "+
    "they should hold a lot of nice hot water!\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,"Make bubbles, not war!\n");
    

    add_exit(HOBGLD_DIR + "start","west","@@check_exit@@");
        
    reset_room();  
}

int
check_exit()
{
   if(TP->query_prop("i_am_wet"))
   {
    write("You must dry yourself before leaving!\n");
    return 1;
   }

   if(TP->query_prop("i_am_bathing"))
   {
    write("You must get out of the tub and dry off first.\n");
     return 1;
   }
 
   if(present("towel",TP))
   {
     write("Please leave your towel in the hamper!\n");
     write("You should not take guild property.\n");
      return 1;
    }


   write("Make sure you have all of your belongings!\n");
   return 0;

}


void
init()
{
    ::init();
    add_action("do_splash","splash");
    add_action("do_bathe","wash");
    add_action("do_bathe","clean");
    add_action("do_bathe","bathe");
    add_action("do_enter","enter");
    add_action("do_stand","stand");

}

int
do_enter(string str)
{
    if(!str)
    {
      write("Enter what?\n");
      return 1;
     }

    if((str != "bathtub") && (str != "tub") && (str != "metal tub"))
    {
      write("Enter what? A "+str+"? Are you sure?\n");
      return 1;
    }

   if(TP->query_prop("i_have_bathed"))
   {
     write("But you've already had one bath today, that's enough, "+
     "don't you think?\n");
     return 1;
   }

    TP->add_prop("i_am_wet",1);
    TP->add_prop("i_am_bathing",1);

    write("You walk over to the nearest tub and get ready to splash!\n");
    TP->command("remove all");
    TP->command("put armours in stand");
    say(QCTNAME(TP)+ " climbs into one of the cast iron bathtubs.\n");
    write("You climb into one of the cast iron bathtubs.\n");
    write("The attendant fills your tub with water and hands you a soap.\n");
     say("The attendant fills "+QTNAME(TP)+"'s tub and gives "+HIM_HER(TP)+
     " a soap.\n");

     write("It's a little too warm at first but soon you relax and enjoy it.\n"+
     "Ahh!\n");
     say(QCTNAME(TP)+ " jumps a bit at the temperature of the water, but "+
     "soon relaxes in enjoyment.\n");
     return 1;

}

int
do_bathe(string str)
{
    object filthy;

    if(!str)
    {
     write(capitalize(query_verb())+ " what? Yourself?\n");
     return 1;
     }

   if(str != "myself")
   {
     write(capitalize(query_verb())+ " what? Yourself?\n");
     return 1;
   }

   filthy = present("dirty",TP);

   if(filthy)
   {
    filthy->remove_object();
   }


   write("You bathe yourself with the soap in the warm water.\n");
   say(QCTNAME(TP)+ " washes "+HIM_HER(TP)+"self in the tub.\n");
   TP->add_prop("i_have_bathed",1);
   return 1;

}

int
do_splash(string str)
{
   if(!str)
   {
     write("You splash around in the warm water.\nWhee!\n");
     say(QCTNAME(TP)+ " splashes around in the bathtub.\n");
     return 1;
   }

   if(str == "wildly")
   {
     write("You splash wildly in the tub, drenching your surroundings!\n");
     say(QCTNAME(TP)+ " splashes wildly in "+HIS_HER(TP)+ " tub, drenching "+
     "everything in the room, including you.\n");
     return 1;
    }

    write("Splash how? Please don't splash wildly, it will soak the room!\n");
    return 1;

}

int
do_stand(string str)
{
   object towel;

   if(!TP->query_prop("i_am_bathing"))
   {
    write("But you're not in the tub!\n");
    return 1;
   }

   if(!str)
   {
     write("Stand where? Up?\n");
     return 1;
   }

   if(str != "up")
   {
    write("Stand "+str+"? Why not stand up?\n");
    return 1;
   }

   TP->remove_prop("i_am_bathing");
   write("You stand up and drip dry a little.\n"); 
   write("Belladonna gives you a plush towel.\n");
   say(QCTNAME(TP)+ " stands up out of the tub and drips a little.\n");
   say("Belladonna gives a plush towel to "+QTNAME(TP)+".\n");
   

   if(!present("towel",TP))
   {
     towel = clone_object(HOBGLD_DIR + "towel");
     towel->move(TP);
     return 1;
   }

   return 1;

}



void  
reset_room()
{ 
    if (!hob)
    {
        hob = clone_object(HOBGLD_DIR + "bathhobbit");
        hob->move(TO);
    }

   if(!hamper)
   {
      hamper = clone_object(HOBGLD_DIR + "hamper");
      hamper->move(TO);
    }

   if(!rack)
   {
      rack = clone_object(HOBGLD_DIR + "clothesrack");
      rack->move(TO);
    }
}