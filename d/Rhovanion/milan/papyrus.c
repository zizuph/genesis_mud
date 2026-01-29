/*
 * This papyrus contains recepy for potion used in Smaug quest
 * It also handles all herbs necessary+locations where they are
 * to be found.
 * All you need to do is call function 'init_papyrus' with name
 * of the player as paraneter when creating the papyrus.
 *
 * Milan
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define SELECT "/d/Rhovanion/milan/s_h_sel"
#define HERBS(x)  SELECT->select_herbs(x)
#define SITES(x)  SELECT->select_sites(x)

/*
 * Global variables
 */
private string name, *herbs, *sites;
private int    state, *control;

void init_papyrus(string str)
{
  name = str;
  herbs = HERBS(str);
  sites = SITES(str);
  control = allocate(sizeof(sites));
}

/* This is for debug/check reasons */
mixed query_papyrus(){ return ({ name, herbs, sites }); }

void create_object()
{
  set_name("papyrus");
  set_pname("papyri");
  set_long("@@my_long");
  add_item("string", "@@my_string");
  add_item("wax", "It keeps the string safely on the papyrus.\n");
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  state = 2;
}

string my_long()
{
  if(state == 2)
    return "It is nicely rolled old papyrus with a string tied around it.\n";
  if(state == 1)
    return "It is rolled old papyrus with a string hanging from its edge.\n";
  return "It is old papyrus with a string hanging from its edge.\n";
}

string my_string()
{
  if(state == 2)
    return "It is tied around papyrus to keep it nicely rolled.\n";
  return "It is fixed to the edge of the papyrus by a piece of wax.\n";
}

void init()
{
  ::init();
  add_action("search","search");
  add_action("untie","untie");
  add_action("tie","tie");
  add_action("unroll","unroll");
  add_action("roll","roll");
  add_action("read","read");
}

int search(string str)
{
  int i;

  if(!str || (TP!=ENV(TO))) return 0;
  if(TP->query_attack())
  {
    write("But you are in the middle of a fight!\n");
    return 1;
  }
  if((str!="here for herbs") && (str!="here for herb")) return 0;

  /* are we in the right room to find a herb? */
  if((i = member_array(file_name(ENV(TP)), sites)) == -1) return 0;
  /* now we will check if he already searched here */
  if(control[i]) return 0;

  /* we will disallow searching again for 30 min */
  control[i] = 1;
  set_alarm(1800.0, 0.0, "reset_control", i);

  write("You start to search here for herbs.\n");
  say(QCTNAME(TP)+" starts to search here for herbs.\n");
  search_object(herbs[i]);
  return 1;
}

void reset_control(int i){ control[i] = 0; }

string herb_search(object who, string str)
{
who->catch_msg("*** search in papyrus ***\n");
  if(member_array(str,herbs) != -1)
  {
who->catch_msg("*** "+HERB_DIR+str+" ***\n");
    return ENV(who)->search_for_herbs(who,HERB_DIR+str);
  }
  return "";
}

int untie(string str)
{
  if((str!="papyrus") && (str!="string"))
  {
    NF("Untie what?\n");
    return 0;
  }
  if(state!=2)
  {
    NF("But the string is not tied around papyrus.\n");
    return 0;
  }
  write("You carefully untie string from the papyrus.\n");
  say(QCTNAME(TP)+" carefully unties string from the papyrus.\n");
  state = 1;
  return 1;
}

int tie(string str)
{
  if((str!="papyrus") && (str!="string"))
  {
    NF("Tie what?\n");
    return 0;
  }
  if(state==2)
  {
    NF("But the string is already tied around papyrus.\n");
    return 0;
  }
  if(!state)
  {
    NF("First you must roll the papyrus.\n");
    return 0;
  }
  write("You carefully tie string around papyrus.\n");
  say(QCTNAME(TP)+" carefully ties string around papyrus.\n");
  state = 2;
  return 1;
}

int unroll(string str)
{
  if(str!="papyrus")
  {
    NF("Unroll what?\n");
    return 0;
  }
  if(state==2)
  {
    NF("First you must untie string from the papyrus.\n");
    return 0;
  }
  if(!state)
  {
    NF("The papyrus is already unrolled.\n");
    return 0;
  }
  write("You unroll the papyrus.\n");
  say(QCTNAME(TP)+" unrolls the papyrus.\n");
  state = 0;
  return 1;
}

int roll(string str)
{
  if(str!="papyrus")
  {
    NF("Roll what?\n");
    return 0;
  }
  if(state)
  {
    NF("But the papyrus is already rolled.\n");
    return 0;
  }
  write("You carefully roll the papyrus.\n");
  say(QCTNAME(TP)+" carefully rolls the papyrus.\n");
  state = 1;
  return 1;
}

int read(string str)
{
  if(str != "papyrus")
  {
    NF("Read what?\n");
    return 0;
  }
  if(state)
  {
    NF("First you must unroll papyrus.\n");
    return 0;
  }
  write("This is a recepy for a potion...\n");
  return 1;
}
