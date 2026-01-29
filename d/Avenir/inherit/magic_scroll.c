/*
 * /std/magic_scroll.c
 *
 * This is the standard object used for magical scrolls.
 *
 * It works much the same way as /std/herb.c and is modified
 * from /std/potion.c
 * 
 * Just plain 'read scroll' won't work. This is a safeguard.
 * Default activation verb: 'recite' 
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/herb_support";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define TEMP_STDSCROLL_CHECKED "_temp_stdscroll_checked"
#define MSCROLL_OBJECT ("/d/Avenir/lilith/ms")
#define ASH  "/d/Avenir/common/obj/ashpinch"

int     id_diff,        /* Difficulty level: 0 - 100 */
        id_plvl,        /* Player's identify 'skill' (spellcraft&language) */
        magic_resist,	/* How strong is the resistance against magic */
        scroll_value,   /* How much it is worth in cc */
        identified = 0, /* Identified? True or false */
        recited_it;     /* Scroll magic is activated */        

object *gFail;

string  recite_verb,     /* Verb to activate the scroll */
        scroll_name,    /* Special name of the scroll */
        id_long,        /* Long desc for those who can id it */
        unid_long;      /* Long desc for those who can't it */

/*
 * Function name: do_id_check
 * Description:   This little function is called each time the scroll
 *                is referred to by a player, to check if (s)he
 *                identifies it or not.
 * Arguments:     player - The player
 * Returns:       1 for identification, else 0.
 */
varargs int
do_id_check(object player)
{
    if (!objectp(player))
        player = this_player();
 
    if (!objectp(player) || (environment(this_object()) != player)) 
        return 0;
    
    if (identified)
        return 1;

    id_plvl = ( (player->query_skill(SS_LANGUAGE) + 
                 player->query_skill(SS_SPELLCRAFT)) / 2); 
    if (id_diff <= id_plvl)
        return 1;
    else
        return 0;
}

/*
 * Function name: query_ability_level
 * Description:   The equivalent of the herbalism and alchemy
 *                skills in players.
 * Returns:       The ability level of the player.
 */
int
query_ability_level() { return id_plvl; }

varargs void
set_ability_level(int i) { id_plvl = i; }

/*
 * Function name: query_identified
 * Description:   Did you identify the scroll?
 * Returns:       True if identified
 */
int
query_identified() { return identified; }

varargs void
set_identified(int i = 1) { identified = i; }

/*
 * Function name: long_func
 * Description:   This is an VBFC function for the set_long in the
 *                scroll, which tests if the player examining it can
 *                identify it.
 *                Make sure to set_id_long(str) and set_unid_long(str)
 *                from the create_scroll() function.
 */
nomask string
long_func()
{
    if (do_id_check(this_player()))
        return id_long;
    return unid_long;
}

/*
 * Function name: set_id_long
 * Description:   Set the long description you see if you know
 *                what scroll it is.
 * Arguments:     str - The description
 */
void set_id_long(string str) { id_long = str; }

/*
 * Function name: query_id_long
 * Description:   The long description if you can id the scroll
 * Returns:       The long description
 */
string query_id_long() { return id_long; }

/*
 * Function name: set_unid_long
 * Description:   Set the long description you see if you cannot 
 *                identify the scroll.
 * Arguments:     str - The long description
 */
void set_unid_long(string str) { unid_long = str; }

/*
 * Function name: query_unid_long
 * Description:   Query the long description you get if you cannot identify
 *                the scroll.
 * Returns:       The unidentified long description
 */
string query_unid_long() { return unid_long; }

/*
 * Function name: set_id_diff
 * Description:   Set how hard it is to identify a scroll
 * Arguments:     i - The skill needed to know the scroll
 */
void set_id_diff(int i) { id_diff = i; }

/*
 * Function name: query_id_diff
 * Description:   How hard is it to identify this scroll
 * Returns:  	  The difficulty
 */
int query_id_diff() { return id_diff; }

/*
 * Function name: set_scroll_name
 * Description:   Set the true name of the scroll
 * Arguments:     str - The name
 */
