/* a baldric
 *   worn over the right shoulder and chest
 *   it incorporates stuff from the standard pack
 * created by Lilith Oct 1996
 * revised by Lilith March 1997
 */

inherit "/std/receptacle";
inherit "/lib/commands";
inherit "/lib/keep";

#include "../holm.h"
#include "/sys/cmdparse.h"
#include <filter_funs.h>
#include <wa_types.h>

#define HIS  this_player()->query_possessive()
#define PACK_SUBLOC "_pack_subloc" + query_where()

int worn = 0;
int wearable = 1; 
string where = "right shoulder and across the chest"; 
string how = "over";
string sigil;
string query_sigil()       {  return sigil;    }
string query_where()       {  return where;    }
string query_how()         {  return how;      }
void set_sigil(string str) {  sigil = str;     }
int query_worn()           {  return worn;     }
int query_wearable()       {  return wearable; }
int query_standard_pack()  {  return 1;        }

int 
blade_filter(object ob)
{
    if (ob->query_wt() == W_KNIFE)
        return 1;
    if (ob->query_wt() == W_SWORD)
        return 1;
    else
        return 0;
}

int
wp_filter(object o)
{
    if (o->query_standard_pack() &&
        o->query_wearable())  
        return 1;
    else
        return 0;
}

mixed 
check_ins()
{
    if (sizeof(all_inventory(TO)) >= 1)
        return "The "+ short() +" cannot hold another weapon.\n";

    if (query_verb() != "sheathe")
        return "You can only sheathe bladed weapons in the " + short() 
            +".\n";

    return 0;
}

/*
 * Return whether the baldric is worn or not
 */

string
my_long()
{
    string str;
 
    str = "This ornamental baldric is worn "+ how +" your "+ where + 
          ". "+ "It is made of white samite, a heavy webcloth fabric "+
          "interwoven with spun platinum. ";
    if (query_sigil())
        str += "This baldric is marked with a House escutcheon: "+
               query_sigil() +". ";
    str += "There is a clasp at the end of the baldric "+
           "through which a bladed weapon may be "+
           "sheathed and suspended at the perfect height for "+
           "a swift draw in times of need.\n";

    return str;
}

public varargs string 
short(object for_obj)
{
    return real_short(for_obj);
}

public varargs string 
long(object for_obj)
{
    return container::long(for_obj);
}

/************* creation ************/
void
create_receptacle()
{
 
    set_name("baldric");
    add_adj(({"ornamental", "unworn"}));
    add_name(({"sash", "belt"}));
    set_short("ornamental baldric");
    set_long("@@my_long@@");
 
    set_keep(1);

    add_prop(OBJ_I_VALUE, 144 + random(100));
    add_prop(CONT_M_NO_INS, "@@check_ins@@");
    add_prop(OBJ_I_VALUE,  100);             
    add_prop(OBJ_I_WEIGHT, 500);        
    add_prop(OBJ_I_VOLUME, 500);        
    add_prop(OBJ_M_NO_STEAL, "The buckles of the baldric are "+
        "cinched too tightly.");
    add_prop(CONT_I_MAX_WEIGHT, 10000);  
    add_prop(CONT_I_MAX_VOLUME, 10000);  

    add_item(({"clasp", "loop" }), "It is a simple metal loop "+
        "which holds a naked blade in place with the help of "+
        "gravity and a hilt. The handle of the blade is then "+
        "suspended at waist-height for easy access.\n");
}

