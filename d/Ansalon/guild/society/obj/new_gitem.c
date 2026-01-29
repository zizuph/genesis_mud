/* 
 * /d/Ansalon/guild/society/obj/gitem.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender guild object -- beads that one can wear in the hair.
 * Masks peek to give fun messages.
 *
 * Gwyneth, July 1999
 * Modification log:
 * Gwyneth, added hoopak altering
 * Gwyneth, added ksong January 2001
 * Gwyneth, added ability to 'behave' and not autoborrow for
 * 5 minutes, then a half hour unable to 'behave'.
 */
inherit "/std/object";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../songlist.c"
#include "../stories.c"

#define BEAD_SUBLOC		"_bead_subloc"
#define BEHAVE_TIME		300.0
#define RESET_BEHAVE_TIME	1800.0

static object Worn = 0;
string *fadjs = ({ "green-feathered", "red-feathered", "white-feathered" });
string *sadjs = ({ "green", "red", "white" });
int gBehaving = 0;
int gCanBehave = 1;

void acquire_things();

void
setup_beads(string type, string colour)
{
    set_adj(type);
    add_adj(colour);
    set_short(type + " " + colour + " string of beads");
    set_pshort(type + " " + colour + " strings of beads");
    set_long("This " + type + " " + colour + " string of beads was given " +
        "to you on the day you joined the guild. Well, something much " +
        "like it anyways. Perhaps another kender left a similar one " +
        "in your pouch and borrowed the other ones! A small tag has " +
        "been attached to the bottom. It reads:\n" +
        "<help kender menu>\n"); 
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
        return;

    gHe = to->query_pronoun();
    gHis = to->query_possessive();
    gHim = to->query_objective();
    setup_stories();
}

void
borrow_things()
{
    int i = -1, j;
    mixed *p;
    object *living_things, who = environment(), target;

    if (!living(who))
    {
        return;
    }

    if (gBehaving)
    {
        set_alarm(1.0, 0.0, &acquire_things());
        return;
    }

    p = FILTER_CAN_SEE(all_inventory(environment(who)) - ({ who, 0 }), who);
    living_things = FILTER_LIVE(p);

    if (!sizeof(living_things))
    {
        set_alarm(15.0, 0.0, &borrow_things());
        return;
    }

    target = living_things[random(sizeof(living_things))];
    j = sizeof(living_things);

    if (target->query_wiz_level())
    {
        while (++i < j)
        {
            if (!living_things[i]->query_wiz_level())
            {
                target = living_things[i];
            }
        }
    }

    if (random(100) > 50)
    {
        who->command("$borrow something from " + OB_NAME(target));
        acquire_things();
    }
    else
    {
        who->command("$peek " + OB_NAME(target));
        set_alarm(1.0, 0.0, &acquire_things());
    }
}

void
acquire_things()
{
    int num;

    if (environment()->query_npc())
        return;

    if (!environment()->query_wiz_level())
    {
        num = 300 + random(300);
        set_alarm(itof(num), 0.0, &borrow_things());
        return;
     }
    else
    {
        environment()->catch_tell("You are immune to the wild " +
            "desire to borrow things.\n");
    }
}

void
create_object()
{
    string *first_adj = ({"pale", "shiny", "dark", "long",
        "sparkly", "metallic", "large", "small", "medium",
        "bright", "short"});
    string *second_adj = ({ "red", "orange", "green", "blue", "violet",
        "pink", "white", "black", "silver", "gold",
        "bronze", "brass", "platinum"});

    string first = first_adj[random(sizeof(first_adj))];
    string second = second_adj[random(sizeof(second_adj))];

    setup_beads(first, second);

    set_name(({"beads", "string", "kender_guild_emblem"}));
    set_pname("strings");

    add_name(GUILD_NAME + " emblem");
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    remove_prop(OBJ_I_VALUE);

    set_alarm(0.5, 0.0, &acquire_things());
}

