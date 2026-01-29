/* created by Aridor 04/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#define TUB_MAX        100000
#define FURNACE_ROOM   THEIWAR + "r21"

object smith;
object iron;
object fblock;
mixed form = 0; 
/* is a form block attached to the second pipe? if so which */
int tub = random(TUB_MAX / 10);

mixed
query_form_block()
{
    return form;
}

void
reset_ld_room()
{
    if (fblock)
      fblock->remove_object();
    if (!fblock)
      if (!random(4))
	{
	    fblock = clone_object(OBJ + "formblock");
	    fblock->set_produced_name("cogwheel");
	    fblock->move(TO);
	}
    if (!iron)
      {
	  iron = clone_object(CAST_IRON);
	  iron->move(TO);
      }
    if (smith)
      return;
    smith = clone_object(LIV + "wep_smith");
    smith->move(TO);
    DOORROOM->add_inhabitant(smith);
}


void
create_ld_room()
{
    set_short("In a smithy");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r21", "north");
    
    add_item(({"anvil"}),
	     "It's a heavy, bulky, piece of metal. Well, a typical anvil " +
	     "to be exact.\n");
    add_item(({"pool","water","pool of water"}),
	     "This is cold water to cool off hot metal.\n");
    add_item(({"tub","metal"}),"@@tub_state@@");
    add_item(({"pipeline","pipelines","pipe","pipes"}),"@@pipeline_state@@");
    add_item(({"wall","walls","rock"}),
	     "The walls are made from rock.\n");
    add_item(({"sign"}),"You can read it.\n");
    add_item(({"fire","hearth"}),"It looks hot enough to melt metal in it.\n");
    add_cmd_item(({"sign"}),"read","You read:\n" +
		 "'Order' your personal weapon here!\n" +
		 "You can 'enquire' or ask the smith about weapons, too.\n" +
		 "Ordered weapons can be 'collect'ed later on.\n");
    
    reset_room();
}


string
my_long()
{
    return "You are standing in a smithy. An anvil is placed in the middle " +
      "of the room and you can see a pool of water in the back. A tub is " +
      "placed at the east wall. A sign is hanging from the ceiling. A fire " +
      "is burning in a hearth" + (smith && E(smith) == TO ? " and in the " +
				  "middle of the room stands a massive " +
				  "dwarf looking you up and down." :
				  ", but apart from that, " +
				  "the room is empty.") + "\n";
}

string
pipeline_state()
{
    string str;
    if (!form)
      str = "simply ends out onto the floor. It seems like something could be connected here";
    else
      str = "has a block of stone connected to it";
    return "They come from out of the wall. One leads into a tub and the " +
      "other " + str + ".\n";
}

void
init()
{
    ADA("hook");
    ADA("plug");
    ADA("connect");
    ADD("unplug","remove");
    ADD("unplug","disconnect");
    ADA("unplug");
    ::init();
}

int
formblock_access(object ob)
{
    if (ob->id("formblock") && !ob->query_prop(OBJ_I_BROKEN))
      return 1;
    return 0;
}

int
unplug(string str)
{
    NF("What?\n");
    if (!form)
      return 0;
    NF(C(query_verb()) + " what?\n");
    if (!form->id(str))
      return 0;
    form->remove_prop(OBJ_M_NO_GET);
    form = 0;
    write("You " + query_verb() + " the formblock from the pipeline.\n");
    say(QCTNAME(TP) + " disconnects the block of stone from the pipeline " +
	"coming out of the wall.\n");
    return 1;
}

int
hook_it(int i, string str1, string str2, string where)
{
    object *the_forms, the_form;
    if (i != 2 || !str1 || !str2)
      return 0;

    the_forms = CMDPARSE_ONE_ITEM(str1,"formblock_access","formblock_access");
    if (!the_forms)
      the_forms = CMDPARSE_ONE_ITEM(str2,"formblock_access","formblock_access");
    if (!the_forms || !sizeof(the_forms))
      return 0;
    the_form = the_forms[0];
    
    if (str2 != "pipe" && str2 != "pipeline" &&
	str1 != "pipe" && str1 != "pipeline")
      return 0;   

    NF("There is only room for one formblock to be connected.\n");
    if (sizeof(the_forms) > 1)
      return 0;

    if (the_form)
      {
	  NF("There is already a formblock connected.\n");
	  if (form)
	    return 0;
	  form = the_form;
	  form->move(TO,1);
	  form->add_prop(OBJ_M_NO_GET, "The block is connected to the pipeline.\n");
	  write("You " + query_verb() + " the formblock " + where + " the " +
		"unconnected pipeline.\n");
	  say(QCTNAME(TP) + " connects the pipeline coming out of the wall with a " +
	      "block of stone.\n");
	  return 1;
      }
    return 0;
}