int 
sheathe_it(string str)
{
    object *obs, ob;

    notify_fail("Sheathe what? Use <sheathe [blade] in baldric>.\n");
    if (!str)
        return 0;

    if (environment(this_object()) != this_player())
    {
        notify_fail("You do not have it!\n");
        return 0;
    }

    notify_fail("Use <sheathe [blade] in baldric>.\n");
    if (!parse_command(str, all_inventory(this_player()), 
        "[the] %s 'in' [the] %o'", str, ob))
        return 0;
    if (ob != this_object())
    {
        return 0;
    }

    obs = filter(FIND_STR_IN_OBJECT(str, this_player()), "blade_filter",
          this_object());
    notify_fail("You can only sheathe bladed weapons in the baldric.\n");

    obs = filter(obs, "blade_filter", this_object());
    if (!sizeof(obs))
        return 0;

    if (sizeof(obs) > 1)
    {
        write("Please be specific. You have more than one "+
            "blade of that type in your inventory.\n");
        return 0;
    }

    ob = obs[0];
    ob->unwield(this_object());
    if (ob->move(TO))
    {
        write("You cannot sheathe anything else on your "+ short() +".\n");
        return 1;
    }
    TP->catch_msg("You sheathe " + LANG_THESHORT(ob) + " in the "+ 
        short() +", where it can be quickly and easily drawn again.\n");
    say(QCTNAME(TP) + " sheathes "+ LANG_ASHORT(ob) +" in the "+
        short() +", where it can be quickly and easily drawn again.\n");
    return 1;
}

int
draw_it(string str)
{
    object *obs, ob;

    notify_fail("Draw what?\n");
    if (!str)
        return 0;

    notify_fail("Use <draw [blade] from baldric>.\n");
    if (!parse_command(str, all_inventory(this_player()), 
        "[the] %s 'from' [the] %o", str, ob))
        return 0;

    if (ob != this_object())
    {
        return 0;
    }


    obs = FIND_STR_IN_OBJECT(str, this_object());
    notify_fail("Your baldric doesn't have a "+ str +" in it.\n");
    if (!sizeof(obs))
        return 0;

    ob = obs[0];
    TP->catch_msg("You swiftly draw the "+ ob->short()+" hanging at "+
        "your side from the "+ short() +".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" swiftly draws the "+ ob->short() +
        " hanging at "+ HIS + " side from the "+ short() +".\n", TP);

    if (ob->move(TP))
        ob->move(TP, 1);
    TP->command("wield "+ ob->query_name());
    return 1;
}

/*
 * Attempt to wear this particular pack.
 * Returns a message, "ok" if worked, or the fail message if it didn't. 
 */
string
wear_me_pack(object tp)
{
    if (environment(this_object()) != tp)
        return "You need to get the " + short() + " first.\n";    
    
    if (worn)
        return "You are already wearing the " + short() + ".\n";
  
    if (member_array(PACK_SUBLOC, tp->query_sublocs()) > -1)
       return "There is no space on your "+ query_where() 
              +" for the " + short() + ".\n";

    /* Successful wear */
    tp->add_subloc(PACK_SUBLOC, this_object());
    tp->catch_msg("You wear the "+ short() +" "+ query_how() 
        +" your "+ query_where() +".\n");
    tell_room(environment(tp), QCTNAME(tp) + " wears the " + 
        short() +" "+ query_how() +" "+ tp->query_possessive() +
        " "+ query_where() +".\n", tp);
    worn = 1;
    /* Do not show in ordinary inventory */
    this_object()->move(tp, PACK_SUBLOC); 
    return "ok";
}


/* 
 * Attempt to remove this particular pack 
 * Returns a message, "ok" if worked, or the fail message if it didn't. 
 */
string
remove_me_pack(object tp)
{
    if (environment(this_object()) != tp)
        return "You do not have the " + short() + ".\n";    
    
    if (!worn)
        return "You are not wearing the " + short() + ".\n";
  
    /* Successful remove */
    tp->remove_subloc(PACK_SUBLOC);
    tp->catch_msg("You remove the " + short() + ".\n");
    tell_room(environment(tp), QCTNAME(tp) + " removes the " +
              short() + ".\n", tp);
    worn = 0;
    /* Display in inventory again */
    this_object()->move(tp);   
    return "ok";
}

/* 
 * An attempt to remove something. See if it is a pack that the player
 * is trying to remove. If it is, try to carry the remove out. 
 * Returns 1 if player attempted to remove a pack, 0 if s/he did not.
 */ 