public int
do_wear(string str)
{
    object *beads;

    if(!strlen(str))
        return 0;

    beads = FIND_STR_IN_OBJECT(str, this_player());

    if(member_array(this_object(), beads) == -1)
    {
        notify_fail("Wear the beads?\n");
        return 0;
    }

    if(objectp(Worn))
    {
        notify_fail("You are already wearing it!\n");
        return 0;
    }

    if(member_array(BEAD_SUBLOC, this_player()->query_sublocs()) > -1)
    {
        if(str != "all")
        {
            write("You already wear beads.\n");
            return 1;
        }
        return 0;
    }

    this_player()->add_subloc(BEAD_SUBLOC, TO);
    write("You wind the " + short() + " into a lock of hair.\n");
    say(QCTNAME(this_player()) + " winds the " + short() + " into a lock " +
        "of hair.\n");
    Worn = this_player();
    set_no_show_composite(1);
    return (str != "all" ? 1 : 0);
}

public int
do_remove(string str)
{
    object *beads;

    if(!strlen(str))
        return 0;

    beads = FIND_STR_IN_OBJECT(str, this_player());

    if(member_array(this_object(), beads) == -1)
    {
        notify_fail("Remove the beads?\n");
        return 0;
    }

    if(!objectp(Worn))
    {
        notify_fail("You are not wearing them!\n");
        return 0;
    }

    this_player()->remove_subloc(BEAD_SUBLOC);
    write("You unwind the " + short() + " from your hair.\n");
    say(QCTNAME(this_player()) + " unwinds the " + short() + " from " +
        this_player()->query_possessive() + " hair.\n");
    Worn = 0;
    set_no_show_composite(0);
    return (str != "all" ? 1 : 0);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if(subloc == BEAD_SUBLOC)
    {
        if(for_obj != on)
            data = capitalize(on->query_pronoun()) +
                " is wearing " + LANG_ASHORT(this_object()) + " in " +
                on->query_possessive() + " hair.\n";
        else
            data = "You are wearing " + LANG_ASHORT(this_object()) +
                " in your hair.\n";
        return data;
    }
    return 0;
}

string
query_recover()
{
    return 0;
}

int
peek_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == this_player())
        return 0;
    else
        return 1;
}

int
kpeek(string str)
{
    string vb;
    object *p, *inv;
    int id, i, pp_skill;

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        return this_player()->light_fail("see");
    }

    vb = query_verb();
    notify_fail(capitalize(vb) + " at whom?\n");

    if (!stringp(str))
        return 0;

    p = CMDPARSE_ONE_ITEM(str, "peek_access", "peek_access");

    if (!sizeof(p))
    {
        return 0;
    }
    if (sizeof(p) > 1)
    {
        notify_fail(capitalize(vb) + " at one person at a time.\n");
        return 0;
    }

    pp_skill = this_player()->query_skill(SS_PICK_POCKET) / 2;
    if ((pp_skill + random(pp_skill) > p[0]->query_skill(SS_AWARENESS)) &&
        (!p[0]->query_wiz_level()))
    {
        inv = all_inventory(p[0]);

        p[0]->add_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS, 1);
        id = set_alarm(0.1, 0.0,
            &(p[0])->remove_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS));
        write(p[0]->show_sublocs(this_player()));
        p[0]->remove_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS);
        remove_alarm(id);

        inv = (object*)p[0]->subinventory(0);
        inv = FILTER_SHOWN(inv);
        if (sizeof(inv))
            write("Making a quick check just for curiousity, " +
                "you notice that " + p[0]->query_the_name(this_player()) +
                " is currently in possession of: " +
                COMPOSITE_DEAD(inv) + ".\n");
        else
            write("Making a quick check just for curiousity, " +
                "you notice that " + p[0]->query_the_name(this_player()) +
                " does not own anything.\n");
    }
    else
    {
        switch(random(4))
        {
            case 0:
                tell_object(p[0], "You notice " +
                    this_player()->query_the_possessive_name(p[0]) +
                    " hands wandering curiously through your belongings!\n");
                break;
            case 1:
                tell_object(p[0], "You notice " +
                    this_player()->query_the_possessive_name(p[0]) +
                    " hands brushing against you.\n");
                break;
            case 2:
                tell_object(p[0], "As " +
                    this_player()->query_the_name(p[0]) +
                    " moves around, you notice a slight shift in " +
                    "the weight of your pockets. Or maybe it's " +
                    "just your imagination.\n");
                break;
            case 3:
                tell_object(p[0], "You feel someone's hands against " +
                    "you, and when you look down you see " +
                    this_player()->query_the_name(p[0]) +
                    " busily examining your belongings. When " +
                    this_player()->query_pronoun() + " notices " +
                    "the look on your face, " +
                    this_player()->query_pronoun() + " removes " +
                    this_player()->query_possessive() + " hands " +
                    "with a sheepish grin on " +
                    this_player()->query_possessive() + " face.\n");
                break;
            }

        write("Oops! " + p[0]->query_The_name(this_player()) +
            " notices your hands wandering curiously through " +
            HIS(p[0]) + " belongings!\n");
    }

    return 1;
}

