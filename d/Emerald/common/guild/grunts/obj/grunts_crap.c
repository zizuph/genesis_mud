/* A pile of goblin dung - coded by Charon. Used by Grunts guild members. */
/* Recoded with a surprise for the unwary 11/08/95 by Tulix III.          */

inherit "/std/object";
inherit "/cmd/std/command_driver";
#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/grunts/grunts_defs.h"
#include <tasks.h>
#include <cmdparse.h>
#include <filter_funs.h>

/* Global variables */
int i;
object *players_seen_crap;

/* Prototype functions */
public void do_smell();
public int do_throw(string arg);
public void hit_target(object *ob);
public int do_eat(string arg);
public int try_exit();

public void
create_object()
{
    set_name("dung");
    set_pname("dung");
    add_name("crap");
    add_pname("crap");
    add_name("shit");
    add_pname("shit");
    add_name("grunts_crap");
    add_name("pile");
    add_pname("piles");
    set_adj("goblin");
    add_adj("smelly");
    add_adj("steaming");
    set_short("steaming pile of goblin dung");
    set_pshort("steaming piles of goblin dung");
    set_long("This disgusting pile of dung was left here by one of "+
        "those stinking grunts. "+
        "You would probably slip over in it if you were not careful.\n");
    setuid();
    seteuid(getuid(TO));

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 100); /* This means that it will float. #;-) */

    set_alarm( 15.0, 65.0, do_smell);
}

/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       dest: destination environment
 *                  old:  previous environment
 */
public void
enter_env(object dest, object old)
{
    object crap;
    
    players_seen_crap = ({old});              
    
    ::enter_env(dest, old);

    if (old->query_prop(LIVE_I_SLIP_POSSIBLE))
    {
        old->remove_prop(LIVE_I_SLIP_POSSIBLE);
    }
    return;
}

public void
init()
{
    object grunts_slip_timer;
   
    add_action(do_eat, "eat");
    add_action(do_throw, "throw");
    
    /* Players may slip over in crap if they take these exits too quickly */
    add_action(try_exit, "north");
    add_action(try_exit, "east");
    add_action(try_exit, "south");
    add_action(try_exit, "west");
    add_action(try_exit, "northeast");
    add_action(try_exit, "southeast");
    add_action(try_exit, "northwest");
    add_action(try_exit, "southwest");
    
    /* Add slip timing object to player who have not seen the crap before */
    if (TP != ENV(TO) && (member_array(TP, players_seen_crap) == -1))
    {    
         grunts_slip_timer = clone_object(GRUNTS_SLIP_TIMER);
         grunts_slip_timer -> move(TP);
    }
    
    ::init();
}

/*
 * Function name:   do_smell
 * Description:     tell environment what is happening as the dung decays
 */
public void
do_smell()
{
    i++;
    if (i >= 10)
    {
        tell_room(ENV(TO),"The pile of dung dries up, and crumbles away.\n");
        TO -> remove_object();  /* The dung crumbles away after a while */
        return;
    }

    if (i >=8)
    {
        tell_room(ENV(TO),"The pile dung is drying out, but still stinks.\n");
        return;
    }
    
    if (i ==7)
    {
        tell_room(ENV(TO),"Flies start to buzz around the pile of dung.\n");
        return;
    }
    
    if (i >=4)
    {
        tell_room(ENV(TO),"The pile of dung gives off a pungent smell.\n");
        return;
    }
    
    if (i >=2)
    {
        tell_room(ENV(TO),"You catch a whiff of the smelly pile of dung.\n");
        return;
    }

    tell_room(ENV(TO),"A nasty stench wafts up from the pile of dung.\n");
    return;
}

/*
 * Function name:   do_throw
 * Description:     see if player successfully throws dung at target
 * Arguments:       arg: string containing target
 * Returns:         1 if dung is thrown, 0 if not thrown.
 */
public int
do_throw(string arg)
{
    object *oblist;
    
    int dex_dif;
    
    oblist = parse_this(arg,"[throw] [pile] [of] [crap] [shit] [dung] " +
        "[at] [the] %l");

    notify_fail("Throw dung at whom?\n");
    if(!sizeof(oblist))
        return 0;       /* Fail, target not sensible */

    notify_fail("You don't have the dung.\n");
    if(ENV(TO) != TP)
        return 0;       /* Fail, dung not carried */

    notify_fail("You must be more specific.\n");
    if (sizeof(oblist) > 1)
        return 0;       /* Fail, more than one target */

    notify_fail("Somehow the dung resists being thrown! How odd....\n");
    if (oblist[0]->query_guild_name_race() == GUILD_NAME) /* Throw at grunt */
    {
        if (TP->query_guild_name_race() != GUILD_NAME)
            return 0;   /* Non-grunts cannot throw crap at a grunt */

        notify_fail("You simply cannot pluck up the courage to do it...\n");
        if (TP->query_stat(SS_DIS) <= oblist[0]->query_average_stat() / 2)
            return 0;   /* Grunts can, but must have enough discipline */
    }
    
    notify_fail("That would be a very bad move. Remember you're mortal...\n");
    if((oblist[0]->query_wiz_level() >= 1) && (TP->query_wiz_level() == 0))
        return 0;       /* Immortality does has its privileges, you know */

    actor("You throw the pile of dung at",oblist,".");
    tell_room(ENV(TP),QCTNAME(TP)+" throws a large pile "+
        "of goblin dung at "+QTNAME(oblist[0])+".\n",({TP,oblist[0]}));
    
    dex_dif = TP->query_stat(SS_DEX) - oblist[0]->query_stat(SS_DEX);
    dex_dif += random(20);   /* Check dex of thrower & target */
    
    if(dex_dif < 0)     /* Looks like a miss this time */
    {
        write("The dung missed your intended victim.\n");
        oblist[0]->catch_msg("The dung missed you.\n");
        tell_room(ENV(TP),"The dung missed its intended "+
            "victim.\n",({TP,oblist[0]}));
        
        TO->move(ENV(TP));
        tell_room(ENV(TO),"The dung hits the ground with a splat!\n");
        return 1;
    }
    
    set_alarm( 2.0, 0.0, "hit_target", ({oblist[0]}));     /* Try a hit */
    add_prop(OBJ_I_INVIS, 1);      /* After all, it has now been thrown */
    return 1;
}

