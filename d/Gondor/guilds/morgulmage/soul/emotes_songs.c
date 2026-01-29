/*
 *    /d/Gondor/guilds/morgulmage/soul/emotes.c
 *
 *    This file is part of the command soul for the Morgul mages.
 *    Emotes dealing with large amounts of text.
 *
 *    Created by Eowul, Apr 30, 2009, split from the other various
 *    command soul files.
 *
 */

#define BATTLE_SONG ({ \
    "\tThe fields of Rohan we will raze, hoorah, hoorah,\n" \
  + "\ttheir stable houses set ablaze hoorah, hoorah!\n\n" \
  + "\tWe kill of course both man and horse,\n" \
  + "\twe've yet to learn the word remorse\n" \
  + "\tand we kill, kill, kill, kill,\n" \
  + "\twe are the Dark Lord's host.\n", \
\
    "\tThe dwarves will dance and do a skip, hoorah, hoorah,\n" \
  + "\tbefore the balrogs slashing whip, hoorah, hoorah!\n\n" \
  + "\tA merry day, the balrog will flay,\n" \
  + "\tevery beard and limb away\n" \
  + "\tand we kill kill kill kill,\n" \
  + "\twe are the Dark Lord's host.\n", \
\
    "\tLorien fairest forest is, hoorah, hoorah,\n" \
  + "\twe burn it all it is amiss, hoorah, hoorah!\n\n" \
  + "\twe slay the elves, amuse ourselves,\n" \
  + "\tthey'll find no maid among themselves\n" \
  + "\tand we kill, kill, kill kill,\n" \
  + "\twe are the Dark Lord's host.\n", \
\
    "\tCome here my hobbit do not flee, hoorah hoorah,\n" \
  + "\tcome back come back come play with me, hoorah, hoorah!\n\n" \
  + "\tThe hobbit char, the fresh new tar,\n" \
  + "\tthe cooking smell will spread afar\n" \
  + "\tand we kill kill kill kill, \n" \
  + "\twe are the Dark Lord's host.\n", \
\
    "\tThe wizards come to us repel, hoorah, hoorah,\n" \
  + "\twe kill'em, send'em down to hell, hoorah, hoorah!\n\n" \
  + "\tWe won the west, we are the best, \n" \
  + "\twe kill you all with a jolly zest\n" \
  + "\tand we kill, kill, kill, kill, \n" \
  + "\twe are the Dark Lord's host.\n", \
\
    "\tThe King of Gondor soon will die, hoorah, hoorah,\n" \
  + "\twhen his town in cinders lies, hoorah, hoorah!\n\n" \
  + "\tThe west is won, the world is gone,\n" \
  + "\tall the bloody creation undone,\n" \
  + "\tand we kill, kill, kill, kill,\n" \
  + "\twe are the Dark Lord's host!\n", \
})

#define WHIP_SONG \
    "\tWhere there's a whip, there's a way!\n" \
  + "\tWhere there's a whip, there's a way!\n" \
  + "\tWhere there's a whip...\n" \
  + "\tWe don't wanna' go to war today,\n" \
  + "\tBut the Lord of the Lash says \"Nay, nay, NAY!\"\n" \
  + "\tWe're gonna' march all day, all day, all day!\n" \
  + "\tWhere there's a whip there's a way!\n\n" \
  + "\tWhere there's a whip there's a way!\n" \
  + "\tLeft, right, left, right, left,\n" \
  + "\tWhere there's a whip...there's a way!\n"

public int battlesong( string str )
{
 int verse = 0;
 string song;

    if (song = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( song ) ? song :
            "You are gagged and cannot sing.\n" );
        return 1;
    }
    notify_fail( "You do not know any battle song of that name!\n" );
    if (str == "whip" || str == "lash")
    {
        song = WHIP_SONG;
    }
    else if (strlen( str ))
    {
        if (sscanf( str, "%d", verse ) == 1)
        {
            if (verse <= 0)
            {
                return 0;
            }
            else if (verse > sizeof( BATTLE_SONG ))
            {
                notify_fail( "You do not know verse number "+
                    LANG_WNUM( verse )+ ".\n" );
                   return 0;
            }
            song = BATTLE_SONG[verse-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        song = ONE_OF_LIST( BATTLE_SONG );
    }
    all( " sings in a terrible scratching voice a battle song of Mordor:" );
    write( "You sing one verse of the battle song of Mordor:\n" );
    tell_room( environment( this_player() ), "\n"+ song+ "\n");
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
    return 1;
}

public int recite( string str )
{
 string temp;

    if (temp = this_player()->query_prop( LIVE_M_MOUTH_BLOCKED ))
    {
        write( stringp( temp ) ? temp :
            "You are gagged and cannot recite.\n" );
        return 1;
    }

    if (str == "ash nazg")
    {
        all( " recites a powerful spell in the Black Speech:\n\n"+
            "\t     Ash nazg durbatuluk, ash nazg gimbatul,\n"+
            "\t ash nazg thrakatuluk agh burzum-ishi krimpatul.\n" );
        write( "You recite a powerful spell in the Black Speech:\n\n"+
            "\t     Ash nazg durbatuluk, ash nazg gimbatul,\n"+
            "\t ash nazg thrakatuluk agh burzum-ishi krimpatul.\n" );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }
    if (str == "rings")
    {
        all( " recites the verse about the Rings of Power:\n\n" );
        write( "You recite the verse about the Rings of Power:\n\n" );
        tell_room( environment( this_player() ),
            "\tThree Rings for the Elven-kings under the sky,\n"+
            "\t  Seven for the Dwarf-lords in their halls of stone,\n"+
            "\tNine for the Mortals doomed to die,\n"+
            "\t  One for the Dark Lord on his dark throne\n"+
            "\tIn the Land of Mordor where the Shadows lie.\n"+
            "\t  One Ring to rule them all, One Ring to find them,\n"+
            "\t  One Ring to bring them all and in the darkness bind them\n"+
            "\tIn the Land of Mordor where the Shadows lie.\n\n" );
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION );
        return 1;
    }
    notify_fail( "Recite which verse?\n" );
    return 0;
}
