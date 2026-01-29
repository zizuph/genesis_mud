inherit "/std/monster";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

/* global vars */
int log_file;
string get_file;

void create_monster()
{
  set_name("helper");
  set_short("Rhovanion helper");
  set_long("This is Rhovanion helper. You can:\n"+
           "    'order helper start log'\n"+
           "or  'order helper stop log'\n");
  set_race_name("human");
  /*          str dex con int wis dis */
  set_stats(({34, 54, 30, 15, 17, 30}));
}

void init_living()
{
  ::init_living();
  add_action("do_order","order");
}

void catch_msg(mixed str, object from)
{
    mixed *sarray;

    seteuid(getuid());
    ::catch_msg(str, from);

    if(log_file && (from != this_object()))
    {
        if(stringp(str))
        {
            write_file(get_file, check_call(str));
        }
        else
        {
            write_file(get_file, check_call(str[0]));
        }
    }
}

int do_order(string args)
{
    object tp = this_player();

    seteuid(getuid());

    NF("Order what?\n");
    if(!args) return 0;
    if(member_array(tp->query_real_name(),
       "secure/master"->query_domain_members("Rhovanion")) < 0)
    {
        write("Only Rhovanion wizards can order helper.\n");
        return 0;
    }

    if(args == "helper stop log")
    {
        if(log_file)
        {
            log_file = 0;
            set_tell_active(0);
            write_file(get_file,"LOG STOPPED: "+ctime(time())+"\n");
            command("say Stopped logging in: "+get_file);
            return 1;
        }
        command("say I am not logging anything now.");
        return 1;
    }
    if(args == "helper start log")
    {
        if(log_file)
        {
            write("Already making log in: "+get_file+"\n");
            return 1;
        }
        get_file = "/d/Rhovanion/meeting/"+
                   implode(explode(ctime(time())," "),"_");
        command("say Starting log in: "+get_file);
        log_file = 1;
        set_tell_active(1);
        return 1;
    }
    return 0;
}
