#include "default.h"
inherit "/std/object";

string str;

void
create_object()
{
    seteuid(getuid());

    set_name("cat");
    set_adj("small");
    add_adj("black");
    set_short("small black cat");
    set_pshort("small black cats");
    set_long("An adorable little black cat.\n"+
      "A small tag on the cat's collar has the following words written on it:\n"+
      "You can 'stroke' the cat or you can try 'catmeow' to make the cat "+
      "meow.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 144);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
stroke(string str)
{
    if((str == "cat"))
    {
	write("You stroke the small black cat. It purrs contentedly.\n");
	say(QCTNAME(TP) + " strokes a small black cat softly. It purrs contentedly.\n");
    }
    return 1;
}

int
kill_animal(string str)
{
    if((str == "cat"))
    {
	write("You viciously smash the small black cat's head in!\n");
	say(QCTNAME(TP) + " viciously smashes the small black cat's head in!\n");
	remove_object();
	return 1;
    }
    return 0;
}

int
meow()
{
    write("The small black cat meows softly.\n");
    say("The small black cat meows softly.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(stroke, "stroke");
    add_action(kill_animal, "kill");
    add_action(meow, "catmeow");
}
