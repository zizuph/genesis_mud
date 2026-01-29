inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

static int worn;

void
create_object()
{
   ::create_object();
   set_name("_fang_");
   add_name("badge");
   set_adj("blood-red");
   set_short("blood-red badge");
   set_pshort("blood-red badges");
   set_long("This blood-red badge is in the shape of a sharp fang. You "+
   "are to wear it on your chest, to show your devotion to the cause "+
   "of the Red Fang.\n"+
   "Try 'fanghelp' to get information on your commands.\n");
   add_prop(OBJ_I_VALUE,1440);
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_M_NO_DROP,"You cannot be rid of this unless you leave "+
   "the Red Fang Guild.\n");
   add_prop(OBJ_M_NO_SELL,"You dare not sale your badge of honor.\n");
   set_alarm(3.0,0.0,"message");
}


int
wear(string arg)
{
    object badge;
    NF("Wear what?\n");
    parse_command("wear "+arg,TP,"'wear' %o",badge);
    if(!badge)
        return 0;
    if(badge != TO)
        return 0;
    NF("But you already wear it!\n");
    if(worn) 
        return 0;
    write("You wear the "+short()+" on your chest.\n");
    say(QCTNAME(TP)+" wears a "+short()+" on "+HIS(TP)+" chest.\n");
    worn = 1;
    TP->add_subloc(file_name(TO), TO);
    set_no_show_composite(1);
    return 1;
}

int
remove(string arg)
{
    NF("Remove what?\n");
    if(!parse_command(arg, TP, " %o ")) return 0;
    NF("First you must have it!\n");
    if(E(TO) != TP) 
        return 0;
    NF("But you don't wear it!\n");
    if(!worn) 
        return 0;
    write("You remove the "+short()+" from your chest.\n");
    say(QCTNAME(TP)+" removes a "+short()+" from "+HIS(TP)+" chest.\n");
    worn = 0;
    TP->remove_subloc(file_name(TO));
    set_no_show_composite(1);
    return 1;
}

string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
      return "";

    if (for_obj != on)
      return capitalize(HE(on))+" is wearing a blood-red badge on "+HIS(on)+
    " chest.\n";
    else
      return "You are wearing a blood-red badge on your chest.\n";
}

void
message(object ob)
{
    tell_object(ob,"Hail Red Fang Warrior! Power to the Goblin Race!\n");
    return;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (to->query_wiz_level())
        return;
    if(to->query_race_name() != "goblin")
    {
        to->catch_msg("Your badge is blown up as you have betrayed the "+
                      "Red Fang by changing your race!\n");
        remove_object();
    }
    if(living(to))
        message(to);
}

void
init()
{
    ::init();
    AA(wear,wear);
    AA(remove,remove);
}
