#pragma save_binary

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "local.h"
#include <stdproperties.h>

#define ANIMALS ({"moose",\
             "elk",\
             "fox",\
             "deer",\
             "coyote",\
             "duck",\
             "goose",\
             "turtle",\
             "beaver",\
             "bear",\
             "chipmunk",\
             "butterfly",\
             "bee",\
             "oppossum",\
             "raccoon",\
             "skunk",\
             "snake",\
             "worm",\
             "toad",\
             "muskrat"})

#define ANIMALNUM 19
#define EXITNUM 17
#define MYEXITS ({"a","b","c","d","e","f","g","h","i","j","k","l","m",\
                             "n","o","p","q","r"})
#define MAXCOUNT 2
void make_animals();
void do_animals();
void do_rocks();


static int count;
int alarm_id;


void
reset_room()
{
   count = 0;
   set_alarm(4.0,0.0,"make_animals");
     set_alarm(10.0,0.0,"do_rocks");
}




void
create_room()
{
   set_short("Animal making room.");
   set_long("Lots of animals are cloned here and sent to places all over the "+
   "Shire.  This happens automatically.\n");

   add_prop(ROOM_I_INSIDE,1);

   add_exit(ER_DIR + "er1n","a",0,1);
   add_exit(ER_DIR + "er16n","b",0,1);
   add_exit(ER_DIR + "er3n","c",0,1);
   add_exit(ER_DIR + "er14n","d",0,1);
   add_exit(ER_DIR + "er2n","e",0,1);
   add_exit(ER_DIR + "er11n","f",0,1);
   add_exit(ER_DIR + "er14n","g",0,1);
   add_exit(ER_DIR + "er18n","h",0,1);
   add_exit(ER_DIR + "er4n","i",0,1);
   add_exit(ER_DIR + "er14n","j",0,1);
   add_exit(ER_DIR + "er11n","k",0,1);
   add_exit(ER_DIR + "er5n","l",0,1);
   add_exit(ER_DIR + "er15n","m",0,1);
   add_exit(ER_DIR + "er7n","n",0,1);
   add_exit(ER_DIR + "er17n","o",0,1);
   add_exit(ER_DIR + "er9n","p",0,1);
   add_exit(ER_DIR + "er22n","q",0,1);
   add_exit(ER_DIR + "er10n","r",0,1);

   reset_room();

}


void
do_rocks()
{
   object rock;

    rock = clone_object(COMMON_DIR + "obj/rock");
   rock->move(ER_DIR + "er2s");
   rock = clone_object(COMMON_DIR + "obj/rock");
   rock->move(ER_DIR + "stonebows");
   rock = clone_object(COMMON_DIR + "obj/rock");
   rock->move(ER_BASE_DIR +"girdley/isle3");

}

void
make_animals()
{
    alarm_id = set_alarm(2.5,600.0,"do_animals");
}

void
do_animals()
{
   object animal;
   int ran, ran2;

   ran = random(ANIMALNUM);
   ran2 = random(EXITNUM);

   if(count > MAXCOUNT)
   {
     remove_alarm(alarm_id);
     return;
    }

   count++;
   
    animal = clone_object(ANIMAL_DIR + ANIMALS[ran]);
    animal->move(TO);
    tell_room(ENV(TO),QCTNAME(animal)+" is cloned to the room.\n");
    tell_room(ENV(TO),"Count is: "+count+".\n");
    animal->command(MYEXITS[ran2]);
    return;

}
