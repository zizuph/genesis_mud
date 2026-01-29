#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <std.h>

inherit "/lib/keep";
inherit "/std/object";

#define EYEPATCH_SUBLOC   "_eyepatch_subloc"

int worn = 0;

void
create_object()
{
    set_name("eyepatch");
    add_name("patch");
    add_adj("black"); 
    set_short("black eyepatch");
    set_long("This eyepatch has been made completely out of thick "+
             "leather. The large patch ends in two leather straps, "+
             "which enables the wearer to tie it over one of the "+
             "eyes. A small note has been attached to the patch.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_M_NO_SELL, 1);

    add_item(({"words", "note"}),"The words read:\n"+
                                "'etie'     - Tie the patch around your head.\n"+
                                "'elift'    - Reveal an eyeless socket.\n"+
                                "'etwang'   - Attempt to pull the patch away.\n"+
                                "'eadjust'  - Adjust your patch.\n");
}

int
wear_eyepatch(string str)
{
    NF("Wear what?\n");
    if (!str)
        return 0;

    if (str != "patch" && str != "eyepatch")
        return 0;

    NF("You are already wearing your eyepatch.\n");
    if (worn == 1)
        return 0;

    if (TP->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
        worn = 1;

        write("You tie your back eyepath around your head, making sure "+
              "that the patch covers one of your eyes.\n");
        say(QCTNAME(TP)+" ties "+POSSESSIVE(TP)+" black eyepatch "+
            "around "+POSSESSIVE(TP)+ " head.\n");

        TP->add_subloc(EYEPATCH_SUBLOC, TO);
        set_no_show_composite(1);
        return 1;
    } 
    else
        write("Only true pirates may wear an eyepatch.\n");
}

int
remove_eyepatch(string str)
{

    NF("Remove what?\n");
    if (!str)
        return 0;

    if (str != "eyepatch" && str != "patch")
        return 0;

    NF("You are not wearing the black eyepatch around your head.\n");
    if (worn == 0)
        return 0;

    worn = 0;

    write("You remove your black eyepatch.\n");
    say(QCTNAME(TP)+" removes "+POSSESSIVE(TP)+
      " black eyepatch.\n");

    TP->remove_subloc(EYEPATCH_SUBLOC);
    set_no_show_composite(0);
    return 1;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{

    string str;

    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You have a black eyepatch covering your right eye.\n";

    if(for_obj == carrier)
        str = "Your right eye is covered with a black eyepatch.\n";
    else
         str = capitalize(carrier->query_possessive()) +" right eye "+
            "is covered with a black eyepatch.\n";
    return str;
}


void leave_env(object from, object to)
{
    ::leave_env(from,to);
    worn = 0;
    TP->remove_subloc(EYEPATCH_SUBLOC);
    set_no_show_composite(0);
}

int
emote_elift()
{
    write("You remove your "+short()+", briefly revealing a grim "+
          "eyeless socket.\n");
    TP->tell_watcher(QCTNAME(TP)+ " removes "+HIS(TP)+
          " "+short()+ ", briefly revealing a grim "+
          "eyeless socket.\n");
    return 1;
}

int
emote_etwang()
{
    write("You pull your "+short()+ " away from your head, but the "+
          "elastic snaps back and it smacks you in the face. OUCH!!\n");
    TP->tell_watcher(QCTNAME(TP)+ " pulls "+HIS(TP)+" "+short()+ " away from "+
        HIS(TP)+" head, but the elastic snaps back and it smacks "+HIM(TP)+
        " in the face. OUCH!!\n");
    return 1;
}

int
emote_eadjust()
{
    write("You adjust your "+short()+" in readiness for an impending raid.\n");
    TP->tell_watcher(QCTNAME(TP)+ " adjusts "+HIS(TP)+" "+short()+" in readiness for "+
        "an impending raid.\n");
    return 1;
}

void
init()
{
    ::init();
    if (this_player() != environment())
        return;

    add_action(wear_eyepatch, "wear");
    add_action(wear_eyepatch, "etie");
    add_action(remove_eyepatch, "remove");
    add_action(emote_elift, "elift");
    add_action(emote_etwang, "etwang");
    add_action(emote_eadjust, "eadjust");
}
