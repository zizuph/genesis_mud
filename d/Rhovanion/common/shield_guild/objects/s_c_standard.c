inherit "/std/object";
inherit "/cmd/std/command_driver";
inherit "/d/Rhovanion/common/shield_guild/objects/s_c_ranks";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#define SUBLOC_STANDARD "_s_c_standard_subloc"
#define CHEER    ONE_OF_LIST(({"cheer","bounce","applaud",\
			       "shout ANGMAR ! ANGMAR !! ANGMAR !!!"}))

int is_shown;

void
create_object()
{
  set_name(({"standard","angmar","Angmar","flag"}));
  set_adj(({"red","and","black","standard","of","angmar","Angmar"}));
  set_short("standard of Angmar");
  set_long("@@my_long");
  
  add_item("flag", "@@my_long");
  add_item(({"pole","long pole"}), "It is a simple long wooden pole "+
               "that bears the flag on its end. You also notice that there "+
               "is <help AA standard> written on it.\n");


  add_prop(OBJ_I_WEIGHT,100);
  add_prop(OBJ_I_VOLUME,100);
  add_prop(OBJ_M_NO_SELL,"You would never sell the standard of Angmar.\n");
  add_prop(OBJ_M_NO_DROP,"You decide to keep the standard.\n");

}

string
my_long()
{
  if(is_shown)
    return "It is the red and black flag on a long pole. It bears the "+
		"symbol of a Dunedain head on a black shield being "+
		"smashed in by a heavy mace.\n";
  return "It is the red and black flag neatly rolled around a long pole.\n";
}

void
init()
{
    ::init();
    add_action("hide","hide");
    add_action("hide","roll");
    add_action("unroll","unroll");
    add_action("wave","wave");
    add_action("plant","plant");
    add_action("raise","raise");
    add_action("lower","lower");
    add_action("rally","rally");
    add_action("help","help");
}

int
help(string str)
{
  string *arr, sss;

  if(!str || (str != "AA standard")) return 0;

  write("The standard provides the following emotes:\n"+
        "   unroll standard\n"+
        "   hide standard\n"+
	"   wave standard [how] [to] [target]\n"+
	"   plant standard\n"+
	"   raise standard [how] [to] [target]    - for higher members\n"+
	"   lower standard [how] [to] [target]    - for lower members\n"+
	"   rally troops      - this calls wariors from near area to you\n"+
	"\nSuggestions on more emotes are welcome!\n");
  return 1;
}

void
call_them_here()
{
  object *rooms, *pcs, troom;
  int i,j,k;
  string sroom, cmd;
  mixed ex_fun, ranks;

  if (!(troom = ENV(TP))) return;
 
  rooms = find_neighbour(({ troom }), ({ troom }), 1);
  rooms -= ({ troom });
  sroom = MASTER_OB(troom);

  for(i=0; i<sizeof(rooms); i++)
    if((j = member_array(sroom, rooms[i]->query_exit_rooms())) != -1)
    {
      ex_fun = (rooms[i]->query_exit_functions())[j];
      if(intp(ex_fun) && !ex_fun) /* player can move */
      {
        cmd = (rooms[i]->query_exit_cmds())[j];
	pcs = FILTER_PLAYERS(all_inventory(rooms[i]));
        ranks = select_ranks(pcs);

        for(j=0; j<sizeof(ranks); j++) pcs -= ranks[j];

        for(k=0; k<sizeof(pcs); k++)
	  if(CAN_SEE_IN_ROOM(pcs[k]))
	    pcs[k]->catch_msg("You notice a red and black flag to the "+
			      cmd+".\n");

        for(j=2; j<sizeof(ranks); j++) for(k=0; k<sizeof(ranks[j]); k++)
	  if(CAN_SEE_IN_ROOM(ranks[j][k]))
	    ranks[j][k]->catch_msg("You notice signal with standard of "+
				   "Angmar calling troops to the "+cmd+".\n");

        for(j=0; j<2; j++) for(k=0; k<sizeof(ranks[j]); k++)
	  if(CAN_SEE_IN_ROOM(ranks[j][k]))
	    ranks[j][k]->catch_msg("You notice signal with standard of "+
				   "Angmar to the "+cmd+", ordering you "+
				   "to go there.\n");
      }
    }
}

