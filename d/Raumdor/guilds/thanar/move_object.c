// informational object given to people moved into the new guild

#include "/d/Raumdor/defs.h"
#include "guild.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

int counter = -1;

void
tear_it(void)
{
    write("Your thanarian guild scroll disappeared. Hopefully you managed " +
          "to read it before this happened.\n");
    remove_object();
}

public void
create_object()
{
    if(counter == -1) counter = 5; // number of logins to selfdestruction
    else if(! --counter) set_alarm(0.0, 0.0, tear_it);

    set_name("scroll");
    set_adj("thanar");
    set_short("Thanar guild scroll");
    set_long("This is an important message sent to you by " +
      "the Great Thanar! You can read it, or tear it apart " +
      "when you are done with it.\n");
    add_prop(OBJ_S_WIZINFO, "A scroll that selfdestructs after few logins.\n");
    add_prop(OBJ_M_NO_DROP,"If you want to get rid of it, tear it apart.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 0);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(to->query_guild_name_race() == GUILD_NAME)
    {
        write("\nThere happened a change with your Thanar guild. " +
          "Read the scroll for more information.\n\n");
    }
    else remove_object();
}

public string 
query_auto_load()
{
  return MASTER + ":" + counter;
}

public void
init_arg(string s)
{
   sscanf(s, "%d", counter);
   create_object();
}

int
tear(string s)
{
    if(!s || member_array(s, ({"scroll", "thanar scroll",
                      "scroll apart", "thanar scroll apart"})) == -1)
    {
        notify_fail("Tear what?\n");
        return 0;
    }
    say(QCTNAME(TP) + " tears his scroll apart.\n");
    write("You tear your thanarian guild scroll apart.\n");
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

int
read(string s)
{
    if(!s || member_array(s, ({"scroll", "thanar scroll"})) == -1)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    say(QCTNAME(TP) + " reads over his scroll.\n");
    write("       ____________________________________________________\n"+
    "      / \\                                                  \\\n"+
    "      \\_/__________________________________________________/\n"+
    "      |                                                   |\n"+
    "      |                                                   |\n"+
    "      |         News from the Great Lord Thanar           |\n"+
    "      |         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           |\n"+
    "      |                                                   |\n"+
    "      |    The guildhall has moved and many changes have  |\n"+
    "      | taken place. You have now been given a surname    |\n"+
    "      | and you have also been given a new title. If you  |\n"+
    "      | would like to change your surname you must visit  |\n"+
    "      | Thanar's temple and it will be granted you.       |\n"+
    "      |                                                   |\n"+
    "      |    All other information about the changes will   |\n"+
    "      | be found at the new temple. Travel to the old and |\n"+
    "      | you will find the new if you look close enough.   |\n"+
    "      |                                                   |\n"+
    "      |___________________________________________________|\n"+
    "     / \\                                                  \\\n"+
    "     \\_/__________________________________________________/\n");
    return 1;
}

void
init()
{
    add_action(tear, "tear");
    add_action(read, "read");
}
