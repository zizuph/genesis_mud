/*
 * Review Reader.
 * Orginally by Tintin, editted quite substantually by Napture.
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define MORE_OBJ "/std/board/board_more"

#include "review.h"
#define REVS PATH + "reviews/"

string *files;

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
      "of the review that you want to read.\n", 75));
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

    notify_fail("What are you trying to read?  A review?\n");
    if (!arg)   return 0;
    
    if (arg == "review")  {
/* Got this far, so must be within review reader;
 * so we want write, return 1
 * This is the case with in each of these if (arg ==) tests.
 */
        if (file_size(REVS + this_player()->query_real_name()) > 0)  {
            ob = clone_object(MORE_OBJ);
            export_uid(ob);
            ob->more(REVS + this_player()->query_real_name(), 1);
            return 1;
        }
        write("There is no review written specifically for you.\n");
        return 1;
    }
    if (arg == "review dir" || arg == "review directory" || arg == "dir"
            || arg == "directory")   {
        if (file_size(REVS + this_player()->query_domain()) != -2)  {
            write("There is no directory for your Domain!\n");
            return 1;
        }
        if (sizeof(files=
		get_dir(REVS+this_player()->query_domain()+"/*")) < 3)  {
            write("There are no files in your domain directory.\n");
            return 1;
        }
        if (files[0]=="." || files[0]=="..") /* Yes, this does appear twice..*/
            files = files[1..sizeof(files) - 1];
        if (files[0]=="." || files[0]=="..")
            files = files[1..sizeof(files) - 1];
            
        namel = 1;
        for (i=0; i<sizeof(files); ++i)  
            if (strlen(files[i])>namel)
                namel=strlen(files[i]) + 1;;

        for (i=0; i<sizeof(files); ++i)
            if (file_size(REVS+this_player()->query_domain()+"/"+files[i])!=-2)
                write(sprintf("#%d: %-*s   %s\n", i+1, namel,  files[i], 
                    ctime(file_time(REVS + this_player()->query_domain()
                    + "/" + files[i]))[4..9] ));
 	return 1;
    }
    if (sscanf(arg, "#%d", which) == 1)  {
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
        ob->more(REVS + this_player()->query_domain() + "/" + 
            files[which], 1);
        return 1;
    }
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


