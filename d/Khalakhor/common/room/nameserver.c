/*
** NAMESERVER.C
**
** This "room" provides unique random celtic names for NPCs who need one.
** All an npc has to do is get a pointer to this object and invoke
** the get functions to get a name. NPCs who use this should return
** their name to the server upon their death by masking do_die as shown
** below. If the server runs out of names, it resets the available list
** to the start list, so some duplication is possible.
**
** Include this in any NPC which uses the server:
** NOTE: should include <const.h> and define SERVERFILE as the
**       fully-qualified path/filename to this file
**       (conveniently done in nameserver.h, so just include it)
 
//
// DO_DIE (MASK) - return my name to the server for reuse when I die
//
public void do_die(object enemy)
{
   (SERVERFILE)->return_name(query_gender(),lower_case(query_name()));
   ::do_die(enemy);
}
 
**
** To use the server, where the name is needed:
**
 
   string name = (SERVERFILE)->get_name(query_gender());
 
**
** History:
** Date       Name          Action
** --------   ------------- -------------------------------------------
** 4/15/98    Zima          Created
**
*/
inherit  "/d/Khalakhor/std/room";
#include "/d/Khalakhor/sys/defs.h"
#include "nameserver.h"
#include "namelist.h"
 
string* male = (({}));
string* female = (({}));
 
// ********** GET_NAME functions ***********
public string get_female_name() {
   string n;
   if (sizeof(female)==0) female = FLIST;
   n = female[(random(sizeof(female)))];
   female = female - ({n});
   return n;
}
 
public string get_male_name() {
   string n;
   if (sizeof(male)==0) male = MLIST;
   n = male[(random(sizeof(male)))];
   male = male - ({n});
   return n;
}
 
public string get_name(int gender) {
   if (gender==G_FEMALE)
      return (get_female_name());
   else
      return (get_male_name());
}
 
// ********** RETURN_NAME functions ***********
public int return_female_name(string n) {
   if (member_array(n,female)>=0) return 0;
   female = female + ({n});
   return 1;
}
 
public int return_male_name(string n) {
   if (member_array(n,male)>=0) return 0;
   male = male + ({n});
   return 1;
}
 
public int return_name(int gender, string n) {
   if (!stringp(n)) return 0;
   if (n=="ob_0") return 0;
   if (gender==G_FEMALE)
      return (return_female_name(n));
   else
      return (return_male_name(n));
}
 
public object query_pointer()
{
   return this_object();
}
 
public void create_khalakhor_room() {
   set_short("Celtic name server room");
   set_long("This is the Celtic name server room. Type 'nhelp' to see what "+
            "you can do here.\n");
   male=MLIST;
   female=FLIST;
}
 
int do_help() {
   write("NAME SERVER ROOM COMMANDS:\n");
   write("LIST: - get a list of names:\n");
   write("   list [current] <gender> - get a list of currently available "+
                                       "names for the gender\n");
   write("   list all <gender>       - get a list of all names for "+
                                       "the gender\n\n");
   write("RESET: - reset current list of names to all list of names:\n");
   write("   reset <gender> [list] \n\n");
   write("Where <gender> is 'male', 'female', 'males', or 'females'\n\n");
   return 1;
}
 
int do_list(string cmd) {
   string list;
   notify_fail("List what? do 'nhelp' for help.\n");
   if      (parse_command(cmd,({TO}),"[current] 'male' / 'males'"))
      list=implode(male,", ");
   else if (parse_command(cmd,({TO}),"[current] 'female' / 'females'"))
      list=implode(female," ");
   else if (parse_command(cmd,({TO}),"'all' 'male' / 'males'"))
      list=implode(MLIST," ");
   else if (parse_command(cmd,({TO}),"'all' 'female' / 'females'"))
      list=implode(FLIST," ");
   else
      return 0;
 
   write(list+"\n");
   return 1;
}
 
int do_reset(string cmd) {
   if (parse_command(cmd,({TO}),"'male' / 'males' [list]"))
      {
      male = MLIST;
      write("List of male names reset.\n");
      }
   else if (parse_command(cmd,({TO}),"'female' / 'females' [list]"))
      {
      female = FLIST;
      write("List of female names reset.\n");
      }
   else
      write("Reset what? do 'nhelp' for help.\n");
   return 1;
}
 
public void init() {
   ::init();
   add_action(&do_list(),"list");
   add_action(&do_reset(),"reset");
   add_action(&do_help(),"nhelp");
}
