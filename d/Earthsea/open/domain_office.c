inherit "/d/Genesis/start/human/town/tower_office.c";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Genesis/start/human/town/tower.h"

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"


#define BOOK "/d/Earthsea/obj/red_book"
#define TO this_object()
#define CHAIR_O_OCCUPIED "_chair_o_occupied"
#define EXTRA " sitting in the chair, looking very comfortable"
#define SITOB "/d/Earthsea/obj/sit_ob"

object book, sit_ob;


int sit_down(string str);
int stand_up(string str);
string who_sitting();

void
create_tower_office()
{

    set_short("Earthsea Domain Office");
    set_long(break_string("A fire crackling in a large "+
	"stone hearth welcomes you into the living room of this "+
	"cottage. There is no one around, "+
	"yet you have the feeling that someone has just stepped out "+
	"and will soon return. A glazed window looks out onto the "+
	"wintry dark night, and you see snow falling wet against the "+
	"window pane. Inside it is much warmer, and the scent of "+
	"the dried herbs that hang in clusters from the rafters "+
	"blends with the scent of applewood burning in the hearth. "+
	"Among the sparse furnishings there is a low wooden table "+
	"standing close to a large comfortable chair. There is a "+
	"book on the table. "+
	"Beside the oak door a staff carved from yew wood leans "+
	"against the wall."+
	"\n", 70));

    add_item((({"chair", "large chair", "comfortable chair"})),
      "The chair is cushioned and large, although it is "+
      "only large enough for one person to sit in very comfortably. "+
      "It has a footrest where you can prop up your feet."+
      "@@who_sitting");
    add_item((({"hearth", "fire", "stone hearth", "applewood"})),
      "Small logs of applewood burn in the hearth, making the "+
      "room warm, light, and fragrant.\n");
    add_item((({"window", "glazed window", "window pane"})),
      "You look through the window and see large wet snowflakes "+
      "falling against it silently. "+
      "Beyond the night is dark and wintry.\n");
    add_item((({"staff", "yew staff"})), "It might be a wizard's "+
      "staff that waits for its master's return.\n");
    add_item((({"table", "wooden table", "low wooden table"})),
      "A small oaken table stands by the chair. You notice a red "+
      "leather bound book lying upon it.\n");
    add_item((({"herbs", "dried herbs"})),
      "Among the dried herbs that hang in clusters from the rafters "+
      "you notice what looks like mint, moly, white hallows, and "+
      "abundant quantities of rushwash leaves.\n");


    set_tell_time(230);
    add_tell("Flames on the hearth cast shadows around the "+
      "room.\n");
    add_tell("Snow falls silently against the "+
      "window pane.\n");

    setuid();
    seteuid(getuid(TO));
    book = clone_object(BOOK);
    book->move(TO);

    add_tower_link("tower");
    set_project_dir("/d/Earthsea/open/projects/");
    add_office_sign();
    disable_logged_in_display();

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}


void
init()
{
    ::init();
    add_action(&sit_down(), "sit");
    add_action(&stand_up(), "stand");
}

string
who_sitting()
{

    object sp, tp;
    string str;

    sp = TO->query_prop(CHAIR_O_OCCUPIED);
    tp = this_player();

    if (sp == tp)
	return " You are sitting in the chair.\n";

    if (!objectp(sp))
	return "\n";

    if (!tp->query_met(sp))
	return " " + capitalize(LANG_ADDART(sp->query_nonmet_name())) +
	" is sitting in the chair, looking very comfortable.\n";

    return " " + capitalize(sp->query_met_name()) +
    " is sitting in the chair, looking very comfortable.\n";

}

int
sit_down(string str)
{
    object tp = this_player();

    notify_fail("Sit how/where?\n");

    if (objectp(query_prop(CHAIR_O_OCCUPIED)))
    {
	tp->catch_msg("The chair is occupied, so you will "+
	  "have to stand.\n");
	return 1;
    }

    if (str != "on chair" && str != "down on chair" &&
      str != "in chair")
	return 0;

    tp->catch_msg("You sit down on the chair, propping up your "+
      "feet.  Ahhh...\n");
    tell_room(TO, QCTNAME(tp) + " sits down on the chair, "+
      "propping up " + tp->query_possessive() + " feet on the "+
      "footrest.\n", ({tp}));
    tp->change_prop(LIVE_S_EXTRA_SHORT, EXTRA);
    TO->add_prop(CHAIR_O_OCCUPIED, tp);

    setuid();
    seteuid(getuid(TO));
    sit_ob = clone_object(SITOB);
    sit_ob->move(tp);

    return 1;
}

void
leave_inv(object ob, object to)
{

    object sitob;

    ::leave_inv(ob, to);
    // if player leaves the room, remove sit props

    if (interactive(ob))
    {
	if (ob->query_prop(LIVE_S_EXTRA_SHORT) == EXTRA)
	{
	    ob->change_prop(LIVE_S_EXTRA_SHORT, "");
	    TO->remove_prop(CHAIR_O_OCCUPIED);
	    sitob = present("sit_ob", ob);
	    if (objectp(sitob))
		sitob->remove_object();
	}
    }
}

int
stand_up(string str)
{
    object tp = this_player();
    object sitob;

    notify_fail("Do you mean stand up?\n");

    if (tp != TO->query_prop(CHAIR_O_OCCUPIED))
    {
	write("But you are already standing up!\n");
	return 1;
    }

    if (str != "up" && str != "up from chair")
	return 0;

    tp->catch_msg("You stand up from the chair, feeling refreshed.\n");
    tell_room(TO, QCTNAME(tp) + " stands up from the chair.\n",
      ({tp}));
    tp->change_prop(LIVE_S_EXTRA_SHORT, "");

    sitob = present("sit_ob", tp);
    if (objectp(sitob))
	sitob->remove_object();
    TO->remove_prop(CHAIR_O_OCCUPIED);
    return 1;
}

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Earthsea");
        quest_orb->set_extra_line("The orb rests on the table beside"
          + " a red leather-bound book.");
        quest_orb->move(this_object(), 1);
    }    
} /* reset_room */
