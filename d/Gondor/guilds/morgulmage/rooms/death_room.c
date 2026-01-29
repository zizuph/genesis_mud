/*
 * /d/Gondor/guilds/morgulmage/rooms/death_room.c
 *
 * Join room for the Morgul Mages. Used to function as the guild
 * master object, but that functionality has been moved out.
 *
 * Eowul, May 2009
 *
 * 12-Jan-2019, Arman: Only full mages are occ+lay now.
 */
 
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define  MORGUL_I_DEATH_WARNING   "_morgul_i_death_warning"
#define  MORGUL_S_SPONSOR         "_morgul_s_sponsor"

public void first_death(string str);
public void second_death(string str);
public void third_death(string str);
public void get_sponsor(string name);

/*
 * Function name: create_morgul_tower_room
 * Description:   room creator for tower rooms
 */
private void
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("great hall");
    set_extra_long("The hall is devoid of decorations and furniture "
      + "except for a large black stone slab in the back of the hall. "
      + "The hall continues to the south.");

    add_floor();
    add_no_roof();
    add_walls();

    add_item(({"stone","stone slab","altar","slab"}), 
        "The stone slab is about four feet high, eight feet long, and "
      + "four feet broad. It was hewn from the same rock as the stones "
      + "that make the walls and the floor. On the smooth surface are "
      + "dark brown stains. If you are a servant of the Dark Lord, you "
      + "can beg for a new robe at this altar if you have lost your "
      + "old one. If you should decide to leave the Society, you can "  
      + "come here to betray its Lord Sauron.\n");
    add_item(({"stain","stains","blood","blood stains","brown stains",
        "dark stains"}), 
        "On top of the stone slab are dark brown stains. They look "
      + "like dried blood.\n");
    add_item(({"hall","great hall"}),
        "Except for the altar, the hall is devoid of decorations and "
      + "furniture. The walls are also almost featureless, the seams "
      + "between the stone blocks are hardly visible. The roof is hidden "
      + "in the darkness above. The hall continues further to the south, "
      + "where a doorway is visible.\n");
    add_item(({"door","entrance","doorway","exit"}),
        "The doorway in the southern half of the hall is leading out "
      + "onto the staircase.\n");

    add_prop(ROOM_I_LIGHT,1);
    add_prop( ROOM_I_NO_CLEANUP, 1 );

    add_exit("tower_2n" ,"south");

    /* Allow players to use the "mlist" command even when paralyzed. */
    CMDPARSE_PARALYZE_ALLOW_CMDS( ({ "mlist" }) );
}

public int
do_beg(string str)
{
    int     nl;
    object  robe;

    if (!IS_MEMBER(this_player()))
        return 0;

    if (!strlen(str) ||
        !parse_command(str, ({}), "[for] [a] [new] 'robe'"))
    {
        NFN0("Beg for what?");
    }

    if (present(MORGUL_S_GUILD_OBJECT, TP))
    {
        write("You have a robe! Why should you want to anger the Dark Lord "
          + "by begging for a new one?\n");
        return 1;
    }

    this_player()->add_morgulmage_robe();
    write( "Since you have lost your robe, the Dark Lord listens to your "
      + "begging.\n");
    say( "A large black robe materializes out of the air.\n"
      + QCTNAME(TP) + " grabs it quickly.\n" );

    return 1;
}

public int 
accept_player( object player )
{
    string  race = player->query_race_name();

    /*  Only full mages are occ and lay now - Arman
    if ((player->query_guild_member_lay() != 0) || 
        (player->query_guild_member_occ() != 0)) 
    {
        notify_fail("The Lord of Morgul requires full allegiance. You cannot "
            + "be a member of another Occupational or Layman guild.\n");
        return 0;
    }
    */

    if ((player->query_guild_member_occ() != 0)) 
    {
        notify_fail("The Lord of Morgul requires full allegiance. You cannot "
            + "be a member of another Occupational guild.\n");
        return 0;
    }

    if (member_array(race, MORGUL_AS_ILLEGAL_RACE_ON_JOIN) > -1)
    {
        notify_fail( "The Lord of Morgul does not accept "+
            LANG_ADDART( player->query_race_name() )+ " into his service!\n");
        return 0;
    }
    
    if (player->query_guild_style( "cleric" ))
    {
        notify_fail( "The Lord of Morgul does not tolerate clerics in his "+
            "service!\n");
        return 0;
    }
    if (player->query_alignment() > MORGUL_I_ALIGN_JOIN)
    {
        notify_fail( "The Lord of Morgul accepts only servants devoted to "+
            "darkness!\n" );
        return 0;
    }

    return 1;
}

