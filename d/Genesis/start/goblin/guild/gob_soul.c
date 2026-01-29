/*
  Written by Quis for the Goblin Start area, 24 Aug 1992
  /d/Genesis/start/goblins/guild/gob_soul.c
*/

#pragma save_binary

inherit "/cmd/std/soul_cmd";

#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

#include "../goblins.h"

/* 
 * Prototypes
 */

static mixed parse_this(string str, string form);
static string desc_many(object *oblist);
static string desc_vbfc(object ob);

/* 
 * Return a proper name of the soul in order to get a nice printout.
 */

string
get_soul_id()
{
    return "goblin tribal soul";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()    
{
    return ([
           "drool":"drool",
           "grunt":"grunt",
           "scratch":"scratch"
	 ]);
}

int
drool(string str)
{
    object         *oblist;

    notify_fail("Drool on whom?\n");

    if (!strlen(str))
    {
      write("You drool on your shirt.\n");
      all(" drools on " + this_player()->query_possessive()+ " shirt.");
      return 1;
    }
    oblist = parse_this(str, "[on] [on the] %l");

    if(!sizeof(oblist)) return 0;

    target(" drools all over you!", oblist);
    actor("You drool on", oblist);
    all2act(" drools on", oblist);
    return 1;
}

int
grunt(string str)
{
    if (strlen(str))
    {
      notify_fail("Grunt what?\n");
      return 0;
    }
    write("Unhh!!\n");
    all(" grunts angrily.");
    return 1;
}

int
scratch(string str)
{
    if (strlen(str))
    {
      notify_fail("Scratch what?\n");
      return 0;
    }
    write("Ahh..!!\n");
    if (this_player()->query_gender()==G_MALE)
        all(" scratches his testicles.");
    else if (this_player()->query_gender()==G_FEMALE)
        all(" scratches her armpit.");
    else 
        all(" scratches its fleas.");
 
    return 1;
}