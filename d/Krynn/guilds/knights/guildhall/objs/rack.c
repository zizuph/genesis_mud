/*
 * The armoury rack in the guild of the solamnian knights
 *
 * Made by Nick
 *                        Update: 4 May 1995 by Grace
 *                                Commented out added properties per AoB request.
 *                                (see lines 90, 110, 135, 159)
 */
inherit "/std/container";

#include "../../guild.h"
#include "/d/Krynn/common/defs.h"

#include <stdproperties.h>
#include <macros.h>

/*
 * Prototypes
 */
void restore_old_objects();
void update_box_state(object ob, int enter);
void update_box_state_heap();

/*
 * Variables
 */
public string *auto; /* Autoloading objects */
public string  *recover; /* Recoverable objects */
static int recovering; /* Recovering objects, don't log and so on */
static int no_update = 0; /* Needed when the object is destructed */
static object armoury = find_object(VROOM + "armoury");

void
create_container()
{
    set_name("rack");
    add_name("krynnarm_rack");
    set_adj("equipment");
    set_long("This rack contains expensive equipment that members of the Solamnian"
	     + " Knighthood have donated to further the cause of their guild"
	     + ". If you are a Solamnian Knight you may put or take items"
	     + " from the racks.\n");
    add_prop(OBJ_I_VALUE, 2031);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 14000000);
    add_prop(CONT_I_MAX_WEIGHT, 39000000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The rack won't budge.\n");
    
    seteuid(getuid());

    if (IS_CLONE)
      restore_old_objects();
}

void
enter_inv(object ob, object from)
{
    int val, noget;
    string stringtmp;

    ::enter_inv(ob, from);

    if (!IS_CLONE)
      return;

    if (recovering)
      return;

    ob->remove_prop(OBJ_M_NO_GET);

    seteuid(getuid(this_object()));
    if (!ob->query_prop(CHAR_OBJ) && !ob->query_prop(HEAP_I_IS))
    {
	ob->add_prop(CHAR_WHO_GAVE, this_player()->query_real_name());
	ob->add_prop(CHAR_OBJ, 1);
	if (stringp(ob->query_long())) //MK fix: may be functionp
	{
	    stringtmp = ob->query_long();
	    stringtmp += "\n(Donated by "+this_player()->query_name()+".)\n";
	    ob->set_long(stringtmp);
	}
    }
    
    update_box_state(ob, 1);
}
/* ***This function no longer needed with the no_get prop removed  /|Grace *** */
mixed
check_no_get(string str)
{
    object ob = find_object(str);
    if (!ob)  /* something is seriously wrong in this case */
      return "Bug?!? please report in or near Vingaard Keep.\n";
    if (TP->query_real_name() == ob->query_prop("_char_s_current_owner"))
    {
        if (query_verb() == "give")
            return "This object is entrusted to you and should not be " +
                   "given away!\n";
        else
            return 0;
     }
    else
      return "This object was entrusted to a Knight by Paladine. " +
	"Having been carelessly dropped, it cannot be recovered!\n";
}

void
leave_inv(object ob, object to)
{
    int val;
    
    ::leave_inv(ob, to);
    
    if (!IS_CLONE)
      return;

    if (!objectp(ob)) return;
    if (recovering)
      return;
    ob->add_prop("_char_s_current_owner",to->query_real_name());
/* 
    ******These properties removed per the request of the AoB (Sorgum)******

    ob->add_prop(OBJ_M_NO_GIVE,"This object was entrusted to you by " +
		 "Paladine. You cannot give it away.\n");
    ob->add_prop(OBJ_M_NO_GET,"@@check_no_get:" + file_name(TO) +
		 "|" + file_name(ob) + "@@");
*/
    seteuid(getuid(this_object()));
    update_box_state(ob, 0);
}

void
clone_auto_objects()
{
    int i;
    object ob;
    string arg, file;
    
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(auto); i++)
      if (sscanf(auto[i], "%s:%s", file, arg) == 2)
	{
	    ob = clone_object(file);
	    ob->init_arg(arg);
	    if (!ob->may_not_recover())
	      ob->move(this_object(), 1);
	    else
	    {
		ob->move(armoury,1);
		tell_room(armoury,"A squire arrives, drops " + LANG_ADDART(ob->short()) + " from the high armoury rack and leaves again.\n");
	    }
/* 
            *** Removed per AoB request ***
	    if (!ob->query_prop(OBJ_M_NO_SELL))
	      ob->add_prop(OBJ_M_NO_SELL, "This object has been sacred " +
			   "by Paladine to stay in the world.\n");
*/
	    ob->add_prop(CHAR_OBJ, 1);
	}
}

void
clone_recover_objects()
{
    int i;
    object ob;
    string file, arg;
    
    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(recover); i++)
      if (sscanf(recover[i], "%s:%s", file, arg) == 2)
	{
	    ob = clone_object(file);
	    ob->init_recover(arg);
	    if (!ob->may_not_recover())
	      ob->move(this_object(), 1);
	    else
	    {
		ob->move(armoury,1);
		tell_room(armoury,"A squire arrives, drops " + LANG_ADDART(ob->short()) + " from the high armoury rack and leaves again.\n");
	    }
/*
            *** Removed per AoB request ***
	    if (!ob->query_prop(OBJ_M_NO_SELL))
	      ob->add_prop(OBJ_M_NO_SELL, "This object has been sacred " +
			   "by Paladine to stay in the world.\n");
*/
	    ob->add_prop(CHAR_OBJ, 1);
	}
}

void
restore_old_objects()
{
    seteuid(getuid(this_object()));
    restore_object(CHARITY_FILEHIGH);
    recovering = 1;
    set_alarm(1.0,0.0,"clone_auto_objects");
    set_alarm(1.0,0.0,"clone_recover_objects");
    set_alarm(5.0,0.0,"restore_recovering");
}

void
restore_recovering()
{
    recovering = 0;
    update_box_state_heap();
}

int
query_recovering()
{
    return recovering;
}

void
update_box_state(object ob, int enter)
{
    string tmp;
    int irecover;
    
    if (!(tmp = ob->query_auto_load()))
      {
	  tmp = ob->query_recover();
	  irecover = 1;
      }
    
    if (!tmp)
      return;
    
    if (enter)
      {
	  if (irecover)
	    recover += ({ tmp });
	  else
	    auto += ({ tmp });
      }
    else if (irecover)
      recover -= ({ tmp });
    else
      auto -= ({ tmp });
    
    if (!no_update && IS_CLONE)
      save_object(CHARITY_FILEHIGH);
}

void
update_box_state_heap()
{
    object *arr;
    int i;
    string tmp;
    
    auto = ({});
    recover = ({});
    arr = all_inventory(this_object());
    
    for (i = 0; i < sizeof(arr); i++)
      if (tmp = arr[i]->query_auto_load())
	auto += ({ tmp });
      else if (tmp = arr[i]->query_recover())
	recover += ({ tmp });

    if (!no_update && IS_CLONE)
      save_object(CHARITY_FILEHIGH);
}


void
remove_object()
{
    no_update = 1;
    ::remove_object();
}
