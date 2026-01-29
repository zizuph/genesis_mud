inherit "/d/Rhovanion/lib/room.c";
#include <macros.h>
#include <stdproperties.h>

nomask void
create_room()
{
   set_short("Hazelnut's library");
   set_long("This is Hazelnut's library. "+
      "There is a gorgeous Ishvahan rug on the floor, and a jet "+
      "black ebony desk in the corner.  There are black library "+
      "shelves full of books, scrolls and maps.  A painting adorns the "+
      "north wall;  it looks quite hideous. "+
      "There is a comfortable looking black leather chair here and a "+
      "Black Dragonskin chesterfield. \n\n");

   add_exit("/d/Rhovanion/workroom", "rhovanion");
   add_exit("/d/Rhovanion/common/mirkwood/mirk-2-10", "mirkwood");

/*
    create_lock("/d/Rhovanion/hazelnut/private/workroom");
*/

   add_item(({ "painting", "oil painting" }),
	"It is a wonderful oil painting created by an Old Master.  " +
        "It depicts the Legions of Evil slaughtering the Forces of Good "+
	"in a Battle at the Fords of Isen.  Maybe that is why Hazelnut "+
        "was able to get it so cheaply!\n");

    add_item(({"chair", "leather chair" }),
        "It is made of the finest tooled black leather you have ever seen.\n" +
        "It looks extremely comfortable. \n");

    add_prop(ROOM_M_NO_TELEPORT,
	     "That is not the correct way of getting there.\n");
    add_prop(ROOM_I_NO_EXTRA_DESC, 1);
    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
    add_prop(ROOM_I_NO_EXTRA_ITEM, 1);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(OBJ_S_SEARCH_FUN, "search_chair");
   add_prop(OBJ_I_SEARCH_TIME, 1);

    set_lock();
}
 
nomask void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
}

string
search_chair(object searcher, string str)
{
  if(str == "chair" || str == "the chair")
    {
      say(QCTNAME(this_player()) + " searches the chair.  \n");
      return("You do not think that sitting here is a good idea. \n");
    }

}

nomask void
init()
{
	::init();
	add_action("my_sit", "sit");
}

int
my_sit(string str)
{
	notify_fail("Sit on what?\n");
	if (!str)
		return 0;
	if (str!="chair" && str!="on chair" && str!="on the chair" && str!="on my chair" && str!="my chair" && str!="the chair")
		return 0;

	if (this_player()->query_real_name()=="hazelnut")  {
		write("You sit in your comfortable chair!\n");
		say(QCTNAME(this_player()) + " sits in " +
		  this_player()->query_possessive() + " chair.\n");
		return 1;
	}

	this_player()->set_hp((this_player()->query_hp()/2)-10);
	write("Ouch!  The chair gives you a nasty shock!\n");
	say(QCTNAME(this_player()) + " tried to sit on the chair, but " +
	  this_player()->query_pronoun() + " got a nasty shock!\n");
	return 1;
}
