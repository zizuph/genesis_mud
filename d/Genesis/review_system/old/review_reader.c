inherit "/std/object";
#include <stdproperties.h>
#define MORE_OBJ "/std/board/board_more"

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
      + "it.Commands are 'read review' and 'done reading'.\n",70));
  /* Some properties */
    add_prop(OBJ_I_NO_DROP,"@@slow_destruct");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
}

void
init()
{
    add_action("done", "done");
    add_action("read", "read");
}

int
done(string arg)
{
    if (arg && arg == "reading")
    {
	remove_object();
	return 1;
    }
    return 0;
}

int
read(string arg)
{
    object ob;

    if (arg && arg == "review")
    {
	if (file_size("/d/Debug/debugwiz/" + this_player()->query_real_name()) > 0)
	{
	    ob = clone_object(MORE_OBJ);
	    export_uid(ob);
	    ob->more("/d/Debug/debugwiz/" + this_player()->query_real_name(), 1);
	    return 1;
	}
	return 0;
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
            "The mailreader falls on the floor and shatters to pieces.\n");
        remove_object();
    }
}

