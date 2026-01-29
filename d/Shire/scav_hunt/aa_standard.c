/*
 * Modified standard of Angmar's Army
 * Cleaned up for Scavenger hunt 2001 to go with the costume
 * -- Finwe, October 2001
 *
 * Thanks Milan and Co for the original code!!!
 */

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"

inherit "/std/object";
inherit "/cmd/std/command_driver";

#define SUBLOC_STANDARD "_s_c_standard_subloc"
#define CHEER    ONE_OF_LIST(({"cheer","bounce","applaud",\
                   "shout ANGMAR ! ANGMAR !! ANGMAR !!!"}))

// standard not hidden by default
int is_shown = 1;

// prototypes
int hide(string str);
int unroll(string str);
int wave(string str);
int plant(string str);
int raise(string str);
int lower(string str);
int rally(string str);
int help(string str);

void
create_object()
{
    set_name(({"standard","angmar","Angmar","flag"}));
    set_adj(({"red","and","black","standard","of","angmar","Angmar"}));
    set_short("faded standard of Angmar's Army");
    set_long("@@my_long");

    add_item("flag", "@@my_long");
    add_item(({"pole","long pole"}), "It is a simple long wooden pole "+
        "that bears the flag on its end. You also notice that there "+
        "is <help AA standard> written in blood on it.\n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
//    add_prop(OBJ_M_NO_SELL,"You would never sell the standard of Angmar.\n");
//    add_prop(OBJ_M_NO_DROP,"You decide to keep the standard.\n");
}

string
my_long()
{
    if(is_shown)
        return "It is the red and black flag on a long pole. It bears the "+
            "symbol of a Dunedain head on a black shield being "+
            "smashed in by a heavy mace. On the pole, written in blood, is written <help AA standard>. \n";
    return "It is the red and black flag neatly rolled around a long pole.\n";
}

void
init()
{
    ::init();
//    add_action(hide,"hide");
    add_action(hide,"hide");
    add_action(unroll,"unroll");
    add_action(wave,"wave");
    add_action(plant,"plant");
    add_action(raise,"raise");
    add_action(lower,"lower");
    add_action(rally,"rally");
    add_action(help,"help");
}

int
help(string str)
{
    string *arr, sss;

    if(!str && (str != "AA standard") && (str != "aa standard") 
        && (str != "AA faded standard") && (str != "aa faded standard")) 
        return 0;

    write("The standard provides the following emotes:\n"+
        "   unroll standard\n"+
        "   hide standard\n"+
        "   wave standard [how] [to] [target]\n"+
        "   plant standard\n"+
        "   raise standard - raise your standard for all to see\n"+
        "   lower standard - lower your standard.\n"+
        "   rally troops   - this enables you to rally your troops around you\n");
//        "\nSuggestions on more emotes are welcome!\n");

    return 1;
}
make_them_happy(object *list)
{
    int i;
    for(i=0; i<sizeof(list); i++)
        if(CAN_SEE_IN_ROOM(list[i]))
            list[i]->command(CHEER);
}

int
hide(string str)
{
    string name;
    
    if((!str) || (str != "standard") && (str != "faded standard")) return 0;

    if(!is_shown)
    {
        NF("");
        write("Your faded standard of Angmar's Army is hidden now!\n");
        return 0;
    }
    
    write("You roll your faded standard of Angmar's Army around the pole and " +
        "hide it from sight of others.\n");
    allbb(" rolls "+HIS_HER(TP)+" faded standard of Angmar's Army around the "+
        "pole and hides it from your sight.");
    TP->remove_subloc(SUBLOC_STANDARD);
    name = TP->query_name();
    TP->remove_item(name+" standard");
    is_shown = 0;

    return 1;
}

int
unroll(string str)
{
    string name, cname;
    
    if((!str) || (str != "standard") && (str != "faded standard")) 
    {
        NF("Unroll what?\n");
        return 0;
    }

    if(is_shown)
    {
        NF("You are already displaying the standard.\n");
        return 0;
    }
    write("You unroll the faded standard of Angmar's Army and display it for "+
        "everyone to see.\n");
    allbb(" unrolls "+HIS_HER(TP)+" faded standard of Angmar's Army and displays it for "+
        "all to see.");
/*
    TP->add_subloc(SUBLOC_STANDARD, TO);
    name = TP->query_real_name();
    cname = TP->query_name();
    TP->add_item(({name+" standard", cname+" standard",
        name+"s standard", cname+"s standard",
        name+"'s standard", cname+"'s standard"}), 
        VBFC_ME("item_standard"));
*/
    is_shown = 1;

    return 1;
}

string
item_standard()
{
    object ob = ENV(TO);
    if(TP == ob) return my_long();
    ob->catch_msg(QCTNAME(TP)+" examines your faded standard of Angmar's Army.\n");
    tell_room(ENV(ob), QCTNAME(TP)+" examines the faded standard of Angmar's Army.\n", ({ TP,ob }) );
    TP->catch_msg("You examine the faded standard of Angmar's Army.\n");
    return my_long();
}

int
wave(string str)
{
    object *oblist;
    string *how;
    
    if(!str) return 0;
    
    how = explode(str, " ");
    if(how[0] != "standard") return 0;
    
    if(!is_shown)
    {
        NF("");
        write("You must unroll the standard first!\n");
        return 0;
    }
    
    str = implode((how-({"standard"})), " ");
    
    if(str == "") str = 0;
    how = parse_adverb_with_space(str, "confidently", 0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" wave the faded standard of Angmar's Army.\n");
        allbb(how[1]+" waves the faded standard of Angmar's Army.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    
    if (!sizeof(oblist))
    {
        NF("Wave standard to whom?\n");
        return 0;
    }
    
    targetbb(how[1]+" waves the faded standard of Angmar's Army"+
        " in your direction.", oblist);
    actor("You"+how[1]+" wave the faded standard of Angmar's Army in", oblist, 
        "'s direction.");
    all2actbb(how[1]+" waves the faded standard of Angmar's Army in", oblist, 
        "'s direction.");
    return 1;
}

int
plant(string str)
{
    if((!str) || (str != "standard") && (str != "faded standard")) return 0;
    
    if(!is_shown)
    {
        NF("");
        write("You must unroll the standard first!\n");
        return 0;
    }
    
    write("You plant the faded standard of the Army of Angmar in the ground and "+
        "make your stand.\n");
    allbb(" plants the faded standard of Angmar's Army in the ground and make "+
        HIS_HER(TP)+" stand.");
    
    return 1;
}

int
raise(string str)
{
    object *oblist;
    string *how;
    
    if(!str) return 0;
    
    how = explode(str, " ");
    if(how[0] != "standard") return 0;
    
    if(!is_shown)
    {
        NF("");
        write("You must unroll the standard first!\n");
        return 0;
    }
    
    str = implode((how-({"standard"})), " ");
    
    if(str == "") str = 0;
    how = parse_adverb_with_space(str, "triumphantly",0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" raise the faded standard of Angmar's Army.\n");
        allbb(how[1]+" raises the faded standard of Angmar's Army.");
        
        write("You shout: ANGMAR! ANGMAR!! ANGMAR!!!\n");
        allbb(how[1]+" shouts: ANGMAR! ANGMAR!! ANGMAR!!!");
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    
    if (!sizeof(oblist))
    {
        NF("Raise standard to whom?\n");
        return 0;
    }
    if(sizeof(oblist) > 1)
    {
        write("You should honour only one at a time.\n");
        return 1;
    }
    
    targetbb(how[1]+" raises the faded standard of Angmar's Army"+
        " in your honour.", oblist);
    actor("You"+how[1]+" raise the faded standard of Angmar's Army in", oblist, 
        "'s honour.");
    all2actbb(how[1]+" raises the faded standard of Angmar's Army in", oblist, 
        "'s honour.");
    
        write("You shout: ANGMAR! ANGMAR!! ANGMAR!!!\n");
        allbb(how[1]+" shouts: ANGMAR! ANGMAR!! ANGMAR!!!");
    return 1;
}

int
lower(string str)
{
    object *oblist;
    string *how;
    
    if(!str) return 0;
    
    how = explode(str, " ");
    if(how[0] != "standard") return 0;
    
    if(!is_shown)
    {
        NF("");
        write("You must unroll the standard first!\n");
        return 0;
    }
    
    str = implode((how-({"standard"})), " ");
    
    if(str == "") str = 0;
    how = parse_adverb_with_space(str, "slowly", 0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" lower the faded standard of Angmar's Army.\n");
        allbb(how[1]+" lowers the faded standard of Angmar's Army.");
        
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    
    if (!sizeof(oblist))
    {
        NF("Lower standard to whom?\n");
        return 0;
    }
    if(sizeof(oblist) > 1)
    {
        write("You should honour only one at a time.\n");
        return 1;
    }
    
    targetbb(how[1]+" lowers the faded standard of Angmar's Army"+
        " to you.\nYou kneel down and kiss the edge of the flag.", oblist);
    actor("You"+how[1]+" lower the faded standard of Angmar's Army to", oblist, 
        ".\n"+QCTNAME(oblist[0])+
        " kneels down and kisses the edge of the flag.");
    all2actbb(how[1]+" lowers the faded standard of Angmar's Army to", oblist, 
        ".\n"+QCTNAME(oblist[0])+
        " kneels down and kisses the edge of the flag.");
    
    return 1;
}

int
rally(string str)
{
//    object *footmen;
    
    if((!str) || (str != "troops")) return 0;
    
    if(!is_shown)
    {
        NF("");
        write("You must unroll the standard first!\n");
        return 0;
    }
    
    write("You hold your faded standard of Angmar's Army high in the air, "+
        "rallying the troops.\n");
    allbb(" holds "+HIS_HER(TP)+" faded standard of Angmar's Army high in the air, "+
        "rallying the troops.");
    
        write("You shout: ANGMAR! ANGMAR!! ANGMAR!!!\n");
        allbb(" shouts: ANGMAR! ANGMAR!! ANGMAR!!!");
//    call_them_here();
    return 1;
}

/*
 * Function name: show_subloc
 * Description:   Shows the specific sublocation description for a living
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if(subloc != SUBLOC_STANDARD) return "";
    if (for_obj == on)
        return "You are bearing the faded standard of Angmar's Army.\n";
    else
        return CAP(HE_SHE(on)) + " is bearing the faded standard of Angmar's Army.\n";
}