void set_scroll_name(string str) { scroll_name = str; }

/*
 * Function name: query_scroll_name
 * Description:   What is the true name of the scroll
 * Returns:       The name of the scroll
 */
string query_scroll_name() { return scroll_name; }

/*
 * Function name: set_scroll_value
 * Description:   Set the value of the scroll when dealing with
 *                a scroll specialist
 * Arguments:     i - The value
 */
void set_scroll_value(int i) { scroll_value = i; }

/*
 * Function name: query_scroll_value
 * Description:   The value of the scroll when dealing with a specialist
 * Returns:	  The value
 */
int query_scroll_value() {     return scroll_value; }

/*
 * Function name: set_recite_verb
 * Description:   Set what verb the player should type to be able to
 *                recite the scroll. Default is "recite", as activation
 *                should involve verbal commands. 
 * Arguments:     str - The verb
 * NB:            "read" is not possible. Too easy to accidentally
 *                activate the magic of the scroll.
 */
void set_recite_verb(string str)
{
    if (str != "read") 
        recite_verb = str;
}

/*
 * Function name: query_recite_verb
 * Description:   What verb is required to recite this scroll?
 * Returns:       The verb;
 */
string query_recite_verb() { return recite_verb; }

/*
 * Function name:       set_recited_it
 * Description:         This is called if the scroll is recited and the 
 *                      recite_verb != "recite"
 */
void
set_recited_it() { recited_it = 1; }

/*
 * Function name: recited_non_recite_scroll
 * Description:   This function is called instead of do_herb_effects
 *                if you recite a scroll that isn't supposed to be
 *                recited.
 */
void
recited_non_recite_scroll()
{
    write("Nothing happens.\n");
}

/*
 * Function name: set_magic_res
 * Description:   Set how resistant this scroll is to  / how easy it
 *	            is to dispel it.
 * Arguments:     resistance - the resistance
 */
void set_magic_res(int resistance) { magic_resist = resistance; }

/*
 * Function name: query_magic_res
 * Description:   Query the magic resistance
 * Returns:       How resistive the scroll is
 */
int
query_magic_res(string prop)
{ 
    if (prop == MAGIC_I_RES_MAGIC)
        return magic_resist;
    else
        return 0;
}

public void
create_scroll()
{
    ::create_object();
    
    set_name("scroll");
}

public nomask void
create_object()
{
    set_name("scroll");
    set_short("unknown magical scroll");
    set_scroll_name("qwertymnbvc");
    set_id_diff(20);   /* Range between 0 - 100 */       

    set_id_long("This scroll has not been described by the wizard.\n");
    set_unid_long("This is an undescribed, unknown scroll.\n");

    /* Other possible verb ideas: utter, intone, sing */
    set_recite_verb("recite"); 

    set_scroll_value(10);
    add_prop(OBJ_I_VALUE, 0);
    set_magic_res(10);    

    create_scroll();
    set_long("@@long_func");
}

public nomask void
reset_object() { this_object()->reset_scroll(); }

void action_text(object *arr, string vb)
{
    string str;

    write("Unrolling "+ (str = COMPOSITE_DEAD(arr)) +
        ", you " + vb + " words written therein.\n");
    say(QCTNAME(this_player()) + " unrolls "+ str +" and "+
        vb + "s it.\n");
}

string recite_fail()
{
    string str;

    str = "You try to " + recite_verb + " " + COMPOSITE_DEAD(gFail) +
        " but fail.\n";
    say(QCTNAME(this_player()) + " tries to " + recite_verb + " " +
        QCOMPDEAD + " but fails.\n");
    this_player()->remove_prop(TEMP_STDSCROLL_CHECKED);
    return str;
}

int recite_access(object ob)
{ 
    string vb = query_verb();

    if ((environment(ob) == this_player()) &&
        (function_exists("create_object", ob) == MSCROLL_OBJECT) &&
        (vb == ob->query_recite_verb() || vb == "recite"))
        return 1;
    else
        return 0;
}

