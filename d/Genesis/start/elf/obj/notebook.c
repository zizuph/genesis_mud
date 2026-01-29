#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit "/std/object";
/*inherit MISCLIB;*/

#define USE_DESC \
 "On it is written:\n" + \
 "     By virtue of my magic, I will make a note of everything you speak,\n"+ \
 "     from when you say \"take a note\" to when you say \"end note\".\n"

int num_of_pages;
status taking_note;
string note_txt;

string query_the_name() { return "the notebook"; }
string query_real_name() { return "notebook"; }
string query_nonmet_name() { return "notebook"; }
string query_cap_name() { return "Notebook"; }

string cont_desc()
{
  if (num_of_pages == 0)
    return "All its pages has been torn out";
  else if (num_of_pages == 1)
    return "It contains a single page of crisp, new parchment.";
  else
    return "It contains " + num_of_pages + " pages of crisp, new parchment.";
}

create_object() {
  set_name("notebook");
  set_pname("notebooks");

  set_short("leather-bound notebook");
  set_pshort("leather-bound notebooks");

  set_long("This is a notebook, bound in soft leather.\n@@cont_desc@@\n\n" + 
	   USE_DESC);

  num_of_pages = 20;

  add_prop(OBJ_I_WEIGHT, 250);
  add_prop(OBJ_I_VOLUME, 250);
  add_prop(OBJ_I_VALUE, num_of_pages * 5);

  enable_commands();
}

init()
{
  add_action("do_read", "read");
}

do_read(string str)
{
  if (plural_id(str)) {
    notify_fail("Try to read them one at a time instead.\n");
    return 0;
  }

  if (id(str)) {
    if (num_of_pages == 0)
      write ("There are no pages left in it.\n");
    else if (num_of_pages == 1)
      write ("The single page is blank.\n");
    else
      write ("All the pages are blank.\n");
    
    return 1;
  }
  
  return 0;
}
      

static status start_id(string str)
{
  string str2;

  str = lower_case(str);
  if (sscanf(str, "%s, please", str2)) 
    str = str2;

  return (str == "take note" || str == "take a note");
}


static status stop_id(string str)
{
  string str2;

  str = lower_case(str);
  if (sscanf(str, "%s, please", str2)) 
    str = str2;

  return (str == "end note" || str == "stop note");
}


create_note(string txt)
{
  object note;

  seteuid(getuid());
  
  /*note = make_object(OBJDIR + "note");*/
  note = clone_object(OBJDIR + "note");

  if (note == 0 || note->move(this_player())) {
    write("The notebook whispers: " + 
	  "Sorry, but something does not permit me to give you the\nnote.\n");
    if (note != 0) 
      note->remove_object();
  } else {
    write("One of the pages crawls out of the notebook.\n");
    note->set_txt(txt);
  }
  num_of_pages--;
  add_prop(OBJ_I_VALUE, num_of_pages * 5);
}

  
catch_msg(mixed str, object obj)
{
  string msg;

  if (environment() && stringp(str) &&
      sscanf(str, 
	     "@@query_The_name:" + file_name(environment()) + 
	     "@@ @@race_sound:" + file_name(environment()) + "@@: %s\n", 
	     msg)) {
    if (!taking_note && start_id(msg)) {

      taking_note = 1;
      note_txt = "";
      write("The notebook seems to tremble eagerly.\n");

    } else if (taking_note && stop_id(msg)) {

      taking_note = 0;
      create_note(note_txt);

    } else if (taking_note) {
     
      note_txt += "    " + msg + "\n";
      
    }
  }
}