void
make_them_happy(object *list)
{
  mixed ranks;
  int i;

  ranks = select_ranks(list);

  for(i=0; i<sizeof(ranks[0]); i++)
    if(CAN_SEE_IN_ROOM(ranks[0][i])) ranks[0][i]->command(CHEER);
  for(i=0; i<sizeof(ranks[1]); i++)
    if(CAN_SEE_IN_ROOM(ranks[1][i])) ranks[1][i]->command(CHEER);
}

int
hide(string str)
{
  string name;
 
  if((!str) || (str != "standard")) return 0;

  if(!is_shown)
  {
    NF("");
    write("Your standard is hidden now!\n");
    return 0;
  }

  write("You roll your standard of Angmar's Army neatly around the pole "+
	"and hide it from sight of others.\n");
  allbb(" rolls "+HIS(TP)+" standard of Angmar's Army neatly around the "+
	"pole and hides it from your sight.");
  TP->remove_subloc(SUBLOC_STANDARD);
  name = TP->query_name();
  TP->remove_item(name+" standard");
  is_shown = 0;
  return 1;
}

int
unroll(string str)
{
  string name, cname;

  if((!str) || (str != "standard")) 
  {
    NF("Unroll what?\n");
    return 0;
  }
  if(is_shown)
  {
    NF("You are already displaying the standard.\n");
    return 0;
  }


  write("You unroll your standard of Angmar's Army and display it for "+
	"everyone to see.\n");
  allbb(" unrolls "+HIS(TP)+" standard of Angmar's Army and displays it for "+
	"everyone to see.");
  TP->add_subloc(SUBLOC_STANDARD, TO);

  name = TP->query_real_name();
  cname = TP->query_name();
  TP->add_item(({name+" standard", cname+" standard",
		 name+"s standard", cname+"s standard",
		 name+"'s standard", cname+"'s standard"}), 
	       VBFC_ME("item_standard"));
  is_shown = 1;
  return 1;
}

string
item_standard()
{
  object ob = ENV(TO);

  if(TP == ob) return "";

  ob->catch_msg(QCTNAME(TP)+" examines your standard of Angmar's Army.\n");
  tell_room(ENV(ob), QCTNAME(TP)+" examines "+QTNAME(ob)+
	             "'s standard of Angmar's Army.\n", ({ TP,ob }) );
  TP->catch_msg("You examine "+QTNAME(ob)+"'s standard of Angmar's Army.\n"+
		VBFC_ME("my_long"));
  return "";
}

int
wave(string str)
{
  object *oblist;
  string *how;

  if(!str) return 0;

  how = explode(str, " ");
  if(how[0] != "standard") return 0;

  if(!is_shown)
  {
    NF("");
    write("You must unroll the standard first!\n");
    return 0;
  }

  str = implode((how-({"standard"})), " ");

  if(str == "") str = 0;
  how = parse_adverb_with_space(str, "confidently", 0);

  if (!strlen(how[0]))
  {
    write("You"+how[1]+" wave the standard of Angmar's Army.\n");
    allbb(how[1]+" waves the standard of Angmar's Army.");
    return 1;
  }

  oblist = parse_this(how[0], "[to] [the] %l");

  if (!sizeof(oblist))
  {
    NF("Wave standard to whom?\n");
    return 0;
  }

  targetbb(how[1]+" waves the standard of Angmar's Army"+
	   " in your direction.", oblist);
  actor("You"+how[1]+" wave the standard of Angmar's Army in", oblist, 
	"'s direction.");
  all2actbb(how[1]+" waves the standard of Angmar's Army in", oblist, 
	    "'s direction.");
  return 1;
}

int
plant(string str)
{
  if((!str) || (str != "standard")) return 0;

  if(!is_shown)
  {
    NF("");
    write("You must unroll the standard first!\n");
    return 0;
  }

  write("You plant the standard of the Army of Angmar in the ground and "+
	"make your stand.\n");
  allbb(" plants the standard of Angmar's Army in the ground and make "+
	HIS(TP)+" stand.");

  return 1;
}

