#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <language.h>
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>


#define DESK_SUBL "desk_subloc"

object frustum, cabinet;

public int library_exit_block();
public void sit_down(string subloc);

void
create_vamp_room()
{
    object desk, scroll, crib;
    string subl;
    int i;

    set_short("A study");
    set_em_long("This cavern seems to be dedicated to the"
        + " study of knowledge. A desk of great antiquity rests near"
        + " the back wall beside a dust-coated painting which has been"
        + " mounted there.\n");

    add_item( ({ "painting", "dust-coated painting" }),
        "The painting is coated with a great deal of dust and does"
      + " not appear to have been cleaned in centuries. It depicts"
      + " the image of a fearsome wraith, clad all in black, standing"
      + " atop a mounded pile of ashes.\n");
    add_item( ({ "wraith", "fearsome wraith" }),
        "The image of the wraith is both fearsome and poignant. Somehow,"
      + " the image conveys a great sense of loss and waste, as if"
      + " the wraith itself is the victim in the scene.\n");
    add_item( ({ "ashes", "pile", "mounded pile", "pile of ashes",
                 "mounded pile of ashes" }),
        "The ashes in this painting seem to represent lost opportunity,"
      + " and the ruination of once great things.\n");
    add_item( ({ "background" }),
        "The background of the painting is very dim. The vague image"
      + " of a few figures seems visible.\n");
    add_item( ({ "figures" }),
        "One of the figures in the background seems unmistakably"
      + " orc-like.\n");
    add_item( ({ "orc", "goblin" }),
        "As you look at the figure, you notice that the image"
      + " suddenly becomes very clear. It is a wraith, and yet not"
      + " human ... it is something much different. It is impossible"
      + " to tell if this be he or she, and you realize that you gaze"
      + " upon the image of a neuter goblin. With growing horror, you"
      + " behold the cloak, which has parted to reveal not one, but"
      + " two glowing red eyes - one in the region of the face, and"
      + " the other ... \n\nLightning strikes suddenly outside, and"
      + " you hear the tortured cry of an owl in the distance:"
      + " 'Chmeeeeeeee .... Chmeeeeeeee ....' \n");

    add_exit("crypt", "north", library_exit_block);

    frustum = clone_object(VAMP_OBJ_DIR + "frustum");
    frustum->move(this_object(), 1);
    frustum->set_no_show_composite(1);

    cabinet = clone_object(VAMP_OBJ_DIR + "scroll_cabinet");
    cabinet->move(this_object(), 1);
    cabinet->set_no_show_composite(1);

//  crib = clone_object("/w/gorboth/crib");
//  crib->move(this_object(), 1);


    for (i = 0; i < 4; i++)
    {
	subl = DESK_SUBL + (i + 1);
	add_subloc(subl, this_object());
	desk = clone_object(VAMP_OBJ_DIR + "desk");
	desk->move(this_object(), subl);
	desk->set_no_show_composite(1);
    }

    add_my_desc(capitalize(LANG_ASHORT(frustum)) + " stands at the center " +
        "of the cavern.\n", frustum);
    add_my_desc(capitalize(LANG_ASHORT(cabinet)) + " stands near the wall.\n",
        cabinet);

}

public int
library_exit_block()
{
    if (cabinet->library_exit_block())
    {
        write("You cannot leave with a library book!\n");
        return 1;
    }

    return 0;
}

public int
sit(string str)
{
    mixed *oblist;

    if (!parse_command(str, all_inventory(), "[down] [at] [the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        if (!parse_command(str, ({}), "[down] [at] 'table' %w", str) ||
            (member_array(str, query_sublocs()) < 0))
	{
            notify_fail("Sit where?\n");
	    return 0;
	}
    }
    else if (sizeof(oblist) > 1)
    {
        notify_fail("You can only sit at one desk at a time.\n");
        return 0;
    }
    else
    {
        str = oblist[0]->query_subloc();
    }

    sit_down(str);
    return 1;
}

public int
stand(string str)
{
    string subloc;

    if (subloc = this_player()->query_subloc())
    {
        write("You stand up from the desk.\n");
        say(QCTNAME(this_player()) + " stands up from "+
            this_player()->query_possessive()+" desk.\n");
        this_player()->move(this_object());
	return 1;
    }

    notify_fail("You are not sitting!\n");
    return 0;
}


void
sit_down(string str)
{
    if ((this_player()->query_subloc()))
    {
        write("You are already sitting at a desk.\n");
    }
    else
    {
        this_player()->move(this_object(), str);
        write("You sit down at a desk.\n");
        say(QCTNAME(this_player()) +" sits down at a desk.\n");
    }
}

public string
show_subloc(string subloc, object ob, object for_obj)
{
    object *livings = FILTER_LIVE(subinventory(subloc));
    int i;
    string *names;

    if (sizeof(livings))
    {
        if ((i = member_array(for_obj, livings)) >= 0)
	{
	    names = ({ "You" });
	    livings = exclude_array(livings, i, i);
	}
	else
	{
	    names = ({});
	}

	names += map(livings, &->query_the_name(for_obj));
        return capitalize(COMPOSITE_WORDS(names)) +
            (((sizeof(names) == 1) && (names[0] != "You")) ? 
            " is " : " are ") + "sitting at a writing desk.\n";
    }

    return "";
}


public int
subloc_access(string sloc, object ob, string acs, object for_obj)
{
    return 0;
}

void
init()
{
    ::init();
    add_action(sit, "sit");
    add_action(stand, "stand");
}