int
hook(string str)
{
    string str1, str2;
    int i;
    if (!str)
      return 0;
    i = sscanf(str,"%s up to %s", str1,str2);
    NF("Hook what up to where?\n");
    return hook_it(i,str1,str2,"up to");
}

int
plug(string str)
{
    string str1, str2;
    int i;
    if (!str)
      return 0;
    i = sscanf(str,"%s into %s", str1,str2);
    NF("Plug what into where?\n");
    return hook_it(i,str1,str2,"into");
}

int
connect(string str)
{
    string str1, str2;
    int i;
    if (!str)
      return 0;
    i = sscanf(str,"%s with %s", str1,str2);
    NF("Connect what with what?\n");
    return hook_it(i,str1,str2,"with");
}

string
tub_state()
{
    string how_full, txt = "";
    int i;
    if (tub < TUB_MAX / 100)
      how_full = "empty";
    else if (tub < TUB_MAX / 100 * 40)
      how_full = "partly full";
    else if (tub < TUB_MAX / 100 * 60)
      how_full = "about half full";
    else if (tub < TUB_MAX / 100 * 95)
      how_full = "almost full";
    else
      how_full = "about full";
    txt += "The tub is made from stone and is affixed to the wall. It is " +
      "covered with a silvery colored layer with a few golden and copper " +
      "spots on the inside and it is " + how_full + ". ";
    txt += "Some kind of pipeline seems to lead into the tub, " +
      "coming out of the wall.";
    if (!form)
      txt += " Another pipeline simply ends out onto the floor!";
    else
      txt += " A second pipeline has a block of stone attached, into " +
	"which the pipe disappears.";
    return txt + "\n";
}

int
query_tub_state()
{
    return tub;
}

int
overflow_tub(int how_much)
{
    object obj;
    tell_room(TO, "The tub flows over! Hot metal spills onto the floor!\n");

    /* do something nasty here!!! - or let the hot metal object do it :) */

    seteuid(getuid(TO));
    obj = clone_object(OBJ + "liquid_metal");
    obj->set_adj("silvery");
    obj->move(TO);
    obj->set_volume(how_much > 25000 ? 25000 : how_much);
    if (how_much > 25000)
      {
	  tell_room(FURNACE_ROOM,"Liquid metal flows in from the south. " +
		    "It is extremely hot!\n");
	  obj = clone_object(OBJ + "liquid_metal");
	  obj->set_adj("silvery");
	  obj->move(FURNACE_ROOM);
	  obj->set_volume(how_much - 25000);
      }
    
}

/* call this to fill or empty (argument negative)
 * one of the tubs.
 * Returns: negative arg: How much has been removed.
 *          positive arg: -1;
 *                     0: 0;
 */
int
fill_tub(int how_much, string color)
{
/*formblock present? yes: fill block...
                            block full: yes: fill tub...
                                         no: fill block.
                      no: fill tub...
                            tub full? yes: overflow tub
                                       no: fill tub.

*/
    int left = how_much;
    /* don't want anything really? */
    if (how_much == 0)
      return 0;
    /* remove something */
    if (how_much < 0)
      {
	  left = tub;
	  tub -= how_much;
	  if (tub < 0)
	    tub = 0;
	  else
	    left = how_much;
	  return left;
      }
    /* add something */
    if (form && (form->query_full() < form->query_max_fill()))
      {
	  tell_room(TO, "Something seems to run through the pipe into the " +
		    "formblock.\n");
	  left -= (form->fill_me(left, color));
      }
    if (left > 0 && tub < TUB_MAX)
      {
	  tell_room(TO,"The tub fills itself with liquid metal from the " +
		    "pipeline.\n");
	  if (tub + left > TUB_MAX)
	    {
		left -= (TUB_MAX - tub);
		tub = TUB_MAX;
	    }
	  else
	    {
		tub += left;
		left = 0;
	    }
      }
    if (left > 0)
      {
	  overflow_tub(left);
      }
    return -1;
}
