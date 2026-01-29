// file name:    ~Avenir/tools/typo.c
// creator(s):   Lord Cirion, August 15th, 1996
// last update:  
// purpose:      Toolsoul to allow the quick and easy repair of typos
//               in objects of files.
// note:
// bug(s):
// to-do:        Perhaps add in a check to make sure replaced words
//               are surrounded by "" marks.
// revision:

#pragma strict_types
#pragma save_binary

#include <macros.h>    /* MASTER_OB, etc      */
#include <cmdparse.h>  /* FIND_STR_IN_OBJECT  */

inherit "/cmd/std/tracer_tool_base";

/*
 * RESERVED_WORDS may not be replaced ... high chance of messing
 * things up.
 */
#define RESERVED_WORDS ({ "if","break","create","create_room", \
        "create_object","create_weapon","for","continue" })

string
get_soul_id()
{
  return "Cirion's Typo Fixer";
}

int
query_tool_soul()
{
  return 1;
}

mapping
query_cmdlist()
{
  return ([
           "tfix" : "tfix",
           "help": "help",
          ]);
}

int help(string str)
{
  string  *strs;

  if(!strlen(str))
    return 0;

  strs = explode(str, " ");

  if(strs[0] != "tfix")
   return 0;

  notify_fail("No such help option for the typo fixer.\n");
  if(sizeof(strs) == 1)
  {
  write(
    "NAME\n"
   +"        tfix - fix a typo in an object or file\n"
   +"\n"
   +"SYNOPSIS\n"
   +"        tfix <object / file> <typo word> <replace word>\n"
   +"\n"
   +"DESCRIPTION\n"
   +"        Tfix allows you to repair typos in an object or file\n"
   +"        by doing a search/replace on the file path of your item.\n"
   +"        If an object (you can also use 'here' for your environment)\n"
   +"        is selected, the fixer will try to update the object to\n"
   +"        make sure that it reloads after it is rewritten.\n"
   +"\n"
   +"ARGUMENTS\n"
   +"        <object/file> - the object in your inventory or environment\n"
   +"                        you wish to fix, else the partial or full\n"
   +"                        path of the file\n"
   +"\n"
   +"EXAMPLES\n"
   +"        tfix here wader water\n"
   +"        tfix sword blage blade\n"
   +"        tfix /d/Avenir/cirion/doc/typo_fixer tepo typo\n"
   +"\n"
   +"CAVEAT\n"
   +"        If used incorrectly, this object can make a file buggy. For\n"
   +"        example, if you do:\n"
   +"        tfix here create_room yibble_yibble\n"
   +"        The create_room function in the room will be rewritten, so that\n"
   +"        the room won't reload properly.\n"
   +"        Use this command with extreme care.\n"
   +"\n"
   +"SEE ALSO\n"
   +"        tfix warranty\n"
   +"        tfix failures\n");
    return 1;
  }

  if(strs[1] == "warranty")
  {
    write("This item comes with absolutely no warranty, so use "
     +"it at your own risk.\n");
    return 1;
  }

  if(strs[1] == "failures")
  {
    write("Here is a list of possible reasons your typo fix may "
         +"have failed:\n"
         +"    You may have no read access to the file\n"
         +"    You may have no write access to the file\n"
         +"    The string you searched for may not exist in the file\n"
         +"      Note: It might, however, have existed in an inherited\n"
         +"            or included file, in which case you would need\n"
         +"            to fix that file instead.\n"
         +"    You may have introduced a bug into your file by replacing\n"
         +"      a function with your string.\n"
         +"SEE ALSO: tfix warranty\n");
    return 1;
  }

  return 0;
}

/*
 * Tfix - the command 'tfix', fixes a typo in a file or object
 */
