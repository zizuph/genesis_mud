#include "../guild.h"

inherit KOT_SOUL_DIR + "kot_soul";

#include <filter_funs.h>
#include <composite.h>
#include "/d/Emerald/sys/skills.h"
#include <cmdparse.h>
#include <files.h>
#include <state_desc.h>
#include <macros.h>

#define TPOS this_player()->query_possessive()
#define TPRO this_player()->query_pronoun()

#define HIS_OR_THEIR ( (sizeof(oblist)>1) ? "their" : oblist[0]->query_possessive())
#define HIM_OR_THEM ( (sizeof(oblist)>1) ? "them" : oblist[0]->query_objective())

mapping
query_caste_cmdlist()
{
    return ([
             "ktbalance"      : "balance",
             "ktbrandish"     : "brandish",
             "ktcharge"       : "charge",
             "ktclash"        : "clash",
             "ktshout"        : "shout",
             "kttend"         : "tend",
             "ktconvey"       : "convey",
             "ktclasp"        : "wclasp",
           ]);
}

void
create_caste_soul()
{
    read_help_dir(KOT_HELP_DIR, "warrior_help");
}

/*
 * BALANCE
 * Warrior will check and balance a weapon in their inventory
 * Usage: balance <weapon> at <player>
 */
int 
balance(string str)
{
    object *oblist;
    string targetstr;
    object *weplist;

    /* Sanity check on the argument. */
    if (!strlen(str))
    {
        notify_fail("Test the balance of which weapon?\n");
        return 0;
    }

    /* See whether the player wants to balance at another living. */
    if (sscanf(str, "%s at %s", str, targetstr) == 2)
    {
        oblist = parse_this(targetstr, "[the] %l");

        if (!sizeof(oblist))
        {
            notify_fail("Balance a weapon at whom?\n");
            return 0;
        }
    }

    /* Find the weapon the player wants to balance. */
    parse_command(lower_case(str), this_player(), "[the] %i", weplist);

    weplist = NORMAL_ACCESS(weplist, 0, 0);

    /* Check the weapons found. */
    switch(sizeof(weplist))
    {
    /* No weapons found. */
    case 0:
        notify_fail("Balance which weapon?\n");
        return 0;

    /* One object found. See whether it is a weapon. */
    case 1:
        if (function_exists("create_object", weplist[0]) != WEAPON_OBJECT)
        {
            notify_fail("You can only balance weapons.\n");
            return 0;
        }

        str = weplist[0]->short();
        break;

    /* Too many items found. */
    default:
        notify_fail("You can balance only one weapon at a time.\n");
        return 0;
    }

    /* If there is no target, give a general message to the onlookers. */
    if (!sizeof(oblist))
    {
        write("You swing your " + str + " gracefully through the air, " +
              "checking its balance and weight.\n");
        allbb(" swings " + TPOS + " " + str +
              " gracefully through the air, checking its balance and weight.");
        return 1;
    }
    else
    {
        actor("You swing your " + str + " through the air, testing its " +
            "balance and weight as you sight", oblist, " as " +
            ( (sizeof(oblist) > 1 ) ? "example targets" : "an example target") +
            ".");
        targetbb(" swings " + TPOS + " " + str +
            " through the air, testing its balance and weight as " +
            TPRO +
            " sights you as an example target.", oblist);
        
        all2actbb(" swings " + TPOS + " " + str +
            " through the air, testing its balance and weight as " +
            TPRO + " sights", oblist, " as " +
            ( (sizeof(oblist) > 1) ? "example targets" : "an example target") +
            ".");
        return 1;
    }
}

int
brandish(string str)
{
    mixed *oblist;
    mixed *weplist;

    if (!strlen(str))
    {
        notify_fail("Brandish your weapon at whom?\n");
        return 0;
    }

    if (!parse_command(str, all_inventory(this_player()),
        "[the] %i [at] [the] %s", weplist, str) ||
        !sizeof(weplist = NORMAL_ACCESS(weplist, 0, 0)))
    {
        notify_fail("Brandish which weapon?\n");
        return 0;
    }

    if (!sizeof(oblist = parse_this(str, "%l")))
    {
        notify_fail("Brandish you weapon at whom?\n");
        return 0;
    }

    switch(sizeof(weplist))
    {
    case 0: 
        notify_fail("Brandish which weapon?\n");
        return 0;
        break;
    case 1:
        if (function_exists("create_object", weplist[0]) != WEAPON_OBJECT )
        {
            notify_fail("You can only brandish weapons.\n");
            return 0;
        }
        
        str = weplist[0]->short();
        break;
    default:
        notify_fail("You can only brandish one weapon at a time.\n");
        return 0;
    }  // ... END SWITCH ...
    
    // if no targets could be found, give error message.
    if (!sizeof(oblist))
    {
        notify_fail("You doubt it would be worth the effort to brandish "+
                    "your weapon without an intended audience.\n");
        return 0;
    }
    
    actor("You brandish your "+str+" at",oblist," threateningly.");
    targetbb(" brandishes "+TPOS+" "+str+" at you "+
             "threateningly.", oblist);
    all2actbb(" brandishes "+TPOS+" "+str+" at",oblist,
              " threateningly.");
    return 1;
}

int 
charge(string str)
{
    string *exits;
    
    if (!strlen(str))
    {
        notify_fail("Charge in which direction?\n");
        return 0;
    }
    
    exits = environment(this_player())->query_exit_cmds();
    if ( (member_array(str, exits))==-1)
    {
        notify_fail("You cannot charge in that direction.\n");
        return 0;
    }
    
    if (this_player()->query_attack())
    {
        notify_fail("You cannot charge away from a fight!\n");
        return 0;
    }
    
    write("You let out a mighty battle cry and charge "+str+"!\n");
    say(QCTNAME(this_player())+" lets out a mighty battle cry and charges "+str+"!\n");
    this_player()->command(str);
    return 1;
}

