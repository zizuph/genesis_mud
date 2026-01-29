/* The standard Field-of-Gondor-file, made by Elessar for Genesis   
*  February 1992. No copyrights, but would like to have my name    
*  mentioned if anyone modifies this file for own use.          
   *  Totally changed to make it into a hobbit hole builder, by Elix February 95
*/

#pragma save_binary

inherit "/d/Shire/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"

int   roomtype;   /* 1=Front Hall 2=Parlor 3=Dining Room 4=Kitchen 
*   5=Master Bed Room 6=Bed Room 7=Storage Room       *   8=Corridor 9=Cellar 10=Pantry 
*/

string  smialsize,    /* eg "small", "large"*/
areaname,    /* eg "Mithlond", "Michel Delving", /*
/*"Hobbiton", "Bree" */
areatype,   /*eg "hamlet", "village", "town", "city" */
land,          /* "the Shire" */
extraline;  /* additional room description */

string short_func()
{
   switch(roomtype)
   {
      case 1:
        return "A front hall of a "+smialsize+" smial";
      case 2:
        return "A "+smialsize+" parlor";
      case 3:
        return "A "+smialsize+" dining room";
      case 4:
        return "A "+smialsize+" kitchen";
      case 5:
        return "A master bedroom";
      case 6:
        return "A small bedroom";
      case 7:
        return "A storage room";
      case 8:
        return "A tube-shaped hall";
      case 9:
      return "A cool cellar";
      case 10:
      return "A large pantry";
   }
}

void make_the_room()
{
   set_short("@@short_func@@");
   set_long("@@describe@@");
   
   switch(roomtype)
   {
      case 1:
      add_item("door","This round wooden door is small, as "
         +"befits the door to a hobbit hole.  There is a little "
         +"window set into the door, that lets you look outside.\n");
      add_item("window","This quaint little window is round, "
         +"as you would expect, with glass panels set in a lead "
         +"border.  The frame is painted bright white, and the "
         +"window is kept clean.  You could look outside through "
         +"this window if you wanted to.\n");
      add_item("outside","Looking through the window, you can "
         +"see the "+areatype+" of "+areaname+".\n");
      break;
      case 2:
      add_item(({"chairs","chair","comfortable chair"}),
         "Hobbits are well known for their love of comforts. "
         +"This is obvious, looking at these chairs that are just "
         +"begging out for you to sit upon.\n");
      add_item(({"sofa","sofa","comfortable sofa"}),
         "These sofas look as comfortable as the chairs. "
         +"They are well padded, and would be nice to "
         +"lie down on.\n");
      add_item("fireplace","This large fireplace, set into the wall, "
         +"can heat up the entire room nicely. The fireplace is "
         +"not lit, as no fire has been set.\n");
      break;
      case 3:
      add_item(({"table","dining table"}),
         "This dining table has been lovingly cared for, and has "
         +"been much polished, until its oaken surface shines "
         +"with a soft glow.\n");
      add_item(({"chairs","chair","comfortable chair"}),
         "Hobbits are well known for their love of comforts. "
         +"This is obvious, looking at these chairs that are just "
         +"begging out for you to sit upon, ready to eat.\n");
      break;
      case 4:
      add_item(({"utensils","cooking utensils"}),
         "These cooking utensils hang from the roof of this "
         +"smial, ready for use in making delicious meals.\n");
      add_item("stove",
         "This large stove looks like it can cook a huge meal, and "
         +"guessing from the soot around it, it obviously has cooked "
         +"many meals.\n");
      add_item(({"cupboard","cupboards"}),
         "These cupboards contain pots and pans and other "
         +"implements used in cooking the many meals that "
         +"hobbits are prone to eat.\n");
      break;
      case 5:
      add_item("bed",
         "This huge bed would easily fit a couple of hobbits. "
         +"It looks soft and comfortable and inviting, ready "
         +"to be slept in.\n");
      add_item(({"cupboards","cupboard"}),
         "The cupboards in this room presumably hold clothes "
         +"and other such items. However, they are firmly "
         +"locked, and look too strong to break into.\n");
      add_item(({"dresser","dressers"}),
         "Like the cupboards, these dressers hold clothes and "
         +"similar items.  Like the cupboards, the dressers are "
         +"firmly locked.\n");
      break;
      case 6:
      add_item("bed",
         "This small bed looks just right for a hobbit to use. "
         +"It looks soft and comfortable and inviting, ready "
         +"to be slept in.\n");
      add_item("dresser",
         "This dresser is used to hold clothes for visiting "
         +"hobbits. At the moment, it seems to be empty.\n");
      break;
      case 7:
      add_item(({"shelf","shelves"}),
         "The shelves in this storage room are currently "
         +"empty, although they look like they can store "
         +"a lot of goods.\n");
      break;
      case 8:
      add_item("walls",
         "The walls of this hallway are panelled in oak. "
         +"The oak has been polished lovingly, and glows "
         +"with a soft shine.\n");
      add_item(({"floor","carpet"}),
         "The floor of this hallway is carpeted with a plush red "
         +"wool carpet.  Once a rich carpet, it has now faded "
         +"with time and with the passing of many tiny feet.\n");
      break;
      case 9:
      add_item(({"rack","wine rack","racks","wine racks"}),
         "The wine racks in this cellar were once full, but "
         +"now they are only coated in dust and spiderwebs.\n");
      add_item("spiderwebs",
         "These spiderwebs have been spun over the wine "
         +"racks, which obviously haven't been used in a long "
         +"time.\n");
      break;
      case 10:
      add_item("shelves",
         "The shelves in this pantry have the remnants of food "
         +"in them - old flour, moldy apples...\n");
      break;
   }
   add_prop(ROOM_I_INSIDE,1);
}