int recite_one_thing(object ob)
{
    string  vb = query_verb();

    /* Test if you recited a non-recite scroll */
    if ((vb == "recite") && (vb != ob->query_recite_verb()))
    {
        ob->set_recited_it();    
        return 1;
    }
    return 1;
}

/*
 * Function name:	recite_it
 * Description:		recites the objects described as parameter to the
 *                      recite_verb. It uses command parsing to find which
 *                      objects to recite.
 * Arguments:		str: The trailing command after 'recite_verb ...'
 * Returns:		True if command successful
 */
public int
recite_it(string str)
{
    int	il;
    object *a,
           *scrolls;
    string  str2,
            vb;
        
    if (this_player()->query_prop(TEMP_STDSCROLL_CHECKED) ||
        query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

    gFail = ({ });
    vb = query_verb(); 

    notify_fail(capitalize(vb) + " what?\n");
    if (!stringp(str))
        return 0;

   /* It's impossible to recite all scrolls at once. */
    notify_fail("You must specify which scroll to " + vb + ".\n");
    if (str == "all")
        return 0;

    a = CMDPARSE_ONE_ITEM(str, "recite_one_thing", "recite_access");
    if (sizeof(a) > 0)
    {
        action_text(a, vb);
        for (il = 0; il < sizeof(a); il++)
            a[il]->destruct_object();
        return 1;
    }
    else
    {
        set_alarm(1.0, 0.0,
            &(this_player())->remove_prop(TEMP_STDSCROLL_CHECKED));
        this_player()->add_prop(TEMP_STDSCROLL_CHECKED, 1);
        if (sizeof(gFail))
            notify_fail("@@recite_fail:" + file_name(this_object()));
        return 0;
    }
}

/*
 * Function name: destruct_object
 * Description:   Call do_herb_effects or recited_non_recite_scroll
 *                Remove scroll and clone some ash.
 */
void
destruct_object()
{
    object ash;

    /* See /lib/herb_support.h */
    do_herb_effects();

    seteuid(getuid());
    ash = clone_object(ASH);
    ash->add_name(query_scroll_name() +" ash");
    if (ash->move(environment(this_object())))
        ash->move(environment(this_object()), 1);

    add_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT, 1);
    set_alarm(1.0, 0.0, remove_object);
}

/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:      magic - How strong the dispel is
 * Returns:	      0 - No dispelling, 1 - Object dispelled
 */
int dispel_magic(int magic)
{
    object env = environment(this_object());

    if (magic < query_magic_res(MAGIC_I_RES_MAGIC))
        return 0;

    if (living(env))
    {
        tell_room(environment(env), "The " + QSHORT(this_object()) +
            " held by " + QTNAME(env) + " turns to ash!\n", env);
        env->catch_msg("The " + QSHORT(this_object()) + " that you hold " +
            "turns to ash!\n");
        remove_object();
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + QSHORT(this_object()) +
            " turns to ash!\n");
        remove_object();
    }
    return 1;
}

int
read_it(string str)
{
    if (!str)
        return 0;

    notify_fail("But you don't have it!\n");    
    if (environment(this_object()) != this_player())
        return 0;

    write("You attempt to read the "+ short() +
        ", but the letters change shape as you do so, and "+
        "you cannot hold the words in your mind.\nPerhaps "+
        "you should try to "+ query_recite_verb() +" it, "+
        "instead.\n");
}
 
/*
 * Function name: init
 * Description:   adds the relevant actions to the player
 */
void init()
{
    int i;

    ::init();
    
    add_action(recite_it, recite_verb);
    add_action(read_it,   "read");

}

void leave_env(object from, object to)
{
    if (from && living(from))
    {
        remove_name(scroll_name);
        identified = 0;
    }

    ::leave_env(from, to);
}

void enter_env(object dest, object old)
{
    if (dest && living(dest) && do_id_check(dest))
    {
        add_name(scroll_name);
        identified = 1;
    }

    ::enter_env(dest, old);
}
