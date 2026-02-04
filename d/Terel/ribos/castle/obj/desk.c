/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * desk.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDOBJECT;

#include <ss_types.h>

public int steal(string str);

int keygotten = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("desk");
    set_adj("wooden");
    set_long("This ornate wooden desk is large and elegant.  It has " +
             "a drawer, but that is closed and locked using magic.  " +
             "There is no way you can open it.\n");

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    keygotten = 0;
}

 
public void
reset_object()
{
    keygotten = 0;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object.
 */
public void
init()
{
    ::init();
    /*
     * DO NOT add any more actions here, in particular DO NOT add
     * "steal" as an action.  Any questions, mail Sorgum.
     */
    add_action("steal", "remove");
}

/*
 * Function name: steal
 * Description:   Handle the steal action
 * Returns:       1/0
 */
public int
steal(string str)
{
    object key;
    string s1, s2;

    if (!strlen(str)) {
        NF(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (sscanf(str, "%s from %s", s1, s2) != 2) {
        NF(capitalize(query_verb()) + " what?\n");
        if (!strlen(str) || (str != "key")) return 0;
    } else {
        NF(capitalize(query_verb()) + " what from what?\n");
        if (s1 != "key") return 0;
        if (!id(s2) && s2 != "hiding place") return 0;
    }

    if (TP->query_prop(PASS_HANDS) == 0) return 0;

    if (keygotten == 0) {
        FIX_EUID;
        key = clone_object(CASTLE_DIR + "obj/treas_key");
        key->move(TP, 1);
        key->set_key(TREASURE_KEY);
        write("Your hand slips through the " + short() +
              ", easily removing the " + key->short() +
              " from its hiding place.\n");
        keygotten = 1;
    }
    else
        write("Your hand slips through the " + short() + ", but finds " +
              "nothing.\n");
    return 1;
}

/*
 * Function name: do_search
 * Description:   Handle the search of this object, give clue about the key
 * Returns:       clue string
 */
public string
do_search(object searcher, string str)
{
    if (!strlen(str) || !id(str)) return "";
    
    if (searcher->query_skill(SS_AWARENESS) < 25 ||
        searcher->query_prop(PASS_HANDS) == 0) {
        return "";
    } else {
        if (keygotten == 0)
            return "You find a small hiding place in the " + short() +
                   ". It contains a key. Maybe you can remove it?\n";
        else
            return "You find a small hiding place in the " + short() +
                   ". It feels empty though.\n";
    }
}
 
int
query_keygotten()
{
    return keygotten;
}