/* 
 * Function name : no_steal
 * Description   : Disable the steal command, replaced by "borrow"
 */
int
no_steal(string str)
{
    write("Shame on you! Kender don't steal!\n");
    return 1;
}

/* 
 * Function name : alter
 * Description   : Initial parsing
 * Arguments     : string str - the argument given
 * Returns       : 0 on failure, 1 on success
 */
int
alter(string str)
{
    mixed  *polearm;
    mapping hoopak_list;
    object  clone;
    string *func, fname;
    int     s;

    setuid();
    seteuid(getuid());
            
    if (!mappingp(hoopak_list))
        hoopak_list = ([]);
            
    hoopak_list = restore_map(KGLOG + "hoopak_list");
    
    /* Failure message if no string */
    if (!strlen(str))
    {
        notify_fail("Alter which weapon?\n");
        return 0;
    }

    /* Find if the argument is valid */
    str = lower_case(str);
    
    if (!parse_command(str, all_inventory(this_player()), "[the] %i", polearm))
    {
        notify_fail("Alter which weapon?\n");
        return 0;
    }

    polearm = NORMAL_ACCESS(polearm, 0, 0);
    s = sizeof(polearm);

    if (s > 1)
    {
        notify_fail("You can only alter one weapon at a time.\n");
        return 0;
    }

    if (!s)
    {
        notify_fail("Alter which weapon?\n");
        return 0;
    }

    /* Don't convert broken weapons */
    if (polearm[0]->query_prop(OBJ_I_BROKEN))
    {
        notify_fail("You can't alter broken items.\n");
        return 0;
    }

    /* Don't convert weapons with this prop. */
    if (polearm[0]->query_prop(OBJ_I_NO_CONVERT_HOOPAK))
    {
        notify_fail("You can't seem to alter this weapon.\n");
        return 0;
    }

    /* Only alter polearms or those with the right prop */
    if ((polearm[0]->query_wt() != W_POLEARM) &&
      (!polearm[0]->query_prop(OBJ_I_CONVERT_HOOPAK)))
    {
        notify_fail("You can't convert that weapon into a hoopak.\n");
        return 0;
    }
    
    if (polearm[0]->id("hoopak"))
    {
        notify_fail("It's already a hoopak!\n");
        return 0;
    }

    if (!function_exists("create_weapon", polearm[0]))
    {
        notify_fail("You can only alter weapons.\n");
        return 0;
    }

    if (sizeof(func = ({    function_exists("did_hit", polearm[0]),
                            function_exists("try_hit", polearm[0]) })))
    {
        if (!sscanf(file_name(polearm[0]), "%s#", fname))
            fname = file_name(polearm[0]);
        
        if (member_array(fname, func) > -1 && 
            !polearm[0]->query_prop(OBJ_I_CONVERT_HOOPAK))
        {
            if (member_array(fname, m_indexes(hoopak_list)) < 0)
            {
                hoopak_list[fname] = ctime(time());
                save_map(hoopak_list, KGLOG + "hoopak_list");
            }
            
            notify_fail("You failed in your attempts at imagining this " +
            "polearm as a hoopak, maybe there is simply no way to alter it.. " +
            "yet..\n");
            return 0;
        }
    
        if (member_array(fname, m_indexes(hoopak_list)) > -1)
        {
            m_delkey(hoopak_list, fname);
            save_map(hoopak_list, KLOG + "hoopak_list");
        }
        
        if (member_array(fname, m_indexes(hoopak_list)) < 0)
        {
            hoopak_list = restore_map(KGLOG + "hoopak_altered");
            hoopak_list[fname] = "code altered";
            save_map(hoopak_list, KGLOG + "hoopak_altered");
        }
    }
    
    clone = clone_object(HOOPAK_CREATION);
    clone->move(environment(this_object()));
    clone->init_hoopak(polearm[0], this_player());
    
    
    return 1;
}