public int
do_join( string str )
{
    notify_fail( capitalize( query_verb()) + " what?" );
    if (!strlen( str ))
    {
        return 0;
    }
    if (!parse_command( lower_case( str ), ({ }),
        "[the] 'service' [of] [the] [dark] [lord]" ))
    {
        return 0;
    }
    
    if (IS_MEMBER(this_player()))
    {
        notify_fail( "You are already one of the Morgul Mages." );
        return 0;
    }
    
    if (!accept_player( this_player() ))
    {
        return 0;
    }
    
    tell_room( this_object(), "You feel a dark terrible power arriving "
      + "somewhere close to the altar, but you cannot see anything. ");
    say( QCTNAME( this_player() )+ " seems terrified and looks around "
      + "like searching for something.\n" );
    write("A menacing voice whispers in your head:\n"
      + HANGING_INDENT("So you want to enter the Service of Sauron, "
      + "the Dark Lord? Few mortals do so of their own free will, and of "
      + "those few hardly none dare to come here to offer their service, "
      + "nor do they know what to expect! And the Dark Lord is suspicious "
      + "of them, for He detests traitors!", 4, 0)
      + HANGING_INDENT("Therefore, the Dark Lord demands utmost fealty "
      + "and allegiance and He demands your life before you may serve "
      + "Him!", 4, 0)
      + "Three times I will ask you, and three times will you answer!\n\n"
      + "The dark voice asks you:\n"
      + HANGING_INDENT("What gift will you receive before you will be "
      + "allowed to join our ranks?", 4, 0)
      + "Answer me now!\n> ");
    input_to( first_death );
    return 1;
}

