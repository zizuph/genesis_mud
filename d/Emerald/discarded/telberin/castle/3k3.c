/*
 * 3k3.c
 * Entrance room into the Keepers of Telberin hidden headquarters.
 * - Alaron January 1997
 */

#include <composite.h>
#include "default.h"
#include "/d/Emerald/common/guild/kot/guild.h"

#undef NOTIFY_CHANGE

inherit "/std/room";

int do_sit(string str);                // called via add_action
int do_stand(string str);              // called via add_action
string through_arch();

int query_player_seated(object ob);
void force_stand(object ob);

// Allocate 'storage' for players to sit in various places in
// the room.

object cont_chair1;
object cont_chair2;
object *cont_couch = allocate(3);

void
create_room()
{
    set_short("Comfortable study");
    set_long("   You are in a welcoming, comfortable-feeling study. The "+
	     "walls are made of panels of a soft, warm colored mahogany."+
	     " Tall, cedar bookshelves rest snugly against "+
	     "the walls, proudly displaying their widely varying contents "+
	     "of old and new titles. There are two very wide, "+
	     "soft-cushioned chairs facing the east wall, and a long, "+
	     "comfortable-looking couch resting in front of a round "+
	     "table. The table is sporting a collection of contemporary "+
	     "titles of various theme and genre.\n");
  
    add_prop(ROOM_I_INSIDE, 1);

    add_item("east wall",
             "The east wall hosts a dazzling array of knick-knacks "+
	     "and other decorative trinkets on the tops of several "+
	     "bookshelves.  You notice a narrow, inconspicuous archway " +
             "between two shelves; above it there is a large bust with " +
             "a golden placque at its base.\n");

    add_item(({ "arch", "archway" }),
             "A narrow archway leading into a nicely appointed series " +
             "of rooms to the east.\n");

    add_item( ({"walls", "wood walls", "panels", "mahogany", "wood"}),
	     "The walls of this room are paneled with mahogany. The "+
	     "wood is a soft, warm color. The dim amber glow of the "+
	     "room reflects in the lacquered and polished surface "+
	     "of the wooden walls.\n");

    add_item( ({"shelves", "bookshelves", "cedar shelves", "cedar",
		"cedar bookshelves", "tall shelves", "tall bookshelves"}),
	     "Several tall, cedar bookshelves rest snugly against the "+
	     "mahogany walls. Each of the shelves is placed so that it "+
	     "can display its contents to all of the room at once, facing "+
	     "the center of the room. Hundreds of books of all shapes, "+
	     "sizes, age and color are contained within those shelves.\n");

    add_item( ({"chairs", "wide chairs", "soft chairs",
		"soft-cushioned chairs"}),
	     "The soft-cushioned chairs look extremely comfortable. They "+
	     "are stuffed to near overflowing with a very soft "+
	     "material. The cushions themselves are made from a very "+
	     "dark, furry material. It feels like it could be an animal "+
	     "hide, but something about the way it feels tells you that "+
	     "it could be made of something fibrous, perhaps a bi-product "+
	     "of an animal or a plant pulp of some kind.\n");

    add_item( ({"couch", "long couch", "comfortable-looking couch",
		"long comfortable-looking couch"}),
	     "The couch is covered with the same soft, furry material "+
	     "as the chairs. It is long enough to probably support "+
	     "three large people sitting comfortably.\n");

    add_item(({"table", "round table", "collection", "titles", "books"}),
	     "The round table in front of the couch is strategically "+
	     "placed in the middle of the room so that all those seated "+
	     "can easily reach its contents. It is currently sporting "+
	     "a large collection of various titles of several varying "+
	     "genres including history, legend and documentary.\n");

    add_item( ({"knick-knacks", "trinkets"}),
	     "The east wall seems to be host to a collection of small "+
	     "decorative items. There are little statues of mythical "+
	     "creatures, small pictures, glittering glass and jeweled "+
	     "designs and dozens more.\n");

    add_item(({"bust", "large bust"}),
             "The bust is an amazingly detailed carving for its size. It "+
	     "must have taken months, perhaps even years to accomplish "+
	     "this carving. The bust is of a thick-jawed, "+
	     "long-haired male elf. The countenance imprinted on the "+
	     "fine marble is obviously that of a leader of some kind, "+
	     "the gleam of power and confidence can even be seen "+
	     "in this lifeless carving. Peering into the dark eyes "+
	     "of the bust, you are overcome with a feeling of "+
	     "subservience, as if the man depicted by this statue "+
	     "was worthy of such outright worship. There is a golden "+
	     "plaque in the base of the bust.");

    add_item(({"plaque", "golden plaque"}),
             "The golden plaque is plain and unmarked with two exceptions. "+
	     "Centered at the top of the plaque is one word: Telan-Ri.\n"+
	     "In the middle of the plaque there is an imprint. The imprint "+
	     "looks to be about the size and shape of a dagger. The plaque "+
	     "is not riveted to the stone as one might expect. It seems "+
	     "to be a part of the bust. You notice an extremely fine "+
	     "empty space in the stone surrounding the plaque, as if the "+
	     "plaque might have been inserted into a hole in the bust "+
	     "during construction.\n");

    add_my_desc("@@seated_desc@@");

    add_exit(CASTLE_DIR + "3k2", "west");

    add_cmd_item(({ "arch", "archway", "through arch", "through archway" }),
        ({ "enter", "go", "walk" }), through_arch);
}

