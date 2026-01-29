/* A pillory. For Avenir, Mortricia Dec. 1994 */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>

#define RETNF(xx)     {notify_fail(xx + "\n"); return 0;}
#define TO            this_object()
#define TP            this_player()
#define ETO           environment(TO)

#define HIT_PROB      40
#define HIT_LOCS      ({"right in the face",\
                        "right on the nose",\
                        "right in the eye",\
                        "on the head",\
                        "on the hand"})

/* Global vars */
static int    locked=0, closed=0;
static object scapegoat=0;
static object the_key=0;

/* Prototypes */
public void   set_key(object key);
public void   set_prisoner(object prisoner);
public object query_key();
public object query_prisoner();
public void   lock_and_close();

void
init()
{
    ::init();
    add_action("do_open",   "open");
    add_action("do_close",  "close");
    add_action("do_lock",   "lock");
    add_action("do_unlock", "unlock");
    add_action("do_throw",  "throw");
}

void
create_object()
{
    set_name("pillory");
    set_adj("wooden");
    set_long("@@my_long");

    add_prop(OBJ_M_NO_GET, "It is securely fastened to the ground.\n");

    add_item(({"lock", "iron lock"}),
        "The lock seems quite sophisticated and made of iron. " +
        "From the shape of the lock you realise that " +
        "the key needed to open it, must be quite big.\n"
        );
}

do_open(string what)
{
    object pobj;
    
    if (what != "pillory") RETNF("Open what?")

    if (locked) {
        write("The pillory is locked.\n");
        return 1;
    }
    if (!closed) {
        write("The pillory is already opened.\n");
        return 1;
    }
    write("You open the pillory.\n");
    say(QCTNAME(TP) + " opens the pillory.\n");
    closed = 0;
    
    if (query_prisoner() && (pobj = ETO->query_pobj())) {
        pobj->premature_interupt();
    }
    
    return 1;
}

do_close(string what)
{
    if (what != "pillory") RETNF("Close what?");

    if (closed) {
        write("The pillory is already closed.\n");
        return 1;
    }
    write("You close the pillory.\n");
    say(QCTNAME(TP) + " closes the pillory.\n");
    closed = 1;
    return 1;
}

do_unlock(string what)
{
    object *keys;
    string s1;

    if (!what) RETNF("Unlock what?")

    if (what == "pillory") RETNF("Unlock pillory with what?")

    if (sscanf(what, "pillory with %s", s1) != 1) RETNF("Unlock what?")

    keys = FIND_STR_IN_OBJECT(s1, TP);

    if (sizeof(keys) <= 0) RETNF("You don't have that!")

    if (sizeof(keys) > 1) RETNF("Which one?")

    if (!the_key || the_key != keys[0]) {
        write(capitalize(keys[0]->short()) +
              " doesn't fit in the lock.\n");
        return 1;
    }
    if (!locked) {
        write("The pillory is already unlocked.\n");
        return 1;
    }

    write("You unlock the pillory with your "+the_key->short()+".\n");
    say(QCTNAME(TP) + " unlocks the pillory with the " + the_key->short() + ".\n");
    locked = 0;
    return 1;
}

do_lock(string what)
{
    object *keys, who;
    string s1;

    if (!what) RETNF("Lock what?")

    if (what == "pillory") RETNF("Unlock pillory with what?")

    if (sscanf(what, "pillory with %s", s1) != 1) RETNF("Lock what?")

    keys = FIND_STR_IN_OBJECT(s1, TP);
    if (sizeof(keys) <= 0) RETNF("You don't have that!\n")

    if (sizeof(keys) > 1) RETNF("Which one?")

    if (!the_key || the_key != keys[0]) {
        write(capitalize(keys[0]->short()) +
              " doesn't fit in the lock.\n");
        return 1;
    }

    if (locked) {
        write("The pillory is already locked.\n");
        return 1;
    }
    if (!closed) {
        write("The pillory is opened, you have to close it first.\n");
        return 1;
    }
    write("You lock the pillory with your "+the_key->short()+".\n");
    say(QCTNAME(TP) + " locks the pillory with the " + the_key->short() + ".\n");

    who = query_prisoner();
    if (who) {
        tell_room(ETO, QCTNAME(who) + " has now been fastened in the " +
                  "pillory.\n", who);
        who->catch_msg("You are now fastened in the pillory.\n");
    }
    locked = 1;
    return 1;
}

do_throw(string str)
{
    string s1, what, how;
    object *ob, who;
    
    if (!str) RETNF("Throw what at pillory?")
    
    if (sscanf(str, "%s at pillory", s1) != 1) RETNF("Throw what at pillory?")
    
    ob = FIND_STR_IN_OBJECT(s1, TP);
    
    if (!sizeof(ob)) RETNF("You don't have that!")
    
    if (sizeof(ob) > 1) RETNF("Which one?")
    
    what = ob[0]->short();
    
    write("You throw the " + what + " at the pillory.\n");
    say(QCTNAME(TP) + " throws the " + what + " at the pillory.\n");
    
    ob[0]->move(ETO);
    
    who = query_prisoner();
    if (!who) return 1;
    
    if (random(100) < HIT_PROB) {
       how = HIT_LOCS[random(sizeof(HIT_LOCS))];
       TP->catch_msg("The " + what + " hits " + QTNAME(who) + " " +
                     how + ".\n");
       who->catch_msg("The " + what + " hits you " + how + ". That hurt!\n");
       who->command("moan painfully");
       say("The " + what + " hits " + QTNAME(who) + " " + how + ".\n",
           ({TP, who}));
    } else {
       TP->catch_msg("The " + what + " misses " + QTNAME(who) + ".\n");
       who->catch_msg("The " + what + " misses you.\n");
       who->command("sigh relieved");
       say("The " + what + " misses " + QTNAME(who) + ".\n", ({TP, who}));
    }
    
    return 1;
}

string
my_long()
{
    string str;
    object who;

    str = "A structure used to secure an individual for punishment. " +
          "It is composed of two pieces of wood with holes cut to fit " +
          "head and hands. The framework stands upright on a pole";
    if (closed) str += ". It is closed";
    if (locked) str += " and locked";

    who = query_prisoner();
    if (who && TP != who) str += ". " + process_string(QCTNAME(who)) +
                                        " has been fastened into it";
    if (who && TP == who) str += ". You have been fastened into it";
    str += ".\n";
    return str;
}

public void
set_key(object key)
{
    the_key = key;
}

public void
set_prisoner(object prisoner)
{
     scapegoat = prisoner;
}

public object
query_key()
{
    return the_key;
}

public object
query_prisoner()
{
    if (scapegoat && environment(scapegoat) == ETO) return scapegoat;
    return 0;
}

public void
lock_and_close()
{
    closed = 1;
    locked = 1;
}
