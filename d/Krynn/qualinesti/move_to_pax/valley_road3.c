/*
   Pax Tharkas, Valley.....

   valley_road3.c
   --------------

   Coded ........: 95/04/09
   By ...........: Jeremiah

   Latest update : 2003/03/03
   By ...........: Blizzard
   Modified for quest purposes.
*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

object enter_room = VALLEY + "forest3";

int    elf_safe(object dest);
int    quest_check();
void   remove_me();

#define I_RELEASED_ELF   "_i_released_elf"
#define ELF_SAFE         "_elf_safe"


void
create_pax_room()
{
   set_short("Bend on road in narrow valley");
   set_long("You are standing on a road in a narrow valley. The valley " +
            "and the road turns northeast to west here. Northeastwards, " +
            "the valley widens a bit, enlarging the distance to the " +
            "mountains to the north. To both sides of the road the " +
            "valley floor gently slopes upwards towards the mountain " +
            "ranges bounding the valley. South the view of the lower " +
            "slopes of the mountains is obstructed by a small forest, " +
            "almost reaching all the way down to the road.\n");

   OUTSIDE;

   add_item("road", "A simple dusty road, running through a small " +
            "valley.\n");

   add_item("valley", "You are standing in it. A small valley cutting " +
            "into the mountains.\n");

   add_item("slopes", "The lower slopes of the mountains bordering " +
            "the southside of the valley are covered by a small forest. " +
            "The forest is almost reaching all the way down to the road.\n");

   add_item(({"forest", "Forest"}), "This is a light forest covering the " +
            "slopes of the southern mountains. You wonder what might be " +
            "hidden in that forest. Maybe it's possible, somehow, to enter " +
            "the light forest and investigate it.\n");
	
   add_item(({"mountain", "mountains"}), "Mountains rising high into the " +
            "sky, bordering this valley, north and south. The slopes of " +
            "the southern mountain reaches are covered with a light " +
            "forest, obscuring the view to these.\n");


   add_exit(VALLEY + "valley_road4", "northeast", "@@quest_check", 2);
   add_exit(VALLEY + "valley_road2", "west", "@@quest_check", 2);

   add_cmd_parse("[the] 'forest' / 'Forest'", "enter", "@@enter_forest");
}

int
quest_check()
{
    object elf;
    
    if ( TP->query_prop(I_RELEASED_ELF) && (elf = present("sarist", TO)) )
    {
        elf->command("emote stops.");
        elf->command("say Wait.");
        return 1;
    }
    
    return 0;
}

void
enter_inv(object dest, object old)
{
    ::enter_inv(dest, old);
    
    if ( dest->query_prop(I_RELEASED_ELF) )
        set_alarm(2.0, 0.0, &elf_safe(dest));

}

int
elf_safe(object dest)
{
    object elf;
        
    if ( (dest->query_prop(I_RELEASED_ELF)) && (elf = present("sarist", TO)) )
    {
        elf->command("say Thank you for your assistance. I owe you my life.");
        elf->command("emote looks around.");
        elf->command("say As I said, I will go on my own from this place. " +
            "I have nothing but my sword now so I can't reward you.");
        elf->command("say Qualthas will be informed about your actions " +
            "and next time you are in our camp ask him about me.");
        dest->catch_msg(QCTNAME(elf) + " shakes your hand.\n");
        say(QCTNAME(elf) + " thanks " + QTNAME(dest) + ".\n", dest);
        
        dest->add_prop(ELF_SAFE, 1);
        set_alarm(2.0, 0.0, &remove_me());
        
        return 1;
    }    
   
    return 0;     
}

void
remove_me()
{
    object elf;
    
    if ( elf = present("sarist", TO));
    {
        elf->command("emote leaves towards the mountains to the north.\n");
        elf->remove_object();
    }    
}

int
enter_forest()
{
      set_dircmd("forest");
      write("You enter the light forest south of the road.\n");
      say(QCTNAME(TP) + " enters the forest south of the road.\n");
      enter_room->someone_arrives(TP);
      TP->move_living("M", VALLEY + "forest3", 0);
      return 1;
}


int
construction()
{
   write("This area is under construction. You can't go there.\n");
   return 1;
}

