/*
 * Review Reader.   Arch and Reviewer's version!
 * Orginally by Tintin, editted quite substantually by Napture.
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define MORE_OBJ "/std/board/board_more"

#include "review.h"
#define REVS PATH + "reviews/"

#ifndef TP
#define TP this_player()
#endif

string *files, old_who;

void
create_object()
{
    seteuid(getuid());
    set_name(({"reviewreader", "reader"}));
    set_pname(({"reviewreaders", "readers"}));
    set_short("reviewreader");
    set_pshort("reviewreaders");
    set_long(break_string(
        "This device is made of the finest of elven materials from Lorien, "
      + "put together by Lady Galadriel herself. It has a magical air over "
      + "it.\n", 75) + 
      break_string("Commands are 'read review' 'read review dir' and " +
      "'stop reading'. Once you have read the directory (and there are " +
      "reviews for you to read), then use 'read #n' where n is the number " +
      "of the review that you want to read.\n", 75) +
       break_string("As this is the better version, you may specify " +
       "a name at the end of the above commands - eg 'read review tintin' " +
       "or 'read review dir wiz'.  Also, you may 'list reviews' and " +
       "'list domains' to see what is available.\n", 70));                   
    /* Some properties */
    add_prop(OBJ_I_NO_DROP,"@@slow_destruct");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    files = ({});
}

void
init()
{
    add_action("done", "stop");
    add_action("read", "read");
    add_action("list", "list");
}

int
done(string arg)
{
    if (arg && arg == "reading")  {
	write("You discard the review reader now that you have finished.\n");
	say(QCTNAME(this_player()) + " discards something.\n");
        remove_object();
        return 1;
    }
    return 0;
}

int
read(string arg)
{
    object ob;
    int i, namel, which;
    string *args, who;

    notify_fail("What are you trying to read?  A review?\n");
    if (!arg)   return 0;
    
    args = explode(arg, " ");    
    if (member_array(args[sizeof(args)-1], 
	    ({"review", "dir", "directory"})) == -1)  {
/* Must be a name or domain name at the end... */
	who = lower_case(args[sizeof(args)-1]);
	arg = implode(args[0..sizeof(args)-2], " ");
    }
    else 
	who = TP->query_real_name();
    
write("You tried : " + arg + " and for " + who + "\n");    
    if (arg == "review")  {
/* Got this far, so must be within review reader;
 * so we want write, return 1
 * This is the case with in each of these if (arg ==) tests.
 */
        if (file_size(REVS + who) > 0)  {
            ob = clone_object(MORE_OBJ);
            export_uid(ob);
            ob->more(REVS + who, 1);
            return 1;
        }
        write("There is no review written specifically for " + who + ".\n");
        return 1;
    }
    if (arg == "review dir" || arg == "review directory" || arg == "dir"
            || arg == "directory")   {
	if (who == TP->query_real_name())
	    who = TP->query_domain();
	who = capitalize(who);
	old_who = who;
        if (file_size(REVS + who) != -2)  {
            write("There is no directory for the " + who + " Domain!\n");
            return 1;
        }
        if (sizeof(files=
		get_dir(REVS + who + "/*")) < 3)  {
            write("There are no files in the " + who + " domain directory.\n");
            return 1;
        }
        if (files[0]=="." || files[0]=="..") /* Yes, this does appear twice..*/
            files = files[1..sizeof(files) - 1];
        if (files[0]=="." || files[0]=="..")
            files = files[1..sizeof(files) - 1];
            
        namel = 1;
        for (i=0; i<sizeof(files); ++i)  
            if (strlen(files[i])>namel)
                namel=strlen(files[i]) + 1;

        for (i=0; i<sizeof(files); ++i)
            if (file_size(REVS + who + "/" + files[i]) != -2)
                write(sprintf("#%d: %-*s   %s\n", i+1, namel,  files[i], 
                    ctime(file_time(REVS + who + "/" + files[i]))[4..9] ));
	return 1;
    }
    if (sscanf(who, "#%d", which) == 1)  {
        if (!sizeof(files))  {
	    write("You either haven't 'read review dir' before this " +
		"command, or there are no reviews for you to read " +
		"at present.\n" +
		"If you are trying to read something else, then please " +
		"let this review-reader know that you want to <stop " +
		"reading> reviews.\n");
            return 1;
        }
	if (which)  which--;
	if (which > sizeof(files)-1)  {
	    write("There aren't that many reviews to be read! The " +
		"maximum number of reviews is " + sizeof(files) + ".\n" +
		"If you are trying to read something else, then please " +
		"let this review-reader know that you want to <stop " +
		"reading> reviews.\n");
                return 1;
        }
        ob = clone_object(MORE_OBJ);
        export_uid(ob);
write("Trying to read : " + files[which] + " in " + old_who + "\n");
        ob->more(REVS + old_who + "/" + files[which], 1);
        return 1;
    }
    notify_fail("You've reached the end of the read function!\n");
    return 0;
}

