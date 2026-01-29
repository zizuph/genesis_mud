/*
 *    /d/Gondor/guilds/morgulmage/soul/nazgul.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    The council code in the soul of the Morgul Mages
 *
 *    Olorin, July 1994
 *
 *    Morbeche, March 2000 -  Wizards cannot be punished or expelled
 *    Minor update, Chmee, 04.09.2003
 *
 *    Toby, 11 November 2006 - Added mopine for the Anzgul to get the
 *                             Dark Lords opinion of an Archmage.
 *                             This in accordance to making it possible
 *                             for the Nine to strip the Archmage of
 *                             its spells. 
 *    Eowul, 30 April 2009 - split from the other various command soul 
 *                           files.
 *
 */

public int regard( string str )
{
 object *oblist;
 string *how, pp;

    if (this_player()->query_nazgul() == 0)
    {
        return 0;
    }
    if (!strlen( str ))
    {
        return 0;
    }
    how = parse_adverb_with_space( str, "thoroughly", 0 );

    notify_fail( "Regard whom?\n" );
    if (!strlen( how[0] ))
    {
        return 0;
    }
    oblist = parse_this( how[0], "[at] [the] %l" );
    oblist -= ({ this_player() });
    if (!sizeof( oblist ))
    {
        return 0;
    }
    if (sizeof( oblist ) > 1)
    {
        pp = "them";
    }
    else
    {
        pp = HIM( oblist[0] );
    }
    actor( "You focus your burning red eyes upon", oblist,
        ", inspecting "+ pp+ how[1]+ "." );
    targetbb( " focuses "+ TP_HIS+ " burning red eyes upon you, inspecting "+
        "you"+ how[1]+ ".", oblist );
    all2actbb( " focuses "+ TP_HIS+" burning red eyes upon", oblist,
        ", inspecting "+ pp+ how[1]+ "." );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int mreveal( string str )
{
 object tp = this_player(), robe;

    if (tp->query_nazgul() == 0)
    {
        notify_fail( "This command is not for you yet!\n" );
        return 0;
    }
    if (strlen( str ))
    {
        notify_fail( "You can not reveal anyone else!\n" );
        return 0;
    }
    if ((tp != (robe = present( MORGUL_S_GUILD_OBJECT, tp ))->query_worn()))
    {
        notify_fail( "You are not wearing your robe!\n" );
        return 0;
    }
    if (!tp->query_hooded())
    {
        notify_fail( "You are not wearing your hood!\n" );
        return 0;
    }
    if ((tp->query_nazgul() > 1) &&
        (present( MORGUL_MORGUL_CROWN, tp )->query_worn() == tp))
    {
        write( "You draw back your hood, revealing the Crown of "+
            "Morgul.\n" );
        allbb( " draws back "+ TP_HIS+ " hood revealing a gleaming crown "+
            "suspended in the nothingness that surrounds "+ TP_HIS+
            " terrible eyes." );
    }
    else
    {
        write( "You slowly draw back your hood, revealing your head and "+
            "eyes.\n" );
        allbb( " slowly draws back his black hood, and all that emerges "+
            "are two gleaming eyes surrounded by nothingness." );
    }

    robe->do_reveal( "hood", 1 );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

private nomask int nazgul_test()
{
    return this_player()->query_nazgul();
}

int nazgul_punish( string str )
{
    int nl, level, mpen, delta, new_level;
    object target;
    string name, how, reason, vb = query_verb();

    if (!(nl = nazgul_test()))
    {
        return 0;
    }

    notify_fail( capitalize( vb )+ " whom?\n" );
    if (!strlen( str ))
    {
        return 0;
    }
    
    if (sscanf( str, "%s %s %s", name, how, reason ) != 3)
    {
        notify_fail( capitalize( vb )+ " whom how for what?\n" );
        return 0;
    }

    notify_fail( "There is no Servant of the Dark Lord with that name "+
        "within this world.\n" );
    if (!(objectp( target = find_player( name ) )))
    {
        return 0;
    }
    if (!IS_MEMBER(target))
    {
        return 0;
    }

    if (target->query_wiz_level())
    {
        notify_fail( "Don't be silly. You didn't think you could do "+
            "that, did you?\n" );
        return 0;
    }

    if (target == this_player())
    {
        notify_fail( "You cannot punish yourself!\n" );
        return 0;
    }

    if (nl <= target->query_nazgul())
    {
        notify_fail( "Your power is not sufficient to punish "+
            capitalize( name )+ "!\n" );
        return 0;
    }

    level = target->query_morgul_level();
    mpen  = target->query_morgul_penalty();

    switch (how)
    {
    case "mildly":
        delta = 1;
        break;
    case "sternly":
        delta = 3;
        break;
    case "severely":
        delta = 7;
        break;
    case "ultimately":
        delta = 100;
        break;
    default:
        write( "You can punish 'mildly', 'sternly', 'severely', or "+
            "'ultimately'.\n" );
        return 1;
    }

    // remove _all_ levels down to 1
    if (level <= 0)
    {
        write( "You cannot punish "+ capitalize( name )+ " any further.\n");
        return 1;
    }

    if (level < delta)
    {
        delta = level;
    }
    new_level = level- delta;
    setuid();
    seteuid( getuid() );
    target->set_morgul_penalty( mpen- delta );

    write_file(MORGUL_WIZARD_NAZGUL_LOG, 
          "NAZGUL: " + capitalize(name) + " punished " + how + " by "
        + this_player()->query_name()+ ": new level = " + new_level
        + ". " + ctime( time() )+ ".\n");
        
    write("By the authority the Dark Lord bestowed upon you, you "
        + "withdraw a part of His power from "+ capitalize( name )+ "!\n");
    target->catch_msg( "You feel weakened when you realize that "+
        QTNAME( this_player() )+ " withdraws a part of the power of the "+
        "Dark Lord from you!\n" );
    if (delta > 1)
    {
        target->add_mana( -(target->query_mana()) );
    }
    tell_room( environment( target ), QCTNAME(target)+ " grows pale and "+
        "stumbles from a sudden fit of weakness.\n", target );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUNISH );
    if ((new_level <= APPRENTICE_LEVEL) && (level > APPRENTICE_LEVEL))
    {
        MORGUL_MASTER->remove_mage_name( name );
        write_file( MORGUL_REGULAR_RECORDS, "DEMOTION: "+ capitalize( name )+
            " was demoted to level "+ new_level+ " by "+ this_player()->
            query_name()+ " and lost the "+ "mage name!\n" );
        write_file( MORGUL_NAZGUL_RECORDS, this_player()->query_name()+
            " punished "+ capitalize( name )+ " "+ how+ " "+ reason+
            ", withdrawing the mage status ("+ ctime( time() )+ ").\n" );
    }
    else
    {
        write_file( MORGUL_NAZGUL_RECORDS, this_player()->query_name()+
            " punished "+ capitalize( name )+ " "+ how+ " "+ reason+
            " ("+ ctime( time() )+ ").\n" );
    }

    (MORGUL_MASTER)->update_mage_rank(target);

    if ((new_level <= TUVALE_LEVEL) && !MORGUL_MASTER->query_is_tuvale(target)) {
        MORGUL_MASTER->set_tuvale(target, 1);

        write_file( MORGUL_NAZGUL_RECORDS, target->query_name()+ " is "
            + " restricted to the rank of Tuvale ("+ ctime( time() )+
            ").\n");
    }

    return 1;
}

int nazgul_reward( string str )
{
    int nl, level, base_level, mpen, pot, delta;
    object target;
    string name, how, reason, vb = query_verb();

    if (!(nl = nazgul_test()))
    {
        return 0;
    }

    notify_fail( capitalize( vb )+ " whom?\n" );
    if (!strlen( str ))
    {
        return 0;
    }

    if (sscanf( str, "%s %s %s", name, how, reason ) != 3)
    {
        notify_fail( capitalize( vb )+ " whom how for what?\n" );
        return 0;
    }

    notify_fail( "There is no Servant of the Dark Lord with that name "+
        "within this world.\n" );
    if (!(objectp( target = find_player( name ) )))
    {
        return 0;
    }
    if (!IS_MEMBER(target))
    {
        return 0;
    }

    notify_fail( "You cannot reward yourself!\n" );
    if (target == this_player())
    {
        return 0;
    }

    notify_fail( "Your power is not sufficient to reward "+
        capitalize( name )+ "!\n" );
    if (nl <= target->query_nazgul())
    {
        return 0;
    }
    mpen  = target->query_morgul_penalty();
    level = target->query_morgul_level();
    base_level = target->query_morgul_level( 1 );
    pot   = base_level- level;

    if(IS_ARCHMAGE(target))
    {
       pot++;
    }

    switch (how)
    {
    case "sparingly":
        delta =   1;
        break;
    case "graciously":
        delta =   3;
        break;
    case "generously":
        delta =   7;
        break;
    case "bountifully":
        delta = 100;
        break;
    default:
        write( "You can reward 'sparingly', 'graciously', 'generously', "+
            "or 'bountifully'.\n" );
        return 1;
    }

    if (pot <= 0)
    {
        write( "You cannot reward "+ capitalize( name )+ " any further.\n");
        return 1;
    }
    if (delta > pot)
    {
        delta = pot;
    }
    setuid();
    seteuid( getuid() );
    target->set_morgul_penalty( mpen+ delta );
    write_file( MORGUL_WIZARD_NAZGUL_LOG, "NAZGUL: "+ target->query_name()+ " rewarded "+
        how+ " by "+ this_player()->query_name()+ ": base level = "+
        base_level+ ", penalty = "+ mpen+ ", new level = "+ (level+ delta)+
        ". "+ ctime( time() )+ ".\n" );
    write_file( MORGUL_NAZGUL_RECORDS, this_player()->query_name()+ " rewarded "+
        target->query_name()+ " "+ how+ " "+ reason+ " ("+ ctime( time() )+
        ").\n" );
    write( "By the authority the Dark Lord bestowed upon you, you "
        + "reluctantly grant additional power to "+ capitalize( name )
        + "!\n" );
    target->catch_msg( "You feel stronger when you realize that "
        + QTNAME( this_player() )+ " has reluctantly granted you additional "
        + "power.\n" );
    tell_room( environment( target ), QCTNAME( target )+ " suddenly looks "+
        "more powerful!\n", target );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_REWARD );
    (MORGUL_MASTER)->update_mage_rank(target);

    if (MORGUL_MASTER->query_is_tuvale(target)) {
        MORGUL_MASTER->set_tuvale(target, 0);

        write_file( MORGUL_NAZGUL_RECORDS, target->query_name()+ " is no "
            + " longer restricted to the rank of Tuvale ("+ ctime( time() )+
            ").\n");
    }

    return 1;
}

