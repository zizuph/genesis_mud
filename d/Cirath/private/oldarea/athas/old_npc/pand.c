inherit "/d/Roke/common/monster";

#include <stdproperties.h>
#include "/d/Genesis/login/login.h"
#include "/d/Roke/common/defs.h"

#define VISIT_TIME 150
#define DEST "/d/Roke/Athas/room/quests/sorcerer/house/study"
#define PANDORA_QUEST_LETTER "_pandora_quest_letter"
#define PLAYER_KILLED_PANDORA "_player_killed_pandora"

static object here;
static object letter;

void
create_monster()
{
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_name("pandora");
    set_adj("merry young-looking");
        set_title("the Templar of Tyr, Proctor of Athas");
    set_long("Pandora is an female elf in her old ages, she has lived here\n"+
             "for over four centuries, but the ones who meet her, would\n"+
             "swear that she can't be a day over eighty. She seems to be\n"+
             "waiting for something, but you can't think of what.\n");
    set_race_name("elf");
    set_living_name("pandora");
        set_gender(1);
    set_alignment(100);
        set_stats(({ 30, 100, 50, 100, 100, 75}));
        refresh_mobile();
}


do_die(object killer)
{
  if(query_hp()>0)
    return;

  killer->notify_you_killed_me(this_object());

        tell_room(E(TO),"Pandora dies.\nThe corpse dissolves "+
                "magically, and leaves nothing behind.\n");
	killer->add_prop(PLAYER_KILLED_PANDORA, 1);
  remove_object();
}

void enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);
    if(ob->query_prop(PANDORA_QUEST_LETTER)) 
    {
        remove_call_out("magic_visit");
        call_out("magic_visit", 1);  /* Don\'t ever call action stuff
                                        directly from an encounter
                                        function */
        letter = ob;
    }
}

int
magic_visit() 
{
    int failed;

    if(environment(letter) != this_object())
        return 0;
    remove_call_out("magic_return"); /* just in case */

    here = environment(this_object());
    /* maybe check that we actually HAVE an environment ... */

    if(failed = move_living("X", DEST, 1))
        return failed;
                letter->remove_object();

     call_out("magic_return", VISIT_TIME);
    return 0;
}

void
magic_return() {
    move_living("X", here, 1); /* "here" is the old saved location */

    /* Would be nice to do some checks on success around here, too. */
}
