inherit "/std/room";
#include "/d/Emerald/defs.h"

#define FAIL "Your search reveals nothing special.\n"

void
reset_room()
{
    set_searched(0);
}

void create_room()
{
    set_short("Western Edge");
    set_long("You stand on the western edge of the summit "+
       "of Mount Black. A magnificent view can be seen through "+
       "a gap in the fog that swirls about you. It's unsafe to "+
       "go anywhere but back east.\n");
    add_item(({"gap", "view"}), "Through the gap in the "+
       "fog, you see a wonderous view of Emerald. Gazing into "+
       "the depths of the land you see the greenery of the land "+
       "and the vibrance of life within it.\n");
    add_item(({"summit", "ground", "mountain", "Mount Black"}), "You "+
       "are standing at the summit of the legendary Mount Black. "+
       "Under your feet is some fragrant smelling grass.\n");
    add_item("fog", "The fog is especially thick on this "+
       "side of the mountain. There is a gap in it in which "+
       "you can see a great view.\n");
    add_item(({"grass", "fragrent grass", "fragrent smelling grass"}),
       "The grass is a lush green but appears to be very hardy "+
       "to be able to stand up to the cold weather here. You see "+
       "some traces of some sort of herb here.\n");
    add_item(({"herb", "herbs"}), "No herbs seem to be on the "+
       "surface of the grass.\n");
    add_exit(MBLACK_DIR + "top", "east", 0);
    add_prop(OBJ_S_SEARCH_FUN, "search_fun");
}

string
search_fun(object player, string what)
{
    object berry;
    if(what=="grass"||what=="ground")
    return FAIL;
    if(what=="grass for herbs"||what=="ground for herbs")
    {
     if(player->query_skill(SS_HERBALISM)>=10)
      {
       if(searched==0)
       {
        seteuid(getuid());
        berry=clone_object("/d/Gondor/common/herbs/attanar");
        berry->move(player);
        set_searched(1);
        return "You find a little blue berry in the grass!\n";
        }
      }
    }
    return FAIL;
}
