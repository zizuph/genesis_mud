#pragma save_binary

inherit "/std/spells";

#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <ss_types.h>

int allofit,nummer;

#define LOCATIONHANDLER (CARISCA+"obj/locationhandler")

#define MANALIMIT 10
#define CASTLIMIT 10

query_auto_load()
{
  return MASTER+":"+allofit+"#"+nummer;
  //return MASTER+":"+allofit+"#"+nummer; 
  return "/d/Roke/common/carisca/obj/spellpaper";
}
init_arg(string arg)
{
  sscanf(arg,"%d#%d",allofit,nummer);
}

fixa()
{
  allofit = 1;
}

cast_spell(string str)
{
  int i;

  if(!present("egg",TP))
    return "You need an egg to cast that spell!\n";

  if(TP->query_mana()<MANALIMIT)
    return "You don't have enough mental powers to cast that spell.\n";

  TP->add_mana(-MANALIMIT);

  i = TP->query_skill(SS_SPELLCRAFT)+TP->query_stat(SS_WIS);
  i/=2;

  if(i<random(CASTLIMIT))
    return "Your skills were not sufficient to cast that spell.\n";

  TP->add_tmp_stat(SS_STR,random(i/5),random(i));

  present("egg",TP)->remove_object();

  say(QCTNAME(TP)+" smashes an egg in "+TP->query_possessive()+" face.\n");
  return "You smash the egg in your face and feel stronger.\n";

}
append(string s)
{
  object ob;

  NF("append what? the papers?\n");
  if(s!="papers")
    return 0;

  NF("Too bad that you don't have more papers.\n");
  if(!(ob=present("ppapp",TP)))
    return 0;

  NF("Don't be silly... You've already done that.\n");
  if(allofit)
    return 0;

  ob->remove_object();

  allofit = 1;

  TP->catch_msg("You append the papers. Suddenly they become readable.\n");
  
  return 1;
}
mylong()
{
  string s;

  s = "It looks very interesting. Why don't you read it?\n";

  if(present("ppapp",TP))
    return s+"It looks a little similar to the other paper you are carrying.\n"+
      "It looks like it just might be possible to append this one to it.\n";
  else
    return s;
}
void
create_spells()
{

    set_name("paper");   /* A name for the object. */
    set_adj("magic");   /* It's a spell book. */
    add_name("sppapp");

    set_long("@@mylong");

    add_prop(OBJ_I_NO_DROP,"If you want to get rid of the paper, just eat it.\n");
    
    add_spell("strength","cast_spell","get better strength");
    nummer = LOCATIONHANDLER->assign_nummer();
}

int read(string s)
{
  NF("Read what? The paper?\n");
  if(!id(s))
    return 0;

  seteuid(getuid(TO));
 
  if(nummer<0)
    {
      TP->catch_msg("On the top of the paper are some runes and the word\n"+
		    "'strength'. There is also a picture of an egg.\n"+
		    "Some powerful magic force has made the paper all\n"+
		    "fluffy and has also created a picture of a blue\n"+
		    "dragon on it.\n");
      return 1;
    }
 
  if(!allofit)
    {
      TP->catch_msg("On the top of the paper are some runes and the word\n"+
		    "'strength'. There is also a picture of an egg.\n"+
		    "On the back side of the paper someone has written\n"+
		    "an old legend. Unfortunately the paper has been torn\n"+
		    "apart, so you can't read it. You really wish that you\n"+
		    "had that second part...\n");
    }
  else
    {
      TP->catch_msg("On the top of the paper are some runes and the word\n"+
                    "'strength'. There is also a picture of an egg.\n"+
                    "On the back side of the paper someone has written\n"+
                    "an old legend. It tells a tale about an old treasure,\n"+
		    "hidden on a place that fits the description in the tale:\n"+
		    LOCATIONHANDLER->give_location(nummer));
    }
  return 1;
}
int query_nummer()
{
  if(!allofit)
    return -1;

  return nummer;
}
eat(string s)
{
  NF("Eat what? The paper?\n");
  if(s!="paper")
    return 0;
  TP->catch_msg("You eat the paper.\n");
  remove_object();
  return 1;
}

void
init()
{
    ::init(); /* Always good to do. */
    add_action("read", "read");
      add_action("eat","eat");
      add_action("append","append");
}

transform_me()
{
  nummer = -1;

  TP->catch_msg("Your paper glows briefly.\n");
}