string describe() 
{
    string long_descf = short_func(), temp_longdescr;

    switch(roomtype)
    {
        case 1:
            temp_longdescr = "It is located in the " + areatype + " of " + 
                areaname + " in " + land + ". There is a round wooden " +
                "door leading out of here.";
        case 2:
            temp_longdescr = "There are several comfortable looking chairs " +
                "and sofas here, as well as a large fireplace set into one " +
                "of the walls.";
        case 3:
            temp_longdescr = "This is without a doubt the most popular " +
                "room in the smial--it is the dining room. Dominating " +
                "the room is a large table that could seat many hobbits, " +
                "and surrounding it are a number of chairs.";
        case 4:
            temp_longdescr = "You are standing in one of the largest " +
                "rooms, the kitchen of the smial. There are cupboards " +
                "lining the walls, cooking utensils hang from the roof, " +
                "and a large stove and cooking range against a wall.";
        case 5:
            temp_longdescr = "";
        case 6:
            temp_longdescr = "";
        case 7:
            temp_longdescr = "This is really nothing more than a slightly " +
                "over-sized cupboard. The storage room is fitted with shelves.";
        case 8:
            temp_longdescr = "The walls are paneleld and the floor " +
                "covered with a carpet.";
        case 9:
            temp_longdescr = "It is cool and dry and fitted out with " +
                "a number of wine-racks.";
        case 10:
            temp_longdescr = "It has shelves fitted to the walls to " +
                "store all sorts of food. All through this room a faint " +
                "smell of apples permeates the air.";
        }
        

//    long_descf = short_func() + ". " + temp_longdescr + extraline + "\n";

    if(!extraline)
        long_descf = short_func() + ". " + temp_longdescr + "\n";
    else
        long_descf = short_func() + ". " + temp_longdescr + " " +extraline + "\n";

    return (long_descf + roomtype);
}

void init()
{
   ::init();
   if(roomtype == 5 || roomtype == 6)
      add_action("do_sleep_bed","sleep");
   if(roomtype == 2 || roomtype == 3)
      add_action("do_sit","sit");
   if(roomtype == 2)
      add_action("do_sleep_sofa","lie");
   if(roomtype == 10)
      add_action("do_smell","smell");
   
}

int do_sleep_bed()
{
   NF("You sink down into the soft bed, and try to sleep.  "
      +"However, the bed is too soft for an adventurer like "
      +"you, and you are unable to fall asleep.  Giving up "
      +"on sleep, you stand.\n");
   return 0;
}
int do_sleep_sofa()
{
   NF("The sofa, that looked so comfortable, does not seem "
      +"to suit your body, accustomed to the rigours of travel "
      +"as you are.  You decide to stand up again.\n");
   return 0;
}
int do_sit()
{
   NF("You settle yourself into one of the comfortable chairs, "
      +"and after a short rest, you stand, ready to seek new "
      +"adventures.\n");
   TP->add_fatigue(1);
   return 0;
}
int do_smell()
{
   NF("You take a deep breath, breathing in the air in the pantry. "
      +"The air is musty, and full of old food smells. You can "
      +"detect the faint lingering scent of spices like cinnamon "
      +"and cardamon, but the overpowering scent is that of old "
      +"apples, that must have been stored in here once upon a "
      +"time.\n");
   return 0;
}
