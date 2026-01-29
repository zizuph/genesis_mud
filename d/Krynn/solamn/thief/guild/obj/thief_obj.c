/* The guild object for the Cabal of Hiddukel Thief Guild. */
/* created by Aridor,  02/08/94 */

/* Adjusted by Mercade, May 2006
 * - Had to change the key storage from inventory based to object array based
 *   since quitting moves the keys out of the key ring. Also, when keys are
 *   moved into the ring, make them undroppable.
 */

/* Navarre August 5th 2007.
 * Fixed remove key.
 */

inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/* Global variables. */
static int     show_title;
static object *keys = ({ });

string
my_long()
{
    string str = "  ";
    if (sizeof(keys) == 0)
      str += "There are no keys attached.";
    else if (sizeof(keys) == 1)
      str += "There is " + LANG_WNUM(sizeof(keys)) + " key attached.";
    else 
      str += "There are " + LANG_WNUM(sizeof(keys)) + " keys attached.";
    return "This is an ordinary key ring, except for the fact that you " +
      "have been entrusted with it as your token of membership in the " +
      "Cabal of Hiddukel. To see what you can do with it, type 'help " +
      "thief menu'.\n" + str + "\n";
}

string
my_keys()
{
    string str;

    if (sizeof(keys) > 0)
      str = "There is " + COMPOSITE_DEAD(keys) + " attached to the keyring.";
    else
      str = "There are no keys attached to the keyring.";
    return str + "\n";
}

void
create_container()
{
    if (!IS_CLONE)
      return;
    
    set_name("key ring");
    add_name("keyring");
    add_name("cabal_of_hiddukel_thief_obj");
    add_name(THIEF_OBJ_ID);
    
    set_long(my_long);
    add_item(({"keys","keys on keyring"}), my_keys);
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(CONT_M_NO_INS, "You can only 'add' keys to the keyring.\n");
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(CONT_I_ATTACH, 1);
    /*add_prop(CONT_I_IN, 0);*/
    add_prop(CONT_I_HIDDEN, 1);
    add_prop(CONT_I_VOLUME, 10);
    add_prop(CONT_I_WEIGHT, 10);
    add_prop(CONT_I_MAX_VOLUME, 800);
    add_prop(CONT_I_MAX_WEIGHT, 600);
    add_prop(CONT_I_REDUCE_WEIGHT, 300);
    add_prop(CONT_I_REDUCE_VOLUME, 300);
}

public int
prevent_enter(object ob)
{
    /* All keys are forcefully added through the add routine. */
    return 1;
}

public int
prevent_leave(object ob)
{
    /* All keys are forcefully removed through the add routine. */
    return 1;
}

string
query_key_master_ob(object ob)
{
    return MASTER_OB(ob);
}

string
query_auto_load()
{
    keys = filter(keys, objectp);
    return MASTER_OB(this_object()) + ":#" + show_title + "##" +
        implode(map(keys, query_key_master_ob), "$$"); 
}

void
give_message(int who)
{
    if (who)
      E(TO)->catch_msg("\nThere is a note for the Ringleader in " +
		       "the Cabal of Hiddukel.\n\n");
    else
      E(TO)->catch_msg("\nThere is a note for you in the post " +
		       "office in the Cabal of Hiddukel from " +
		       "the Ringleader.\n\n");
}

/* We clone each key individually called by an alarm, due to the
 * fact that keys may stop existing, and thus will generate an
 * error. With this setup, all other keys will still be loaded.
 */
void
clone_one_key(string key)
{
    object ob;
    
    ob = clone_object(key);
    ob->move(TO, 1);
    ob->add_prop(OBJ_I_NO_DROP, 1);
    keys += ({ ob });
    keys = filter(keys, objectp);
}

void
delay_init_arg(string key_arg)
{ 
    string *key_names;
    object key;
    int i;

    seteuid(getuid(TO));
    key_names = explode(key_arg,"$$");
    for(i=0;i<sizeof(key_names);i++)
      set_alarm(0.0,0.0,&clone_one_key(key_names[i]));

    if (POSTMASTER->has_mail(E(TO),0))
      set_alarm(2.0,0.0,&give_message(0));
    
    if ((MASTER_ROOM)->is_master(E(TO)) &&
	(POSTMASTER)->has_mail(E(TO),1))
      set_alarm(3.0,0.0,&give_message(1));
}

void
init_arg(string str)
{
    string key_arg;

    if (sscanf(str, "#%d##%s", show_title, key_arg) != 2)
      show_title = 0;
    else
      set_alarm(0.1,0.0, &delay_init_arg(key_arg));
}