/* 
 * Function name : reverse
 * Description   : Reverses an altered hoopak
 * Arguments     : string str - the argument given
 * Returns       : 0 on failure, 1 on success
 */
int
reverse(string str)
{
    mixed hoopak;

    notify_fail("Which hoopak do you wish to reverse alter?\n");
    if (!strlen(str))
        return 0;
    
    parse_command(str, ({ }), "[the] / [a] / [an] %s", str);
    
    if (!sizeof(hoopak = FIND_STR_IN_OBJECT(str, this_player())))
        return 0;
    
    if (pointerp(hoopak))
        hoopak = hoopak[0];
    
    if (!objectp(hoopak))
        return 0;
    
    notify_fail("This isnt even a hoopak.\n");
    if (!hoopak->id("hoopak"))
        return 0;
    
    notify_fail("You can only reverse crafted hoopaks.\n");
    if (!hoopak->query_std_hoopak())
        return 0;
    
    write("You take a seat while you dismantle the " + hoopak->query_short() +
    ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + " takes " +
    "a seat while " + this_player()->query_pronoun() + " disassembles the " +
    hoopak->query_short() + ".\n", this_player());
    
    hoopak->alter_reverse(this_player());
    
    return 1;
}

/*
 * Function name : kstory
 * Description   : Tell a story based on a scar.
 * Arguments     : Story to tell
 * Returns       : 0 on failure, 1 on success
 */