int
raise(string str)
{
  object *oblist;
  string *how;

  if(!str) return 0;

  how = explode(str, " ");
  if(how[0] != "standard") return 0;

  if(!is_shown)
  {
    NF("");
    write("You must unroll the standard first!\n");
    return 0;
  }

  str = implode((how-({"standard"})), " ");

  if(str == "") str = 0;
  how = parse_adverb_with_space(str, "slowly", 0);

  if (!strlen(how[0]))
  {
    write("You"+how[1]+" raise the standard of Angmar's Army.\n");
    allbb(how[1]+" raises the standard of Angmar's Army.");

    make_them_happy(parse_this("all", "%l"));
    return 1;
  }

  oblist = parse_this(how[0], "[to] [the] %l");

  if (!sizeof(oblist))
  {
    NF("Raise standard to whom?\n");
    return 0;
  }
  if(sizeof(oblist) > 1)
  {
    write("You should honour only one at a time.\n");
    return 1;
  }
  if((get_rank(oblist[0]) < 3) && (!oblist[0]->query_wiz_level()))
  {
    write(CAP(HE(oblist[0]))+" is too low in army for that.\n");
    return 1;
  }

  targetbb(how[1]+" raises the standard of Angmar's Army"+
	   " in your honour.", oblist);
  actor("You"+how[1]+" raise the standard of Angmar's Army in", oblist, 
	"'s honour.");
  all2actbb(how[1]+" raises the standard of Angmar's Army in", oblist, 
	    "'s honour.");

  make_them_happy(parse_this("all", "%l"));
  return 1;
}

int
lower(string str)
{
  object *oblist;
  string *how;

  if(!str) return 0;

  how = explode(str, " ");
  if(how[0] != "standard") return 0;

  if(!is_shown)
  {
    NF("");
    write("You must unroll the standard first!\n");
    return 0;
  }

  str = implode((how-({"standard"})), " ");

  if(str == "") str = 0;
  how = parse_adverb_with_space(str, "slowly", 0);

  if (!strlen(how[0]))
  {
    write("You"+how[1]+" lower the standard of Angmar's Army.\n");
    allbb(how[1]+" lowers the standard of Angmar's Army.");

    return 1;
  }

  oblist = parse_this(how[0], "[to] [the] %l");

  if (!sizeof(oblist))
  {
    NF("Lower standard to whom?\n");
    return 0;
  }
  if(sizeof(oblist) > 1)
  {
    write("You should honour only one at a time.\n");
    return 1;
  }
  if((get_rank(oblist[0]) > 1) || (oblist[0]->query_wiz_level()))
  {
    write(CAP(HE(oblist[0]))+" is too high in army for that.\n");
    return 1;
  }
  if(get_rank(oblist[0]) == -1)
  {
    write(CAP(HE(oblist[0]))+" is not in the army!\n");
    return 1;
  }

  targetbb(how[1]+" lowers the standard of Angmar's Army"+
	   " to you.\nYou kneel down and kiss the edge of the flag.", oblist);
  actor("You"+how[1]+" lower the standard of Angmar's Army to", oblist, 
	".\n"+QCTNAME(oblist[0])+
	" kneels down and kisses the edge of the flag.");
  all2actbb(how[1]+" lowers the standard of Angmar's Army to", oblist, 
	    ".\n"+QCTNAME(oblist[0])+
	" kneels down and kisses the edge of the flag.");

  return 1;
}

int
rally(string str)
{
  object *footmen;

  if((!str) || (str != "troops")) return 0;

  if(!is_shown)
  {
    NF("");
    write("You must unroll the standard first!\n");
    return 0;
  }

  write("You hold your standard of Angmar's Army high in the air, "+
	"rallying the troops.\n");
  allbb(" holds "+HIS(TP)+" standard of Angmar's Army high in the air, "+
	"rallying the troops.");

  make_them_happy(parse_this("all", "%l"));
  call_them_here();
  return 1;
}

/*
 * Function name: show_subloc
 * Description:   Shows the specific sublocation description for a living
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if(subloc != SUBLOC_STANDARD) return "";
    if (for_obj == on)
        return "You are bearing the Standard of Angmar.\n";
    else
        return CAP(HE(on)) + " is bearing the Standard of Angmar.\n";
}

