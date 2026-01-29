inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

void create_object()
{
    set_name("statue");
    set_adj("tall");
    add_adj("bronze");
    set_short("tall bronze statue");
    set_long("This is a bronze statue of a minotaur. Both his hands "+
             "raised into the air and his mouth is wide open, in a "+
             "silent scream of victory. Deep scars decorate his chest and "+
             "arms and huge bracers covers some of this thick arms. The "+
             "statue is over twice as big as a normal minotaur, making it "+
             "a very impressive piece of art. This statue looks ancient "+
             "and most of the bronze has been tarnished into a green color.\n");

   add_item(("bracers"),"The bracers are made out of once polished bronze "+
                        "and covers the minotaurs lower arms.\n");

    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_WEIGHT, 90000);
    add_prop(OBJ_I_VALUE, 0);
}

void
search_object(string what)
{
    if (this_player()->query_prop(HAS_SEARCHED_THIRD_STATUE))
    {
	set_alarm(6.0,0.0, &write("You find nothing special except "+
                "that the statue is missing it's right horn.\n"));
    }
    if (!this_player()->query_prop(HAS_SEARCHED_THIRD_STATUE))
    {
	this_player()->add_prop(HAS_SEARCHED_THIRD_STATUE, 3);
	set_alarm(10.0,0.0, &write("You carefully examine the statue "+
                "closer, and you notice that a it's right horn is "+
                "missing.\n"));
    }
  return 0;
}
