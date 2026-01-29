inherit "/d/Gondor/lorien/lorien";
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <cmdparse.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"
#define ROOM_AS_DRINK_WHERE  ({ "Celebrant", "Silverlode", "stream", "river", "water" })
#include "/d/Gondor/common/lib/drink_water.h"
#define OTHER_ROOM  (LORIEN_DIR + "paths/e_cel_ford")
#define DUMMY    (LORIEN_DIR + "paths/dummy")
#define LORIEN_DUMMY_ROPE  "_lorien_dummy_rope"
#define LORIEN_ROPE_THROWN  "_lorien_rope_thrown"
#define LORIEN_ROPE_END    "_lorien_rope_end"

object  tied_rope;
object  dummy_rope;
int     thrown_over = 0;
int     cur_alarm;

void throw_over(object *arr);
void throw_rope_over(object rope);

void
create_lorien_room()
{
    loc = 9; 
    set_short_desc("by the west bank of the Silverlode");
    set_show_time();
    extraline = "The Celebrant flows past, running both swift and " +
      "strong. The water looks silvery cold, and it does not seem " +
      "crossable here. Along the banks on both sides the great mallorn " +
      "trees are growing, casting their shadows on the silvery water. " +
      "A path leads into the woods to the northwest.";
    add_item(({"water","river","stream","celebrant","silverlode"}),BSN(
      "The Silverlode runs past here as a strong stream, deep and swift, "
      + "and with its water cold from the mountains. It does not seem "
      + "possible to cross, as you cannot set foot in such cold water."));
    add_item(({"thicket","thickets"}),BSN("There are thickets along the "
      + "bank, of young mallorn trees."));
    add_exit(LORIEN_DIR + "paths/n_path1","northwest",0);
    add_exit(OTHER_ROOM, "east", "@@cross_river");
    set_noshow_obvious(1);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!living(ob)) return;
    if (!objectp(from)) return;
    if (from == find_object(OTHER_ROOM)) return;
    if (ob->query_prop(OBJ_I_HIDE)) return;
    tell_room(OTHER_ROOM, "Across the river you notice " +
        QNAME(ob)+" appearing from the thickets by the bank.\n");
}

int
test_ropes_connect()
{
    if (dummy_rope)
    {
        if (dummy_rope->query_prop(LORIEN_DUMMY_ROPE) == OTHER_ROOM->query_tied_rope())
            return 1;
        return 0;
    }
    if (tied_rope)
    {
        if (tied_rope == OTHER_ROOM->query_tied_rope()->query_prop(LORIEN_DUMMY_ROPE))
            return 1;
        return 0;
    }
    return 0;
}

string
describe()
{
    string tot_txt;
    tot_txt = ::describe();
    if (test_ropes_connect())
        tot_txt += "Across the river, "+LANG_ADDART(tied_rope->query_name())
          + " has been stretched, allowing the possibility to "
          + "balance across. ";
    return tot_txt;
}

int
cross_river()
{
    if (test_ropes_connect())
    {
        write(BSN("You balance across the Silverlode on "
          + "the "+tied_rope->query_name()+" that has been stretched "
          + "across the stream."));
        say(QCTNAME(TP)+" balances on the "+tied_rope->query_name()+" across the "
          + "Silverlode.\n", TP);
        tell_room(OTHER_ROOM, QCNAME(TP)+" comes balancing across the river on the "
          + tied_rope->query_name()+" that has been stretched across.\n");
        return 0;
    }
    write(BSN("No, you decide not to try wading across. " +
      "The Celebrant is deep, the current strong, and the water cold."));
    return 1;
}

int
tie_object(object rope, string str)
{
    NF("You cannot tie anything to the "+str+".\n");
    if(!str || (str != "branch" && str != "tree branch" && str != "tree"
        && str != "trunk" && str != "mallorn"))
        return 0;
    NF("There is already "+LANG_ADDART(tied_rope->query_name())+
      " tied to the "+str+".\n");
    if(objectp(tied_rope))
        return 0;
    
    tied_rope = rope;
    if (OTHER_ROOM->query_tied_rope())
        if (OTHER_ROOM->query_tied_rope() == rope->query_prop(LORIEN_DUMMY_ROPE))
        {
            TO->remove_my_desc(OTHER_ROOM);
            dummy_rope = rope;
        }
    return 1;
}