void
check_actions(object who)
{
    if (who != E(TO))
        return;

    if (LAYMAN(who))
        MASTER_ROOM->check_actions(who);
    else if (!who->query_wiz_level())
        remove_object();
}

int
add_a_key(string str)
{
    object *ky;
    object *succ = ({ }), *fail = ({ });
    int i;
    string str1,str2;

    if (!str)
      return 0;
    if (sscanf(str,"%s to %s",str1,str2) != 2)
      str1 = str;

    ky = FIND_STR_IN_OBJECT(str1,TP);
    NF(C(query_verb()) + " what?\n");
    if (!ky || !sizeof(ky))
      return 0;

    NF(C(query_verb()) + " what to where?\n");
    if (!str2 || (str2 != "key ring" &&
		  str2 != "keyring"))
      return 0;

    ky -= ({ TO, 0 });
    for(i=0;i<sizeof(ky);i++)
      {
	  if ((sizeof(all_inventory(TO)) < KEYS_ON_RING) &&
	      IS_KEY_OBJECT(ky[i]) &&
	      !ky[i]->query_prop(KEY_I_NO_KEYRING) &&
	      !ky[i]->move(TO,1))
	    succ += ({ ky[i] });
	  else
	    fail += ({ ky[i] });
	  
      }
    if (sizeof(succ))
    {
      succ->add_prop(OBJ_I_NO_DROP, 1);
      keys += succ;
      keys = filter(keys, objectp);
      write("You " + query_verb() + " " + COMPOSITE_DEAD(succ) +
	    " to the key ring.\n");
    }
    if (sizeof(fail))
      write("You fail to " + query_verb() + " " + COMPOSITE_DEAD(fail) +
	    " to the key ring.\n");
    if (sizeof(all_inventory(TO)) >= KEYS_ON_RING)
      write("The key ring is full, no more keys fit on it.\n");
    return 1;
}

int
remove_a_key(string str)
{
    object *ky;
    object *succ = ({ }), *fail = ({ });
    int i;
    string str1,str2;

    NF(C(query_verb()) + " what from where?\n");
    if (!str || sscanf(str,"%s from %s",str1, str2) != 2)
      return 0;

    ky = FIND_STR_IN_OBJECT(str1,TO);
    NF(C(query_verb()) + " what?\n");
    if (!ky || !sizeof(ky))
      return 0;

    NF(C(query_verb()) + " what from where?\n");
    if (!str2 || (str2 != "key ring" &&
		  str2 != "keyring"))
      return 0;
    ky -= ({ TO, 0 });
    for(i=0;i<sizeof(ky);i++)
      {
	  if (E(ky[i]) == TO &&
	      !ky[i]->move(TP,1))
	    succ += ({ ky[i] });
	  else
	    fail += ({ ky[i] });
	  
      }
    if (sizeof(succ))
    {
	succ->remove_prop(OBJ_I_NO_DROP);

	for(int i = 0; i < sizeof(succ); i++)
	{
	    keys = keys - ({ succ[i] });
	}
	
	keys = filter(keys, objectp);
	write("You " + query_verb() + " " + COMPOSITE_DEAD(succ) +
	      " from the key ring.\n");
    }
    if (sizeof(fail))
	write("You fail to " + query_verb() + " " + COMPOSITE_DEAD(fail) +
	      " from the key ring.\n");
    if (sizeof(all_inventory(TO)) == 0)
	write("The key ring is empty, there are no keys attached.\n");
    return 1;
}

void
init()
{
    ::init();

    if (!MEMBER(TP) && (E(TO) == TP) && !TP->query_wiz_level())
    {
        write("You are not a member of the Cabal of Hiddukel! Cheater!\n");
        remove_object();
        return;
    }
    if (!interactive(TP))
    {
        return;
    }

    seteuid(getuid(TO));
    this_player()->add_cmdsoul(THIEF_SOUL);
    this_player()->update_hooks();

    add_action("add_a_key", "add");
    add_action("add_a_key", "append");
    add_action("remove_a_key", "remove");

    set_alarm(30.0, 0.0, &check_actions(TP));
}

int
query_show_title_on_intro()
{
    return show_title;
}

void
set_show_title_on_intro(int id)
{
    show_title = id;
}

/* query_recover
 * don't allow this object to be recoverable since it is already
 * autoloading!
 */
string
query_recover()
{ 
    return 0; 
}