public nomask int 
tfix(string str)
{
  object   what,       /* The file, if it is an object     */
          *things,     /* Possible object, parsed          */
          *people,     /* People standing in 'here'        */
           where;      /* Environment for 'here'           */
  string  *strs,       /* Explosion                        */ 
           dir,        /* Wizz's dir path                  */
           file,       /* file name                        */
           read,       /* contents of the file             */
           newfile,    /* replaced contents of the file    */
           str1,       /* Typo                             */
           str2,       /* Replacement string               */
          *ostrs,      /* Explosion of the read_file       */ 
          *places;     /* Everyone's query_default_start   */
  int      i;          /* General index                    */
  int    force;
  
  notify_fail("Usage: tfix <file/object> <typo> <correction>\n");
  if(!strlen(str))
    return 0;

  strs = explode(str, " ");

  if(sizeof(strs) && strs[0] == "-f")
  {
    force = 1;
    strs -= ({ strs[0] });
  }
  /* Needs to have 3 arguments */
  if(sizeof(strs) != 3)
    return 0;

  /* Fixing typo with itself? Silly ;)  */
  notify_fail("Cirion arrives.\nCirion says: That would be silly.\n"
    +"Cirion returns to the void.\n");
  if(strs[1] == strs[2])
    return 0;

  /* Wizards current dir path */
  dir = this_player()->query_path();
  file = "";

  /* Did they try to fix a reserved work, like 'create_room' ? */
  notify_fail("Failed: " + strs[1] + " is a reserved word.\n");
  if(member_array(strs[1], RESERVED_WORDS) != -1)
    return 0;
  if(member_array(strs[2], RESERVED_WORDS) != -1)
    return 0;

  /* Selected the room */
  if(strs[0] == "here")
    file = MASTER_OB(environment(this_player())) + ".c";

  /* Otherwise, try to figure out what the player is trying to select */
  if(file_size(file) < 0)
    file = dir + "/" + strs[0];

  if(file_size(file) < 0)
    file += ".c";

  if(file_size(file) < 0)
    file = strs[0];

  if(file_size(file) < 0)
    file += ".c";

  /* Selected an object? */
  if(file_size(file) < 0)
  {
     things = FIND_STR_IN_OBJECT(strs[0], this_player());
     if(!sizeof(things))
      things = FIND_STR_IN_OBJECT(strs[0], environment(this_player()));
     if(!sizeof(things))
     {
       write("Failed: no such file or object: " + strs[0] + ".\n");
       return 1;
     }

     file = MASTER_OB(things[0]) + ".c";
     if(file_size(file) < 0)
     {
       write("Failed: no such file or object: " + strs[0] + ".\n");
       return 1;
     }
  }

  /* Fail is over 50kb file */
  notify_fail("Failed: The file " + file + " is too large.\n");
  if(file_size(file) > 50000)
    return 0;

  /* Read 'em */
  read = read_file(file);

  notify_fail("Failed: Could not read " + file + "\n");
  if(!read || !strlen(read))
    return 0;

  /* Check to see if the typo is really there */
  notify_fail("Failed: The file " + file + " does not contain the word '"
    + strs[1] + "'\n");
  if(!wildmatch("*" + strs[1] + "*", read))
    return 0;

  /* Break it up based on the typo */
  ostrs = explode(read, strs[1]);

  /* Implode it back with the new replacement word */
  read = implode(ostrs, strs[2]);

  /* How many did we find? */
  i = sizeof(ostrs) - 1;

  if(force && i > 4)
  {
    /* Too many! */
    notify_fail("Found " + i + " instances of the word: '" + strs[1]
     +"'\nAborting, chances are it isn't really a typo.\n");
    return 0;
  }

  write("Found " + LANG_WNUM(i)
   + " instance" + (i > 1 ? "s" : "") + " of the word: '" + strs[1]
   + "'\nReplaced " + ( i > 1 ? "them all with: '" : "it with: '")
   + strs[2] + "'\n");


  /* Get people out of the room before we try to update it */
  if(strs[0] == "here" && (where = find_object(extract(file, 0, -3))))
  {
    people = filter(all_inventory(where), interactive);
    places = people->query_default_start_location();

    if(member_array(file_name(where), places) != -1)
    {
       notify_fail("Failed: Cannot update the start location of "
         +"someone who is present in the room.\nFile is "
         +"unchanged.\n");
       return 0;
    }

    for(i=0;i<sizeof(people);i++)
      people[i]->move(places[i], 1);

    if(sizeof(filter(all_inventory(where), interactive)))
    {
      notify_fail("Failed: Someone in the room could not be moved "
          + "out of it.\nFile is unchanged.\n");
      return 0;
    }

    i = -101;
  }

  /* Remove the old file */
  notify_fail("Failed: Could not remove the file " + file + "\n");
  if(!rm(file))               /* Try to remove the file  */
    return 0;

  /* Write back the new file */
  notify_fail("Failed: Could not write back to file " + file + "\nUh oh.\n");
  if(!write_file(file, read))  /* Try to write back the new file */
    return 0;

  /* Reload the new file if it has the '.c' ending */
  file = extract(file, 0, -3);  /* Get rid of the '.c' */
  if(what = find_object(file))  /* File was an object, check for reload */
  {
     notify_fail("Failed: File will not reload. DAMN DAMN DAMN!\n");

     find_object(file)->remove_object();
     if(catch((file)->teledensanka()))
       return 0;

     if(i == -101)
     {
       /* Move back people to the room */
       for(i=0;i<sizeof(people);i++)
         people[i]->move(find_object(file), 1);
     }
  }

  /* Woo woo! */
  write("Success!\n");
  return 1;
}
