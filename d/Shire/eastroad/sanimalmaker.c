#pragma save_binary

#include "local.h" 
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

inherit "/d/Shire/std/room";

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
             "toad",\
             "muskrat"})

#define ANIMALNUM 18
#define EXITNUM 17
#define MYEXITS ({"a","b","c","d","e","f","g","h","i","j","k","l","m",\
                             "n","o","p","q","r"})
#define MAXCOUNT 2
void make_animals();
void do_animals();

static int count;
int alarm_id;


void
reset_shire_room()
{
    count = 0;
    set_alarm(4.0,0.0,"make_animals");
}




void
create_shire_room()
{
    set_short("Animal making room.");
    set_long("Lots of animals are cloned here and sent to places all over the "+
      "Shire.  This happens automatically.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(ER_DIR + "er1s","a",0,1);
    add_exit(ER_DIR + "er16s","b",0,1);
    add_exit(ER_DIR + "er3s","c",0,1);
    add_exit(ER_DIR + "er13s","d",0,1);
    add_exit(ER_DIR + "er2s","e",0,1);
    add_exit(ER_DIR + "er12s","f",0,1);
    add_exit(ER_DIR + "er4s","g",0,1);
    add_exit(ER_DIR + "er9s","h",0,1);
    add_exit(ER_DIR + "er4s","i",0,1);
    add_exit(ER_DIR + "er14s","j",0,1);
    add_exit(ER_DIR + "er11s","k",0,1);
    add_exit(ER_DIR + "er5s","l",0,1);
    add_exit(ER_DIR + "er15s","m",0,1);
    add_exit(ER_DIR + "er7s","n",0,1);
    add_exit(ER_DIR + "er26s","o",0,1);
    add_exit(ER_DIR + "er9s","p",0,1);
    add_exit(ER_DIR + "er23s","q",0,1);
    add_exit(ER_DIR + "er10s","r",0,1);

    reset_shire_room();

}


void
make_animals()
{
    alarm_id = set_alarm(2.5,1200.0,"do_animals");
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