public void 
first_death(string str)
{
    string  poss = TP->query_possessive();
    say(QCTNAME(TP) + " seems to be fighting a battle in "+ poss + " mind.\n"
      + CAP(TP->query_pronoun()) + " has a strained look and is mumbling "
      + "under " + poss + " breath.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" + 
          "    GO AWAY, FOOL!\n" +
          "    The only gift the Lord of Gifts has to give you is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    
    write("The dark voice chuckles:\n"
      + HANGING_INDENT("Yes, that is why He once called himself Anna-Tar, "
      + "the Lord of Gifts!", 4, 0)
      + "The menacing voice asks you the second question:\n" 
      + HANGING_INDENT("What will be your fate when the Dark Lord or one of "
      + "His servants will find you unfit for His service, because you "
      + "turned towards the accursed so-called 'good' or became a cleric, or "
      + "because you withstand His Power like the detested dwarves or "
      + "halflings or the accursed elves?", 4, 0)
      + "Answer me now!\n>");
    input_to(second_death);
}

public void 
second_death(string str)
{
    say(QCTNAME(TP) + " is still mumbling and seems to be far away in "
      + "thoughts.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" +
          "    GO AWAY, FOOL!\n" +
          "    The only fate you can expect is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    
    write("The dark voice whispers:\n"
      + "Yes, expect only death, since only death you will meet!\n" 
      + HANGING_INDENT("Know, that the head of the Society, the Lord of the "
      + "Nazgul, once was a mortal worm like you are now, and although an "
      + "undead now, still is not immortal like the creators of the "
      + "world.", 4, 0)
      + "The dark voice asks you the third question:\n"
      + HANGING_INDENT("What will you receive out of the hand of the Lord "
      + "of the Nazgul, with sound reason or without, with warning or "
      + "without, if you should ever dare to disobey or displease him?", 4, 0)
      + "Answer me now!\n> ");
      
    input_to(third_death);
}

public void 
third_death(string str)
{
    say(QCTNAME(TP) + " seems to be lost for this world, dreaming in far away "
      + "spheres.\n");

    str = LOW(str);
    if (str != "death")
    {
        write("The dark voices screams in your head:\n" +
          "    GO AWAY, FOOL!\n" +
          "    The only thing you will receive is ...\n" +
          "     ... DEATH!!!\n");
        return;
    }
    write("The dark voice hisses:\n"
      + "    Yes! Death, Death, DEATH!!!!!\n"
      + HANGING_INDENT("Death, Obedience, complete and utter Allegiance to "
      + "the Dark Lord and His appointed servants! Do not expect power or "
      + "secrets, the Dark Lord takes and gives like He pleases, and it "
      + "pleases Him more to take than to give!", 4, 0)
      + "The threatening voice asks again:\n"
      + "    Now I must know, which servant of the Dark Lord will "
      + "assist you?\n> ");
      
    say(QCTNAME(TP) + " decided to forsake life and to enter the service "
      + "of the Dark Lord.\n" + CAP(TP->query_pronoun()) + " wants to "
      + "join the Society of Morgul Mages!\n");
    input_to(get_sponsor);
}

public void get_sponsor(string name)
{
    object  sponsor, death_flag;

    name = lower_case(name);

    if (!objectp(sponsor = present(name,TO))) 
    {
        write("Where is one that is to show you the path of shadow?\n");
        return 0;
    }

    if (!IS_MEMBER(sponsor))
    {
        write(sponsor->query_name() + " is not one of the servants of Melkor!\n");
        return 0;
    }

    sponsor->add_prop(MORGUL_S_SPONSOR, TP->query_real_name());
    death_flag = clone_object(MORGUL_OBJ_DIR + "death_flag");
    death_flag->set_initiate(TP->query_real_name(), name);
    death_flag->move(TP, 1);

    tell_room(TO, 
        "A dark menacing voice says:\n"
      + "    " + QCTNAME(TP) + " has chosen " + CAP(name) + " to make "
      + TP->query_objective() + " meet Death!\n"
      + "    Now I, Sauron, King of the World and Lord of the Darkness,\n"
      + "    order you, "+CAP(name)+", to convey " + TP->query_name() 
      + " from life to death\n    so that " + TP->query_pronoun() 
      + " may join us in the service of Melkor.\n");
}

public int
do_list(string arg)
{
    string str;

    if ((arg != "guild") && (arg != "guilds"))
    {
        NFN("List what? Your guilds perhaps?");
        return 0;
    }

    str = TP->list_mayor_guilds();
    if (strlen(str))
        write("You are member of following guilds.\n" + str);
    else
        write("You are not member of any guilds.\n");

    return 1;
}

public int
do_leave(string str)
{
    NFN("Betray whom?");
    if (!strlen(str))
        return 0;

    str = LOW(str);
    if ((str != "sauron") && (str != "morgul") && (str != "guild") &&
      (str != "mages") && (str != "morgul mages"))
        return 0;

    if (!IS_MEMBER(TP)) 
    {
        NFN("But you are no member of our guild.");
        return 0;
    }
    
    if (MORGUL_MASTER->remove_player_from_guild(TP, "Betrayed the Society", 1))
        write("You left the Society of Morgul Mages.\n");
    else
        write("There was a strange error, I'm afraid you are stuck with us.\n");

    return 1;
}


void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (!objectp(ob)) return;
    
    if(living(ob) && !ob->query_ghost()) {
        object  flag;

        if (objectp(flag = present("_morgul_death_flag", ob)))
            flag->remove_object();
    }
    
    ob->remove_prop(MORGUL_I_DEATH_WARNING);
}

public int 
do_sacrifice(string str)
{
    int i,j;
    object victim, heart, *livings;

    notify_fail( capitalize(query_verb()) + " whom?");
    if (!strlen(str))
        return 0;

    str = lower_case( str );

    if ((str == "being" || str == "me" || str == "self" ||
        str == "life" || str == "myself") ||
        (str == this_player()->query_real_name()))
    {
        notify_fail( "If you are seeking Death, enter the service of "+
            "the Dark Lord!\n" );
        return 0;
    }
    
    if (!objectp( victim = present(str,TO) ))
    {
        write( "There is no " + str + " here.\n");
        return 1;
    }

    if (!living( victim ))
    {
        write("That is not alive!\n");
        return 1;
    }
    
    if (!present( "_morgul_death_flag", victim ))
    {
        write( victim->query_name() + " is not yet ready to die "
          + "in order to enter the service of Melkor!\n");    
        return 1;
    }
    
    if (this_player()->query_prop( MORGUL_S_SPONSOR ) !=
        victim->query_real_name())
    {
        write("You have not been elected to sacrifice "
            + victim->query_name() + "!\n");
        return 1;
    }
    
    this_player()->remove_prop(MORGUL_S_SPONSOR);
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_SACRIFICE);
    
    write( "With your bare hands, you tear open the ribcage of "
      + victim->query_the_name( this_player() ) + ".\n"
      + "From the still living body, you rip the bloody heart.\n");
    tell_room( this_object(), "With " + this_player()->query_possessive()
      + " bare hands, " + QCTNAME( this_player() )
      + " tears open the ribcage of " + QTNAME( victim ) + ".\n"
      + "From the still living body, " + this_player()->query_pronoun()
      + " rips the bloody heart.\n", ({victim, this_player()}) );
    victim->catch_msg( "With " + this_player()->query_possessive()
      + " bare hands, " + QCTNAME( this_player() )
      + " tears open your ribcage.\nStrangely, you feel no pain.\n"
      + "Distantly, you watch " + this_player()->query_objective()
      + " ripping the heart out of your body.\n" );
      
    heart = clone_object( "/std/leftover" );
    heart->leftover_init( "heart", victim->query_race_name() );
    heart->set_decay_time( 120 );
    heart->set_long( "This is the bloody heart of " +
        LANG_ADDART( victim->query_race_name()) + ".\n" );
    if (heart->move( this_player() ))  
    {
        if (heart->move( this_object() ))
        {
            heart->move(this_object(), 1);
        }
    }
    
    victim->heal_hp( - victim->query_max_hp() - 100 );
    victim->do_die( this_player() );

    livings = FILTER_OTHER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i=0;i<j;i++)
    {
        MORGUL_MASTER->increase_activity( livings[i], ACTIVITY_SACRIFICE*2/3 );
    }
    
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_join, "enter");
    add_action(do_sacrifice, "sacrifice");
    add_action(do_leave, "betray");
    add_action(do_list, "list");
    add_action(do_sacrifice, "kill");
    add_action(do_beg, "beg");
}
