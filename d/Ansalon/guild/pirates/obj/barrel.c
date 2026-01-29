/* Navarre July 3rd 2006, fixed typo, changed cherywood to cherrywood */



inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"


#define OBJ_I_DONATED_TO_PIRATES   "_obj_i_donated_to_pirates"

void
create_container()
{
    set_name("barrel");
    set_adj("reinforced");
    add_adj("wooden");
    set_short("reinforced wooden barrel");
    set_long("@@long_descr");
    add_prop(CONT_I_WEIGHT, 4500);      /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 300000); /* grams */
    add_prop(CONT_I_VOLUME, 8000);      /* ml */
    add_prop(CONT_I_MAX_VOLUME, 300000); /* ml */
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "Take the barrel? How strong do you think you are?\n");
    add_prop(OBJ_I_VALUE, 120);
}


void
enter_inv(object obj, object from)
{
   if (living(obj))
      {
      write("You cannot put that into the barrel.\n");
      return;
   }
   ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
   ::leave_inv(obj,to);
}

string
long_descr()
{
   return "This barrel has been delicately carved out of cherrywood. Four "+
          "thick steel rings surround it and keeps the wood tight "+
          "together, making it very sturdy. The words 'The Pirates "+
          "Donation Barrel' has been etched into the wood.\n";
}

public int
do_default_close(string str)
{
    write("The barrel doesn't have any lid, you can't close it!\n");
    return 1;
}


/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    if (TP->query_guild_name_lay() != "Pirate of the Bloodsea")
    {
        write("Steal the pirates treasure, that they have stolen "+
              "fair and square? Are you mad?!\n");
        return 1;
    }
    return 0;
}


/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container
 *                to see if we allow it to enter.
 * Arguments:     object ob - the object trying to enter
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    string text;

    if (living(ob))
    {
       write("You can't put THAT thing on the table!\n");
   	   return 1;
    }

    setuid();
    seteuid(getuid());

    if (ob->query_value() > 1000 || ob->query_prop("_magic_am_magic"))
    {
        text = read_file("/d/Ansalon/log/donate_log.txt"); 
        text = strlen(text) ? implode(explode(text, "\n")[-19..], "\n") : "";

        rm("/d/Ansalon/log/donate_log.txt");
        write_file("/d/Ansalon/log/donate_log.txt",
            text + "\n" + extract(ctime(time()), 4, 15)+ " -- "+
            TP->query_name() + " donated: "+
            ob->short()+ ".\n");
    }
    write("You feel as if the Pirate King senses your donation.\n");
    return 0;
}

