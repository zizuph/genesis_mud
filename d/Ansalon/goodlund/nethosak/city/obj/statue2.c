inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

void create_object()
{
    set_name("statue");
    set_adj("towering");
    add_adj("stone");
    set_short("towering stone statue");
    set_long("This is a giant stone statue of a minotaur. Both his hands "+
             "raised into the air and his mouth is wide open, in a "+
             "silent scream of victory. Deep scars decorate his chest and "+
             "arms and huge bracers covers some of this thick arms. The "+
             "statue is over twice as big as a normal minotaur, making it "+
             "a very impressive piece of art.\n");

   add_item(("bracers"),"The bracers are made out of flawless grey stone "+
                        "and covering the minotaurs lower arms.\n");

    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_WEIGHT, 90000);
    add_prop(OBJ_I_VALUE, 0);
}

void
search_object(string what)
{
    if (this_player()->query_prop(HAS_SEARCHED_SECOND_STATUE))
    {
	set_alarm(6.0,0.0, &write("You find nothing special except "+
                "that the statue is missing the left horn.\n"));
    }
    if (!this_player()->query_prop(HAS_SEARCHED_SECOND_STATUE))
    {
	this_player()->add_prop(HAS_SEARCHED_SECOND_STATUE, 3);
	set_alarm(10.0,0.0, &write("You carefully examine the statue "+
                "closer, and you notice that it's "+
                "left horn is missing.\n"));
    }
  return 0;
}