int
remove_pack(string str)
{
    object tp = this_player();
    object *o;
    string s;
    
    if (!stringp(str) || (str == "all")) {
         notify_fail("Remove what?\n");
         return 0;
    }

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                                  all_inventory(environment(tp)), wp_filter));

    if (!sizeof(o)) {
        notify_fail("Remove what?\n");
        return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't remove more than one thing from " +
                      "your "+ query_where() +".\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        s = o[0]->remove_me_pack(tp);
        if (s == "ok")
        {
            add_adj(({"unworn"}));
            remove_adj(({"worn"}));
            return 1;
        }
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}


/* 
 * An attempt to wear something. See if it is a pack that the player
 * is trying to wear. If it is, try to carry the wear out. 
 * Returns 1 if player attempted to wear a pack, 0 if s/he did not.
 */ 
int
wear_pack(string str)
{
    object tp = this_player();
    object *o;
    string s;
    
    if (!stringp(str) || (str == "all")) {
        notify_fail("Wear what?\n");
        return 0;
    }    

    o = FIND_STR_IN_ARR(str, filter(all_inventory(tp) + 
                                  all_inventory(environment(tp)), wp_filter));

    if (!sizeof(o)) {
         notify_fail("Wear what?\n");
         return 0;
    }

    if (sizeof(o) > 1) {
        tp->catch_msg("You can't wear more than one thing on your "+             
            query_where() +".\n");
        return 1;
    }

    if (sizeof(o) == 1) {
        s = o[0]->wear_me_pack(tp);
        if (s == "ok")
        {
            add_adj(({"worn"}));
            remove_adj(({"unworn"}));
            return 1;
        }
        else {
           tp->catch_msg(s); 
           return 1;
        }
    }
}

/* 
 *  adjust_pack is an emote available to wearable packs.
 *     Lilith, Nov 1996 
 */
int
adjust_pack(string str)
{

    if (!strlen(str))
    {
        notify_fail("Adjust what?\n");
        return 0;
    }
    if (str != "baldric")
        return 0;
          
    write("You adjust the way the "+ short() +" rests "+ 
        query_how() +" your "+ query_where() +".\n");
    allbb(" adjusts the way the "+ short() +" rests "+ 
        query_how() +" "+ this_player()->query_possessive() +
        " "+ query_where() +".");
    return 1;
}

void 
init()
{
    ::init();
    add_action(sheathe_it,"bsheathe");
    add_action(sheathe_it,"sheathe");
    add_action(sheathe_it,"sheath");
    add_action(sheathe_it, "resheathe");
    add_action(draw_it, "draw");
    add_action(draw_it, "bdraw");
    add_action(draw_it, "unsheath");
    add_action(draw_it, "unsheathe");
    add_action(wear_pack, "wear");
    add_action(remove_pack, "remove");
    add_action(adjust_pack, "adjust");        
}


/* Can't open or close it */
varargs int close(object what)
{
  return 2;
}

varargs int open(object what)
{
  return 2;
}

/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory.
 */
void
leave_env(object old, object dest)
{
    if (worn) {
        if (living(old)) {
            if (member_array(PACK_SUBLOC, old->query_sublocs()) > -1)
                old->remove_subloc(PACK_SUBLOC);
            old->catch_msg("You remove the " + short() + ".\n");
            tell_room(environment(old), QCTNAME(old) + " removes " +
                      "the " + short() + ".\n", old);
        }
        worn = 0;
    }
    ::leave_env(old, dest);
}

/* 
 * Display the pack sublocation 
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (subloc == PACK_SUBLOC)
    {
        if (for_obj != on)
            data = capitalize(on->query_pronoun()) + 
                " is wearing " + LANG_ADDART(short()) + " " +
                query_how() + " "+ on->query_possessive() + 
                " " + query_where() + ".\n";
        else
            data = "You are wearing " + LANG_ADDART(short()) + 
                   " "+ query_how() +" your "+ query_where() +".\n";
        return data;
    }
}


/************ recovery **************/
string
query_recover()
{
     return MASTER + ":" + query_keep_recover() + 
     query_container_recover();
}

void
init_recover(string arg)
{
     init_keep_recover(arg);
     init_container_recover(arg);
}