int
pull_rope_back(object rope)
{
    if (OTHER_ROOM->query_tied_rope() == rope)
    {
        cur_alarm = set_alarm(15.0,0.0,"current_pull",rope);
        NFN0("The rope appears to be stuck or tied to something on " +
          "the other side of the river.");
    }
    rope->remove_prop(LORIEN_ROPE_THROWN);
    tell_room(OTHER_ROOM, "Suddenly, someone on the other side pulls the " +
      rope->query_name()+" back.\n");
    write("Ok.\n");
    SAY(" pulls the "+rope->query_name()+" back.\n");
    thrown_over = 0;
    OTHER_ROOM->remove_my_desc(TO);
    OTHER_ROOM->remove_item(rope->query_name());
    return 1;
}

int
untie_object(object rope)
{
    if (rope != tied_rope)
        return 0;
    if (rope == dummy_rope)
    {
        thrown_over = 0;
        dummy_rope = 0;
        OTHER_ROOM->current_pull(OTHER_ROOM->query_tied_rope());
    }
    if(thrown_over)
    {
        pull_rope_back(rope);
    }
    tied_rope = 0;
    return 1;
}

void
init()
{
    ::init();
    add_action("do_throw","throw");
    add_action("do_pull","pull");
    add_action("drink_water","drink");
}

int
do_pull(string str)
{
    string  vb = query_verb(),
            dummy,
            what;
    object *ob;

    NF(CAP(vb) + " what?\n");
    if(!str)
        return 0;
find_player("ratard")->catch_msg(sprintf("%O %O\n", tied_rope, thrown_over));

    if(!objectp(tied_rope) || !thrown_over)
        return 0;
    
    if(tied_rope->id(str))
        what = str;
    else if(sscanf(str,"at %s",dummy) == 1)
        what = dummy;
    else if(sscanf(str,"%s back",dummy) == 1)
        what = dummy;
    else
        return 0;

    if(!sizeof(ob = FIND_STR_IN_OBJECT(what, ENV(TP))))
        return 0;

    if(ob[0] != tied_rope)
        return 0;

    pull_rope_back(tied_rope);
    return 1;
}

int
do_throw(string str)
{
    string  vb       = query_verb(),
            what,
            dir;
    object *ob;
    int     diff,
            result;
    mixed   msg;

    NF(CAP(vb) + " what?\n");
    if(!str)
        return 0;

    NF(CAP(vb) + " what into which direction?\n");
    if(sscanf(str,"%s acros%s", what, dir) != 2 && sscanf(str,"%s eas%s", what, dir) != 2)
        return 0;

    NF(CAP(vb) + " what?\n");
    if(!sizeof(ob = FIND_STR_IN_OBJECT(what, TP)))
        if(!sizeof(ob = FIND_STR_IN_OBJECT(what, ENV(TP))))
            return 0;

    if(msg = ob[0]->query_prop(OBJ_M_NO_DROP))
    {
        if( (function_exists("create_object", ob[0]) != "/std/rope") ||
            (!objectp(ob[0]->query_tied_to())) || (ob[0] != tied_rope) )
        {
            if(stringp(msg))
                NF(msg);
            else
                NF("You cannot throw away the "+ob[0]->query_name()+"!\n");
            return 0;
        }
    }
    if (ob[0] == dummy_rope)
        NFN0("No, that rope is securely tied to the " +
          ob[0]->query_tied_to_text()+".");

    if (ob[0]->query_prop(LORIEN_ROPE_THROWN))
    {
        NF("It is already thrown across.\n");
        return 0;
    }

    diff = ob[0]->query_prop(OBJ_I_WEIGHT) / 60;

    if(diff/10 > TP->query_fatigue())
    {
        NF("You are too tired.\n");
        return 0;
    }

    write("You throw the "+ob[0]->query_name()+" across the river.\n");
    SAY(" throws the "+ob[0]->query_name()+" across the river.");

    ob[0]->add_prop(LORIEN_ROPE_THROWN, 1);

    TP->add_fatigue( - diff/20 );

    if(!msg)
    {
        ob[0]->move(DUMMY);
        set_alarm(4.0, 0.0, &throw_over(({TP, ob[0]})));
    }
    else
    {
        if(ob[0]->query_length() < 2000)
        {
            NF("The "+ob[0]->short()+" is too short.\n");
            return 0;
        }
    /* is rope tied in here */
        set_alarm(2.0, 0.0, &throw_rope_over(ob[0]));
    }
    return 1;
}

