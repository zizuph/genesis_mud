// file name:    ~Avenir/tools/props.c
// creator(s):   Cirion, March 10, 1997
// last update:  
// purpose:      Toolsoul to allow the quick and easy addition of
//               of props in the source code.
// note:
// bug(s):
// revision:

#pragma strict_types
#pragma save_binary

#include <macros.h>    /* MASTER_OB, etc      */
#include <cmdparse.h>  /* FIND_STR_IN_OBJECT  */
#include <stdproperties.h>

#define DEFAULT_INDENT     "    "
#define LAST_PROP          "_wizard_props_s_last_prop"
#define LAST_VALUE         "_wizard_props_s_last_value"

inherit "/cmd/std/tracer_tool_base";

/* Prototypes */
string file_from_str(string str);
int reload_file(string file);
string *divide_object(string str);
int last_char(string str);

string
get_soul_id()
{
  return "Cirion's Properties Adder";
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
           "prop" : "prop",
           "help": "help",
          ]);
}

int help(string str)
{
  string  *strs;

  if(!strlen(str))
    return 0;

  strs = explode(str, " ");

  if(strs[0] != "prop")
   return 0;

  notify_fail("No such help option for the properties adder.\n");
  if(sizeof(strs) == 1)
  {
/*
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
*/
    return 1;
  }

  if(strs[1] == "warranty")
  {
    write("This item comes with absolutley no warranty, so use "
     +"it at your own risk.\n");
    return 1;
  }

  return 0;
}

/*
 * Props - the command "props" that adds a prop to a file.
 */
public nomask int 
prop(string str)
{
    string    *strs,
               file,
               read,
               prop,
               value,
               toadd,
               pre,
               suf,
               suf1,
               s1,
               s2,
               s3,
               s4,
               s5,
               s6,
              *division,
              *flags,
               rep;
    int        i,
               found,
               backup,
               reload,
               verbose,
               force,
               replace,
               index,
               rep_index;

    notify_fail("Usage: prop <file/object> <prop> [value]\n");

    /* scan for command line flags */
    if(strlen(str))
    {
       strs = explode(str, " ");
       if(strs[0][0] == '-')
       {
           flags = explode(strs[0], "");
           strs -= ({ strs[0] });

           for(i=0;i<sizeof(flags);i++)
           {
              if(flags[i] == "-")
                continue;
              else if(flags[i] == "f")
              {
                 force = 1;
                 continue;
              }
              else if(flags[i] == "v")
              {
                 verbose = 1;
                 continue;
              }
              else if(flags[i] == "l")
              {
                 reload = 1;
                 continue;
              }
              else if(flags[i] == "r")
              {
                 replace = 1;
                 continue;
              }
              else if(flags[i] == "b")
              {
                 backup = 1;
                 continue;
              }
              else
              {
                 notify_fail("Strange flag: \"" + flags[i] + "\"\n");
                 return 0;
              }
           }
       }

    /* reconstruct the command line */
    if(sizeof(strs))
       str = implode(strs, " ");
    else
       str = "";
    }

    /*
     *  No arg given? Default to the last added prop for the room
     *  the player is in.
     */
    if(!strlen(str))
    {
        if(!strlen(this_player()->query_prop(LAST_PROP)) 
         || !strlen(this_player()->query_prop(LAST_VALUE)))
            return 0;

        write("Defaulting to last prop: " + prop
            + " with value " + this_player()->query_prop(LAST_VALUE) + "\n");
        str = "here " + this_player()->query_prop(LAST_PROP)
            + " " + this_player()->query_prop(LAST_VALUE);
    }

    strs = explode(str, " ");

    /* gets the desired file, handles notify_fails()'s */
    if(sizeof(strs))
       file = file_from_str(strs[0]);

    if(!file)
       return 0;

    /* Fail is over 50kb file */
    notify_fail("Failed: The file " + file + " is too large.\n");
    if(file_size(file) > 50000)
        return 0;

    /* Read 'em */
    read = read_file(file);

    notify_fail("Failed: Could not read: " + file + "\n");
    if(!read || !strlen(read))
        return 0;

    /* Did they specify they wanted to keep a backup of the file? */
    if(backup)
    {
       if(!rename(file, file + ".bak"))
       {
          notify_fail("Failed: Could not make backup of: " + file + "\n");
          return 0;
       }
       else
          write("Backup saved to: " + file + ".bak\n");
    }

    /* *** Find the props *** */

    notify_fail("Failed: no prop specified.\n");
    if(sizeof(strs) > 1)
       prop = strs[1];
    else if(!(prop = this_player()->query_prop(LAST_PROP)))
       return 0;

    /* Did we specify a value? If not, default to 1 */
    if(sizeof(strs) > 2)
       value = implode(strs[2 .. (sizeof(strs) - 1)], " ");
    else if(!(value = this_player()->query_prop(LAST_VALUE)))
       value = "1";

    this_player()->add_prop(LAST_PROP, prop);
    this_player()->query_prop(LAST_VALUE, value);

    toadd = "add_prop(" + prop + ", " + value + ");\n";

    write("Trying to add line: " + toadd);

    /* *** Find a suitable place to put it *** */

    division = divide_object(read);

    notify_fail("Failed: was unable to divide the file into header, body, and footer.\n");
    if(sizeof(division) != 3 || !strlen(division[0]) || 
      !strlen(division[1]) || !strlen(division[2]))
       return 0;

    /* is this prop already in the body? If we are unforced and unreplaced, fail */
    if(!force && !replace && wildmatch("*add_prop(*" + prop + "*", read))
    {
        write("Failed: That prop has already been added to this file.\n"
            + "        Force append with -f flag, replace with -r.\n");
        return 1;
    }

    strs = explode(division[1], "\n");

    for(i=0;i<sizeof(strs);i++)
    {
       if(sscanf(strs[i], "%sadd_prop(%s);%s", pre, suf, suf1))
       {
          index = i;

          if(replace && sscanf(strs[i], "%sadd_prop(%s" + prop + "%s);%s", pre, rep, suf, suf1))
              rep_index = i;
       }
     }

    if(rep_index)
    {
        write("Replacing prop: " + prop + ".\n");
        strs[rep_index] = pre + toadd;
        found = 1;
    }
    else if(index)
    {
        write("Appending prop: " + prop + ".\n");
        strs[index] = pre + "add_prop(" + suf + ");" + suf1 + "\n" + pre + toadd;
        found = 1;
    }
       
    division[1] = implode(strs, "\n");

    /* Just stick it on the end of the body if there is nowhere else to put it */
    if(!found)
    {
       write("Appending at end of body: " + prop + ".\n");
       division[1] += "\n\n" + DEFAULT_INDENT + toadd + "\n";
       found = 1;
    }
    else if(last_char(division[1]) != '\n')
       division[1] += "\n";

    read = division[0] + division[1] + division[2];

    /* Add a newline at the end if there isn't one already */
    if(last_char(read) != '\n')
       read += "\n";

    if(!found)
    {
        notify_fail("Failed. Couldn't find a good place in the file to add it.\n");
        return 0;
    }

    /* Remove the old file */
    notify_fail("Failed: Could not remove the file " + file + "\n");
    if(!rm(file))               /* Try to remove the file  */
       if(!backup)
          return 0;

    /* Write back the new file */
    notify_fail("Failed: Could not write back to file " + file + "\nUh oh.\n");
    if(!write_file(file, read))  /* Try to write back the new file */
          return 0;

    if(reload && !reload_file(file))
       return 0;

    if(verbose)
    {
       write("The file now looks like this:\n");
       this_player()->more(read);
    }
    else
      write("Success!\n");

    return 1;

}

