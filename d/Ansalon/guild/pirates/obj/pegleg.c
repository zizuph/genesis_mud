#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <std.h>
#include <cmdparse.h>

inherit "/lib/keep";
inherit "/lib/commands";
inherit "/std/object";

#define LEG_SUBLOC   "_pegleg_subloc"

int worn = 0;

void
create_object()
{
    set_name("pegleg");
    add_adj("wooden");
    set_short("wooden pegleg");
    set_long("This is a light pegleg, that has been made out of oakwood. "+
             "Two thick leather strips connected to the top of the pegleg "+
             "enables the wearer to strap it on. A few words have been etched "+
             "in to the wood.\n");

    add_item(({"words", "writing"}),"The words read:\n"+
                                "'strap'         - Strap on the pegleg.\n"+
                                "'ltwirl'        - Twirl the pegleg around your head.\n"+
                                "'lexamine'      - Examine the pegleg for woodworm.\n"+
                                "'lhobble'       - Hobble around in circles.       \n"+
                                "'lbop <target>' - Bop <target> with your pegleg.\n");

    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE,100);
    add_prop(OBJ_M_NO_SELL, 1);
}

int
wear_pegleg(string str)
{
    NF("Wear what?\n");
    if (!str)
        return 0;

    if (str != "leg" && str != "pegleg")
        return 0;

    NF("You are already wearing your pegleg.\n");
    if (worn == 1)
        return 0;

    if (TP->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
        worn = 1;

        write("You strap your pegleg on you left leg.\n");
        say(QCTNAME(TP)+" straps "+POSSESSIVE(TP)+" pegleg on "+POSSESSIVE(TP)+
            " left leg.\n");

        TP->add_subloc(LEG_SUBLOC, TO);
        set_no_show_composite(1);
        return 1;
    } 
    else
        write("Only true pirates may wear a pegleg.\n");
}

int
remove_pegleg(string str)
{

    NF("Remove what?\n");
    if (!str)
        return 0;

    if (str != "pegleg")
        return 0;

    NF("You are not wearing your pegleg.\n");
    if (worn == 0)
        return 0;

    worn = 0;

    write("You unstrap your pegleg.\n");
    say(QCTNAME(TP)+" unstraps "+POSSESSIVE(TP)+
      " pegleg.\n");

    TP->remove_subloc(LEG_SUBLOC);
    set_no_show_composite(0);
    return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{

    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You have a wooden pegleg strapped to your left leg.\n";

    if(for_obj == carrier)
        str = "Your left leg has been replaced with a wooden pegleg.\n";
    else
         str = capitalize(carrier->query_possessive()) +" left leg has been "+
            "replaced with a wooden pegleg.\n";
    return str;
}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    worn = 0;
    TP->remove_subloc(LEG_SUBLOC);
    set_no_show_composite(0);
}


int
emote_ltwirl()
{
    write("You remove your pegleg and twirl it around your head "+
          "in a drunken display of showmanship.\nYou fall flat on "+
          "your face.\n");
    TP->tell_watcher(QCTNAME(TP)+ " removes "+HIS(TP)+" pegleg and twirls "+
          "it round "+HIS(TP)+" head in a drunken display of showmanship.\n"+
          C(HE(TP))+" falls flat on "+HIS(TP)+" face.\n");
    return 1;
}

int
emote_lexamine()
{
    write("You carefully inspect your pegleg for obvious signs "+
          "of woodworm.\n");
    TP->tell_watcher(QCTNAME(TP)+ " carefully inspects "+HIS(TP)+
          " pegleg for obvious signs of woodworm.\n");
    return 1;
}
 
int
emote_lhobble()
{
    write("You hobble around in circles trying to get to grips "+
          "with your pegleg.\n");
    TP->tell_watcher(QCTNAME(TP)+ " hobbles around in circles "+
          "trying to get to grips with "+HIS(TP)+ " pegleg.\n");
    return 1;
}
 
int
emote_lbop(string str)
{
    object *ob;
    object obj;

    if(!strlen(str))
    {
	      notify_fail("Bop whom with your pegleg?\n");
	      return 0;
    }

    ob = PARSE_THIS(str, "[the] %l");

    if(!sizeof(ob))
    {
	      notify_fail("Bop whom with your pegleg?\n");
	      return 0;
    }

    obj = ob[0];

    actor("You remove you pegleg and bop", ob," over the head with it.");
    target(" removes "+HIS(TP)+ " pegleg and bops you over the head with it.", ob);
    all2act(" removes "+HIS(TP)+" pegleg and bops", ob," over the head with it.");
    return 1;
}

void
init()
{
    ::init();
    if (this_player() != environment())
        return;

    add_action(wear_pegleg, "wear");
    add_action(wear_pegleg, "strap");
    add_action(remove_pegleg, "remove");
    add_action(emote_ltwirl, "ltwirl");
    add_action(emote_lexamine, "lexamine");
    add_action(emote_lhobble, "lhobble");
    add_action(emote_lbop, "lbop");
}
