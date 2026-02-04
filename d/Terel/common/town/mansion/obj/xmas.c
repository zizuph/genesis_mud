/*
 * 122392 by dust. A Christmas tree for fun.
 *
 *  Modified: 6 May 2003, by Bleys
 *      - Typing "decorate" added a decoration that
 *          looked like "0". That's not too good, so I
 *          added a check for an argument.
 *
 *  Modified: 11 June 2003, by Bleys
 *      - This tree now logs when mortals add ornaments.
 *
 *  Modified: 9 Sep 2003, by Bleys
 *      - Mortals were abusing the ornamentation ability. There is
 *          now a capability for Terel wizards and administrators
 *          to ban people from adding ornaments.
 *      - Banned mortals are warned, but those who persist in
 *          adding ornaments are punished by the new guardians of
 *          the tree. The punishment is not directly lethal, but
 *          it is dangerous. Indications of this change include
 *          a subtle change to the description of the tree, and
 *          very obvious messages when the mortal attempts to add
 *          ornaments to the tree.
 *      - Banned mortals are logged.
 *      - Failed ban attempts are also logged.
 *      - Punishments delivered by the guardians are also logged.
 *
 *  Modified: 2 Dec 2003, by Bleys
 *      - Second tier of punishment was a duplicate of the first.
 *          Clearly a copy & paste error. The second angelos now
 *          has her voice back.
 *      - Added OBJ_S_WIZINFO and wizard-only text to the sign
 *          because it has recently not been obvious to people
 *          how the ban functionality worked.
 *
 *  Modified: 29 Apr 2019, by Shanoga
 *      - Added string cleanup to remove leading/trailing spaces
 *          and periods.
 *      - Added limit of once-per-Armageddon for players to add
 *          decorations to the tree.
 *      - Added a remove_decorations function to allow wizards to
 *          perform simple cleanup of the tree if necessary.
 *          Updated OBJ_S_WIZINFO with this information.
 *
 *
 *  Ban syntax: ban <who> because <reason>
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <std.h>
#include "/d/Terel/include/zodiac.h"

#define BSNN(s)     BSN(s)

#define MAX_ITEMS 40
#define FNAME "/d/Terel/common/town/mansion/obj/xmas"
#define ORNAMENT_LOG "/d/Terel/log/ornament_log"
#define BAN_LOG "/d/Terel/log/ornament_ban"
#define FAILED_BAN_LOG "/d/Terel/log/ornament_ban_failed"
#define PUNISH_LOG "/d/Terel/log/ornament_punish"
#define WARNED_PROP  "_terel_xmastree_warned"


string  *items;
int first,last;
string *artists = ({ });


public void
log_failed_ban(string args, int wizlev)
{
    write_file(FAILED_BAN_LOG, TP->query_name() + "(wiz level " +
        wizlev + ") tried to 'ban " + args + "'. Timestamp: " +
        ctime(time()) + "\n");
}


public int
do_ban(string args)
{

    string who, reason;
    int wizlev = SECURITY->query_wiz_rank(TP->query_name());

    if ( wizlev == 0 )
    {
        // Freakin' mortals.
        NF("What ?\n");
        log_failed_ban(args, wizlev);
        return 0;
    }

    if ( !args )
    {
        NF("Insufficient arguments. Try 'ban help' for more info.\n");
        return 0;
    }

    if ( wizlev < WIZ_NORMAL )
    {
        // Pilgrims and retireds shouldn't be here.
        NF("You should speak to a Terel wizard or a member " +
            "of the administration about your desire to ban " +
            "somebody from adding ornaments to the xmas tree.1\n");
        log_failed_ban(args, wizlev);
        return 0;
    }

    if ( (wizlev < WIZ_ARCH) &&
        SECURITY->query_wiz_dom(TP->query_name()) != "Terel" )
    {
        // Non-Terel wizards under arch level have no place here.
        NF("You should speak to a Terel wizard or a member " +
            "of the administration about your desire to ban " +
            "somebody from adding ornaments to the xmas tree.2\n");
        log_failed_ban(args, wizlev);
        return 0;
    }


    if ( args == "help" )
    {
        //print help message
        NF("Ban help:\n\nAdministrators and Terel wizards can ban " +
            "mortals who have abused their ornamentation privileges " +
            "by using the 'ban' command.\n\nUsage:\n    ban <who> " +
            "because <reason>\n\nExample:\n    ban Gorboth because he " +
            "keeps adding ornaments of Morgul chickens\n\nEOF\n");
        return 0;
    }

    if ( parse_command(args, TO, "%w 'because' %s", who, reason) )
    {
        if ( SECURITY->exist_player(who) )
        {

            who = capitalize(who);

            write_file(BAN_LOG, who + " was banned from adding " +
                "ornaments to the xmas tree by " + TP->query_name() +
                ". Reason: because " + reason +
                ". Timestamp: " + ctime(time()) + "\n");
            write("You have banned " + who + " from adding ornaments " +
                "to the xmas tree because " + reason + ".\n");
            return 1;
        }
        else
        {
            NF("No player named " + who + " found.\n");
            return 0;
        }

    }
    else
    {
        NF("Ban <who> because <why>?\n");
        return 0;
    }

    NF("Something has gone wrong with the ban attempt.\n");
    return 0;
}


public int
punish_punk(object punk)
{

    int warn_level = punk->query_prop(WARNED_PROP);

    // percentage of mana and hp to take after the first warning
    int tithe = 60 + (20 * (warn_level - 1));
    int hp_tithe = punk->query_hp() * tithe / 100;
    int mana_tithe = punk->query_mana() * tithe / 100;

    object restraint;

    // Speech, 1st person, 3rd person
    string warning, action1, action3;
    string logline = punk->query_name();

    if ( warn_level == 0 )
    {
        punk->add_prop(WARNED_PROP, warn_level + 1);

        // Warn this one.
        // The Angelos of Joy speaks here.
        warning = "Yea, those who abuse the tree shall not " +
            "desecrate it further, nor shall they be suffered " +
            "among the righteous, but they shall be cast into " +
            "the night.";
        action1 = "You attempt to place an ornament upon the " +
            TO->short() + ", but your limbs do not respond. A " +
            "sweet voice says: '" + warning + "'\n";
        action3 = QCTNAME(punk) + " stumbles purposefully " +
            "toward the " + TO->short() + ", but stops suddenly " +
            "just before it. A sweet voice speaks to " +
            punk->query_objective() + ": '" + warning + "'\n";

        write(action1);
        say(action3);

        logline += " was warned not to approach the Xmas tree. " +
            "Timestamp: " + ctime(time()) + "\n";
        write_file(PUNISH_LOG, logline);
        return 1;

    }

    if ( warn_level == 1 )
    {
        punk->add_prop(WARNED_PROP, warn_level + 1);

        // We're done with warnings. Punishment time.
        // The Angelos of Sorrow speaks.
        punk->heal_hp(-hp_tithe);
        punk->add_mana(-mana_tithe);
        warning = "Hearken, for abuse of a gift freely given " +
            "brings shame and sorrow to us, and reveals one " +
            "who has abandoned awareness and cast aside " +
            "wisdom. We are dismayed by our lesser brethren " +
            "who act in defiance of our warnings.";
        action1 = "You attempt to place an ornament upon the " +
            TO->short() + ", but distress overcomes you, and " +
            "you cannot bear to look upon the " + TO->short() +
            "'s glory. A sad voice says: '" + warning + "'\n";
        action3 = QCTNAME(punk) + " takes a halting step toward " +
            "the " +TO->short() + ", but stops suddenly before " +
            "it and averts " + HIS_HER + " gaze. A sweet voice " +
            "speaks to " +
            punk->query_objective() + ": '" + warning + "'\n";

        write(action1);
        say(action3);

        logline += " was mildly punished for approaching the " +
            "Xmas tree. " +
            "HP: " + punk->query_hp() + " of " + punk->query_max_hp() +
            ". Mana: " + punk->query_mana() + " of " +
            punk->query_max_mana() + ". Timestamp: " +
            ctime(time()) + "\n";
        write_file(PUNISH_LOG, logline);

        return 1;
    }

    if ( warn_level > 1 )
    {
        punk->add_prop(WARNED_PROP, warn_level + 1);

        // OK, this person is beyond redemption. Punish and send him
        //  on his way.
        // The Angelos of Wrath is the speaker here.
        punk->heal_hp(-hp_tithe);
        punk->add_mana(-mana_tithe);
        warning = "For he who turns his back upon wisdom " +
            "has cast his very self away from all that is " +
            "held sacred, and descends into ignorance and " +
            "foolishness and brutality, and begets only " +
            "misery and suffering and pain, and shares it " +
            "in equal measure.";
        action1 = "You try once more to place an ornament " +
            "upon the " + TO->short() + ", but the familiar " +
            "distress falls upon you, and an angry voice " +
            "dictates: '" + warning + "'\n";
        action3 = QCTNAME(punk) + " looks determinedly at " +
            "the " + TO->short() + ", but seems to diminish. " +
            "An angry voice dictates to " + punk->query_objective() +
            ": '" + warning + "'\n";

        write(action1);
        say(action3);

        logline += " was punished for approaching the Xmas tree. " +
            "HP: " + punk->query_hp() + " of " + punk->query_max_hp() +
            ". Mana: " + punk->query_mana() + " of " +
            punk->query_max_mana() + ".";

        restraint = clone_object("/d/Terel/janus/garden/balls.c");
        if ( !restraint->move(punk, 1) )
        {
            write("A ball and chain appear, clasped about your " +
                "ankle.\n");
            say("A ball and chain appear, clasped about " +
                QCTPNAME(punk) + " ankle.\n");
            logline += " " + capitalize(punk->query_pronoun()) +
                " also received a ball and chain.";
        }

        if ( TP->query_average_stat() > 100 ) // You should know better...
        {
            if ( !TP->move_living("M", "/d/Terel/LoD/quart29w", 1, 1) )
            {
                write("You are disoriented by your ordeal, but it seems " +
                    "as if some new people have arrived.\n");
                say(QCTNAME(punk) + " is enveloped in a soft glow. The " +
                    "glow diminishes and disappears, and " + QCTNAME(punk) +
                    "is nowhere to be seen.\n");
                logline += " " + capitalize(punk->query_pronoun()) +
                    " was sent to a place of evil.";
            }
        }

        logline += " Timestamp: " + ctime(time()) + "\n";
        write_file(PUNISH_LOG, logline);

        return 1;
    }

    return 0;

}


public int
check_permission(object punk)
{

    string *losers;
    int i;
    string who;

    // Check to make sure he has permission to add an ornament.
    if (file_size(BAN_LOG) > 0)
    {
        seteuid(getuid());
        losers = explode(read_file(BAN_LOG), "\n");
        for ( i = 0 ; i < sizeof(losers) ; i++ )
        {
            if ( !strlen(losers[i]))
            {
                continue;
            }

            who = explode(losers[i], " ")[0];
            if ( who == punk->query_name() )
            {
                return 0;
            }
        }
    }

    return 1;

}


string
decoration()
{
    string temp;
    int i,nexti,nextnexti;

    temp = "This is a glorious green Christmas tree. " +
        "An ornamental trio of shining, winged humans stands watch " +
        "at the peak of the tree. The tree is free for decoration. " +
        "Read the sign next to it to get to know how to do so. ";
    if (first == last)
    return(break_string(temp +
        "There's no decoration on the tree. Would you like to " +
        "add some?\n",70));
    temp = temp + "The tree is decorated with ";
    i = first;
    nexti = i+1;
    if (nexti == MAX_ITEMS) nexti = 0;
    while (i != last)
    {
        nextnexti = nexti+1;
        if (nextnexti == MAX_ITEMS) nextnexti = 0;
        temp = temp + items[i];
        if (nexti == last)
            ;
        else if (nextnexti == last)
            temp = temp + " and ";
        else
            temp = temp + ", ";
        i = nexti;
        nexti = nextnexti;
    }
    return(break_string(temp + ".\n",70));
}

add_decoration(string str)
{
    items[last] = str;
    last++;
    if (last == MAX_ITEMS) last = 0;
    if (last == first) {
        first++;
        if (first == MAX_ITEMS) first = 0;
    }
}

do_decorate(string str)
{
    int i, index, str_arr_size;
    string temp_str;
    string *str_arr;

    seteuid(getuid());

    if ( !str ) {
        NF("What is it that you would like to add to " +
           "the tree?\n");
        return 0;
    }

    if ( !check_permission(TP) )
    {
        punish_punk(TP);
        return 1;
    }
    
    str_arr = explode(str,"");
    str_arr_size = sizeof(str_arr);
    while (str_arr[str_arr_size - 1] == " " || str_arr[str_arr_size - 1] == ".") {
        str_arr = str_arr[0..(str_arr_size-2)];
        str_arr_size = sizeof(str_arr);
    }
    
    while (str_arr[0] == " " || str_arr[0] == ".") {
        str_arr_size = sizeof(str_arr);
        str_arr = str_arr[1..(str_arr_size-1)];
    }
    
    for (i=0; i<sizeof(str_arr); i++)
        if (str_arr[i] == ".") str_arr[i] = " ";
    
    for (i=1; i<sizeof(str_arr); i++) {
        if (str_arr[i] == " " && str_arr[i-1] == " ") {
            str_arr_size = sizeof(str_arr);
            str_arr = str_arr[0..(i-1)] + str_arr[(i+1)..(str_arr_size-1)];
            i -= 1;
        }
        if (i == sizeof(str_arr) - 1) {
            str_arr_size = sizeof(str_arr);
            str_arr = str_arr[0..(str_arr_size-1)];
        }
    }
    
    str = implode(str_arr, "");
    
    if (member_array(this_player()->query_name(), artists) != -1) {
        NF("You have already decorated the tree. " +
           "Try again once the butler has replaced the tree.\n");
        return 0;
    }
    
    foreach(string item: items) {
        if (str == item) {
            NF("The tree has already been decorated with " + str +
               ". Try decorating it with something else.\n");
            return 0;
        }
    }

    if (this_player()) {
        write(break_string("You add " + str +
           " to the tree. How nice!\n",70));
        say(break_string(QCTNAME(this_player()) + " adds " + str +
            " to the tree. How nice!\n",70));
    }

    add_decoration(str);

    write_file(ORNAMENT_LOG, TP->query_name() + " added an " +
        "ornament on " + ctime(time()) +
        ". The ornament was: " + str + "\n");
        
    artists += ({ this_player()->query_name() });

    rm(FNAME);
    i = first;
    while (i != last)
    {
        write_file(FNAME,items[i] + "\n");
        i++;
        if (i == MAX_ITEMS) i=0;
    }
    return 1;
}

start_decoration()
{
    string temp;
    int i;

    seteuid(getuid());
    for ( i=0; i<MAX_ITEMS; i++ )
    {
        temp = read_file(FNAME,i,1);
        if (strlen(temp) < 4) continue;
        temp = (explode(temp,"\n"))[0];
        add_decoration(temp);
    }
    if (first == last)
    {
        add_decoration("a beautiful terellian greeting ball");
        add_decoration("shining angels hair");
        add_decoration("a request to add more");
    }
}

create_object()
{
    int i;

    items = allocate(MAX_ITEMS);
    first = 0;
    last = 0;
    set_name("tree");
    add_adj(({"green", "christmas"}));
    set_short("green Christmas tree");
    set_long("@@decoration");
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_S_WIZINFO, "This tree is public to all who have not " +
             "been banned from using it. Wizards of Terel and members " +
             "of the administration can ban those who abuse the tree." +
             "See 'ban help' for more information.\nIf the decorations " +
             "are inappropriate or need to be reset for any reason, " +
             "use the reset_decorations() function.");
    start_decoration();
}

init()
{
    ::init();
    add_action("do_decorate","decorate");
    add_action("do_decorate","add");
    add_action("instructions","read");
    add_action("do_ban","ban");
}

int
instructions(string str)
{

    int wizlev = SECURITY->query_wiz_rank(TP->query_name());
    string sign_text;

    NF("What do you want to read? Maybe the sign?\n");
    if (str != "sign" && str != "instructions" && str != "instruction")
    {
        return 0;
    }

    sign_text = "This Christmas tree is a gift to all mortals " +
    "from the wizards of the Terel domain. Everybody can add any " +
    "decoration he, she or it likes by entering for example " +
    "'add a blue ball' or 'decorate a blue ball'. Everything " +
    "appearing behind the word 'add' or 'decorate' is taken as " +
    "decoration, so don't include anything like 'add tree with ...'. " +
    "Also, don't forget to include an article 'a' or 'an' where " +
    "it's needed, as shown in the examples above. It is not " +
    "possible to remove any decorations added.\n";

    if ( SECURITY->query_wiz_rank(TP->query_name()) )
    {
        sign_text += "\nWizards may also ban mortals who abuse " +
            "the tree from using it again. See 'ban help' for more " +
            "information.\n";
    }

    write(sign_text);
    return 1;
}

int
reset_decorations()
{   
    rm(FNAME);
    last = 0;
    first = 0;
    start_decoration();
    return 1;
}