/*
 * Function name:   hit_target
 * Description:     try to hit the target at whom the dung was thrown
 * Arguments:       *ob:  intended target
 */
public void
hit_target(object *ob)
{
    object grunts_stink, target;

    target = ob[0];
    
    set_this_player(ENV(TO)); /* this_player() not defined in set_alarm */

    remove_prop(OBJ_I_INVIS);            /* Make the dung visible again */

    if(ENV(TP) != ENV(target))          /* Oh bugger! Someone has moved */
    {
        tell_room(ENV(TP),"The dung missed its intended victim.\n");
        TO->move(ENV(TP));
        tell_room(ENV(TO),"The dung hits the ground with a splat!\n");
        return;
    }
    
    target->catch_msg(QCTNAME(TP) + " throws a steaming pile of smelly " +
        "goblin dung at you!\nThe dung hits you right in the face...!\n");
    tell_room(ENV(target),"The dung hits " +
        QTNAME(target) + " right in the face!\n", target);
    
    grunts_stink = present("grunts_stink", target);     /* Check if target */
    if (grunts_stink)     /* already stinks. If so, reset the stink object */
    {
        grunts_stink->reset_smell();
        TO->remove_object();
        return;
    }
    
    grunts_stink = clone_object(GRUNTS_STINK);
    grunts_stink ->move(target);                /* Target needs a bath now */
    TO->remove_object();              /* used to be TO->move(ENV(target)); */

    return;
}

/*
 * Function name:   do_eat
 * Description:     player tries to eat the dung (!?)
 * Arguments:       arg:  string identifying object to be eaten
 * Returns:         1 if command accepted, 0 otherwise.
 */
public int
do_eat(string arg)
{
    int i;
    
    notify_fail("Eat what?\n");
    if(arg != "dung")
        return 0;
    if(TP != ENV(TO))   /* Must be carrying the dung to be able to eat it */
        return 0;

    if(TP->query_race_name() != "goblin")
    {
        if(TP->query_stat(SS_CON) + random(20) > 40)
        {
            write("You're not sure you can stomach it, but you can try...\n");
            all(" eats a large pile of goblin dung.");
            if (TP->query_stat(SS_CON) < 120)
            {
                for( i = 0; i <= 3 ; i++)
                {
                    TP->command("puke");
                }
                write("Goblin dung too much for you?\n");
                all(" doesn't look like " + TP->query_pronoun() +
                    " is too fond of goblin dung.");
                TO->remove_object();
                
                return 1;
            }
            else
            {
                write("The dung sits comfortably in your stomach.\n");
                TP->eat_food(50);
                TO->remove_object();
                return 1;
            }
        }
        write("The goblin dung is too overpowering for you!\n");
        all(" tries to eat a large pile of goblin dung but fails.");
        return 1;
    }
    write("You devour a large pile of goblin dung.\n" +
          "The dung sits comfortably in your stomach.\n");
    all(" devours a large pile of goblin dung.");
    TP->eat_food(50);
    TO->remove_object();
    
    return 1;
}

/*
 * Function name:   try_exit
 * Description:     called when someone tries to exit the room
 * Returns:         0 if allowed to exit, 1 if player slips in dung
 */
public int
try_exit()
{
    object grunts_stink;
    
    if (TP == ENV(TO))
        return 0;             /* Do not slip in crap that you are carrying */
    
    if (!(member_array(TP, players_seen_crap) == -1))
    {
        write("You remember exactly where the dung is, " + 
            "and step carefully over it.\n");
        return 0;                        /* Player exits the room as usual */
    }
    
    if (TP->query_prop(LIVE_I_SLIP_POSSIBLE) && random(3))
    {
        write("You slip over in a steaming pile of smelly goblin dung!\n" +
            "You should watch where you are going more closely.\n");
        tell_room(ENV(TO), QCTNAME(TP) + " slips over in a steaming " +
            "pile of smelly goblin dung!\n", ({TP}));
    
        grunts_stink = present("grunts_stink", TP);
        if (grunts_stink)
        {
            grunts_stink->reset_smell();
            TP->remove_prop(LIVE_I_SLIP_POSSIBLE);    /* Do not slip twice */
            return 1;           /* Player does not exit the room this time */
        }
        
        grunts_stink = clone_object(GRUNTS_STINK);
        grunts_stink ->move(TP);
        
        TP->remove_prop(LIVE_I_SLIP_POSSIBLE);        /* Do not slip twice */
        return 1;               /* Player does not exit the room this time */
    }
    
    if (member_array(TP, players_seen_crap) == -1)
    {
        players_seen_crap += ({TP});
        write("You make sure you remember where the dung is, " + 
            "so you won't slip in it...\n");
        return 0;                        /* Player exits the room as usual */  
    }
    return 0;
}
