#include "defs.h"
inherit ROAD_ROOM;
#include <macros.h>
#include <stdproperties.h>
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("In the city square");
    set_long("You are now in the center of the city square. The "+
    "ground is made of cobble stone. Right next to you, a large "+
    "fountain juts out of the ground. Various shops surround this "+
    "square, and people are trudging slowly through another grim "+
    "day in Raumdor. To the west is the road to the city west "+
    "gates, while to the east is the road that leads to the east "+
    "part of city. North, the square leads to another road that "+
    "goes into the residential area, and south lies the road to "+
    "the south gates.\n");
    add_item(({"fountain"}),
    "This is a large but simple fountain to drink cool water from.\n");
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_exit(DRAKMERE_DIR + "road17","east",0,0,0);
    add_exit(DRAKMERE_DIR + "road16","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road05","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road07","south",0,0,0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 3);
}
int
wash_it(string str)
{
   if((str == "face"))
          {
  write("You put your hands into the fountain and wash your face with "+
    "some of the fountain water.\n"+
    "It feels cool on your skin.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" puts "+HIS(TP)+" hands into the fountain and "+
    "washes "+HIS(TP)+" face with some of the fountain water.\n");
      return 1;
           }
   if((str == "hands"))
          {
  write("You put your hands into the fountain and wash your hands with "+
    "some of the fountain water.\n"+
    "It feels cool on your skin.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" puts "+HIS(TP)+" hands into the fountain and "+
    "washes "+HIS(TP)+" hands with some of the fountain water.\n");
      return 1;
           }
   if((str == "neck"))
          {
  write("You put your hands into the fountain and wash your neck with "+
    "some of the fountain water.\n"+
    "It feels cool on your skin.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" puts "+HIS(TP)+" hands into the fountain and "+
    "washes "+HIS(TP)+" neck with some of the fountain water.\n");
      return 1;
           }
   if((str == "ears"))
          {
  write("You put your hands into the fountain and wash your ears with "+
    "some of the fountain water.\n"+
    "It feels cool on your skin.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" puts "+HIS(TP)+" hands into the fountain and "+
    "washes "+HIS(TP)+" ears with some of the fountain water.\n");
      return 1;
           }
   if((str == "feet"))
          {
  write("You put your feet into the fountain and wash your feet with "+
    "some of the fountain water.\n"+
    "It feels cool on your skin. But who will want to drink the water "+
    "after you've had your feet in it.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" puts "+HIS(TP)+" feet into the fountain and "+
    "washes "+HIS(TP)+" feet with some of the fountain water.\n"+
    "You may not want to drink the water now!\n");
      return 1;
           }
   if((str == "body"))
          {
  write("You change your mind about washing your body with "+
    "the fountain water, since this is a central location in this village.\n");
      
          /* This what others in room see. */
  say(QCTNAME(TP)+" looks like "+HE(TP)+" is thinking "+
    "about something.\n");
     return 1;
      }
   else
  {
   notify_fail("Wash what? Your face perhaps?\n");
   return 0;
  }

}
int
drink_it(string str)
{
    string what, where;
    int i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
        {
            /* Syntax must simply be "drink <something>" */
            what = str;
        }
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (where && !parse_command(where, ({}), "[the] 'fountain' "))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        notify_fail("Drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("You take a drink of the cool water.  Having " +
            "drunk your fill, you feel refreshed.\n");
    }
    else
    {
        write("You take a drink of the cool water.\n");
    }

    say(QCTNAME(this_player()) +" drinks some water from the "+
       "fountain.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(drink_it, "drink");
    add_action(wash_it, "wash");
}