list(string arg)
{
    string *files, recur;
    int namel, i, inside, count;
    
    notify_fail("List what?  Reviews or Domains perchance?\n");
    if (!arg)  return 0;
    arg = lower_case(arg);
    if (arg!="reviews" && arg!="rev" && arg!="dir" && arg!="domains")
	return 0;
    
    if (sizeof(files = get_dir(REVS + "*")) < 3)  {
	write("There are no reviews at all to list!\n");
        return 1;
    }
    if (files[0]=="." || files[0]=="..") /* Yes, this does appear twice..*/
        files = files[1..sizeof(files) - 1];
    if (files[0]=="." || files[0]=="..")
        files = files[1..sizeof(files) - 1];
            
    namel = 1;                          /* Get the max length */
    for (i=0; i<sizeof(files); ++i)  
	if (strlen(files[i])>namel)
            namel=strlen(files[i]) + 1;
	   
    count = 0;
    if (arg == "reviews" || arg == "rev")  {
	for (i=0; i<sizeof(files); ++i)
	    if (file_size(REVS + files[i]) != -2)  {
		write(sprintf("%-*s   %s\n", namel,  files[i],  
                    ctime(file_time(REVS + files[i]))[4..9] ));
                count++;
            }
        if (count == 0)
            write("Couldn't find any reviews to list!  Maybe they " +
                  "are all in directories?\n");
    }
    else 
        if (arg == "domains" || arg == "dir")  {
    	    for (i=0; i<sizeof(files); ++i)
		if (file_size(REVS + files[i]) == -2)    
		    write(sprintf("%-*s   Date %s    Number of Files %d\n", 
			namel,  files[i],  
    			ctime(file_time(REVS + files[i]))[4..9], 
			sizeof(get_dir(REVS + files[i] + "/*"))-2 ));
    
	}
	else  {
	    write("Uh-oh...what HAVE you been doing??\n");
	}
    return 1;
}


/*
 * Function name:   slow_destruct
 * Description:     This function is called before the object is dropped
 *                  by the OBJ_I_NO_DROP property.
 * Returns:         0 (the object can be dropped)
 */
int
slow_destruct()
{
  /* Let this object be dropped initially, but check afterwards */
    call_out("check_environment",1);
    return 0;
}


/*
 * Function name:   check_environment
 * Description:     Don't destroy this object if it is held by a person.
 */
void
check_environment()
{
  /* Is this object still carried by a person? */
    if (!living(environment()))
    {
        tell_room(environment(), 
            "The review-reader falls on the floor and shatters to pieces.\n");
        remove_object();
    }
}

enter_env(object dest, object from) 
{
    ::enter_env(dest, from);
    if (!living(dest))  {
	remove_object();
    }
    if (dest->query_wiz_level() < 40 && member_array(
		dest->query_real_name(), GLOBAL_READ) == -1)  {
	dest->catch_msg("You are NOT allowed this item!\n");
	remove_object();		
    }
}


