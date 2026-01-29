#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

int clothed;

void
reset_room()
{
    clothed = 0;
}

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Whorehouse");
    set_long("You enter a small waiting room inside the shabby-looking "+
      "building. A few wooden chairs are seated to the north and south "+
      "while a small carpet covers the floor. Several bawdy pictures hang "+
      "on the side walls. A few potted plants decorate the room. A small "+
      "hallway heads east from here.\n");

    add_item(({ "wooden chairs", "chairs" }), "Cheap chairs that look like "+
      "they were bought from a yard sale. It looks as though the chair "+
      "might break if you sit in it.\n");

    add_item(({ "carpet" }), "A tattered brown rug that covers most of the "+
      "floor.\n");

    add_item(({ "floor" }), "It is made out of wooden planks that creak and "+
      "groan with your every movement.\n");

    add_item(({ "wooden planks", "planks", "plank" }), "They look a bit old "+
      "and in need of bad repair.\n");

    add_item(({ "pictures" }), "They all depict erotic sex acts between "+
      "men and women, women and women and well...you get the idea.\n");

    add_item(({ "walls" }), "They are covered in aged peeling wallpaper.\n");

    add_item(({ "wallpaper" }), "It looks like it will fall off at any "+
      "moment.\n");

    add_item(({ "plants" }), "They are green and flowering.\n");

    add_item(({ "hallway" }), "It leads east towards another room, inside "+
      "you can see a lady.\n");

    add_item("lady", "@@exa_lady");

    add_exit(CVAN + "chains/s1", "out");
    add_exit(CVAN + "chains/wh1", "east");

    reset_room();
}

void
wake_bouncer()
{
    clone_object(NPC + "bouncer")->move_living("M", TO);
    tell_room(TO, "The bouncer glares angrily at you!\n");
}

string
exa_lady()
{
    say(QCTNAME(TP) + " stares at a lady in the next room.\n");
    if(clothed)
	return("The lady is covering herself up with a towel.\n");
    clothed = 1;
    set_alarm(4.0, 0.0, "wake_bouncer");
    return("Moving closer to the hallway to get a better look, you hear "+
      "the lady gasp in surprise at you. The sound of running feet can be "+
      "heard!\n");
}