string
through_arch()
{
    if ((TP->query_guild_name_race() != GUILD_NAME) && !TP->query_wiz_level())
    {
	return "You step up to the archway, and just as you "+
	       "start to pass through, "+
	       "you hear a voice echo through your soul, sending a "+
	       "gut-wrenching feeling of nausea and fear through you:\n"+
	       "\t\"None but my children shall be allowed passage!\"\n"+
	       "\t\"You are tresspassing in their home!\"\n";
    }

    this_player()->move_living("through the archway",
        KOT_ROOM_DIR + "kot_hq1", 1);
    return "";
}
    
// Function to show a composite desc of people sitting down.
string
seated_desc()
{
    string *coucharr;
    int i;

    string couch_desc;
    string chair1_desc;
    string chair2_desc;

    coucharr = ({});

    // save myself some looping time if no one is sitting down.
    if ( !cont_couch[0] && !cont_couch[1] && !cont_couch[2] && 
	!cont_chair1 && !cont_chair2 )
	return "";       

    for (i = 0; i < sizeof(cont_couch); i++)
    {
	if (cont_couch[i]) {
	    if (TP==cont_couch[i])
		coucharr += ({"You"});
	    else {
		if (TP->query_met(cont_couch[i]))
		    coucharr += ({ cont_couch[i]->query_met_name() });
		else
		    coucharr += ({ cont_couch[i]->query_nonmet_name() });
	    }
	}
    }

    if (sizeof(coucharr)) {
	couch_desc = COMPOSITE_WORDS(coucharr) + 
	    (sizeof(coucharr)>1 ? " are" : " is") + " sitting on "+
		"the couch";
	if ((coucharr[0] == "You") && (sizeof(coucharr)==1))
	    couch_desc = "You are sitting on the couch";
    }
    else
	couch_desc = "No one is sitting on the couch";
        
    if (cont_chair1)
    {
	if (TP->query_met(cont_chair1))
	    chair1_desc = cont_chair1->query_met_name();
	else
	    chair1_desc = cont_chair1->query_nonmet_name();
	chair1_desc += " is sitting in the light brown chair";
	
	if (TP==cont_chair1)
	    chair1_desc = "You are sitting in the light brown chair";
    } 
    else 
	chair1_desc = "";
    
    if (cont_chair2)
    {
	if (TP->query_met(cont_chair2))
	    chair2_desc = cont_chair2->query_met_name();
	else
	    chair2_desc = cont_chair2->query_nonmet_name();
	chair2_desc += " is sitting in the dark brown chair";
	
	if (TP==cont_chair2)
	    chair2_desc = "You are sitting in the dark brown chair";
    } 
    else
	chair2_desc = "";

    return couch_desc + (chair1_desc!=""?", ":"")+chair1_desc+(chair2_desc!=""?", ":"")+chair2_desc+".\n";
}

