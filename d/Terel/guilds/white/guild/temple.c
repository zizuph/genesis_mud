/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * join_room.c
 *
 * Temporary room where one may join the tracker guild.
 */

#include "/d/Terel/include/Terel.h"
inherit WHITE+"guild/keep_room";

#include "/d/Terel/guilds/white/lib/white.h"

object joiner, door;

public void do_ceremony();
public void do_ceremony2();
public void do_ceremony3();
public void do_ceremony4();
public void reject_player();
public void place_member();
public int do_ceremony5();
public int join(string str);
public int renounce();
public int list();

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_short("Temple of Warriors");
    set_long("Temple of the Stronghold.\n");

    door=clone_object(WHITE + "guild/temp_door")->move(TO);
    reset_room();

}

/*
 * Function name: init
 * Description:   lfun called when this object first comes in contact
 *                with a player
 */
public void
init()
{
    ::init();
    add_action("join", "place");
    add_action("renounce", "renounce");
    add_action("list", "list");
}



/*
 * Function name: join
 * Description:   A player may try and join the guild with this
 *                add_action
 * Arguments:     str - the string following the action verb
 * Returns:       1/0
 */
public int
join(string str)
{
    object member;
    joiner = TP;

    if (!str)
    { 
        return 0;
    }

    if(str == "my right hand upon the seal")
    {
        say(QCTNAME(joiner) +" places "+POSSESSIVE(TP)+" right hand on the seal.\n");
        write("You place your right hand upon the seal.\n");


      /*
       * Put in checks here
       */
        member = find_object(WHITE_LOG);
        if(member->query_member(joiner->query_name())) 
        {
            place_member();
            return 1;
        }

        if(!TP->query_prop(WHITE_ACCEPTED))
        {
            reject_player();
            return 1;
        }

        
        do_ceremony();
        return 1;

    }

    return 0;

}


public void
do_ceremony()
{
    write("Blues erupt from the seal searing your right hand.\n");
    say("Blue flames erupt from the seal engulfing "+POSSESSIVE(joiner)+
           " right hand.\n");
    set_alarm(3.0, -1.0, "do_ceremony2");
    return;
}

public void
do_ceremony2()
{
    write("First set of statue messages.\n");
    say("First set of statue messages\n");
    set_alarm(3.0, -1.0, "do_ceremony3");
    return;
}

public void
do_ceremony3()
{
    write("Second set of statue messages.\n");
    say("Second set of statue messages.\n");
    set_alarm(3.0, -1.0, "do_ceremony4");
    return;
}

public void
do_ceremony4()
{
    write("Third set of statue messages.\n");
    say("Third set of statues messages.\n");
    set_alarm(3.0, -1.0, "do_ceremony5");
    return;
}

public int
do_ceremony5()
{
    
    object shadow,member;
    int result;

    write("Final Joining Sequence.\n");
    say("Final Joining Sequence.\n");
        
    shadow = clone_object(GUILD_SHADOW);
    if((result = shadow->shadow_me(joiner, GUILD_TYPE, GUILD_STYLE,
         GUILD_NAME)) != 1)
    {
        "/secure/master"->do_debug("destroy", shadow);
        return 0;
    }
    joiner->init_guild_member();
    write("You are now a member of the Order of the White.\n");
    write("You raise your hand from the seal, the brand of the Order is "+
              "on your palm.\n");
    clone_object(WHITE+"obj/brand")->move(joiner);
    member = find_object(WHITE_LOG);
    member->add_member(joiner->query_name());

    return 1;


}

public void
reject_player()
{
    if(joiner->query_alignment() < -200)
    {
        write("Blue flames from the seal engulf your right hand and "+
                  "spread to the rest of your body!\n");
        say(QCTNAME(joiner)+" is consumed in a blaze of blue flames!\n");
        joiner->heal_hp(-1000);
        return;
    }

    write("The warmth of the seal comforts you and eases your mind.\n");
    say(QCTNAME(joiner) +" stands in silence for a moment.\n");
    return;
}


/*
 * Function name: renounce
 * Description:   A player may use this add_action to leave the guild
 * Arguments:     str - the string following the action verb
 * Returns:       1/0
 */
public int
renounce()
{
    notify_fail("But you are no member of our guild.\n");
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
     return 0;

    if (this_player()->remove_guild_occ())
     write("You left our beloved guild.\n");
    else
     write("There was a strange error, I'm afraid you are stuck " +
           "with us.\n");

    return 1;
}

void place_member()
{
    write("You pray for the spirits of the Protectors to guide you.\n");
    say(QCTNAME(joiner)+" prays before the statues in the temple.\n");
    return;
}

/*
 * Function name: list
 * Description:   Give player the result of list_major_guilds()
 * Returns:       1
 */
public int
list()
{
     string str;

     str = TP->list_mayor_guilds();
     if (str)
       write("You are member of following guilds:\n" + str);
     else
       write("You are not member of any guilds.\n");

     return 1;
}
