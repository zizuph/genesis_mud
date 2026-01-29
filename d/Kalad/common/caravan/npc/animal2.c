#include "default.h"
inherit "/std/object";

string str;

void
create_object()
{
    seteuid(getuid());

    set_name("puppy");
    set_adj("small");
    add_adj("brown");
    set_short("small brown puppy");
    set_pshort("small brown puppies");
    set_long("A cute, furry little puppy.\n"+
      "A small tag on the puppy's collar has the following words written on it:\n"+
      "You can 'pet' the puppy, use 'dogbark', 'doggrowl' and 'dogwhimper' to "+
      "get the puppy to do things.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 288);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
pet(string str)
{
    if((str == "puppy"))
    {
	write("You pet the small brown puppy. It barks happily.\n");
	say(QCTNAME(TP) + " pets the small brown puppy. It barks happily.\n");
    }

    return 1;
}

int
kill_animal(string str)
{
    if((str == "puppy"))
    {
	write("You viciously crush the small brown puppy with your foot!\n");
	say(QCTNAME(TP) + " viciously crushes the small brown puppy with " + TP->query_possessive() + " foot!\n");
	remove_object();
	return 1;
    }
    return 0;
}

int
bark()
{
    write("The small brown puppy barks excitedly.\n");
    say("The small brown puppy barks excitedly.\n");
    return 1;
}

int
growl()
{
    write("The small brown puppy growls menacingly.\n");
    say("The small brown puppy growls menacingly.\n");
    return 1;
}

int
whimper()
{
    write("The small brown puppy whimpers pitifully.\n");
    say("The small brown puppy whimpers pitifully.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(pet, "pet");
    add_action(kill_animal, "kill");
    add_action(bark, "dogbark");
    add_action(growl, "doggrowl");
    add_action(whimper, "dogwhimper");
}