int
through_door()
{
    if(TP->query_guild_name_race() != GUILD_NAME)
      {
	write("You step up to the gap in the east wall and just as you "+
	  	"start to turn your shoulders to slide through, "+
		"you hear a voice echo through your soul, sending a "+
		"gut-wrenching feeling of nausea and fear through you:\n"+
	      "\t\"None but my children shall be allowed passage!\"\n"+
	      "\t\"You are tresspassing in their home!\"\n");
	return 1;
      }

    return 0;
}

void
init()
{
    ::init();
    add_action(do_sit, "sit");
    add_action(do_stand, "stand");
    add_action(do_stand, "rise");
}

int 
do_stand(string str)
{
    if (!query_player_seated(TP))
    {
	notify_fail("You're not sitting down.\n");
	return 0;
    }

    force_stand(TP);
    return 1;
}

int
query_player_seated(object player)
{
    if ((player == cont_chair1) ||
	(player == cont_chair2) ||
	(member_array(player, cont_couch)!=-1))
	return 1;
    else
	return 0;
}

int
do_sit(string str)
{
    int slot;
    int j;

    if (!str) return 0;

    if ( (member_array(str, ({"in chair", "chair", "on chair", 
			  "in a chair"})))!=-1)
    {
	if (query_player_seated(TP))
	{
	    notify_fail("You are already sitting down.\n");
	    return 0;
	}
	if (!cont_chair1)
	{
	    write("You take a seat in the light brown cushioned chair.\n");
	    say(QCTNAME(TP)+" takes a seat in one of the cushioned chairs.\n");
	    cont_chair1 = this_player();
	    this_player()->set_no_show_composite(1);
	    return 1;
	}
	if (!cont_chair2)
	{
	    write("You take a seat in the dark brown cushioned chair.\n");
	    say(QCTNAME(TP)+" takes a seat in one of the cushioned chairs.\n");
	    cont_chair2 = this_player();
	    this_player()->set_no_show_composite(1);
	    return 1;
	}
	notify_fail("There are no empty chairs in which to sit.\n");
	return 0;
        
    }  // player wanted to sit in a chair.

    if ( (member_array(str, ({"couch", "on couch", "in couch", 
			      "on the couch", "down"})))!=-1)
    {
	if (query_player_seated(TP))
	{
	    notify_fail("You are already sitting down.\n");
	    return 0;
	}

	slot = -1;

        for (j=0; j < sizeof(cont_couch); j++)
	{
	    if (!cont_couch[j])
		slot = j;
	}

	if (slot == -1)
	{
	    notify_fail("The couch is full.\n");
	    return 0;
	}
	cont_couch[slot] = this_player();
	write("You take a seat on the couch.\n");
	say(QCTNAME(TP)+" takes a seat on the couch.\n");
	TP->set_no_show_composite(1);
	return 1;
    }

    notify_fail("Where are you trying to sit?\n");
    return 0;
}

void
force_stand(object ob)
{
    int index;

    ob->catch_msg("You stand up and stretch slightly after your period "+
		  "of relaxation.\n");
    tell_room(this_object(), QCTNAME(ob)+" stands up and stretches "+
	      "slightly.\n", ob);
    if (TP == cont_chair1)
	cont_chair1 = 0;
    if (TP == cont_chair2)
	cont_chair2 = 0;
    if ( (index=member_array(ob, cont_couch))!=-1)
	cont_couch[index] = 0;

    ob->unset_no_show_composite(1);  // show them back in composite descs.
}

public void
leave_inv(object ob, object to)
{
    if (query_player_seated(ob))
	force_stand(ob);
    ::leave_inv(ob, to);
}

#ifdef NOTIFY_CHANGE
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob) && ob->query_kot_member() &&
        (file_name(from) != (KOT_ROOM_DIR + "kot_hq1")))
    {
        set_alarm(0.0, 0.0,
            &ob->catch_tell("Looking about, you notice that the room has " +
                "been changed recently:  where the fireplace once stood, there " +
                "is now a narrow archway.\n"));
    }
}
#endif
