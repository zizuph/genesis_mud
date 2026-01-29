/*
 * painting.c
 *
 * Coded: Stexx, July 3, 95
 *
 * This is the base object for the paintings players may buy or order
 * to decorate their apartments.
 *
 * This object is cloned or inherited, and the short/long/names are then
 * modified to create a unique painting. Anything goes, but the first
 * name of the object must be one that can be used in a description, as it
 * is used to generate and additional long in the room once hung.
 * I.e. set_names( ({"a simple painting", "painting", "simple painting"}) );
 */
#include "/d/Immortal/std/domain.h"
#include <cmdparse.h>

#define LIVE_I_APT_OWNER "_live_i_apartment_owner_"
#define PAINTING_FILE "/d/Immortal/stexx/obj/painting"

inherit STDOBJECT;

string hang_me();
void create_object();
string check_owner();
string query_painting();
void set_painting(string str);
int hang_it(string str);
int hang_access(object obj);
int hang_one_painting(object obj);
string hang_me();

static string painting,           /* The painting design */
              g_fail;

void
create_object()
{
  ::create_object();
  set_name("painting");
  set_short("painting");
  set_long("@@query_painting@@\n@@check_owner@@");
}

/*
 * Function name: check_owner
 * Description: For use by a vbfc in the long, appends the long of the 
 *              painting with a message only apartment owners get which
 *              identifies the painting as a possible decoration
 * Returns: A string.
 */
string
check_owner()
{
  if(TP->query_prop(LIVE_I_APT_OWNER))
    {
    return "You suspect this painting would make a nice addition to your "+
      "residence.\n";
    }
  else
    return "";
}

/*
 * Function name: query_painting
 * Description: Queries the description of the painting. If a design has 
 *              not been set, a default description is returned.
 *              Used both to generate a long desc and an add_item in the
 *              room the painting is hung in.
 * Returns: A string.
 */
string 
query_painting()
{
  if(!strlen(painting))
    return "The picture must be modern art, because you don't see any real "+
      "design in it to speak of.";
  else
    return painting;
}

/*
 * Function name: set_painting
 * Description: Sets the painting design.
 * Arguments: str - A string which is the painting itself.
 */
void
set_painting(string str)
{
  painting = str;
}

/*
 * MASKED
 * Function name: init
 * Description: Initiates some commands in the object's environment or 
 *              livings in the object's environment.
 *              In this case, we want to add the 'hang' command to those
 *              who have a painting.
 */
void
init()
{
  /* If we don't call back the the init() in /std/object.c, some default
   * actions may not be properly defined.
   */
  ::init();
  add_action("hang_it", "hang");
}

/*
 * Function name: hang_it
 * Description: Called when a player tries to hang the (or another)
 *              painting.
 *              The format used here is almost identical to the wear
 *              command in /std/armour.c, and allows player's to specify
 *              which painting or paintings (if they have more than one)
 *              to hang.
 * Arguments: str - A string defining which painting to hang. I.e.
 *                  second painting, two paintings, painting.
 * Returns: 0 - failure.
 *          1 - success.
 */
int
hang_it(string str)
{
object *paintings;

  NF("Hang what?\n");

  g_fail = "";

  /* Figure out which paintings are the ones the player is trying to hang */
  /* Use hang_access to figure out if the painting is a hangable one, */
  /* and hang_one_painting to try hanging one. */
  paintings = CMDPARSE_ONE_ITEM(str, "hang_one_painting", "hang_access");

  if(!sizeof(paintings))
    {
    if(!strlen(g_fail))
      return 0;
    else
      TP->catch_msg(g_fail);
    }
    g_fail = 0;
    return 1;
}

/*
 * Function name: hang_access
 * Description: Checks to see if the object passed from the hang_it function
 *              is first a 'hangable' painting, then if the painting is
 *              in the player's inventory or environment (a bit redundant
 *              since that's the only way the player has access to the
 *              hang command, but *shrug*)
 * Arguments: obj - An object to test for being valid for hanging.
 * Return: 0 - object is not hangable
 *         1 - object is hangable
 */
int
hang_access(object obj)
{
  if(function_exists("set_painting", obj) != PAINTING_FILE)
    return 0;
  if(environment(obj) == TP || environment(obj) == environment(TP))
    return 1;
  else
    return 0;
}

/*
 * Function name: hang_one_painting
 * Description: Finds the object that is supposed to be hanged and hangs it.
 *              Note that with this construction the command does not thread
 *              through every painting in the player's inventory to find
 *              say, the fourth painting. This function will find the proper
 *              painting and call the hanging sequence in it, resulting in
 *              less cpu time in threading the interim paintings.
 * Arguments: obj - The object which is to be hung.
 * Returns: 0 - failed to hang
 *          1 - successfully hung
 */
int
hang_one_painting(object obj)
{
  string fail;

  if(TO != obj)
    fail = obj->hang_me();
  else
    fail = hang_me();

  if(stringp(fail))
    {
    g_fail += fail;
    return 0;
    }
  return 1;
}

/*
 * Function name: hang_me
 * Description: Does the actual hanging, delivers the messages, calls
 *              the add_item generator in the room, and destructs the
 *              actual painting.
 * Returns: Failure/success message from add_decoration in the player's
 *          environment.
 */
string
hang_me()
{
  /* Is the room a 'decoratable' room? */
  if(!strlen(function_exists("add_decoration", environment(TP))))
    return "You don't think that this painting will do any good here.\n";

  /* Is the 'hanger' the owner of this room? */
  if(TP->query_real_name() != environment(TP)->query_owner())
    return "You can't just go around decorating other people's places!  "+
      "People will start to talk about you...\n";

  /* In 1/2 second, destruct the painting */
  set_alarm(0.5, 0.0, &remove_object());

  return environment(TP)->add_decoration("wall",
    query_names(),
    query_painting()+"\n" );
}
