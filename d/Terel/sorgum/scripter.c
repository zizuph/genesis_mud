/* A generalized scripting device for monsters like the alchemist.
 * You need a file with series of commands for a monster, each line
 * will be executed every three seconds.  You can also embed functions
 * within the lines with the '@@' syntax.  
 * Inherit this file along with the std/monster or std/object
 * functions to call when starting up the script
 * set_who_name(name)
 *   set the name of the player we're dealing with (optional)
 * set_who_ob(ob)
 *   set the object number of the player we're dealing with (optional)
 * start_script(filename)
 *   Start using the script 'filename'
 * query_busy_npc()
 *   Check to see if the npc is busy doing a script
 *
 * Here are some control function you can use to control the scripts
 * with the @@function@@ syntax
 * @@who_is@@
 *   returns the name in lower case of the player.
 * @@end_script@@
 *   abort the script before it reaches the end
 * @@script_branch|funct|offset@@
 *   This will call the function funct in the object and if it returns 1
 *   it will add offset to the counter and continue.  The offset can be
 *   positive or negative.
 * @@go_sub_script|funct|file@@
 *   if the function funct returns 1 the present script file name will
 *   be saved along with it's counter and the new file will be loaded
 *   and started.
 * @@return_script@@
 *   If we had branched to another file, this would return us to the
 *   previous file and start up where we left off
 *
 * If you have a blank line in a script it will pause for one beat, good
 * if you want to slow things down.
 */

#include <stdproperties.h>

#define SCRIPTER_I_BUSY "_scripter_i_busy"
#define OBJ_S_NAME "_obj_s_name"
#define OBJ_O_PLAYER  "_obj_o_player"
#define SCRIPT_M_FILE "_script_s_file"
#define SCRIPT_TIME "_script_time"

int heart;
string *active_string;
int active_offset;
string active_file;

void
set_heart(int i) {
  float f;
  remove_alarm(heart);
  heart = 0;
  if(!intp(i) || !i)
     i = 3;

    f = itof(i);
    heart = set_alarm(f, f, "beat");

}

void
end_script() {
  set_heart(0);
  active_offset = 0;
  active_string = ({});
  active_file = 0;
  this_object()->remove_prop(SCRIPTER_I_BUSY);
  this_object()->remove_prop(OBJ_S_NAME);
  this_object()->remove_prop(OBJ_O_PLAYER);
  this_object()->remove_prop(SCRIPT_M_FILE);
}

void
beat() {
  mixed cmdres;
  if(active_offset < sizeof(active_string)) {
    cmdres = this_object()->check_call(active_string[active_offset]);
    if(stringp(cmdres))
      command(cmdres);
    active_offset++;
    return;
  }
  this_object()->remove_prop(SCRIPTER_I_BUSY);
  end_script();
}

int
start_script(string file) {
  string stuff;
  if(this_object()->query_prop(SCRIPTER_I_BUSY))
    return 0;

  seteuid(getuid());
  stuff = read_file(file);
  if(!stuff) 
    return 0;

  active_string = explode(stuff, "\n");
  active_offset = 0;
  active_file = file;
  this_object()->add_prop(SCRIPTER_I_BUSY, 1);
  if(this_object()->query_prop(SCRIPT_TIME) &&
     intp(this_object()->query_prop(SCRIPT_TIME)))
    set_heart(this_object()->query_prop(SCRIPT_TIME));
  else
    set_heart(3);

  return 1;
}

string race_sound() { return "says"; }

string
who_is() {
  return this_object()->query_prop(OBJ_S_NAME);
}

object
who_ob() {
  return this_object()->query_prop(OBJ_O_PLAYER);
}

int
set_who_name(string name) {
  if(!name || !stringp(name))
    return 0;
  name = lower_case(name);
  this_object()->add_prop(OBJ_S_NAME, name);
  return 1;
}

int
set_who_ob(object ob) {
  if(!ob || !objectp(ob))
    return 0;

  this_object()->add_prop(OBJ_O_PLAYER, ob);
  this_object()->add_prop(OBJ_S_NAME, lower_case(ob->query_name()));
  return 1;
}

void
script_branch(string func, int i) {
  if(!stringp(func) || !i)
    return;
  if(call_other(this_object(), func))
    active_offset += i;
  return;
}


void
go_sub_script(string func, string file) {
  mixed files;

  if(!stringp(func) || !stringp(file))
    return;

  if(call_other(this_object(), func)) {
    files = this_object()->query_prop(SCRIPT_M_FILE);
    if(!files)
      files = ({});
    files += ({active_file, active_offset});
    this_object()->add_prop(SCRIPT_M_FILE, files);
    start_script(file);
  }
}

void
return_script() {
  mixed files;
  mixed tmp;
  files = this_object()->query_prop(SCRIPT_M_FILE);
  if(!sizeof(files))
    end_script();
  else {
    tmp = files[sizeof(files) - 1];
    active_file = tmp[0];
    active_offset = tmp[1];
    active_string = explode(active_file, "\n");
    files = files[0..sizeof(files - 2)];
    if(!sizeof(active_string))
      end_script();
  }
}

query_busy_npc() {
  return this_object()->query_prop(SCRIPTER_I_BUSY);
}