/*
 * Function name: nazgul_expel
 * Description  : Function code for the "expel" command for Nazgul.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int nazgul_expel( string str )
{
 int nl;
 object target;

    if (!(nl = nazgul_test()))
    {
        return 0;
    }

    if (!strlen( str ))
    {
        notify_fail( "Expel whom?\n" );
        return 0;
    }

    str = lower_case( str );
    if (!((MORGUL_MASTER)->query_is_mage( str )))
    {
        notify_fail( "There is no Servant of the Dark Lord named "+
            capitalize( str )+ ".\n" );
        return 0;
    }

    if (str == this_player()->query_real_name())
    {
        notify_fail( "You cannot expel yourself!\n" );
        return 0;
    }

    if ((nl < 2) && MORGUL_MASTER->query_is_archmage(str))
    {
        notify_fail( "Only the King has the power to expel "+
            capitalize( str )+ "!\n" );
        return 0;
    }
    
    if (SECURITY->query_wiz_level( str ))
    {
        notify_fail( "Wizards cannot be expelled.\n" );
        return 0;
    }

    setuid();
    seteuid( getuid() );
    write_file( MORGUL_REGULAR_RECORDS, "MORGUL MAGES: "+ capitalize( str )+
        " expelled from the Morgul Mages by "+ this_player()->query_name()+
        ". "+ ctime( time() )+ ".\n" );
    write_file( MORGUL_NAZGUL_RECORDS, capitalize( str )+ " expelled from the "+
        "Morgul Mages by "+ this_player()->query_name()+ ". "+
        ctime( time() )+ ".\n" );
    write( "You remove "+ capitalize( str )+
        " from the ranks of the Society of Morgul Mages.\n" );

    target = find_player( str );
    if (objectp( target ))
    {
        tell_object( target, "The Nine expelled you from His Service! You "+
            "are removed from the ranks of the Society of Morgul Mages!\n");
    }
    else
    {
        write( "As "+ capitalize( str )+ " is not within the realms, the "+
            "unworthy member will not lose the robe until the next time "+
            capitalize( str )+ " dares to enter the realms.\n" );
    }

    (MORGUL_MASTER)->expel_player_from_guild(
        this_player()->query_real_name(), str, ("Expelled by "+
        this_player()->query_name()) );
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EXPEL );
    return 1;
}


public int mopine( string str )
{
    object *oblist;
    string *how, standing, lead;
    int rl;

    if (this_player()->query_nazgul() == 0 && !this_player()->query_wiz_level())
    {
        return 0;
    }

    notify_fail( "Get an opinion of whom?\n" );

    if (!strlen( str ))
    {
        return 0;
    }

    how = parse_adverb_with_space( str, "thoroughly", 0 );

    if (!strlen( how[0] ))
    {
        return 0;
    }

    oblist = parse_this( how[0], "[the] %l" );
    oblist -= ({ this_player() });

    if (!sizeof( oblist ))
    {
        return 0;
    }

    if(!this_player()->query_hooded())
    {
        notify_fail("You are not wearing your hood and can not inspect your " +
              "target surreptisiously and thus descide not to.\n");
        return 0;
    }

    if(!IS_ARCHMAGE(oblist[0]))
    {
        notify_fail( oblist[0]->query_name() + " is not an Archmage!\n");
        return 0;
    }
    
    rl = ARCHMAGE_LEVEL - oblist[0]->query_morgul_level();

    switch (rl)
    {
       case 0:
          standing = "excellent";
          lead = "Thus " +HIS_HER(oblist[0])+ " words and advice can be taken " +
                 "into calculations by the Nine in their work of the Tower.";
          break;
       case 1:
          standing = "good";
          lead = "Thus " +HE_SHE(oblist[0])+ " is quite capable to work with the " +
                 "responsibilities of an Lieutenant.";
          break;
       case 2..4:
          standing = "descent";
          lead = "Thus " +HIS_HER(oblist[0])+ " words and advice about " +
                 "Mages of the Society can still be trusted as any Senior Mage.";
          break;
       case 5..7:
          standing = "poor";
          lead = CAP(HE_SHE(oblist[0]))+ " can not be fully trusted.";
          break;
       case 8..12:
          standing = "very poor";
          lead = "Is this one before you really an Archmage or a mere Warlock?";
          break;
       default:
          standing = "miserable";
          lead = CAP(HE_SHE(oblist[0]))+ " should be as trusted as an Apprentice.";
          break;
    }

    str = "From the depths of your hood you" +how[1]+
          " inspect " + oblist[0]->query_name() + ". " + 
          "This Archmage is in " +standing+ " standing with the Dark Lord. ";

    str += lead + " ";
   
    if(this_player()->query_nazgul() == 2 || this_player()->query_wiz_level())
    {
        str += CAP(HIS_HER(oblist[0]))+ " true rank is ";
 
        if(oblist[0]->query_morgul_level() < 25)
        {
            str += ((oblist[0]->query_gender() == G_FEMALE) ? 
                   MORGUL_COMMON_FEMALE_TITLES[oblist[0]->query_morgul_level()] : 
                   MORGUL_COMMON_MALE_TITLES[oblist[0]->query_morgul_level()]) + ".";
        }
        else
        {
            str += MORGUL_COMMON_MALE_TITLES[ARCHMAGE_LEVEL] + ".";
        }
    }

    write( str + "\n" );
    allbb( " stirs slowly under " +HIS_HER(this_player())+ " hood." );

    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