int
kstory(string str)
{
    int scars = this_player()->query_scar();
    int i = 0, j = 1, story;
    string where;
    string *scar_list = ({ }), *scar_desc = F_SCAR_DESCS;
 
    if(!scars)
    {
        if(this_player()->query_hair_style() != "styled with a top-knot")
        {
            write("Your eyes glaze over as you chatter merrily " +
                "about how exciting it must be to have scars " +
                "to talk about!\n");
            say(QCTPNAME(this_player()) +
                " eyes glaze over as " + this_player()->query_pronoun() +
                " chatters merrily about how exciting it must be to have " +
                "scars to talk about!\n");
            return 1;
        }
        else
        {
            write("You idly twist the end of your topknot around " +
                "one finger, wishing you had some interesting scars " +
                "to talk about.\n");
            say(QCTNAME(this_player()) +
                " idly twists the end of " +
                this_player()->query_possessive() + " topknot around one " +
                "finger, wishing " + this_player()->query_pronoun() + " had " +
                "some interesting scars to talk about.\n");
            return 1;
        }
    }
 
    else
    {
        while(i < F_MAX_SCAR)
        {
            if(scars & j)
                scar_list += ({scar_desc[i]});
            j *= 2;
            i += 1;
        }
 
        where = scar_list[random(sizeof(scar_list))];
 
        if(strlen(str) > 3)
        {
            write("You point excitedly to the scar on your " + where +
                " and rapidly explain about the time you " + str + "\n");
 
            say(QCTNAME(this_player()) +
                " points excitedly to the scar on " +
                this_player()->query_possessive() + " " + where + " and " +
                "rapidly explains about the time " +
                this_player()->query_pronoun() + " " + str + "\n");
            return 1;
        }
        else
        {
            story = atoi(str) - 1;
            if (!strlen(str) ||
              ((story < 0) || (story >= m_sizeof(story_map))))
            {
                set_alarm(0.1, 0.0, &find_story(this_player(), where));
                return 1;
            }
            else
            {
                write("You point excitedly to the scar on your " + where +
                    " and rapidly explain about the time you " +
                    (strlen(story_map[story][1]) ? story_map[story][1] :
                    story_map[story][0]) + "\n");
                say(QCTNAME(this_player()) +
                    " points excitedly to the scar on " +
                    this_player()->query_possessive() + " " + where + " and " +
                    "rapidly explains about the time " +
                    this_player()->query_pronoun() + " " +
                    story_map[story][0] + "\n");
                return 1;
            }
        }
    }
}

void
reset_behave()
{
    gCanBehave = 1;
}

void
end_behave()
{
    gBehaving = 0;
    set_alarm(RESET_BEHAVE_TIME, 0.0, &reset_behave());
}

int
behave(string str)
{
    if (strlen(str) &&
      str != "myself")
    {
        notify_fail("Behave yourself? Oh what a chore that would be!\n");
        return 0;
    }

    if (gBehaving)
    {
        write("You can't behave much more than this! You'll turn into " +
            "a boring human at this rate.\n");
        return 1;
    }

    if (!gCanBehave)
    {
        write("Ahh! Behaving is such a bother! A kender has to have " +
            "a little fun. You can behave later.\n");
        return 1;
    }

    switch(random(3))
    {
    case 0:
        write("You try to behave yourself, sticking your hands in your " +
            "pockets.\n");
        say(QCTNAME(this_player()) + " tries to behave " + 
            this_player()->query_objective() + "self, sticking " +
            this_player()->query_possessive() + " hands in " +
            this_player()->query_possessive() + " pockets.\n");
        break;
    case 1:
        write("Your eyes cross and you break out into a heavy " +
            "sweat as you concentrate on behaving yourself. This " +
            "is hard!\n");
        say(QCTNAME(this_player()) + " crosses " + 
            this_player()->query_possessive() + " eyes and breaks " +
            "out into a heavy sweat. " + 
            capitalize(this_player()->query_pronoun()) + " seems " +
            "to be trying to behave " + this_player()->query_objective() +
            "self!\n");
        break;
    default:
        write("You squirm and fidget as you attempt to behave " +
            "yourself. What a bother.\n");
        say(QCTNAME(this_player()) + " squirms and fidgets. " +
            capitalize(this_player()->query_pronoun()) + " appears " +
            "to be trying to behave " + this_player()->query_objective() +
            "self.\n");
        break;
    }

    gBehaving = 1;    
    gCanBehave = 0;
    set_alarm(BEHAVE_TIME, 0.0, &end_behave());
    return 1;
}

public void
init()
{
    ::init();
    add_action(&behave(), "behave");
    add_action(&ksong(), "ksing");
    add_action(&kpeek(), "peek");
    add_action(&no_steal(), "steal");
    add_action(&do_wear(), "wear");
    add_action(&do_remove(), "remove");
    add_action(&alter(), "alter");
    add_action(&reverse(), "reverse");
    add_action(&reverse(), "revert");
    add_action(&kstory(), "kstory");
}

