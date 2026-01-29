#pragma save_binary
#pragma strict_types

#include <language.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE;

#define PIPE_ID   "_shire_office_pipe"
#define PIPE      "/d/Shire/common/office_stuff/pipe"
#define SIT_PROP  "_i_an_sitting_on_chair"

void
create_tower_office()
{
    set_short("A peculiar hobbit hole");
    set_long("This looks like a typical hobbit dwelling that "+
      "one might find within the Shire.  The floor is decorated with "+
      "a varity of throw rugs and the walls are decorated with a few "+
      "paintings.  There is a table with chairs of different sizes for "+
      "when big folk drop in to visit.  A dense smoke hangs "+
      "around the ceiling and a strange aura fills the room. "+
      "You notice some runes affixed on one of the walls of this "+
      "smial.\n");    
    add_item(({"floor","rug","rugs","throw rugs","throw rug"}),
      "Various coloured rugs are scattered across the floor, adding "+
      "a deep richness to the room.\n");
    add_item(({"chair","chairs"}),
      "They look quite comfortable, perhaps you'd like to sit down "+
      "on one and relax.\n");
    add_item("table","A large table, that could probably hold enough "+
      "food on it for an army.  Unfournuately it is bare at the moment.\n");
    add_item("smoke","A sweet smelling smoke fills the air.\n");
    add_item(({"arua","strange arua"}),
      "This smial is filled with a strange arua of magic..  rather "+
      "peculiar for a hobbit dewelling.\n");

    add_item(({"walls","pictures"}),"@@pictures@@");

    add_item("runes","Perhaps you should read them?\n");
    add_cmd_item("runes","read","@@my_sign@@");

    set_project_path("/d/Shire/open/projects/");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK,1);

    add_tower_link("out");
}

string
my_sign()
{
    return "You read the runes:\n\n"+
    "You have the following two commands at your disposal.\n"+
    "wizards                  - Lists the wizards of the Shire.\n"+
    "projects <shire/wizard>  - The projects of the Shire/wizard.\n";
}

// Eventually We'll show actual rooms in the Shire when you examine this.
string
pictures()
{
    return "Your are unable to make out what these pictures are indeed "+
      "supposed it be.  They seem to take the form of one shape and then "+
      "a few seconds later they shift and become an enitirely different "+
      "one.\n";
}


void
init()
{
    ::init();
    add_action("do_sit","sit");
    add_action("do_out","out");
    add_action("do_stand","stand");
    add_action("do_stand","rise");
}

int
do_sit(string str)
{
    if (!str || str != "chair" && str != "on chair" && str != "in chair")
    {
        NF("Sit on what?\n");
	return 0;
    }
    if (TP->query_prop(SIT_PROP))
    {
        NF("But you are already sitting one of the chairs!\n");
	return 0;
    }
    TP->add_prop(SIT_PROP,1);
    write("You grab yourself a chair and sit down upon it.\n");
    say(QCTNAME(TP) + " grabs "+HIM_HER(TP)+"self a chair "+
	"and sits down upon it.\n");
    return 1;
}

int
do_out(string str)
{
    if (TP->query_prop(SIT_PROP) && !str)
    {
        write("You'll have to stand up before you can leave "+
	      "this room.\n");
	return 1;
    }
    return 0;
}

int
do_stand(string str)
{
    if (str != "up" && str != "from chair")
    {
        NF(CAP(query_verb())+" how?\n");
	return 0;
    }
    if (!TP->query_prop(SIT_PROP))
    {
        NF("But your not sitting on the chair!\n");
	return 0;
    }
    TP->remove_prop(SIT_PROP);
    write("You "+query_verb()+" from your chair.\n");
    say(QCTNAME(TP) + " "+query_verb()+"s from "+HIS_HER(TP)+" chair.\n");
    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (!interactive(ob))  //  Not a player so we ignore them 
	return;
    if (!present(PIPE_ID,ob))
    {
        ob->catch_tell("In a blinding flash of magic you find yourself "+
	    "within a mysterious hobbit hole and within your clutched hand "+
	    "a pipe has somehow appeared.\n");
	setuid(); seteuid(getuid());
	clone_object(PIPE)->move(ob);
    }
}

public void
leave_inv(object ob, object to)
{
    object pipe;

    ::leave_inv(ob,to);
    if (!interactive(ob))
        return;
    if (pipe = present(PIPE_ID,ob))
	pipe->remove_object();
    ob->catch_tell("In another flash of blinding magic you find yourself "+
	"back within the Tower of Realms.\n");
}