int
check_wep(object ob, object who)
{
    return (CAN_SEE(who, ob) && 
        (function_exists("create_object", ob) == WEAPON_OBJECT));
}

/* This emote could use some work. --Shiva */
int
clash(string str)
{
    object *oblist;
    object *weplist;
    object *opweps;
    
    string wepstr;
    string str2;
    
    if (!strlen(str))
    {
        notify_fail("Clash weapons in salute with whom?\n");
        return 0;
    }
    
    parse_command(str, ({}), "%s 'using' / 'with' %s", str, wepstr);

    oblist = parse_this(str,"[the] %l");
        
    if (!sizeof(oblist))
    {
        notify_fail("With whom do you wish to clash weapons?\n");
        return 0;
    }

    if (wepstr)
    {
        parse_command(lower_case(wepstr), all_inventory(this_player()),
            "[the] %i", weplist);
        weplist = NORMAL_ACCESS(weplist, 0, 0);
    }
    else
    {
        weplist = filter(all_inventory(this_player()), 
            &check_wep(,this_player()))[0..0];
    }
    
    if (!sizeof(weplist))
    {
        notify_fail("Clash using which weapon?\n");
        return 0;
    }

    if (sizeof(weplist) > 1)
    {
        notify_fail("You can only clash with one weapon at a time.\n");
        return 0;
    }

    if (function_exists("create_object", weplist[0]) != WEAPON_OBJECT)
    {
        notify_fail("You may only clash in salute with a weapon.\n");
        return 0;
    }

    opweps = filter(all_inventory(oblist[0]), &check_wep(,oblist[0]));
    if (!sizeof(opweps))
    {
        notify_fail(oblist[0]->query_The_name(this_player()) +
            " has no weapons with which to clash.\n");
        return 0;
    }
        
    str2 = QSHORT(opweps[0]);
    str = QSHORT(weplist[0]);
    
    actor("You raise your "+ weplist[0]->short(this_player()) +
        " and clash it against", oblist, "'s " + 
        opweps[0]->short(this_player()) + " in a traditional warrior salute.");
    target(" raises " + TPOS + " " + weplist[0]->short(oblist[0]) +
        " and clashes it against your " + opweps[0]->short(oblist[0]) +
        " in a traditional warrior salute.", oblist);
    all2act(" raises " + TPOS + " " + QSHORT(weplist[0]) + " and clashes it "+
        "against", oblist,"'s " + QSHORT(opweps[0]) +
        " in a traditional warrior salute.");
    return 1;
}

int
wclasp(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Clasp whose hand?\n");
        return 0;
    }

    oblist = parse_this(str,"[with] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Whose hand do you want to clasp?\n");
        return 0;
    }

    if (sizeof(oblist)>1)
    {
        notify_fail("It is rather difficult to clasp more than one "+
                    "person's hand at a time.\n");
        return 0;
    }

    actor("You reach out and clasp",oblist,"'s hand with a firm, "+
          "powerful grip.");
    target(" reaches out and clasps your hand with a firm, powerful "+
           "grip.");
    all2act(" reaches out and clasps",oblist,"'s hand with a  firm, "+
            "powerful grip.");
    return 1;
}

int
shout(string str)
{
    string *rooms;
    int i;

    if (!strlen(str))
    {
        notify_fail("What do you want to shout?\n");
        return 0;
    }

    rooms = environment(this_player())->query_exit_rooms();
    
    write("Drawing upon the inner strength granted you by Telan-Ri, you "+
         "throw your head back and shout: "+str+"\n");
    
    for (i=0; i<sizeof(rooms); i++)
    {
        tell_room(rooms[i],
                  "A loud elven voice, booming with authority fills "+
                  "the area, shouting: "+str+"\n");
    }

    tell_room(environment(this_player()),
              QCTNAME(this_player())+" throws "+TPOS+" head back "+
              "and shouts: "+str+"\n",this_player());
    return 1;
}

int 
tend(string str)
{
    string hdesc;
    int num;

    if (this_player()->query_hp() == this_player()->query_max_hp())
    {
        notify_fail("You are in perfect health, and have no need of "+
                    "tending your wounds.\n");
        return 0;
    }

    num = (this_player()->query_hp()*100) / this_player()->query_max_hp();
    hdesc = "/cmd/live/state"->get_proc_text(num, SD_HEALTH, 0, ({}));

    write("You perform a quick evaluation of your injuries, checking "+
          "your condition.\n You are physically "+hdesc+".\n");
    say(QCTNAME(this_player())+" performs a quick check of "+
        TPOS+" injuries, evaluating "+TPOS+
        " condition.\n");
    return 1;
}

int
revoke(string str)
{
    if (!strlen(str) || str != "my allegiance")
    {
        notify_fail("Revoke your allegiance to the Protectorate?\nIf you are "+
                "sure, 'ktrevoke my allegiance', but there is no going "+
                "back!\n");
        return 0;
    }

    write("You lower your eyes and revoke your allegiance to the "+
          "Protectorate.\nYou feel a void in your heart.\n");
    say(QCTNAME(this_player())+" lowers "+TPOS+" eyes and revokes "+
            TPOS+" alliegance to the Protectorate "+
            "of Telberin.\n");
    this_player()->remove_kot_member();
    return 1;
}
