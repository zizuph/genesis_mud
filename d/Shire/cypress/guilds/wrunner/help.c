/* help.c created by Shiva@Genesis
 * This file contains the code for the "help" command
 * This file is a subpart of the vampire guild soul
 */

#include "wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

/*
#define GUILD_HELP_DIR  WRUNNER_HELP_DIR
*/

string help_commands(string file)
{
  string name;
  return (sscanf(file, "%s.help", name) ? name : 0);
}

int help(string str)
{
  string *subjects, help_file;

  setuid();
  seteuid(getuid());

  if (str == "wildrunner" || str == "wrunner" || str == "elf")
  {
    subjects = map(get_dir(GUILD_HELP_DIR), help_commands) - ({ 0 });
    if (!sizeof(subjects))
    {
      return 0;
    }

    str = implode(subjects, "\n");

    write("Help is available to wildrunners on these subjects:\n\n");
    write(sprintf("%-#60s\n", str));
    write("\nUse 'help wildrunner <subject>' to access help files.\n\n");

    return 1;
  }

  if (strlen(str) && (sscanf(str, "wildrunner %s", help_file) ||
      sscanf(str, "wrunner %s", help_file) ||
      sscanf(str, "elf %s", help_file)) &&
      file_size(help_file = GUILD_HELP_DIR + help_file + ".help") >= 0)
  {
    write("\n");

    setuid();
    seteuid(getuid());
    TP->more(read_file(help_file));
    return 1;
  }

  return 0;
}
