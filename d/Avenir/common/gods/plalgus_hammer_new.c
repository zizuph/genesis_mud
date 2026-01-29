// -*-C++-*-
// file name:    /d/Avenir/common/gods/obj/plalgus_hammer.c
// creator(s):   Lilith Aug 2001
// last update:  
//               Sept 2004: updated comments
//               July 2004: fixed logging typo.
//               June 2004: Union enemies are not automatically
//                 infidels anymore. They are hammered and marked.
//                 Initial hammer effect lowered to 1/20 of hp.
//               May 2004: lowered infidel on mark_enemy to 1 from 2
//                 
// purpose:      To make things more interesting for people
//               who break the Laws of Sybarus. 
// note:         This object does two different things:
//               1-It clones an aura to players who are Infidels and 
//                 Enemies of the Union. 
//               2-It makes murderers infidels, which turns the populace
//                 against the player and makes god-gifts unusable.
// bug(s):
// to-do:  
inherit "/std/room";

#include "/d/Avenir/include/relation.h"

# define MORTAL_LOG "/d/Avenir/log/misc/malefactor"
# define LIST      ("/d/Avenir/union/list")
# define ENEMY(x)  (LIST->query_enemy(x))

#ifndef SHORT_LOG
#define SHORT_LOG(file, entry)   ((file_size(file) > 3500) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, entry +" ("+ ctime(time()) + ")\n")))
#endif

/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string.
 */
string 
get_time()
{
    string str;
    "/d/Avenir/inherit/avenir_time"->start_avtime();
    str = "/d/Avenir/inherit/avenir_time"->get_time_text();
    return str;
}

void load_me() {  } //empty function

void
create_room()
{
    set_short("That which smites");
    set_long("This controls the Hammer of Plalgus, "+
        "That which Smites. Functions in this object "+
        "are used to call the Judgement of Plalgus "+
        "down upon those who have offended the Gods. "+
        "You notice a list upon the wall.\n");
    add_item("list","You can smite people here using "+
        "smite <name>.\n");
    setuid();
    seteuid(getuid());
}

public int
mark_enemy(object enemy)
{
    object ob;

    // If they are political Union enemies but haven't killed 
    // something they shouldn't have, then don't make them infidels
    // just mark them.
    if (ENEMY(enemy) && (!enemy->query_skill(SS_INFIDEL)))
    {
        ob = clone_object(WRATHMARK);
        ob->move(enemy, 1);
        ob->hammer_delay(enemy);
        return 1;
    }

    // If they have killed something or done something blasphemous
    // and this is called by code (not mortals) then make infidel,
    // with all attendant complications.
    if (enemy->query_skill(SS_INFIDEL))
        enemy->set_skill(SS_INFIDEL, IS_INFIDEL(enemy) + 1);    
    else 
        enemy->MAKE_INFIDEL;      

    if (enemy->query_prop(EVILDOER))
        enemy->remove_prop(EVILDOER);

    // Now mark them
    ob = clone_object(WRATHMARK);
    ob->move(enemy, 1);
    ob->hammer_delay(enemy);  
    return 1;
}

public void
log_malefactor(object enemy)
{ 
    string name, desc;
    name = enemy->query_real_name();
    desc = enemy->query_nonmet_name();

    if (living(enemy))
    {
        SHORT_LOG(MORTAL_LOG, capitalize(name) + break_string(
            " the "+ desc + " committed murder in the "+ 
            get_time(),70, 2));
    }

}

public void
test_wrath(object enemy)
{
    if (IS_INFIDEL(enemy) || IS_EVILDOER(enemy))
    {
        enemy->add_prop(EVILDOER, IS_EVILDOER(enemy) + 1);
        mark_enemy(enemy);
        log_malefactor(enemy);
    }
    else
    {
         tell_object(enemy, "You get a feeling that something bad "+
             "will happen if you do that again.\n");
	     enemy->add_prop(EVILDOER, 1);
    }
}
   
#if 0
public int
do_smite(string str)
{
    object target;

    if(!str || !strlen(str))
    {
        notify_fail("Smite whom with the Hammer of Plalgus?\n");
        return 0;
    }

    str = lower_case(str);
    target = find_player(str);

    if (!target)
    {
        notify_fail("That person is not in the realms!\n");
        return 0;
    }
    else
    {
        test_wrath(target);
        write("You test the wrath of Plalgus on < "+ str +" >.\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();

    add_action("do_smite", "smite");
}    
#endif