int
reload_file(string file)
{
    object     what,
              *people;
    string    *places;
    int        i;

    what = find_object(file = extract(file, 0, -3));

    if(!objectp(what))
      write("Could not find file.\n");

    /* Get people out of the room before we try to update it */
    if(what->query_prop(ROOM_I_IS))
    {
        people = filter(all_inventory(what), interactive);
        places = people->query_default_start_location();

        if(member_array(file_name(what), places) != -1)
        {
           notify_fail("Failed: Cannot update the start location of "
             + "someone who is present in the room.\nFile is "
             + "unchanged.\n");
           return 0;
        }

        for(i=0;i<sizeof(people);i++)
          people[i]->move(places[i], 1);

        if(sizeof(filter(all_inventory(what), interactive)))
        {
          notify_fail("Failed: Someone in the room could not be moved "
              + "out of it.\nFile is unchanged.\n");
          return 0;
        }
      }

      /* Reload the new file if it has the '.c' ending */
      if(what = find_object(file))  /* File was an object, check for reload */
      {
         notify_fail("Error in reloading.\n");

         what->remove_object();
         if(catch((file)->teledensanka()))
            return 0;

         if(sizeof(people))
         {
           /* Move back people to the room */
           for(i=0;i<sizeof(people);i++)
             people[i]->move(find_object(file), 1);
         }
      }

    return 1;
}

/*
 * divide_object() will divide up a coded object into a header, body, and footer.
 * E.g.:
 *
 * HEADER
 * inherit "/std/room";
 *
 * void create_room()
 * {
 * BODY
 *     set_name("Nothing");
 *
 *     add_prop(OBJ_I_WEIGHT, 10);
 *
 * FOOTER
 * }
 *
 * void
 * init()
 * {
 *     etc...
 */
string *
divide_object(string str)
{
    int i, num;
    string s1, s2, s3, s4, s5, s6,
           ret0, ret1, ret2;

    sscanf(str, "%screate_%s{%s", s1, s2, s3);
    s1 += "create_";

    ret0 = s1 + s2 + "{";

    ret1 = "";

    for(i=0;i<strlen(s3);i++)
    {
       if(s3[i] == '{')
          num++;
       else if(s3[i] == '}')
          num--;

       if(num > -1)
          ret1 += strchar(s3[i]);
       else
       {
          ret2 = s3[i .. strlen(s3) - 1];
          break;
       }
    }

    return ({ ret0, ret1, ret2 });
}

string
file_from_str(string str)
{
    string dir, file;
    object *things;

    /* *** Get the file *** */

    /* Wizards current dir path */
    dir = this_player()->query_path();
    file = "";

    /* Selected the room */
    if(str == "here")
        file = MASTER_OB(environment(this_player())) + ".c";

    /* Otherwise, try to figure out what the player is trying to select */
    if(file_size(file) < 0)
        file = dir + "/" + str;

    if(file_size(file) < 0)
        file += ".c";

    if(file_size(file) < 0)
        file = str;

    if(file_size(file) < 0)
        file += ".c";

    /* Selected an object? */
    if(file_size(file) < 0)
    {
        things = FIND_STR_IN_OBJECT(str, this_player());
        if(!sizeof(things))
            things = FIND_STR_IN_OBJECT(str, environment(this_player()));
        if(!sizeof(things))
        {
            notify_fail("Failed: no such file or object: " + str + ".\n");
            return 0;
        }

        file = MASTER_OB(things[0]) + ".c";
        if(file_size(file) < 0)
        {
           notify_fail("Failed: no such file or object: " + str + ".\n");
           return 0;
        }
     }

    return file;
}

int
last_char(string str)
{
    if(!strlen(str))
      return 0;
    else
      return str[strlen(str) - 1];
}