void
throw_over(object *arr)
{
    object  player   = arr[0],
            thrown   = arr[1];

    tell_room(OTHER_ROOM, CAP(LANG_ADDART(thrown->short())) 
      + " lands on the riverbank before you.\n");
    thrown->move(OTHER_ROOM);
}

void
throw_rope_over(object rope)
{
    object rope_end;
    FIX_EUID
    rope_end = clone_object(MASTER_OB(rope));
    rope_end->set_length(rope->query_length());
    rope_end->add_prop(LORIEN_DUMMY_ROPE, rope);
    rope->add_prop(LORIEN_ROPE_END, rope_end);
    rope_end->move(OTHER_ROOM);
    thrown_over = 1;
    tell_room(OTHER_ROOM,BSN(
      "From the other side of the Silverlode, " +QTNAME(TP) +
      " throws the end of "+LANG_ADDART(rope->query_name())+" across."));
    OTHER_ROOM->change_my_desc(CAP(LANG_ADDART(rope->query_name()))+
      " is stretched loosely across the river, floating in the water "+
      "surface, the end slowly being pulled off the bank by the currents.\n");
    OTHER_ROOM->add_item(rope->query_names(),BSN(
        "The "+rope->query_name()+" is hanging down from a tree on the other "+
        "bank, but the end on this side is still loose, and the part of the "+
        "rope that rests in the water is slowly being pulled by the currents."));
    cur_alarm = set_alarm(15.0,0.0,"current_pull",rope);
}

void
current_pull(object rope)
{
    object other_rope, rope_end;
    other_rope = OTHER_ROOM->query_tied_rope();
    rope_end = rope->query_prop(LORIEN_ROPE_END);
    if (objectp(other_rope))
        if (rope_end == other_rope)
        {
            OTHER_ROOM->remove_item(rope->query_name());
            OTHER_ROOM->remove_my_desc(TO);
            return;
        }
    /* The rope is not thrown over anyway, so the current does not pull it*/
    if (!thrown_over) 
        return;
    /* The rope has been tied in the other end, but not here! */
    if (!tied_rope && (OTHER_ROOM->query_tied_rope() == rope_end))
    {
        OTHER_ROOM->current_pull(rope);
	     rope->move(OTHER_ROOM);
      rope_end->remove_object();
        return;
    }
    if (rope != tied_rope && (OTHER_ROOM->query_tied_rope() != rope))
    {
        if ((ENV(rope) == TO) || (ENV(rope) == OTHER_ROOM))
	{
	    tell_room(ENV(rope), BSN("The "+rope->query_name()+" is pulled " +
              "away by the swift currents of the Silverlode, as it was " +
              "not tied to anything."));
        if (rope_end) rope_end->remove_object();
            rope->remove_object();
	}
        thrown_over = 0;
        return;
    }
    /* The rope is tied here, but not on the other side. Current pulls. */
    thrown_over = 0;
    tell_room(OTHER_ROOM, BSN("The swift currents of the Silverlode pulls " +
      "at the rope that was thrown across, and the end of the rope finally " +
      "slips into the water."));
    tell_room(TO, BSN("It seems that nobody tied up the other end of the " +
      rope->query_name()+", for the Silverlode is now tugging at it, "+ 
        "the length of it now hanging downstream."));
    OTHER_ROOM->remove_item(rope->query_name());
    OTHER_ROOM->remove_my_desc(TO);
    rope_end->remove_object();
    rope->remove_prop(LORIEN_ROPE_END);
}

int query_thrown_over() { return thrown_over; }

object query_tied_rope() { return tied_rope; }

object query_dummy_rope() { return dummy_rope; }


