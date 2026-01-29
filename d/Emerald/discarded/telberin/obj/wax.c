/* Cloned by hive. */
inherit "/std/object";

#include "default.h"
#include "/d/Emerald/defs.h"

#define LIVE_I_HAVE_WAXED_EARS "_live_i_have_waxed_ears"

#define WAX_SUBLOC "_wax_subloc"

int do_wear(string str);
int do_plug(string str);
int do_remove(string str);

void
create_object()
{
   set_short("beeswax");
   set_name("wax");
   add_name("beeswax");
   add_name("_quest_wax_");
   set_long("This dark yellow beeswax is from a productive hive made by the" +
            " workers all day long.\n");
   add_prop(OBJ_I_WEIGHT, 23);
   add_prop(OBJ_I_VOLUME, 24);
   add_prop(OBJ_I_VALUE, 14);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_M_NO_DROP, "@@drop_me@@");
}

drop_me()
{
   if(TP->query_prop(LIVE_I_HAVE_WAXED_EARS))
   {
	write("You have to take the wax out of your ears first.\n");
	return 1;
   }
   return 0;
}

void
init()
{
   ::init();
   add_action(do_wear, "wear");
   add_action(do_plug, "plug");
   add_action(do_remove, "unplug");
   add_action(do_remove, "unplug");
}

int
do_wear(string str)
{
    if (!str)                   /* can't be bothered to do better checks
                                   So I bet the mortals moan..... */
        return 0;
    if (str == "wax" || 
            parse_command(str, TP, "'wax' [in] 'ear' / 'ears'"))  {
        if (TP->query_prop(LIVE_I_HAVE_WAXED_EARS))  {
            write("You are already wearing the wax!\n");
            return 1;
        }
        write("You start wearing the wax by putting it in your ears.\n");
        say(TP->query_The_name() + " wears some wax in " +
            TP->query_possessive() + " ears.\n");
        TP->add_prop(LIVE_I_HAVE_WAXED_EARS, 1);
	TP->add_subloc(WAX_SUBLOC, this_object());
        set_no_show();
        return 1;
    }
    return 0;
}

int
do_plug(string str)
{
    if (!str)
        return 0;
    if (str == "wax" || 
            parse_command(str, TP, "'ear' / 'ears' [with] 'wax'"))  {
        if (TP->query_prop(LIVE_I_HAVE_WAXED_EARS))  {
            write("You have already plugged your ears with the wax!\n");
            return 1;
        }
        write("You plug your ears with the wax.\n");
        say(TP->query_The_name() + " stuffs some wax into " +
            TP->query_possessive() + " ears.\n");
        TP->add_prop(LIVE_I_HAVE_WAXED_EARS, 1);
	TP->add_subloc(WAX_SUBLOC, this_object());
        set_no_show();
        return 1;
    }
    
    return 0;
}

int
do_remove(string str)
{
    if (!str) 
        return 0;
    if (str == "wax" || 
            parse_command(str, TP, "'wax' [from] 'ear' / 'ears'"))  {
        if (!TP->query_prop(LIVE_I_HAVE_WAXED_EARS))  {
            write("What wax?  Maybe you should wear it first?\n");
            return 1;
        }
        TP->remove_prop(LIVE_I_HAVE_WAXED_EARS);
        write("You remove the wax from your ears.\n");
        say(TP->query_The_name() + " removes some wax from " +
            TP->query_possessive() + " ears.\n");
        unset_no_show();
	unset_no_show_composite();
	TP->remove_subloc(WAX_SUBLOC);
        return 1;
    }
    return 0;
}

show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   if(for_obj == carrier)
      str = "You have wax stuffed in your ears.\n";
   else
      str = capitalize(carrier->query_pronoun())+
   " has wax stuffed in "+TP->query_possessive()+" ears.\n";
   return str;
}
