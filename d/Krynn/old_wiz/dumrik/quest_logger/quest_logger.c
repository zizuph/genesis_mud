/*
   This is a general purpose quest-logging object that does 2 things 
   1. Logs when a person solves a quest, in 2 files, 1 file that contains when a person
      last solved that quest, and 1 file where all the persons that ever solved that
      particular quest is. That means that all the quest has one log-file each.

   2. (future project) Gives out XP to the person that solved the quest
      read from a configuration-file.
*/

#include "/d/Krynn/common/defs.h"
#define LOG_DIR   "/d/Krynn/dumrik/quest_logger/logs"
#define DATA_FILE "/d/Krynn/dumrik/quest_logger/data"

inherit R_FILE

mapping quest_mapping;
string *quests;

create_room() 
{
  set_short("The quest-logging room");
  set_long("This is the quest-logging room, which isnt really a room at all, it just " +
	   "seemed like a good object to inherit from :-)\n");
  loadquests();
}


int 
init()
{
  ADA("loadquests");
  ADA("showquests");
  ADA("backup");
  ADA("solve");
}

int
backup()
{
  if (file_size(DATA_FILE + ".backup")!=-1) rm(DATA_FILE + ".backup");
  
  if (file_size(DATA_FILE)==-1) {
    write("The file: " + DATA_FILE + " doesnt exist...BAD.\n");
  } else {
    write_file(DATA_FILE + ".backup", read_file(DATA_FILE));
  }

  return 1;
}

int 
loadquests()
{
  if (file_size(DATA_FILE)==-1) {
    write("OOPS...the data file doesnt exist....trying to fetch the backupfile.\n");
    if (file_size(DATA_FILE + ".backup")==-1) {
      write("THIS IS REALLY BAD...NO BACKUP FILE EXISTS EITHER...\n");
      return 1;
    } else {
      quests = explode(read_file(DATA_FILE + ".backup"),"\n");
      write("Ok, the backup file is now used instead...this should be fixed ASAP.\n");
      return 1;
    }
  } else {  
    quests = explode(read_file(DATA_FILE),"\n");
    tell_room(TO,"Data file re-read\n");
  }

  sort_array(quests,"sort_func",TO);
  
  return 1;
}


int sort_func(string str1, string str2) {
  if (str1 == str2) return 0;
  

  if (str1 > str2)
    return 1;
  else
    return -1;
}


int
showquests()
{
  int i;

  write("\nValid quests\n");
  write("------------\n");
  
  for(i=0;i < sizeof(quests);i++) {
    write(quests[i] + "\n");
  }

  if (!sizeof(quests))
    write("None.\n");

  write("\n");
  
  return 1;
}

int
query_valid_quest(string name)
{
  int i;

  for(i=0;i<sizeof(quests);i++) {
    if (lower_case(quests[i])==lower_case(name)) {
      return 1;
    }    
  }

  return 0;
}



int
log_quest_solved(string quest_name,object solver) 
{
  if (query_valid_quest(quest_name)) {
    log_file("quests/" + lower_case(quest_name),
	     ctime(time()) + "    solved by: " + capitalize(solver->query_real_name()) +
	     "\n", 0);
    quest_mapping[lower_case(quest_name)][0] = solver->query_real_name();
    quest_mapping[lower_case(quest_name)][1] = ctime(time());    
    return 1;
  } else {
    return 0;
  }
}


int 
solve(string questname) 
{
  questname = lower_case(questname);
  log_quest_solved(questname,TP); 
  return 1;
}
